/**
 * \file unit_tests.c
 * \brief Various test functions to demonstrate features of the library
 * \author Andy Gock
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

#include <stdio.h>
#include <stdlib.h>
#include "glcd.h"
#include "unit_tests.h"

#include "eeprom.h"



volatile uint8_t unit_test_return = 0;


/**
 *  Return from test procedure. Global var \p unit_test_return is set to 1 elsewhere,
 *  to signal function to return.
 */
//#define DEMO_RETURN() if (unit_test_return) { unit_test_return = 0; return; }
#define DEMO_RETURN() HAL_Delay(100)


#if defined(GLCD_UNIT_TEST_BITMAP_ENABLE)
	/* Open Source logo -- Size: 128x64 */

		const unsigned char bmp_oslogo[] = {	
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
		0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfc,
		0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfc,
		0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf0, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0xe0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x80, 0xc0, 0xc0, 0xf0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x0f, 0x03, 0x00, 0x00, 0x00,
		0x00, 0x01, 0x0f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f,
		0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x01, 0x0f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x1f,
		0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00   //
	};
#endif /* GLCD_UNIT_TEST_BITMAP_ENABLE */


char *strings[] = {
		"1.GOOD",
		"2.BYE, BYE",
		"3.PIGS",
		"4.BAD",
		"5.UGLY",
		"6.SOUND",
		"7.COLOR",
		"8.WATER"
};
void glcd_test_roll_text(void){
	//glcd_clear_buffer();
	glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);
	glcd_clear_buffer();
	glcd_draw_string_ammend(10, 0, 48, strings[0]);
	glcd_draw_invert_line(6);
	HAL_Delay(500);

	for (int var = 1; var < 8; ++var) {

		glcd_draw_string_ammend(10, 0, 48, strings[var]);
		HAL_Delay(500);

	}
}

void glcd_test_circles(void)
{
	uint8_t x,y,radius;
	uint8_t cnt = 3;
	while (cnt--) {
		uint8_t i;
		
		glcd_clear();

		// generate random(ish) position on display
		x = rand() % GLCD_LCD_WIDTH;
		y = rand() % GLCD_LCD_HEIGHT;
		radius = rand() % 50;

		x = 70; y=25; radius=50; // for debugging

		// fill circle with black
		
		for (i=0; i<=radius; i++) {
			glcd_draw_circle_fill(x,y,i,BLACK);
			glcd_write();
			HAL_Delay(2);
		}

		// fill the same circle above but with white
		for (i=0; i<=radius; i++) {
			glcd_draw_circle_fill(x,y,i,WHITE);
			glcd_write();
			HAL_Delay(1);
		}
		DEMO_RETURN();
	}
}

void glcd_test_counter_and_graph(void)
{
	uint8_t count = 0;
	char string[8] = "";
	while(count<40) {
		glcd_clear_buffer();
		glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);
		glcd_draw_string_P(0,40,(char *)utoa(count,string,10));

		glcd_set_font_c(FC_Liberation_Sans15x21_Numbers);
		//glcd_set_font(Liberation_Sans27x36_Numbers,27,36,46,57);
		//glcd_set_font(Bebas_Neue20x36_Bold_Numbers,20,36,46,57);
		//glcd_set_font(Bebas_Neue18x36_Numbers,18,36,46,57);
		//glcd_set_font(HelveticaNeueLT_Com_57_Cn23x35_Numbers,23,35,46,57); // commercial font - not for public distribution

		sprintf(string,"%d",count);
		glcd_draw_string_P(0,0,string);
		glcd_bar_graph_horizontal(10,38,30,6,count*20);
		glcd_bar_graph_vertical(70,0,8,30,count*10);

		glcd_write();
		count += 1;

		DEMO_RETURN();
	}

}




void glcd_test_glcdutils(void)
{
	uint16_t count = 0;
	char string[8] = "";
	while(count<20) {
		glcd_clear_buffer();

		/* Set the font */
		glcd_set_font_c(FC_Liberation_Sans20x28_Numbers);

		sprintf(string,"%d",count);
		glcd_draw_string_P(30, 15, string);
		glcd_write();
		
		count += 1;

		DEMO_RETURN();
	}
}

void glcd_test_text_up_down(void)
{
	// moves some text up and down the display

	uint8_t y;
	uint8_t max_y;
	uint8_t cnt = 1;

	glcd_set_font_c(FC_Tekton_Pro_Ext27x28_AlphaNumber);

	//glcd_set_font(Liberation_Sans11x14_Numbers,11,14,46,57);
	//glcd_set_font(Liberation_Sans15x21_Numbers,15,21,46,57);
	//glcd_set_font(Liberation_Sans27x36_Numbers,27,36,46,57);
	//glcd_set_font(Liberation_Sans17x17_Alpha,17,17,46,90);

	max_y = GLCD_LCD_HEIGHT - font_current.height - 2; // max y start position for draw_string

	while(cnt--) {
		// move top to bottom
		for (y=0; y<max_y; y++) {
			DEMO_RETURN();
			glcd_clear_buffer();
			glcd_draw_string_P(0,y,"123ABC");
			glcd_write();
			HAL_Delay(10);
		}

		// move bottom to top
		for (y=(max_y); y>0; y--) {
			DEMO_RETURN();
			glcd_clear_buffer();
			glcd_draw_string_P(0,y,"456XYZ");
			glcd_write();
			HAL_Delay(10);
		}
		
	}
	DEMO_RETURN();

}

void glcd_test_tiny_text(void)
{
	/* Write tiny text on display, all chars, scrolling up every second */
	
	char string[GLCD_LCD_WIDTH / 6 + 1];

	uint8_t c = 32;
	uint8_t len = GLCD_LCD_WIDTH / 6;
	uint8_t cnt = 10;

	//GLCD_TEXT_INIT();
	glcd_set_font_c(FC_Tekton_Pro_Ext27x28_AlphaNumber);

	while(cnt--) {
		// write chars to string from 32 to 127 ASCII
		uint8_t i;
		for (i=0; i<len; i++) {
			string[i] = c;
			c++;
			if (c > 127) {
				c = 32;
			}
		}

		// write null terminator
		string[len] = '\0';

		glcd_draw_string_P(0,15,string);
		glcd_write();

		DEMO_RETURN();
		
	}

}

void glcd_test_hello_world(void)
{
	uint32_t delay = 1000;
	uint8_t x = 15;
	uint8_t y = 15;

	glcd_clear_buffer();
	glcd_set_font_c(FC_Liberation_Sans17x17_Alpha);
	glcd_draw_string(x,y,"1234");
	glcd_write();
	HAL_Delay(delay);

	glcd_clear_buffer();
	glcd_set_font_c(FC_Bebas_Neue18x36_Numbers);
	glcd_draw_string(x,y,"1234");
	glcd_write();
	HAL_Delay(delay);

	glcd_clear_buffer();
	glcd_set_font_c(FC_Bebas_Neue20x36_Bold_Numbers);
	glcd_draw_string(x,y,"2234");
	glcd_write();
	HAL_Delay(delay);

	glcd_clear_buffer();
	glcd_set_font_c(FC_Liberation_Sans11x14_Numbers);
	glcd_draw_string(x,y,"3234");
	glcd_write();
	HAL_Delay(delay);

	glcd_clear_buffer();
	glcd_set_font_c(FC_Liberation_Sans15x21_Numbers);
	glcd_draw_string(x,y,"4234");
	glcd_write();
	HAL_Delay(delay);

	glcd_clear_buffer();
	glcd_set_font_c(FC_Liberation_Sans20x28_Numbers);
	glcd_draw_string(x,y,"5234");
	glcd_write();
	HAL_Delay(delay);

	glcd_clear_buffer();
	glcd_set_font_c(FC_Liberation_Sans27x36_Numbers);
	glcd_draw_string(x,y,"6234");
	glcd_write();
	HAL_Delay(delay);

	glcd_clear_buffer();
	glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);
	glcd_draw_string(x,y,"7234");
	glcd_write();
	HAL_Delay(delay);

	glcd_clear_buffer();
	glcd_set_font_c(FC_Tahoma11x13_AlphaNumber);
	glcd_draw_string(x,y,"8234");
	glcd_write();
	HAL_Delay(delay);

	glcd_clear_buffer();
	glcd_set_font_c(FC_Tekton_Pro_Ext27x28_AlphaNumber);
	glcd_draw_string(x,y,"9234");
	glcd_write();
	HAL_Delay(delay);

	glcd_clear_buffer();
	glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);
	glcd_draw_string(x,y,"7 HELLO");
	glcd_write();
	HAL_Delay(delay);

	glcd_clear_buffer();
	glcd_set_font_c(FC_Tahoma11x13_AlphaNumber);
	glcd_draw_string(x,y,"8 HELLO");
	glcd_write();
	HAL_Delay(delay);

	glcd_clear_buffer();
	glcd_set_font_c(FC_Tekton_Pro_Ext27x28_AlphaNumber);
	glcd_draw_string(x,y,"9 HELLO");
	glcd_write();
	HAL_Delay(delay);

/*	glcd_set_font_c(FC_Bebas_Neue20x36_Bold_Numbers);
	glcd_draw_string_P(5,23,"42");

	glcd_set_font_c(FC_Tekton_Pro_Ext27x28_AlphaNumber);
	glcd_draw_string_P(5,37,"FOO");
*/
	//glcd_write();
	//while(1) {
		//DEMO_RETURN();
	//}
}

void glcd_test_rectangles(void)
{
	glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);
	glcd_clear_buffer();
	glcd_draw_string(3,10,"RECTANGLE DEMO");
	glcd_write();
	HAL_Delay(1000);
	uint8_t cnt = 2;

	while(cnt--) {
		
		glcd_clear();
		glcd_draw_rect(30,10,50,30,BLACK);
		glcd_draw_string(3,10,"draw_rect");
		glcd_write();
		HAL_Delay(500);

		glcd_draw_rect(0,0,100,50,BLACK);
		glcd_write();
		HAL_Delay(500);

		glcd_draw_rect(110,15,10,30,BLACK);
		glcd_write();
		HAL_Delay(500);

		DEMO_RETURN();
		

		glcd_clear();
		glcd_draw_string(3,10,"draw_rect_thick");
		glcd_write();

		glcd_draw_rect_thick(5,5,80,25,3,6,BLACK);
		glcd_write();
		HAL_Delay(500);
		DEMO_RETURN();
		
		glcd_draw_rect_thick(30,32,50,20,8,8,BLACK);
		glcd_write();
		HAL_Delay(500);
		DEMO_RETURN();
		
		glcd_draw_rect_thick(100,10,20,20,5,5,BLACK);
		glcd_write();
		HAL_Delay(500);
		DEMO_RETURN();

		glcd_clear();
		glcd_draw_string(3,10,"draw_rect_shadow");
		glcd_draw_rect_shadow(0,0,45,30,BLACK);
		glcd_write();
		HAL_Delay(500);
		DEMO_RETURN();
		
		glcd_draw_rect_shadow(95,5,30,30,BLACK);
		glcd_write();
		HAL_Delay(500);
		DEMO_RETURN();
		
		glcd_draw_rect_shadow(55,20,30,20,BLACK);
		glcd_write();
		HAL_Delay(500);
		DEMO_RETURN();
	}
	
}
#include <stdlib.h>
void glcd_test_scrolling_graph_rand(void){
	glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);

	glcd_clear();
	glcd_write();
	//uint8_t cnt = 2;
	int i;//=rand();
//char string[10];
	while(1) {
		//uint16_t n;
		i=rand()%300;
		//glcd_draw_string_P(30,30,(char *)utoa(i,string,10));
		//glcd_draw_string(10,10,"hello");
		//glcd_write();

		glcd_scrolling_bar_graph(8,10,115,50,i);
		HAL_Delay(50);

	}
}


void glcd_test_volume_box(void){
	//uint8_t count = 0;
	char string[8] = "";


	while(1) {
		glcd_clear_buffer();
		glcd_set_font_c(FC_Tekton_Pro_Ext27x28_AlphaNumber);
		glcd_draw_string_P(5,5,"POT 3");
		glcd_write();

		glcd_set_font_c(FC_Liberation_Sans20x28_Numbers);

		int x = 5;
		int y = 40;
		int w = 60;
		//int h = 7;
/*
		for (int i=x+w-3; i<x+w; i++) {
				for (int j=y; j<y+h; j++) {
					glcd_set_pixel(i, j, 1);
				}
			}
		glcd_update_bbox(x, y, x+w-1, y+h-1);
		glcd_write();
		HAL_Delay(500);
*/
		int cnt = 0;

		while((cnt++) < 255){
			sprintf(string,"%d",cnt);

			//glcd_bar_graph_horizontal_title(x, y, w-3, h, cnt);//*255/100);
			glcd_draw_string(x+w+1, y-10, string);
			glcd_update_bbox(x, y, GLCD_LCD_WIDTH, GLCD_LCD_HEIGHT);
			glcd_write();
			HAL_Delay(10);
		}


		HAL_Delay(1000);

	}

	DEMO_RETURN();

}

void glcd_test_scrolling_graph(void)
{
	glcd_clear();
	glcd_write();
	uint8_t cnt = 2;

	while(cnt--) {
		uint16_t n;
		for (n=0; n<=255; n += 20) {
			glcd_scrolling_bar_graph(0,0,50,50,n);
			glcd_scrolling_bar_graph(60,0,50,30,n);
			glcd_scrolling_bar_graph(60,35,60,20,n);
			DEMO_RETURN();
		}
		for (n=0; n<=255; n += 20) {
			glcd_scrolling_bar_graph(0,0,50,50,255-n);
			glcd_scrolling_bar_graph(60,0,50,30,n);
			glcd_scrolling_bar_graph(60,35,60,20,n);
			DEMO_RETURN();
		}
	}	
}
#if 0
#include <logo/throbber-01.h>
#include <logo/out.h>

#if defined (GLCD_UNIT_TEST_BITMAP_ENABLE)
void glcd_test_bitmap_128x64(void)
{
	int del = 100;
	glcd_clear_buffer();

	glcd_draw_bitmap(kore1);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore3);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore5);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore7);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore9);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore11);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore13);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore15);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore17);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore19);
	glcd_write();
	HAL_Delay(del);

	glcd_draw_bitmap(kore21);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore23);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore25);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore27);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore29);
	glcd_write();
	HAL_Delay(del);

	glcd_draw_bitmap(kore31);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore33);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore35);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore36);
	glcd_write();
	HAL_Delay(del);
	glcd_draw_bitmap(kore37);
	glcd_write();
	HAL_Delay(del);

	glcd_draw_bitmap(kore38);
	glcd_write();
	HAL_Delay(del);

	glcd_draw_bitmap(kore39);
	glcd_write();
	HAL_Delay(del);

	glcd_draw_bitmap(kore40);
	glcd_write();
	HAL_Delay(del);



}
#endif
#endif


void glcd_tests(void){
	static uint8_t state;

	switch ((state++)%10) {
		case 1:
			glcd_test_roll_text();
			break;
		case 2:
			glcd_test_circles();
			break;
		case 3:
			glcd_test_counter_and_graph();
			break;
		case 4:
			glcd_test_glcdutils();
			break;
		case 5:
			glcd_test_text_up_down();
			break;
		case 6:
			glcd_test_hello_world();
			break;
		case 7:
			glcd_test_rectangles();
			break;
		case 8:
			glcd_test_scrolling_graph();
			break;
		case 9:
			glcd_test_bitmap_128x64();
			break;

	}
}

	//
	//();
	//();
	//();
	//();
	//();
	//();
	//();
	//();
	//();
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdlib.h"
/*
 * user includes
 * */
#include "event.h"
#include "push_btn.h"

char str[50];

char *unit_btn_name[] = {
		"BTN_ENTER", "BTN_BYPASS"//, "BTN_3", "BTN_4"
};

char *unit_btn_hold[] = {
		"BTN_HOLD_LONG", "BTN_HOLD_SHORT"
};

char *unit_enc_dir[] = {
		"ENC_DIR_CCW", "ENC_DIR_CW"
};
char *unit_vol_name[] = {
		"VOL_A", "VOL_B", "VOL_C"
};

void unit_init(void){
	efx_init_list();
	glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);
	glcd_clear_buffer();
	glcd_write();
	//glcd_draw_string_xy(0,0,string);
	//glcd_bar_graph_horizontal_no_border(10,38,70,6,v1);
	//glcd_draw_string_xy(90,38,(char *)utoa(v1,string,10));
}
void unit_print_btn(btn_node_t *btn){
	glcd_clear_buffer();
	glcd_draw_string(5,5, "BUTTON");
	glcd_draw_string(5,15, unit_btn_name[btn->name]);
	//glcd_draw_string(5,25, unit_btn_hold[btn->hold]);
	sprintf(str, "%p", btn);
	glcd_draw_string(5,35, str);
	glcd_write();
}
void unit_print_enc(enc_node_t *enc){
	efx_node_t *node = NULL;

	if (enc->dir == ENC_DIR_CCW)
		node = efx_next_node();

	else if (enc->dir == ENC_DIR_CW)
		node = efx_prev_node();

	unit_test_effect_print(node);
}
void unit_print_vol(vol_node_t *vol){

	glcd_clear_buffer();
	glcd_draw_string(5,5, "VOLUME");
	glcd_draw_string(5,15, unit_vol_name[vol->name]);
	glcd_draw_string(5,25, (char*)utoa(vol->val, str, 10));
	sprintf(str, "%p", vol);
	glcd_draw_string(5,35, str);
	glcd_bar_graph_horizontal(5, 45, 70, 10, (vol->val >> 4));

	uint8_t sad = (uint8_t)((float)(vol->val) / (float)4010 * (float)100);
	sprintf(str, "%d%%", sad);
	glcd_draw_string(80,45, str);

	glcd_write();
}
void unit_print_not(void){
	glcd_clear_buffer();
	glcd_draw_string(5,5, "EVENT-DRIVEN TEST");
	glcd_draw_string(5,15, "BUTTONS");
	glcd_draw_string(5,25, "ENCODER");
	glcd_draw_string(5,35, "VOLUMES");
	glcd_write();
}
void unit_test_events(void){
	event_node_t event;

	//if(!event_get_size())
		//return;
	event = event_pop_node();

	switch (event.type) {
		case EVENT_NOT:
			//uint_print_not();
			break;

		case EVENT_BTN:
			unit_print_btn(&event.btn);
			break;
		case EVENT_ENC:
			unit_print_enc(&event.enc);
			break;
		case EVENT_VOL:
			unit_print_vol(&event.vol);
			break;


	}
}




void unit_test_init(void){
	efx_init_list();
	glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);
	glcd_clear_buffer();
	glcd_write();

}

void unit_test_effect_print(efx_node_t *node){

	if (node == NULL)
		return;

	glcd_clear_buffer();
	glcd_write();

	glcd_draw_string(2,5, "EFFECTS");

	sprintf(str, "%d", node->number);
	glcd_draw_string(5,15, "num:");
	glcd_draw_string(55,15, str);

	glcd_draw_string(5,25, (char*)node->fv1->name);
	glcd_draw_string(55,25, (char*)node->fv1->comments);

	sprintf(str, "%d", node->fv1->fv1->eep);
	glcd_draw_string(5,35, "eep:");
	glcd_draw_string(55,35, str);

	sprintf(str, "%d", node->fv1->fv1->pin);
	glcd_draw_string(5,45, "pin:");
	glcd_draw_string(55,45, str);

	sprintf(str, "%p", node);
	glcd_draw_string(55,55, str);
	glcd_write();
}


void unit_test_sizes(void){
	glcd_clear_buffer();
/*
	uint8_t *id[2];
	id[0] = malloc(sizeof(uint8_t*));
	id[1] = malloc(sizeof(uint8_t*));

	uint8_t is[2] = {0};

	sprintf(str, "is[0]:%p", &is[0]);
	glcd_draw_string(5,5, str);

	sprintf(str, "is[1]:%p", &is[1]);
	glcd_draw_string(5,15, str);

	sprintf(str, "is[1]-is[0]:%d", (&is[1] - &is[0]));
	glcd_draw_string(5,25, str);

	sprintf(str, "id[0]:%p", &id[0]);
	glcd_draw_string(5,35, str);


	sprintf(str, "id[1]:%p", &id[1]);
	glcd_draw_string(5,45, str);

	sprintf(str, "id[1]-id[0]:%d", (&id[1] - &id[0]));
	glcd_draw_string(5,55, str);
*/
	efx_node_t n[1];
	efx_node_t *np = n;
	uint64_t number;
	efx_mode_t mode;
	efx_type_t type;
	efx_fv1_base_t *fv1;
	/*efx_isd_base_t *isd;
	uint32_t volume[VOL_MAX];
	uint8_t status;
*/
	sprintf(str, "n:%d", sizeof(n));
	glcd_draw_string(5,5, str);
	sprintf(str, "*np:%d", sizeof(np));
	glcd_draw_string(5,15, str);
	sprintf(str, "number:%d", sizeof(number));
	glcd_draw_string(5,25, str);
	sprintf(str, "mode:%d", sizeof(mode));
	glcd_draw_string(5,35, str);
	sprintf(str, "type:%d", sizeof(type));
	glcd_draw_string(5,45, str);
	sprintf(str, "*fv1:%d", sizeof(fv1));
	glcd_draw_string(5,55, str);
	glcd_write();
	while(1);
}

#include <string.h>
#include "eepromConfig.h"

#define		_EEPROM_FLASH_PAGE_SIZE				1024
#define ADDR_FLASH_PAGE_0     ((uint32_t)0x08000000) /* Base @ of Page 0, 1 Kbytes */
#define _EEPROM_FLASH_PAGE_ADDRESS    (ADDR_FLASH_PAGE_0|(_EEPROM_FLASH_PAGE_SIZE*_EEPROM_USE_FLASH_PAGE))
//#define size_of_node (sizeof(uint32_t))
#define size_of_node (sizeof(efx_node_t) / sizeof(uint32_t))

/*TODO: delete this var*/
uint32_t d_src[size_of_node] = {1, 2, 3, 4};
uint32_t d_des[size_of_node] = {0};
#define addr_index var*size_of_node
#define number_of_node	16

void unit_test_eep_save(void){

	EE_Format();

   	efx_node_t *node[number_of_node] = {0};
	for (int var = 0; var < number_of_node; ++var) {
		//efx_node_t *efx = efx_create_fv1_node((uint8_t)var, EFX_MODE_PRESET, (efx_fv1_preset)var);
		node[var] = efx_create_fv1_node((uint8_t)var+1, EFX_MODE_PRESET, (efx_fv1_preset)var, 0, 0, 0);
	}

	if(!EE_Writes_Efx(0, number_of_node, node))
		_Error_Handler(__FILE__, __LINE__);

	for (int var = 0; var < number_of_node; ++var) {
		//free(node[var]->fv1);
		free(node[var]);
	}

}
void unit_test_eep_read(void){
	static uint32_t cnt = 0;

	efx_node_t *node[number_of_node] = {0};
	if(!EE_Reads_Efx(0,  number_of_node, node))
		_Error_Handler(__FILE__, __LINE__);

	for (int var = 0; var < number_of_node; ++var) {

		glcd_clear_buffer();
		glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);
		glcd_draw_rect(0, 0, 127, 64, 1);
		glcd_draw_rect(1, 1, 125, 62, 1);
		//glcd_draw_rect(2, 2, 123, 60, 1);
		glcd_draw_string(10,5, "--[ EEPROM ]--");
		glcd_draw_string(6,16, (char*)node[var]->fv1->name);
		glcd_draw_string(6,26, (char*)node[var]->fv1->comments);
		glcd_invert_area(4, 14, 70, 22);
		//glcd_draw_string(5,26, (char *)utoa(var,str,10));
		sprintf(str, "cnt:%lu", cnt);
		glcd_draw_string(6,36, str);
		//glcd_draw_string(45,26, (char *)utoa(var,str,10));
		//sprintf(str, "n:%p", (node[var]));
		//glcd_draw_string(6,36, str);
		sprintf(str, "f:%p", (node[var]->fv1));
		glcd_draw_string(6,46, str);

		glcd_set_font_c(FC_Bebas_Neue18x36_Numbers);
		sprintf(str, "%d", (node[var]->number));
		glcd_draw_string_P(80, 24, str);
		glcd_write();

		HAL_Delay(250);
	}
	cnt++;
}
