/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define TEMP1_AD1_Pin GPIO_PIN_0
#define TEMP1_AD1_GPIO_Port GPIOC
#define TEMP2_AD1_Pin GPIO_PIN_2
#define TEMP2_AD1_GPIO_Port GPIOC
#define SEN1_Pin GPIO_PIN_0
#define SEN1_GPIO_Port GPIOA
#define SEN2_Pin GPIO_PIN_1
#define SEN2_GPIO_Port GPIOA
#define SEN3_Pin GPIO_PIN_2
#define SEN3_GPIO_Port GPIOA
#define VALVE_O2_Pin GPIO_PIN_3
#define VALVE_O2_GPIO_Port GPIOA
#define VALVE_O1_Pin GPIO_PIN_6
#define VALVE_O1_GPIO_Port GPIOA
#define VALVE_I2_Pin GPIO_PIN_7
#define VALVE_I2_GPIO_Port GPIOA
#define VALVE_I1_Pin GPIO_PIN_0
#define VALVE_I1_GPIO_Port GPIOB
#define PUMP_Pin GPIO_PIN_1
#define PUMP_GPIO_Port GPIOB
#define SEN4_Pin GPIO_PIN_12
#define SEN4_GPIO_Port GPIOB
#define SEN4_EXTI_IRQn EXTI15_10_IRQn
#define INT0_Pin GPIO_PIN_13
#define INT0_GPIO_Port GPIOB
#define INT0_EXTI_IRQn EXTI15_10_IRQn
#define INT1_Pin GPIO_PIN_14
#define INT1_GPIO_Port GPIOB
#define INT1_EXTI_IRQn EXTI15_10_IRQn
#define VBB_EN_Pin GPIO_PIN_15
#define VBB_EN_GPIO_Port GPIOB
#define M_CW_Pin GPIO_PIN_6
#define M_CW_GPIO_Port GPIOC
#define M_TQ_Pin GPIO_PIN_7
#define M_TQ_GPIO_Port GPIOC
#define M_CLK_Pin GPIO_PIN_8
#define M_CLK_GPIO_Port GPIOC
#define M_ALE_Pin GPIO_PIN_9
#define M_ALE_GPIO_Port GPIOC
#define HEAT2_Pin GPIO_PIN_8
#define HEAT2_GPIO_Port GPIOA
#define HEAT1_Pin GPIO_PIN_9
#define HEAT1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
