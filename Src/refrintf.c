#include <stdio.h>
#include "usart.h"

#define  DEBUG_PORT  huart1

#ifdef  __GNUC__
  #define  PUTCHAR_PROTOTYPE   int  __io_putchar(int ch)
	#define  GETCHAR_PROTOTYPE   int  __io_getchar(void)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
  #define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif


PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&DEBUG_PORT, (uint8_t*)&ch, sizeof(ch), 0xfff);
	while(HAL_UART_GetState(&DEBUG_PORT) != HAL_UART_STATE_READY){
	}
	return ch;
}

GETCHAR_PROTOTYPE
{
	uint8_t ch;
	while(HAL_UART_GetState(&DEBUG_PORT) != HAL_UART_STATE_READY){
	}
	HAL_UART_Receive(&DEBUG_PORT, (uint8_t*)&ch, 1, 0xfff);
	return ch;
}

