/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "gs_pumpctrl.h"
#include "delay.h"
#include "usart.h"
#include "parsecmd.h"
#include "string.h"
#include "mainctrl.h"



static uint8_t Rxbuf[100] = {0};
static uint8_t Rxbyte=0;

osThreadId serialTaskHandle;
osThreadId startTaskHandle;
osThreadId updateStateTaskHandle;
osThreadId heatpidctrlTaskHandle;

void StartTask(void const * argument);
void SerialTask(void const * argument);
void UpdateStateTask(void const * argument);
void HeatPidCtrlTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */



void MX_FREERTOS_Init(void) {
	
	InitallConfig();	

  osThreadDef(startTask, StartTask, osPriorityNormal, 0, 128);
  startTaskHandle = osThreadCreate(osThread(startTask), NULL);   
	
  osThreadDef(serialTask, SerialTask, osPriorityAboveNormal, 0,256);
  serialTaskHandle = osThreadCreate(osThread(serialTask), NULL);
	osThreadSuspend(serialTaskHandle);
	
	osThreadDef(updateStateTask,UpdateStateTask,osPriorityNormal, 0, 256);
	updateStateTaskHandle = osThreadCreate(osThread(updateStateTask),NULL);
	osThreadSuspend(updateStateTaskHandle);
	
	osThreadDef(heatpidctrlTask,HeatPidCtrlTask,osPriorityNormal, 0, 128);
	heatpidctrlTaskHandle = osThreadCreate(osThread(heatpidctrlTask),NULL);
	osThreadSuspend(heatpidctrlTaskHandle);
	
}

/* StartDefaultTask function */
void StartTask(void const * argument)
{  
  for(;;)
  {
		osThreadResume(updateStateTaskHandle);
		osDelay(100);
		osThreadResume(serialTaskHandle);
		osDelay(10);		
		osThreadTerminate(startTaskHandle);			
    osDelay(1);
  }
		
}

void UpdateStateTask(void const * argument)
{
	 for(;;)
  {
		groove1temp.UpdateValue(&groove1temp);		
		groove2temp.UpdateValue(&groove2temp);		
		osDelay(100);
  }
}

void HeatPidCtrlTask(void const * argument)
{	
	//printf("ready to heat!\r\n");
	//uint32_t aa= xTaskGetTickCount();
	for(;;)
	{
		HeatPidCtrl();
		osDelay(200);
		//osDelayUntil(&aa,1000);
	}
}
/*********************************************************************************************************
*	函 数 名: SerialCheckTask
*	功能说明: 串口通讯模块
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/

void SerialTask(void const * argument)
{	
	uint32_t cnt = 0;
	for(;;)
  {			
		uint32_t timeout = 0;
		while(timeout<200)
		{
			timeout++;
			UartRecieve(&huart1,&Rxbyte,1,100);
			Rxbuf[cnt] = Rxbyte;
			if(Rxbuf[cnt]==0x0a)
			{
				if(Rxbuf[cnt-1]==0x0d)
				{					
					cnt = 0;
					break;
				}
			}
			else if(Rxbuf[cnt]!=0)
			{
				cnt++;				
				if(cnt>99) break;
			}
		}
		ParseCommand(Rxbuf);
		memset(Rxbuf,0,100);
 		osDelay(50);
  }
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
