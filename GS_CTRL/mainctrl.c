#include "mainctrl.h"
#include "usart.h"
#include "math.h"
#include "delay.h"

void InitallConfig(void)
{
	InitPumpCtrl(&pumpctrl);
	InitAdCtrl(&groove1temp,&hadc1,ADC_CHANNEL_10);
	InitAdCtrl(&groove2temp,&hadc1,ADC_CHANNEL_12);
	
	//InitMotoCtrl(&stepdrv,&htim3,&tim3config,TIM_CHANNEL_3); //PC6
	
	InitMotoCtrl(&stepdrv,&htim2,&tim2config,TIM_CHANNEL_2);   //PA1   
	
	InitHeatCtrl(&heatdrv1,&htim4,&tim4config,TIM_CHANNEL_4);
	InitHeatCtrl(&heatdrv2,&htim1,&tim1config,TIM_CHANNEL_1);
	
	InitPidCtrl(&temppid1);
	InitPidCtrl(&temppid2);
}

/*********************************water inject module**************************************************/
void WaterInjectionSect(pumpctrl_t *pump,uint8_t stat)
{
	if(!pump->flow) return;
  pump->StartPump(pump);
  pump->injectform = stat;
  switch(pump->injectform)
	{
		case 0:
			pump->OpenPumpValve(&pump->pumpvalve1);	 
      pump->ClosePumpValve(&pump->pumpvalve2);
		 break;
		case 1:
		  pump->OpenPumpValve(&pump->pumpvalve1);	    
		 break;
		case 2:
			pump->OpenPumpValve(&pump->pumpvalve2);      
		 break;
		default:
			break;
	}	
  HAL_TIM_IC_Start_IT(&htim2,TIM_CHANNEL_1);	
}
/*************************************motor control***************************************************/

void StepperInit(motoctrl_t *moto)
{
	moto->SetDutycycle(moto,1000);
	if(READ_INT0_STATE)
	{		
		moto->steps = 400;		
		StepperStart(moto,R);
		while(moto->CheckMovingState(moto)){
		}		
	}  
		moto->steps = ~0;	
		StepperStart(moto,L);
    while(moto->CheckMovingState(moto)){
		}			
}
void StepperStart(motoctrl_t *moto, MOTODIR stat)
{
	if(moto->steps /*&& !stepdrv.extistate*/)
	{		
		//TQ_ON();
		moto->dir = stat;
		if(READ_INT0_STATE && moto->dir ) 
		{
			if(!stepdrv.extistate) 
			{
				moto->steps = 0;
			  return;
			}			
		}			
		moto->movstate = 1;		
		moto->dir ? DIR_LEFT_T():DIR_RIGHT_T();	
	  moto->StartMoto(moto);
	}
}
void StepperStop(motoctrl_t *moto)
{
	moto->StopMoto(moto);
	moto->steps = 0;  
  moto->movstate = 0;
  moto->extistate = 0;
	//TQ_OFF();
}
void SteperrateCtrl(motoctrl_t *moto)
{
	if(moto->steps)
	{		
		if(stepdrv.vecctrlmode)
		{
			if(moto->steps>stepdrv.halfsteps)
			{
				__HAL_TIM_SET_AUTORELOAD(moto->htim,(uint16_t)((moto->htim->Init.Period)*(2-RATE)));
				__HAL_TIM_SET_COMPARE(moto->htim,moto->channel,(uint16_t)((moto->htim->Init.Period)*(2-RATE))>>1);
				
			}			
			else 
			{
				__HAL_TIM_SET_AUTORELOAD(moto->htim,(uint16_t)((moto->htim->Init.Period)*RATE));
				__HAL_TIM_SET_COMPARE(moto->htim,moto->channel,(uint16_t)((moto->htim->Init.Period)*RATE)>>1);
			}
		}
		else
		{
			if(moto->steps<stepdrv.decvecthreshold)
			{
				__HAL_TIM_SET_AUTORELOAD(moto->htim,(uint16_t)((moto->htim->Init.Period)*RATE));
				__HAL_TIM_SET_COMPARE(moto->htim,moto->channel,(uint16_t)((moto->htim->Init.Period)*RATE)>>1);
			}			
			else if(moto->htim->Init.Period>stepdrv.vecmax) //最快速度
			{
				__HAL_TIM_SET_AUTORELOAD(moto->htim,(uint16_t)((moto->htim->Init.Period)*(2-RATE)));
				__HAL_TIM_SET_COMPARE(moto->htim,moto->channel,(uint16_t)((moto->htim->Init.Period)*(2-RATE))>>1);
			}			
		}
    
	}
}
/*************************************heat  control**************************************************/
void HeatPidCtrl(void)
{
	if(groove1temp.currenttemp < temppid1.expectvalue - 4)
	{		
			heatdrv1.SetDutycycle(&heatdrv1,FULL_POWER);		
	}else{
	   float tmp =PidParamCalculate(&temppid1,groove1temp.currenttemp);
		 if(tmp > -3.25 && tmp < 11.75)
	      heatdrv1.SetDutycycle(&heatdrv1, 6500 + (int)(tmp*2000));
	}
	if(groove2temp.currenttemp < temppid2.expectvalue - 4)
	{		
			heatdrv2.SetDutycycle(&heatdrv2,FULL_POWER);		
	}else{
	   float tmp =PidParamCalculate(&temppid2,groove2temp.currenttemp);
//		 if(tmp < -3.25 ) 
//			  tmp = -3.2;
//		 if(tmp > 11.75 ) 
//			  tmp = 11.7;
		 if(tmp > -3.25 && tmp < 11.75)
	      heatdrv2.SetDutycycle(&heatdrv2, 6500 + (int)(tmp*2000));
	} 	
}

/**********************************break hander*****************************************************/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM2)
	{		
		if(pumpctrl.flow > 0)
		{
			pumpctrl.flow--;
		}else{
			switch(pumpctrl.injectform)
			{
				case 0:
					if(!pumpctrl.ReadValveState(&pumpctrl.pumpvalve1) && pumpctrl.ReadValveState(&pumpctrl.pumpvalve2))
					{
						pumpctrl.ClosePumpValve(&pumpctrl.pumpvalve1);						
						pumpctrl.OpenPumpValve(&pumpctrl.pumpvalve2);
						pumpctrl.flow=pumpctrl.flow_ex;
						pumpctrl.flow_ex = 0;
					}else
					if(pumpctrl.ReadValveState(&pumpctrl.pumpvalve1) && !pumpctrl.ReadValveState(&pumpctrl.pumpvalve2))
					{
						pumpctrl.ClosePumpValve(&pumpctrl.pumpvalve2);
						HAL_TIM_IC_Stop_IT(&htim2,TIM_CHANNEL_1);
						pumpctrl.StopPump(&pumpctrl);
				    pumpctrl.flow=0;
					}	
				 break;
				case 1:
					pumpctrl.ClosePumpValve(&pumpctrl.pumpvalve1);
				  HAL_TIM_IC_Stop_IT(&htim2,TIM_CHANNEL_1);
				  pumpctrl.StopPump(&pumpctrl);
				  pumpctrl.flow=0;
				 break;
				case 2:
					pumpctrl.ClosePumpValve(&pumpctrl.pumpvalve2);
				  HAL_TIM_IC_Stop_IT(&htim2,TIM_CHANNEL_1);
				  pumpctrl.StopPump(&pumpctrl);
				  pumpctrl.flow=0;
				default:
					break;				
			}
		}				
	}
}


void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM2)
	{
		if(stepdrv.steps > 0 )
		{
			if(stepdrv.steps > 1 )
			   SteperrateCtrl(&stepdrv);	
      stepdrv.steps--;			
		}else{
			StepperStop(&stepdrv);
		}
	}
	if(htim->Instance==TIM3)
	{
		if(stepdrv.steps > 0 )
		{
			if(stepdrv.steps > 1 )
			   SteperrateCtrl(&stepdrv);	
      stepdrv.steps--;			
		}else{
			StepperStop(&stepdrv);
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{	
	if(GPIO_Pin==INT0_Pin)
	{
		if(READ_INT0_STATE && stepdrv.dir && !stepdrv.extistate)
		{	
			stepdrv.extistate = 1;	//order careful!
			stepdrv.steps = 200;		
		  StepperStart(&stepdrv,L);				  
	  }		
  }
}
