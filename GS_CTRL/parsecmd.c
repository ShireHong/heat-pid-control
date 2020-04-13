#include "parsecmd.h"
#include "mainctrl.h"
#include "string.h"
#include "usart.h"
#include "stdlib.h"
#include "cmsis_os.h"
#include "math.h"

extern osThreadId heatpidctrlTaskHandle;

void ParseCommand(const uint8_t *receiveCmd)
{
	char buf[100] = {0};
	cJSON *root = cJSON_Parse((const char*)receiveCmd);
	if(!root)
		return ;
	cJSON *SendObj = cJSON_CreateObject(); 
	/*
	----------------------------------------temperature----------------------------------
  */	
	if(cJSON_HasObjectItem(root,"GROOVE_TEMP1"))
	{
		float tmp=groove1temp.currenttemp;
		cJSON_AddNumberToObject(SendObj,"GROOVE_TEMP1",tmp);
	}
	if(cJSON_HasObjectItem(root,"GROOVE_TEMP2"))
	{
		float tmp=groove2temp.currenttemp;
		cJSON_AddNumberToObject(SendObj,"GROOVE_TEMP2",tmp);
	}
	/*
	----------------------------------------pump----------------------------------
  */	
	if(cJSON_HasObjectItem(root,"PUMP_START"))
	{
		cJSON *RecObj = cJSON_GetObjectItem(root,"PUMP_START");
		uint8_t tmp = RecObj->valueint;
		WaterInjectionSect(&pumpctrl,tmp);		
		cJSON_AddStringToObject(SendObj,"PUMP_START","ok");
	}
	if(cJSON_HasObjectItem(root,"PUMP_FLOW1"))
	{
		cJSON *RecObj = cJSON_GetObjectItem(root,"PUMP_FLOW1");
		pumpctrl.flow = RecObj->valueint;
		cJSON_AddStringToObject(SendObj,"PUMP_FLOW1","ok");
	}
	if(cJSON_HasObjectItem(root,"PUMP_FLOW2"))
	{
		cJSON *RecObj = cJSON_GetObjectItem(root,"PUMP_FLOW2");
		pumpctrl.flow_ex = RecObj->valueint;
		cJSON_AddStringToObject(SendObj,"PUMP_FLOW2","ok");
	}
	/*
	-----------------------------------moto------------------------------------------
	*/

	if(cJSON_HasObjectItem(root,"MOTO_PERIOD"))
	{
		cJSON *RecObj = cJSON_GetObjectItem(root,"MOTO_PERIOD");
		cJSON *array = cJSON_GetArrayItem(RecObj,0);		
		uint16_t tmp1 = array->valueint;
		array = cJSON_GetArrayItem(RecObj,1);		
		uint16_t tmp2 = array->valueint;
		stepdrv.vecmax = tmp2;
		stepdrv.decvecthreshold = log(tmp1/tmp2)/log(RATE);
		stepdrv.SetDutycycle(&stepdrv,tmp1);
		cJSON_AddNumberToObject(SendObj,"MOTO_PERIOD",stepdrv.htim->Init.Period);		
	}
	if(cJSON_HasObjectItem(root,"MOTO_STEPS"))
	{
		cJSON *RecObj = cJSON_GetObjectItem(root,"MOTO_STEPS");
		uint16_t tmp = RecObj->valueint;
		stepdrv.steps=tmp;
		stepdrv.halfsteps = tmp/2;
		if(tmp>2*stepdrv.decvecthreshold)
			stepdrv.vecctrlmode = 0;
		else
			stepdrv.vecctrlmode = 1;
		cJSON_AddNumberToObject(SendObj,"MOTO_STEPS",stepdrv.steps);
	}
	if(cJSON_HasObjectItem(root,"MOTO_INIT"))
	{
	  StepperInit(&stepdrv);
		cJSON_AddStringToObject(SendObj,"MOTO_INIT","ok");
	}
	if(cJSON_HasObjectItem(root,"MOTO_START"))
	{
		cJSON *RecObj = cJSON_GetObjectItem(root,"MOTO_START");
		StepperStart(&stepdrv,RecObj->valueint);
		while(stepdrv.CheckMovingState(&stepdrv)){
		}
		
		cJSON_AddStringToObject(SendObj,"MOTO_START","ok");
	}
	if(cJSON_HasObjectItem(root,"MOTO_STOP"))
	{
		StepperStop(&stepdrv);
		cJSON_AddStringToObject(SendObj,"MOTO_STOP","ok");
	}
	/*
	---------------------------------heat----------------------------------------
	*/
	if(cJSON_HasObjectItem(root,"HEAT_PULSE"))
	{
		cJSON *RecObj = cJSON_GetObjectItem(root,"HEAT_PULSE");
		heatdrv2.SetDutycycle(&heatdrv2,RecObj->valueint);
		cJSON_AddStringToObject(SendObj,"HEAT_PULSE","ok");
	}
	if(cJSON_HasObjectItem(root,"HEAT_START"))
	{
//		cJSON *RecObj = cJSON_GetObjectItem(root,"HEAT_START");
		//heatdrv1.StartHeat(&heatdrv1);
		osThreadResume(heatpidctrlTaskHandle);
		cJSON_AddStringToObject(SendObj,"HEAT_START","ok");
	}
	if(cJSON_HasObjectItem(root,"HEAT_STOP"))
	{
//		cJSON *RecObj = cJSON_GetObjectItem(root,"HEAT_START");		
		heatdrv1.StopHeat(&heatdrv1);
    heatdrv2.StopHeat(&heatdrv2);  		
		osThreadSuspend(heatpidctrlTaskHandle); 
		cJSON_AddStringToObject(SendObj,"HEAT_STOP","ok");
	}
	/*
	--------------------------------------cut line----------------------------------------
	*/
	char *strtmp = cJSON_PrintUnformatted(SendObj);
	sprintf(buf,"%d,%d,%s\r\n",stepdrv.decvecthreshold,stepdrv.vecctrlmode,strtmp);
	UartSend(&huart1,(uint8_t*)buf,strlen(buf)+1,1000);
	if(strtmp)
	{		
		free(strtmp);
		strtmp = NULL;
	}
	if(SendObj)	cJSON_Delete(SendObj);	
	if(root)		cJSON_Delete(root);	
}
