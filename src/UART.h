/*
 * UART.h
 *
 *  Created on: 2016/02/14
 *      Author: evaota
 */

#ifndef UART_H_
#define UART_H_

#include "LPC11xx.h"
#include <stdint.h>

void UART_Init(uint32_t baudrate);
void Putc(int8_t c);
int8_t Getc(void);
void Puts(char *s);
void intprintf(int32_t num);

#endif /* UART_H_ */
