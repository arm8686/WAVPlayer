/*
 * SPI.h
 *
 *  Created on: 2016/02/24
 *      Author: evaota
 */

#ifndef SPI_H_
#define SPI_H_

#include "LPC11xx.h"
#include <stdint.h>

typedef enum
{
	SSPMASTER,
	SSPSLAVE
}SPIMODE;

void SPI_Init(SPIMODE mode);//initializing SSP module
inline void SPI_Write(uint8_t data);//Transmit one byte data
inline uint8_t SPI_Read(void);//Receive one byte data

#endif /* SPI_H_ */
