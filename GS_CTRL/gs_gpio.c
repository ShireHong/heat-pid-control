#include "gs_gpio.h"
/*
*********************************************************************************************************
*	�� �� ��: _WritePin
*	����˵��: IOд
*	��    �Σ�info����װ�ṹ��
*           pin_state��IO״̬
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void  _writepin(gpioinfo_t *info,GPIO_PinState pin_state)
{
	info->Pin_State=pin_state;
	HAL_GPIO_WritePin(info->Gpio_Port,info->Gpio_Pin,info->Pin_State);
}
/*
*********************************************************************************************************
*	�� �� ��: _readpin
*	����˵��: IOд
*	��    �Σ�info����װ�ṹ��
*	�� �� ֵ: IO״̬
*********************************************************************************************************
*/
static GPIO_PinState _readpin(gpioinfo_t *info)
{
	return  HAL_GPIO_ReadPin(info->Gpio_Port,info->Gpio_Pin);
}
/*
*********************************************************************************************************
*	�� �� ��: InitGpioinfo
*	����˵��: IO��ʼ��
*	��    �Σ�info����װ�ṹ��
*           gpio_port��IO��
*           gpio_pin��IO��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void InitGpioinfo(gpioinfo_t *info,GPIO_TypeDef * gpio_port,uint16_t gpio_pin)
{
	info->Gpio_Port=gpio_port;
	info->Gpio_Pin=gpio_pin;
	info->WritePin=_writepin;
	info->ReadPin=_readpin;
}
/*****************************�Ϻ��������＼�����޹�˾ (END OF FILE) *********************************/
