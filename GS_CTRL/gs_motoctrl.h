#ifndef  __GS_MOTOCTRL_H
#define  __GS_MOTOCTRL_H

#include "stm32f1xx_hal.h"
#include "tim.h"

#define TQ_ON()       HAL_GPIO_WritePin(M_TQ_GPIO_Port,M_TQ_Pin,GPIO_PIN_SET)
#define TQ_OFF()      HAL_GPIO_WritePin(M_TQ_GPIO_Port,M_TQ_Pin,GPIO_PIN_RESET)
#define DIR_RIGHT()   HAL_GPIO_WritePin(M_CW_GPIO_Port,M_CW_Pin,GPIO_PIN_SET)
#define DIR_LEFT()    HAL_GPIO_WritePin(M_CW_GPIO_Port,M_CW_Pin,GPIO_PIN_RESET)

#define DIR_RIGHT_T()   HAL_GPIO_WritePin(SEN4_GPIO_Port,SEN4_Pin,GPIO_PIN_SET)
#define DIR_LEFT_T()    HAL_GPIO_WritePin(SEN4_GPIO_Port,SEN4_Pin,GPIO_PIN_RESET)


typedef enum{
	      R=0,
	      L	
}MOTODIR;


typedef  struct _motoctrl motoctrl_t;
struct  _motoctrl{
			uint8_t    dir;
	    uint8_t    movstate;
	    uint8_t    extistate;
      uint16_t   steps;
	    uint8_t    vecctrlmode;
	    uint16_t   decvecthreshold;
	    uint16_t   vecmax;
	    uint16_t   halfsteps;
	    TIM_HandleTypeDef *htim;
	    uint32_t   channel;
	    TIM_OC_InitTypeDef *timconfig;	
	    void (*StartMoto)(motoctrl_t* moto);
	    void (*StopMoto)(motoctrl_t* moto);
	    void (*SetDutycycle)(motoctrl_t* moto,uint16_t period);
	    uint16_t  (*CheckMovingState)(motoctrl_t* moto);
};

extern motoctrl_t stepdrv;

void InitMotoCtrl(motoctrl_t* moto,TIM_HandleTypeDef *htim,TIM_OC_InitTypeDef *config,uint32_t channel);

#endif //

