#ifndef _MAIN_H_
#define _MAIN_H_

#include "Timer16_32.h"
//#include "SysTick.h"
//#include "UART.h"
#include "PWM.h"
//#include "ADC.h"
//#include "I2C.h"
#include "UART.h"
#include "SPI.h"
#include <stdio.h>
#include <math.h>
#include <stdint.h>
//
//const int8_t sindata[] =
//{
//		6,12,19,25,31,37,43,49,54,60,65,71,76,81,85,90,94,98,102,106,109,
//		112,115,117,120,122,123,125,126,126,127,127,127,126,126,125,123,
//		122,120,117,115,112,109,106,102,98,94,90,85,81,76,71,65,60,54,49,
//		43,37,31,25,19,12,6,0,-6,-12,-19,-25,-31,-37,-43,-49,-54,-60,
//		-65,-71,-76,-81,-85,-90,-94,-98,-102,-106,-109,-112,-115,-117,
//		-120,-122,-123,-125,-126,-126,-127,-127,-127,-126,-126,-125,
//		-123,-122,-120,-117,-115,-112,-109,-106,-102,-98,-94,-90,-85,
//		-81,-76,-71,-65,-60,-54,-49,-43,-37,-31,-25,-19,-12,-6,0
//};

#define GPIO0HIGH(Px) LPC_GPIO0->DATA |= (1<<Px)
#define GPIO0LOW(Px) LPC_GPIO0->DATA &= ~(1<<Px)

#define GPIO0TG(Px) LPC_GPIO0->DATA ^= (1<<Px)
#define GPIO1TG(Px) LPC_GPIO1->DATA ^= (1<<Px)

#define GPIO1HIGH(Px) LPC_GPIO1->DATA |= (1<<Px)
#define GPIO1LOW(Px) LPC_GPIO1->DATA &= ~(1<<Px)

#define GPIO0STAT(Px) (LPC_GPIO0->DATA&(1<<Px))
#define GPIO1STAT(Px) (LPC_GPIO1->DATA&(1<<Px))

#endif
