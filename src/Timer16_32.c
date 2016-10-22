/*
 * Timer16_32.c

 *
 *  Created on: 2016/02/13
 *      Author: evaota
 */
#include "Timer16_32.h"

void SetExternalOut(LPC_TMR_TypeDef *TMRx,uint8_t MRx,EMRMODE mode)
{
		TMRx->EMR |= (((uint32_t)mode<<MRx)<<4);
}

void SetMRxValue(LPC_TMR_TypeDef *TMRx,uint8_t MRx,uint32_t MRxValue)
{
	switch(MRx)
	{
	case 0:
		TMRx->MR0 = MRxValue;
			break;
	case 1:
		TMRx->MR1 = MRxValue;
			break;
	case 2:
		TMRx->MR2 = MRxValue;
			break;
	case 3:
		TMRx->MR3 = MRxValue;
			break;
	default:
		break;
	}
}
void MRxRaiseHandle(LPC_TMR_TypeDef *TMRx,uint32_t MRx)
{
	TMRx->MCR |= (1<<(MRx*3));
}

void MRxClearCT(LPC_TMR_TypeDef *TMRx,uint32_t MRx)
{
	TMRx->MCR |= (1<<(MRx*3+1));
}
void SetPrescal(LPC_TMR_TypeDef *TMRx,uint32_t PRVal)
{
	TMRx->PR = PRVal;
}
void TMRxStart(LPC_TMR_TypeDef *TMRx)
{
	TMRx->CTCR = 0;
	TMRx->TCR = 1;//ENABLE COUNTER
}
