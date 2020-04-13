#include "gs_motoctrl.h"


motoctrl_t stepdrv;

static void _startmoto(motoctrl_t* moto)
{ 
	HAL_TIM_PWM_Start_IT(moto->htim, moto->channel);
}

static void _stopmoto(motoctrl_t* moto)
{
	HAL_TIM_PWM_Stop_IT(moto->htim, moto->channel);
}

static void _setdutycycle (motoctrl_t* moto, uint16_t period)
{
	stepdrv.htim->Init.Period = period-1;
	HAL_TIM_PWM_Init(stepdrv.htim);
	moto->timconfig->Pulse = period>>1;
	HAL_TIM_PWM_ConfigChannel(moto->htim, moto->timconfig, moto->channel);
}

static uint16_t _checkmovingstate(motoctrl_t* moto)
{
	return moto->movstate;
}
void InitMotoCtrl(motoctrl_t* moto, TIM_HandleTypeDef *s_tim, TIM_OC_InitTypeDef *config, uint32_t chl)
{
	moto->movstate=0;
	moto->htim = s_tim;
	moto->timconfig = config;
	moto->channel = chl;
	moto->StartMoto = _startmoto;
	moto->StopMoto = _stopmoto;
	moto->SetDutycycle = _setdutycycle;
	moto->CheckMovingState = _checkmovingstate;
}
