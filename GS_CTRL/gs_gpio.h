#ifndef    __GS_GPIO_H_
#define    __GS_GPIO_H_

#include  "stm32f1xx_hal.h"
#include   "gpio.h"

typedef struct _gpioinfo  gpioinfo_t;
struct _gpioinfo{
	 GPIO_TypeDef   *Gpio_Port;
	 uint16_t        Gpio_Pin;
   GPIO_PinState   Pin_State;	
	 void  (*WritePin)(gpioinfo_t *info,GPIO_PinState pin_state);
	 GPIO_PinState (*ReadPin)(gpioinfo_t *info);
};

void InitGpioinfo(gpioinfo_t *info,GPIO_TypeDef * gpio_port,uint16_t gpio_pin);

#endif   //gs_gpio.h
/*****************************上海贝晶生物技术有限公司 (END OF FILE) *********************************/
