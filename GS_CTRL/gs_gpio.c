#include "gs_gpio.h"
/*
*********************************************************************************************************
*	函 数 名: _WritePin
*	功能说明: IO写
*	形    参：info：封装结构体
*           pin_state：IO状态
*	返 回 值: 无
*********************************************************************************************************
*/
static void  _writepin(gpioinfo_t *info,GPIO_PinState pin_state)
{
	info->Pin_State=pin_state;
	HAL_GPIO_WritePin(info->Gpio_Port,info->Gpio_Pin,info->Pin_State);
}
/*
*********************************************************************************************************
*	函 数 名: _readpin
*	功能说明: IO写
*	形    参：info：封装结构体
*	返 回 值: IO状态
*********************************************************************************************************
*/
static GPIO_PinState _readpin(gpioinfo_t *info)
{
	return  HAL_GPIO_ReadPin(info->Gpio_Port,info->Gpio_Pin);
}
/*
*********************************************************************************************************
*	函 数 名: InitGpioinfo
*	功能说明: IO初始化
*	形    参：info：封装结构体
*           gpio_port：IO口
*           gpio_pin：IO脚
*	返 回 值: 无
*********************************************************************************************************
*/
void InitGpioinfo(gpioinfo_t *info,GPIO_TypeDef * gpio_port,uint16_t gpio_pin)
{
	info->Gpio_Port=gpio_port;
	info->Gpio_Pin=gpio_pin;
	info->WritePin=_writepin;
	info->ReadPin=_readpin;
}
/*****************************上海贝晶生物技术有限公司 (END OF FILE) *********************************/
