#ifndef  __GS_ADC_H
#define  __GS_ADC_H

#include  "stm32f1xx_hal.h"
#include  "adc.h"

typedef struct _adctrl adctrl_t;
struct _adctrl{
	  volatile float currenttemp;
		ADC_HandleTypeDef *hadc;
		uint32_t channel;
		void (*UpdateValue)(adctrl_t *adchandle);			
	
};

extern adctrl_t groove1temp;
extern adctrl_t groove2temp;
void InitAdCtrl(adctrl_t *instance,ADC_HandleTypeDef *hadc,uint32_t adchannel);


#endif //
