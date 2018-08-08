/**
 * \file STM32F10x.c
 * \brief Device implementation for ST STM32F10x ARM Cortex-M3 MCUs
 *        Requires the use of ST's Standard Peripheral Library
 * \author Andy Gock
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


/* Includes from CMSIS and Peripheral Library */
#include "main.h"
#include "stm32f1xx_hal.h"
/* Includes from GLCD */
#include "glcd.h"
#include "_STM32F10x.h"
#include "ST7565R.h"

void glcd_init(void)
{

	/* Initialisation of GPIO and SPI */

	/* Send reset pulse to LCD */
	glcd_reset();
	HAL_Delay(GLCD_RESET_TIME);

	glcd_ST7565R_init();
	
	/* Set all dots black and hold for 0.5s, then clear it, we do this so we can visually check init sequence is working */
	glcd_all_on();
	HAL_Delay(500);
	glcd_normal();

	glcd_set_start_line(0);
	glcd_clear_now();	


			
	glcd_select_screen(glcd_buffer,&glcd_bbox);
	glcd_clear();

}

void glcd_spi_write(uint8_t c)
{

	 int8_t i;
	  for (i=7; i>=0; i--) {
			HAL_GPIO_WritePin(LCD_SCK_GPIO_Port, LCD_SCK_Pin, GPIO_PIN_RESET);

	    //SCLK_PORT &= ~_BV(SCLK);
	    if (c & (1<<i))
			HAL_GPIO_WritePin(LCD_DATA_GPIO_Port, LCD_DATA_Pin, GPIO_PIN_SET);

	      //SID_PORT |= _BV(SID);
	    else
			HAL_GPIO_WritePin(LCD_DATA_GPIO_Port, LCD_DATA_Pin, GPIO_PIN_RESET);

	      //SID_PORT &= ~_BV(SID);

		HAL_GPIO_WritePin(LCD_SCK_GPIO_Port, LCD_SCK_Pin, GPIO_PIN_SET);

	    //SCLK_PORT |= _BV(SCLK);
	  }
}

void glcd_reset(void)
{
	GLCD_SELECT();
	GLCD_RESET_LOW();
	HAL_Delay(GLCD_RESET_TIME);
	GLCD_RESET_HIGH();
	GLCD_DESELECT();
}


