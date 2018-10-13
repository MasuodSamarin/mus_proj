/*
 * app_funcs.c
 *
 *  Created on: Oct 13, 2018
 *      Author: sam
 */


#include "app.h"

void print_on_screen(char* msg){
	glcd_clear_buffer();
	glcd_set_font_c(FC_Tahoma11x13_AlphaNumber);
	glcd_draw_string(10, 20, msg);
	glcd_write();
	HAL_Delay(2000);
}


void Enter_S_SET(void){print_on_screen("Enter_S_SET");};
void Enter_S_IDLE(void){print_on_screen("Enter_S_IDLE");};
void Enter_S_ENC(void){print_on_screen("Enter_S_ENC");};
void Enter_S_VOL(void){print_on_screen("Enter_S_VOL");};
void Enter_S_SLEEP(void){print_on_screen("Enter_S_SLEEP");};
void Enter_S_BYPASS(void){print_on_screen("Enter_S_BYPASS");};



void Do_S_SET(void){print_on_screen("Do_S_SET");};
void Do_S_IDLE(void){print_on_screen("Do_S_IDLE");};
void Do_S_ENC(void){print_on_screen("Do_S_ENC");};
void Do_S_VOL(void){print_on_screen("Do_S_VOL");};
void Do_S_SLEEP(void){print_on_screen("Do_S_SLEEP");};
void Do_S_BYPASS(void){print_on_screen("Do_S_BYPASS");};
