#include "gs_heatctrl.h"


heatctrl_t heatdrv1;
heatctrl_t heatdrv2;

static void _startheat(heatctrl_t* instance)
{	
	HAL_TIM_PWM_Start(instance->htim,instance->channel);	
}

static void _stopheat(heatctrl_t* instance)
{ 
	HAL_TIM_PWM_Stop(instance->htim,instance->channel);
}

static void _setdutycycle (heatctrl_t* instance,uint32_t pulse)
{
	instance->timconfig->Pulse = pulse;
	HAL_TIM_PWM_ConfigChannel(instance->htim,instance->timconfig,instance->channel);
	
	HAL_TIM_PWM_Start(instance->htim,instance->channel);	
}


void InitHeatCtrl(heatctrl_t* instance,TIM_HandleTypeDef *s_tim,TIM_OC_InitTypeDef *config,uint32_t chl)
{
	instance->htim=s_tim;
	instance->timconfig=config;
	instance->channel=chl;
	instance->StartHeat=_startheat;
	instance->StopHeat=_stopheat;
	instance->SetDutycycle=_setdutycycle;
}
