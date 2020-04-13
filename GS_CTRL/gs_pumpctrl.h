#ifndef  __GS_PUMPCTRL_H_ 
#define  __GS_PUMPCTRL_H_ 

#include "stm32f1xx_hal.h"
#include "gs_gpio.h"
#include "gpio.h"

typedef struct _pumpctrl pumpctrl_t;

struct _pumpctrl{
	uint32_t flow;
	uint32_t flow_ex;
	uint8_t  injectform;
	gpioinfo_t pumpvalve1;
	gpioinfo_t pumpvalve2;
 	gpioinfo_t pumpio;
	void (*StartPump)(pumpctrl_t *instance);
	void (*StopPump)(pumpctrl_t *instance);
	GPIO_PinState (*ReadPumpState)(pumpctrl_t *instance);
	void (*OpenPumpValve)(gpioinfo_t *instance);
	void (*ClosePumpValve)(gpioinfo_t *instance);
	GPIO_PinState (*ReadValveState)(gpioinfo_t *instance);
};
extern pumpctrl_t pumpctrl;
void InitPumpCtrl(pumpctrl_t *instance);
#endif //gs_pumpctrl.h
