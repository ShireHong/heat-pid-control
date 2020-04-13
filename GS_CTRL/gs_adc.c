#include "gs_adc.h"


#define SIZE 100
uint32_t advalue[SIZE];
adctrl_t groove1temp;
adctrl_t groove2temp;

static float AdvalueFilter(adctrl_t *instance,uint32_t *pdata,uint32_t length)
{
	uint16_t cnt;
	uint32_t sum1=0,sum2=0;
	HAL_ADC_Start_DMA(instance->hadc,pdata,length);
	for(cnt=0;cnt<length;)
	{
		sum1+=pdata[cnt++];
		sum2+=pdata[cnt++];
	}
	switch(instance->channel)
	{
		case ADC_CHANNEL_10:
			 return (float)sum1/(length>>1);
		case ADC_CHANNEL_12:
			 return (float)sum2/(length>>1);
		default:
			return 1;
	}
}

static float Advalue2temp(float advalue)   // temporary
{
	return (((advalue/4096)*3300*12/311)-(190*12/311)); 
}

static void _updateadvalue(adctrl_t *instance)
{
	float tmp = AdvalueFilter(instance,advalue,SIZE);	
	instance->currenttemp=Advalue2temp(tmp)+7;//OFFSET 7
}
void InitAdCtrl(adctrl_t *instance,ADC_HandleTypeDef *adc,uint32_t adchannel)
{
	instance->hadc=adc;
	instance->channel=adchannel;
	instance->UpdateValue=_updateadvalue;
}

