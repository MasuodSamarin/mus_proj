#include "stm32f1xx_hal.h"
#include "glcd.h"
#include "glcd_graphics.h"
#include "glcd_text.h"

glcd_FontConfig_t font_current;

void glcd_set_font_c(glcd_FontConfig_t font){
	font_current = font;
}
uint8_t glcd_draw_char_xy(uint8_t x, uint8_t y, char c){
	/* Font table in MikroElecktronica format
	- multi row fonts allowed (more than 8 pixels high)
	- variable width fonts allowed
	a complete column is written before moving to the next */
	if (c < font_current.start_char || c > font_current.end_char) {
			c = '.';
	}
	uint8_t i;
	uint8_t var_width;
	uint8_t bytes_high;
	uint8_t bytes_per_char;
	const char *p;

	if ((font_current.height % 8) > 0){
		bytes_high = (font_current.height / 8) + 1;
	}
	else{
		bytes_high = (font_current.height / 8);
	}
	bytes_per_char = font_current.width * bytes_high + 1; /* The +1 is the width byte at the start */

	p = font_current.font_table + (c - font_current.start_char) * bytes_per_char;

	/* The first byte per character is always the width of the character */

	var_width = *p;

	p++; /* Step over the variable width field */

	/*
	if (x+var_width >= GLCD_LCD_WIDTH || y+font_current.height >= GLCD_LCD_HEIGHT) {
	return;
	}
	*/

	for ( i = 0; i < var_width; i++ ) {
		uint8_t j;
		for ( j = 0; j < bytes_high; j++ ) {
			uint8_t dat = *( p + i*bytes_high + j );
			uint8_t bit;
			for (bit = 0; bit < 8; bit++) {

				if (x+i >= GLCD_LCD_WIDTH || y+j*8+bit >= GLCD_LCD_HEIGHT) {
					/* Don't write past the dimensions of the LCD, skip the entire char */
					return 0;
				}

				/* We should not write if the y bit exceeds font height */
				if ((j*8 + bit) >= font_current.height) {
					/* Skip the bit */
					continue;
				}

				if (dat & (1<<bit)) {
					glcd_set_pixel(x+i,y+j*8+bit,BLACK);
				} else {
					glcd_set_pixel(x+i,y+j*8+bit,WHITE);
				}
			}
		}
	}
	return var_width;
}

void glcd_draw_string(uint8_t x, uint8_t y, char *c)
{
	uint8_t width;

	if (y > (GLCD_LCD_HEIGHT - font_current.height - 1)) {
		/* Character won't fit */
		return;
	}

	while (*c) {
		width = glcd_draw_char_xy(x,y,*c);
		x += (width + 1);
		c++;
	}
}
void glcd_draw_string_P(uint8_t x, uint8_t y, const char *str)
{
	uint8_t width;

	if (y > (GLCD_LCD_HEIGHT - font_current.height - 1)) {
		/* Character won't fit */
		return;
	}

	while (1) {

		char c = *(str++);

		if (!c)
			return;

		width = glcd_draw_char_xy(x,y,c);
		x += (width + 1);
		c++;
	}
}


void glcd_draw_string_ammend(uint8_t x, uint8_t top, uint8_t down, char *str) {
	glcd_scroll_line(top);
	glcd_draw_string(x, (down), str);
	glcd_write();
}

void glcd_draw_string_ammend_P(const char *str) {
	glcd_scroll_line(2);
	glcd_draw_string_P(0, (GLCD_LCD_HEIGHT/8-1), str);
	glcd_write();
}

void glcd_draw_invert_line(uint8_t line)
{
	glcd_invert_area(0,line*font_current.height,GLCD_LCD_WIDTH-1,font_current.height);
}
