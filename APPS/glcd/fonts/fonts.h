#ifndef _FONTS_H_
#define _FONTS_H_
#include "stm32f1xx_hal.h"

//typedef uint8_t (*glcd_draw_char_fp)(uint8_t, uint8_t, char);

/**
 * Font table type
 */
/*
typedef enum {
	STANG,
	MIKRO,
	GLCD_UTILS
} font_table_type_t;
*/

typedef struct {
	const char *font_table;
	uint8_t width;
	uint8_t height;
	char start_char;
	char end_char;

} glcd_FontConfig_t;

extern glcd_FontConfig_t font_current;


#include "fonts/Bebas_Neue18x36_Numbers.h"
#include "fonts/Bebas_Neue20x36_Bold_Numbers.h"
#include "fonts/Liberation_Sans11x14_Numbers.h"
#include "fonts/Liberation_Sans15x21_Numbers.h"
#include "fonts/Liberation_Sans17x17_Alpha.h"
#include "fonts/Liberation_Sans20x28_Numbers.h"
#include "fonts/Liberation_Sans27x36_Numbers.h"

#include "fonts/Font5x8.h"
#include "fonts/Tahoma11x13.h"
#include "fonts/Tekton_Pro_Ext27x28.h"

extern const glcd_FontConfig_t FC_Bebas_Neue18x36_Numbers;
extern const glcd_FontConfig_t FC_Bebas_Neue20x36_Bold_Numbers;
extern const glcd_FontConfig_t FC_Liberation_Sans11x14_Numbers;
extern const glcd_FontConfig_t FC_Liberation_Sans15x21_Numbers;
extern const glcd_FontConfig_t FC_Liberation_Sans17x17__AlphaNumber;
extern const glcd_FontConfig_t FC_Liberation_Sans20x28_Numbers;
extern const glcd_FontConfig_t FC_Liberation_Sans27x36_Numbers;

extern const glcd_FontConfig_t FC_Default_Font_5x8_AlphaNumber;
extern const glcd_FontConfig_t FC_Tahoma11x13_AlphaNumber;
extern const glcd_FontConfig_t FC_Tekton_Pro_Ext27x28_AlphaNumber;

#endif //_FONTS_H_
