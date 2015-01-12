#ifndef _USART_H_
#define _USART_H_

#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>

void init_USART1(int baudrate);
void USART_puts(USART_TypeDef* USARTx, char* buffer);

#endif
