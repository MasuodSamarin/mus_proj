/*
 * app_funcs.c
 *
 *  Created on: Oct 13, 2018
 *      Author: sam
 */


#include "app.h"
char str[20];

void print_on_screen(char* msg){
	glcd_clear_buffer();
	glcd_set_font_c(FC_Tahoma11x13_AlphaNumber);
	glcd_draw_string(10, 20, msg);
	glcd_write();
	HAL_Delay(2000);
}


static void app_draw_frame(void){
	int x = 2;
	int y = 3;
	int w = 126;
	int h = 61;
	int tx = 2;
	int ty = 3;

	glcd_clear_buffer();
	glcd_draw_rect_thick(x, y, w, h, tx, ty, BLACK);
}

static void app_add_new_efx_to_ring(APP_typedef data){

	size_t number = efx_get_list_size() + 1;
	efx_fv1_preset pst = (efx_fv1_preset)((uint8_t)data.cur_efx.number-1);
	uint16_t vol[VOL_MAX];
	vol[VOL_A] = data.cur_efx.volume[VOL_A];
	vol[VOL_B] = data.cur_efx.volume[VOL_B];
	vol[VOL_C] = data.cur_efx.volume[VOL_C];


	efx_node_t *efx = efx_create_fv1_node(number, EFX_MODE_USER, pst, vol[0], vol[1], vol[2]);
	efx_push_effect(efx);
}

static void app_update_efx(APP_typedef data){


	uint16_t vol[VOL_MAX];
	vol[VOL_A] = data.cur_efx.volume[VOL_A];
	vol[VOL_B] = data.cur_efx.volume[VOL_B];
	vol[VOL_C] = data.cur_efx.volume[VOL_C];
	efx_set_vols(&(data.cur_efx), vol);

}

void Enter_S_SET(void){

}

void Enter_S_IDLE(void){
	print_on_screen("Enter_S_IDLE");
}
void Enter_S_ENC(void){
	print_on_screen("Enter_S_ENC");
}
void Enter_S_VOL(void){
	print_on_screen("Enter_S_VOL");
}
void Enter_S_SLEEP(void){
	print_on_screen("Enter_S_SLEEP");
}
void Enter_S_BYPASS(void){
	print_on_screen("Enter_S_BYPASS");
}



void Do_S_SET(void){

		switch (app_data.pre_state) {
			case S_IDLE:
			case S_ENC:
			case S_VOL:
				/*change the */
				if(app_data.cur_efx.mode == EFX_MODE_PRESET){
					/* make a new efx and save it and set it. EFX_MODE_PRESET*/
					//app_add_new_efx_to_ring(app_data);

				}else{
					/* update the efx and set it. EFX_MODE_USER*/
					//app_update_efx(app_data);
				}
				break;

			case S_SLEEP:
				/* recover from sleep or screen saver, do not change fv1 state*/

				break;
			default:
				break;
		}
}

void Do_S_IDLE(void){


	char *name = (char*)app_data.cur_efx.fv1->name;
	int number = app_data.cur_efx.number;

	uint16_t vol[VOL_MAX];
	vol[VOL_A] = 12;//app_data.cur_efx.volume[VOL_A];
	vol[VOL_B] = 34;//app_data.cur_efx.volume[VOL_B];
	vol[VOL_C] = 56;//app_data.cur_efx.volume[VOL_C];

	//clear and draw border
	app_draw_frame();

	//print the name of efx
	glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);
	glcd_draw_string(10,15, name);

	//print the number of efx and inert it
	glcd_set_font_c(FC_Liberation_Sans11x14_Numbers);
	sprintf(str, "%d", number);
	glcd_draw_string(83, 12, str);
	glcd_invert_area(80, 10, 35, 20);

	glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);
	glcd_draw_string(10,30, "volA");
	sprintf(str, "%d", vol[VOL_A]);
	glcd_draw_string(40, 30, str);
	glcd_draw_string(10,40, "volB");
	sprintf(str, "%d", vol[VOL_B]);
	glcd_draw_string(40, 40, str);
	glcd_draw_string(10,50, "volC");
	sprintf(str, "%d", vol[VOL_C]);
	glcd_draw_string(40, 50, str);

	glcd_write();

	//print_on_screen("Do_S_ENC");

}
void Do_S_ENC(void){
	print_on_screen("Do_S_ENC");
}
void Do_S_VOL(void){
	print_on_screen("Do_S_VOL");
}
void Do_S_SLEEP(void){
	print_on_screen("Do_S_SLEEP");
}
void Do_S_BYPASS(void){
	Do_S_IDLE();
	//print_on_screen("Do_S_BYPASS");
}














