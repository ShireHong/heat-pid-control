#include "gs_pumpctrl.h"

pumpctrl_t pumpctrl;
static void _startpump(pumpctrl_t *instance)
{
	instance->pumpio.WritePin(&instance->pumpio,GPIO_PIN_RESET);
}

static void _stoppump(pumpctrl_t *instance)
{
	instance->pumpio.WritePin(&instance->pumpio,GPIO_PIN_SET);
}

static void _openpumpvalve(gpioinfo_t *instance)
{
	instance->WritePin(instance,GPIO_PIN_RESET);
}

static void _closepumpvalve(gpioinfo_t *instance)
{
	instance->WritePin(instance,GPIO_PIN_SET);
}

static GPIO_PinState _readpumpstate(pumpctrl_t *instance)
{
	return instance->pumpio.ReadPin(&instance->pumpio);
}

static GPIO_PinState _readvalvestate(gpioinfo_t *instance)
{
	return instance->ReadPin(instance);
}


void InitPumpCtrl(pumpctrl_t *instance)
{
	InitGpioinfo(&instance->pumpio,PUMP_GPIO_Port,PUMP_Pin);
	InitGpioinfo(&instance->pumpvalve1,VALVE_I1_GPIO_Port,VALVE_I1_Pin);
	InitGpioinfo(&instance->pumpvalve2,VALVE_I2_GPIO_Port,VALVE_I2_Pin);
	instance->StartPump=_startpump;
	instance->StopPump=_stoppump;
	instance->ClosePumpValve=_closepumpvalve;
	instance->OpenPumpValve=_openpumpvalve;
	instance->ReadPumpState=_readpumpstate;
	instance->ReadValveState=_readvalvestate;	
}
