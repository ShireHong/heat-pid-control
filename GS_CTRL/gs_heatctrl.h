#ifndef  __HEATCTRL_H
#define  __HEATCTRL_H

#include "stm32f1xx_hal.h"
#include "tim.h"

#define  FULL_POWER 30000

typedef  struct _heatctrl heatctrl_t;
struct  _heatctrl{
      uint16_t   pulsenum;
	    TIM_HandleTypeDef *htim;
	    uint32_t   channel;
	    TIM_OC_InitTypeDef *timconfig;
	    void (*StartHeat)(heatctrl_t* instance);
	    void (*StopHeat)(heatctrl_t* instance);
	    void (*SetDutycycle)(heatctrl_t* instance,uint32_t pulse);
};

extern heatctrl_t heatdrv1;
extern heatctrl_t heatdrv2;

void InitHeatCtrl(heatctrl_t* instance,TIM_HandleTypeDef *htim,TIM_OC_InitTypeDef *config,uint32_t channel);


#endif
