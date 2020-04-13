#ifndef  __MAINCTRL_H
#define  __MAINCTRL_H


#include "gs_gpio.h"
#include "gs_pumpctrl.h"
#include "gs_adc.h"
#include "gs_motoctrl.h"
#include "gs_heatctrl.h"
#include "gs_pidctrl.h"

#define  RATE      1.02
#define READ_INT0_STATE  HAL_GPIO_ReadPin(INT0_GPIO_Port,INT0_Pin)

void InitallConfig(void);
void WaterInjectionSect(pumpctrl_t *pump,uint8_t stat);
void StepperStart(motoctrl_t *moto,MOTODIR stat);
void StepperStop(motoctrl_t *moto);
void StepperInit(motoctrl_t *moto);
void HeatPidCtrl(void);

void CUSTOM_PWM_IRQHandler(motoctrl_t *moto);
#endif //
