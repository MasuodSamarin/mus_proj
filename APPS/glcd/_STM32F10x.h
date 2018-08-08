/**
 * \file STM32F10x.h
 * \brief Device implementation for ST STM32F10x ARM Cortex-M3 MCUs
 *        Requires the use of ST's Standard Peripheral Library
 * \author Andy Gock
 *
 * \todo Code is untested!
 */

/*
	Copyright (c) 2012, Andy Gock

	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
		* Redistributions of source code must retain the above copyright
		  notice, this list of conditions and the following disclaimer.
		* Redistributions in binary form must reproduce the above copyright
		  notice, this list of conditions and the following disclaimer in the
		  documentation and/or other materials provided with the distribution.
		* Neither the name of Andy Gock nor the
		  names of its contributors may be used to endorse or promote products
		  derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL ANDY GOCK BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef STM32F10X_H_
#define STM32F10X_H_
#include "main.h"


/** SPI port number e.g SPI1, SPI2 (not to be confused with GPIOA, GPIOB, etc) */
/*
#define CONTROLLER_SPI_NUMBER      SPI1
#define CONTROLLER_SPI_PORT        GPIOA
#define CONTROLLER_SPI_SCK_PIN     GPIO_Pin_5
#define CONTROLLER_SPI_SCK_PINSRC  GPIO_PinSource5
#define CONTROLLER_SPI_MISO_PIN    GPIO_Pin_6
#define CONTROLLER_SPI_MISO_PINSRC GPIO_PinSource6
#define CONTROLLER_SPI_MOSI_PIN    GPIO_Pin_7
#define CONTROLLER_SPI_MOSI_PINSRC GPIO_PinSource7

#define CONTROLLER_SPI_SS_PORT  GPIOA
#define CONTROLLER_SPI_SS_PIN   GPIO_Pin_1
#define CONTROLLER_SPI_DC_PORT  GPIOA
#define CONTROLLER_SPI_DC_PIN   GPIO_Pin_2
#define CONTROLLER_SPI_RST_PORT GPIOA
#define CONTROLLER_SPI_RST_PIN  GPIO_Pin_3
*/
#define GLCD_SELECT()     	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)
#define GLCD_DESELECT()   	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)
#define GLCD_DC_LOW()		HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, GPIO_PIN_RESET)
#define GLCD_DC_HIGH()    	HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, GPIO_PIN_SET)
#define GLCD_A0_LOW()     	HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, GPIO_PIN_RESET)
#define GLCD_A0_HIGH()    	HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, GPIO_PIN_SET)
#define GLCD_RESET_LOW()	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET)
#define GLCD_RESET_HIGH()	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET)


/** \addtogroup Devices Devices
 *  Functions specific to certain devices (microcontrollers)
 *  \{
 */

/**
 * Initialise the LCD. This function is platform and controller specific.
 */
void glcd_init(void);



/**
 * Write a byte to the connected SPI slave.
 * \param c Byte to be written
 * \return Returned value from SPI (often not used)
 */
void glcd_spi_write(uint8_t c);

/**
 *  Reset the LCD.
 *  \note Not all LCD controllers support reset.
 */
void glcd_reset(void);

/** @}*/


#endif /* STM32F10X_H_ */
