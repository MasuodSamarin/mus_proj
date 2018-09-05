#include "fonts/fonts.h"
#include "glcd_text.h"

/*
 * number only fonts
 * */
const glcd_FontConfig_t FC_Bebas_Neue18x36_Numbers = {
		.font_table = Bebas_Neue18x36_Numbers,
		.width = 18,
		.height = 36,
		.start_char = 46,
		.end_char = 57,
};

const glcd_FontConfig_t FC_Bebas_Neue20x36_Bold_Numbers = {
		.font_table = Bebas_Neue20x36_Bold_Numbers,
		.width = 20,
		.height = 36,
		.start_char = 46,
		.end_char = 57,

};

const glcd_FontConfig_t FC_Liberation_Sans11x14_Numbers = {
		.font_table = Liberation_Sans11x14_Numbers,
		.width = 11,
		.height = 14,
		.start_char = 46,
		.end_char = 57,

};
const glcd_FontConfig_t FC_Liberation_Sans15x21_Numbers = {
		.font_table = Liberation_Sans15x21_Numbers,
		.width = 15,
		.height = 21,
		.start_char = 46,
		.end_char = 57,

};

const glcd_FontConfig_t FC_Liberation_Sans20x28_Numbers = {
		.font_table = Liberation_Sans20x28_Numbers,
		.width = 20,
		.height = 28,
		.start_char = 46,
		.end_char = 57,

};
const glcd_FontConfig_t FC_Liberation_Sans27x36_Numbers = {
		.font_table = Liberation_Sans27x36_Numbers,
		.width = 27,
		.height = 36,
		.start_char = 46,
		.end_char = 57,

};

/*
 * alfa-numbers fonts
 * */
const glcd_FontConfig_t FC_Liberation_Sans17x17_Numbers = {
		.font_table = Liberation_Sans15x21_Numbers,
		.width = 17,
		.height = 17,
		.start_char = 46,
		.end_char = 90,
};
const glcd_FontConfig_t FC_Tahoma11x13_AlphaNumber = {
		.font_table = Tahoma11x13,
		.width = 11,
		.height = 13,
		.start_char = 32,
		.end_char = 127,

};

const glcd_FontConfig_t FC_Tekton_Pro_Ext27x28_AlphaNumber = {
		.font_table = Tekton_Pro_Ext27x28,
		.width = 27,
		.height = 28,
		.start_char = 32,
		.end_char = 127,

};

const glcd_FontConfig_t FC_Default_Font_5x8_AlphaNumber = {
		.font_table = Font5x8,
		.width = 5,
		.height = 8,
		.start_char = 32,
		.end_char = 127,

};
