#ifndef _GLCD_TEXT_NEW_
#define _GLCD_TEXT_NEW_

#include "glcd.h"
//#include "fonts/fonts.h"

void glcd_set_font_c(glcd_FontConfig_t font);
uint8_t glcd_draw_char_xy(uint8_t x, uint8_t y, char c);
void glcd_draw_string(uint8_t x, uint8_t y, char *c);
void glcd_draw_string_P(uint8_t x, uint8_t y, const char *str);
void glcd_draw_string_ammend(uint8_t x, uint8_t top, uint8_t down, char *str);
void glcd_draw_string_ammend_P(const char *str);
void glcd_draw_invert_line(uint8_t line);
#endif //_GLCD_TEXT_NEW_
