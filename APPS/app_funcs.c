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
static void app_print_idle(APP_typedef data){
	char *name = (char*)data.cur_efx.fv1->name;
	int number = data.cur_efx.number;

	uint16_t vol[VOL_MAX];
	vol[VOL_A] = app_data.cur_efx.volume[VOL_A];
	vol[VOL_B] = app_data.cur_efx.volume[VOL_B];
	vol[VOL_C] = app_data.cur_efx.volume[VOL_C];

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

	//print the volumes in number
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

}

static void app_print_vol(APP_typedef data){
	char *name = (char*)app_data.cur_efx.fv1->name;
		int number = app_data.cur_efx.number;

		/*uint16_t vol[VOL_MAX];
		vol[VOL_A] = app_data.cur_efx.volume[VOL_A];
		vol[VOL_B] = app_data.cur_efx.volume[VOL_B];
		vol[VOL_C] = app_data.cur_efx.volume[VOL_C];
	*/
	//clear and draw border
		app_draw_frame();

		//print the name of efx
		//Change font
		glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);
		glcd_draw_string(10,15, name);

		//print the number of efx and inert it
		//Change font
		glcd_set_font_c(FC_Liberation_Sans11x14_Numbers);
		sprintf(str, "%d", number);
		glcd_draw_string(88, 10, str);
		glcd_invert_area(87, 10, 30, 18);

		//Change font
		glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);

		glcd_draw_string(10,30, "volA");
		if(app_data.vol_last_name == VOL_A ){
			app_data.vol_last_name = VOL_MAX;
			app_data.cur_efx.volume[VOL_A] = app_data.vol_last_val;
			glcd_bar_graph_horizontal(40, 30, 70, 7, (app_data.vol_last_val >> 4));
		}else{
			sprintf(str, "%d", app_data.cur_efx.volume[VOL_A]>>6);//*vol_factor_persent);
			glcd_draw_string(40, 30, str);
		}

		glcd_draw_string(10,40, "volB");
		if(app_data.vol_last_name == VOL_B){
			app_data.vol_last_name = VOL_MAX;
			app_data.cur_efx.volume[VOL_B] = app_data.vol_last_val;
			glcd_bar_graph_horizontal(40, 40, 70, 7, (app_data.vol_last_val >> 4));
		}else{
			sprintf(str, "%d", app_data.cur_efx.volume[VOL_B]>>6);//*vol_factor_persent);
			glcd_draw_string(40, 40, str);
		}

		glcd_draw_string(10,50, "volC");
		if(app_data.vol_last_name == VOL_C){
			app_data.vol_last_name = VOL_MAX;
			app_data.cur_efx.volume[VOL_C] = app_data.vol_last_val;
			glcd_bar_graph_horizontal(40, 50, 70, 7, (app_data.vol_last_val >> 4));
		}else{
			sprintf(str, "%d", app_data.cur_efx.volume[VOL_C]>>6);//*vol_factor_persent);
			glcd_draw_string(40, 50, str);
		}


		glcd_write();
}


static void app_print_enc(APP_typedef data){
	static efx_node_t *node = NULL;
	  HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);

	if (data.event.enc->dir == ENC_DIR_CCW)
		node = efx_next_node();

	else if (data.event.enc->dir == ENC_DIR_CW)
		node = efx_prev_node();

	if (node == NULL)
			return;

	data.cur_efx = *node;
	app_print_idle(data);

}

void Enter_S_SET(void){
	//print_on_screen("Enter_S_IDLE");
}
void Enter_S_IDLE(void){
	//print_on_screen("Enter_S_IDLE");
}
void Enter_S_ENC(void){

	//print_on_screen("Enter_S_ENC");
}
void Enter_S_VOL(void){
	//print_on_screen("Enter_S_VOL");
}
void Enter_S_SLEEP(void){
	//print_on_screen("Enter_S_SLEEP");
}
void Enter_S_BYPASS(void){
	//print_on_screen("Enter_S_BYPASS");
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

	app_print_idle(app_data);
}
void Do_S_ENC(void){
	if(app_data.state_changed == 1){
		app_data.state_changed = 0;
		app_print_enc(app_data);

	}
	//print_on_screen("Do_S_ENC");
}
//#define vol_factor_persent	((float)((float)100/(float)4096))
void Do_S_VOL(void){
	app_print_vol(app_data);
}
void Do_S_SLEEP(void){
	print_on_screen("Do_S_SLEEP");
}
void Do_S_BYPASS(void){
	//Do_S_IDLE();
	print_on_screen("Do_S_BYPASS");
}














