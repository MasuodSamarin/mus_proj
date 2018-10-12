/**
 * \file ST7565R.h
 * \brief Constants relating to ST7565R LCD controller.
 * \author Andy Gock
 *
 * Constants and functions specific to ST7565R.
 * Tested with Newhaven Display model NHD-C12864WC-FSW-FBW-3V3-M
 * 
 * \todo Need to move functions to be controller independent
 *
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

#ifndef ST7565R_H_
#define ST7565R_H_
#include "stm32f1xx_hal.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * \addtogroup Controllers Controllers
 * Controller specific functions.
 *
 * Currently only the following controllers are supported:
 *  - ST7565R with SPI interface
 *
 * The C and header files defining these functions are stored in the subdirectory:
 *
 *     devices/
 *
 * \{
 */

/**
 * Send command byte to LCD.
 * \param c Command byte to be written to LCD
 */
void glcd_command(uint8_t c);

/**
 *  Send data byte to LCD.
 *  \param c Data byte to be written to LCD
 */
void glcd_data(uint8_t c);

/**
 * Set contrast.
 * \param val Value from 0 to 127.  This should be experimentally determined. Supported by PCD8544 only.
 */
void glcd_set_contrast(uint8_t val);

/**
 * Power down the device.
 */
void glcd_power_down(void);

/**
 * Power up the device.
 */
void glcd_power_up(void);

/**
 * Set Y address of RAM (select bank).
 * - for PCD8544, device must be under basic instruction set mode before using this.
 * \param y page address of RAM (0 <= Y < GLCD_LCD_HEIGHT/8)
 * \see   GLCD_LCD_HEIGHT
 * \see   GLCD_NUMBER_OF_BANKS
 *
 * \note Update: \p y is actually bank number, not pixel number!
 */
void glcd_set_y_address(uint8_t y);

/**
 * Set X address of RAM (column). Device must be under basic instruction set mode before using this.
 * \param x X address of RAM (0 <= X <= GLCD_LCD_WIDTH-1)
 * \see   GLCD_LCD_WIDTH
 */
void glcd_set_x_address(uint8_t x);

/**
 * Update the display within the specified bounding box. This physically writes data to the device's RAM.
 */
void glcd_write(void);

/** @}*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * define some basic static func
 * */
#define GLCD_SELECT()     	HAL_GPIO_WritePin(LCD_SPI2_NSS_GPIO_Port, LCD_SPI2_NSS_Pin, GPIO_PIN_SET)
#define GLCD_DESELECT()   	HAL_GPIO_WritePin(LCD_SPI2_NSS_GPIO_Port, LCD_SPI2_NSS_Pin, GPIO_PIN_RESET)
//#define GLCD_DC_LOW()		HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, GPIO_PIN_RESET)
//#define GLCD_DC_HIGH()    	HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, GPIO_PIN_SET)
#define GLCD_A0_LOW()     	HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, GPIO_PIN_RESET)
#define GLCD_A0_HIGH()    	HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, GPIO_PIN_SET)
#define GLCD_RESET_LOW()	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET)
#define GLCD_RESET_HIGH()	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET)

/**
 * Initialize the LCD. This function is platform and controller specific.
 */
void glcd_init(void);

/**
 * Write a byte to the connected SPI slave.
 * \param c Byte to be written
 * \cause it uses gpio mode it's nothing to the return
 * \return Returned value from SPI (often not used)
 */
void glcd_spi_write(uint8_t c);

/**
 *  Reset the LCD.
 *  \note Not all LCD controllers support reset.
 */
void glcd_reset(void);

/** @}*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Commands */

#define BLACK 1
#define WHITE 0

#define ST7565_LCD_CMD_DISPLAY_OFF           0xAE
#define ST7565_LCD_CMD_DISPLAY_ON            0xAF

#define ST7565_LCD_CMD_SET_DISP_START_LINE   0x40
#define ST7565_LCD_CMD_SET_PAGE              0xB0

#define ST7565_LCD_CMD_SET_COLUMN_UPPER      0x10
#define ST7565_LCD_CMD_SET_COLUMN_LOWER      0x00

#define ST7565_LCD_CMD_SET_ADC_NORMAL        0xA0
#define ST7565_LCD_CMD_SET_ADC_REVERSE       0xA1

#define ST7565_LCD_CMD_SET_DISP_NORMAL       0xA6
#define ST7565_LCD_CMD_SET_DISP_REVERSE      0xA7

#define ST7565_LCD_CMD_SET_ALLPTS_NORMAL     0xA4
#define ST7565_LCD_CMD_SET_ALLPTS_ON         0xA5
#define ST7565_LCD_CMD_SET_BIAS_9            0xA2
#define ST7565_LCD_CMD_SET_BIAS_7            0xA3

#define ST7565_LCD_CMD_RMW                   0xE0
#define ST7565_LCD_CMD_RMW_CLEAR             0xEE
#define ST7565_LCD_CMD_INTERNAL_RESET        0xE2
#define ST7565_LCD_CMD_SET_COM_NORMAL        0xC0
#define ST7565_LCD_CMD_SET_COM_REVERSE       0xC8
#define ST7565_LCD_CMD_SET_POWER_CONTROL     0x28
#define ST7565_LCD_CMD_SET_RESISTOR_RATIO    0x20
#define ST7565_LCD_CMD_SET_VOLUME_FIRST      0x81
#define ST7565_LCD_CMD_SET_VOLUME_SECOND     0x23
#define ST7565_LCD_CMD_SET_STATIC_OFF        0xAC
#define ST7565_LCD_CMD_SET_STATIC_ON         0xAD
#define ST7565_LCD_CMD_SET_STATIC_REG        0x0
#define ST7565_LCD_CMD_SET_BOOSTER_FIRST     0xF8
#define ST7565_LCD_CMD_SET_BOOSTER_234       0
#define ST7565_LCD_CMD_SET_BOOSTER_5         1
#define ST7565_LCD_CMD_SET_BOOSTER_6         3
#define ST7565_LCD_CMD_NOP                   0xE3
#define ST7565_LCD_CMD_TEST                  0xF0

/* These functions only available on ST7565 implementation (for now) */

/* Private functions */
void glcd_set_column_upper(uint8_t addr);
void glcd_set_column_lower(uint8_t addr);

/** All display points on (native) */
void glcd_all_on(void);

/** Set to normal mode */
void glcd_normal(void);

/** Set start line/page */
void glcd_set_start_line(uint8_t addr);

/** Clear the display immediately, does not buffer */
void glcd_clear_now(void);

/** Show a black and white line pattern on the display */
void glcd_pattern(void);

/** Init ST7565R controller / display */
void glcd_ST7565R_init(void);

#endif /* ST7565R_H_ */
