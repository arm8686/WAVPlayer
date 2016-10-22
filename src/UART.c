/*
 * UART.c
 *
 *  Created on: 2016/02/14
 *      Author: evaota
 */
#include "UART.h"

void UART_Init(uint32_t baudrate)
{
	uint32_t DL;
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);
	LPC_SYSCON->UARTCLKDIV |= (1<<0);

	LPC_IOCON->PIO1_6 &= ~(1<<0);
	LPC_IOCON->PIO1_6 |= (1<<0);
	LPC_IOCON->PIO1_7 &= ~(1<<0);
	LPC_IOCON->PIO1_7 |= (1<<0);
	LPC_GPIO1->DIR |= (1<<7);
	LPC_GPIO1->DIR &= ~(1<<6);

	LPC_UART->LCR = 0x00000083;//Enable divisor latch access and Word length 8bit
	DL = (SystemCoreClock*LPC_SYSCON->SYSAHBCLKDIV)/(16*baudrate*LPC_SYSCON->UARTCLKDIV);
	LPC_UART->DLL = DL%256;
	LPC_UART->DLM = DL/256;
	LPC_UART->LCR  &= ~(1<<7);//Disable divisor latch access
	LPC_UART->FCR = 0x07;
}

void Putc(int8_t c)
{
	while(!((LPC_UART->LSR>>5)&0x01));
	LPC_UART->THR = c;
}
int8_t Getc(void)
{
	while(!(LPC_UART->LSR&0x01));
	return LPC_UART->RBR;
}

void Puts(char *s)
{
	while(*s!='\0')
	{
		Putc(*s);
		s++;
	}
}
void intprintf(int32_t num)
{
	char buf[1000];
	sprintf(buf,"%x",num);
	Puts(buf);
}
