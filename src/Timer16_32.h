/*
 * Timer16_32.h
 *
 *  Created on: 2016/02/13
 *      Author: evaota
 */

#ifndef TIMER16_32_TIMER16_32_H_
#define TIMER16_32_TIMER16_32_H_

#include "LPC11xx.h"
#include <stdint.h>

typedef enum
{
	NONE,
	MATCHHIGH,
	MATCHLOW,
	MATCHTGL
}EMRMODE;

#define ENABLETMR16B0CLK() LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7)
#define ENABLETMR16B1CLK() LPC_SYSCON->SYSAHBCLKCTRL |= (1<<8)
#define ENABLETMR32B0CLK() LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9)
#define ENABLETMR32B1CLK() LPC_SYSCON->SYSAHBCLKCTRL |= (1<<10)

#define EnableTMR16B0IRQ() NVIC_EnableIRQ(TIMER_16_0_IRQn)
#define EnableTMR16B1IRQ() NVIC_EnableIRQ(TIMER_16_1_IRQn)
#define EnableTMR32B0IRQ() NVIC_EnableIRQ(TIMER_32_0_IRQn)
#define EnableTMR32B1IRQ() NVIC_EnableIRQ(TIMER_32_1_IRQn)

#define TMR16B0 LPC_TMR16B0
#define TMR16B1 LPC_TMR16B1
#define TMR32B0 LPC_TMR32B0
#define TMR32B1 LPC_TMR32B1

#define TMR16B0IRCLEAR(MRx) LPC_TMR16B0->IR |= (1<<MRx)
#define TMR16B1IRCLEAR(MRx) LPC_TMR16B1->IR |= (1<<MRx)
#define TMR32B0IRCLEAR(MRx) LPC_TMR32B0->IR |= (1<<MRx)
#define TMR32B1IRCLEAR(MRx) LPC_TMR32B1->IR |= (1<<MRx)

void SetExternalOut(LPC_TMR_TypeDef *TMRx,uint8_t MRx,EMRMODE mode);
void SetMRxValue(LPC_TMR_TypeDef *TMRx,uint8_t MRx,uint32_t MRxValue);
void MRxRaiseHandle(LPC_TMR_TypeDef *TMRx,uint32_t MRx);
void MRxClearCT(LPC_TMR_TypeDef *TMRx,uint32_t MRx);
void SetPrescal(LPC_TMR_TypeDef *TMRx,uint32_t PRVal);
void TMRxStart(LPC_TMR_TypeDef *TMRx);

#endif /* TIMER16_32_TIMER16_32_H_ */
