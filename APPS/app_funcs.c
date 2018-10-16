/*
 * app_funcs.c
 *
 *  Created on: Oct 13, 2018
 *      Author: sam
 */

#include "string.h"
#include "app.h"
char str[20];

/*
 * adc to percent calculator:
 * 	4096	100
 * 	ADC		 X = (ADC * 100) / 4096
 * 	so:	X = ADC * 0.024414062
 * 	*/
#define ADC_TO_PERSENT(ADC)	(ADC * 0.024414062 + 1)

void app_print_on_screen(char* msg){
	glcd_clear_buffer();
	glcd_set_font_c(FC_Tahoma11x13_AlphaNumber);
	glcd_draw_string(10, 20, msg);
	glcd_write();
	HAL_Delay(2000);
}


static void app_draw_empty_frame(void){
	int x = 0;
	int y = 0;
	int w = 128;
	int h = 64;

	glcd_clear_buffer();
	glcd_draw_rect(x, y, w, h,BLACK);
}

static void app_update_efx(APP_typedef *data, efx_node_t *efx){
	data->cur_efx = *efx;
}


static void app_add_new_efx_to_ring(APP_typedef *data){

	size_t number = efx_get_list_size() + 1;
	efx_fv1_preset pst = (efx_fv1_preset)((uint8_t)data->cur_efx.number-1);
	uint16_t vol[VOL_MAX];
	vol[VOL_A] = data->cur_efx.volume[VOL_A];
	vol[VOL_B] = data->cur_efx.volume[VOL_B];
	vol[VOL_C] = data->cur_efx.volume[VOL_C];


	efx_node_t *efx = efx_create_fv1_node(number, EFX_MODE_USER, pst, vol[0], vol[1], vol[2]);
	efx_push_effect(efx);
	app_update_efx(&app_data, efx);
	enc_set_val(app_data.cur_efx.number+1);
}

static void app_update_preset_efx(APP_typedef *data){


	uint16_t vol[VOL_MAX];
	vol[VOL_A] = data->cur_efx.volume[VOL_A];
	vol[VOL_B] = data->cur_efx.volume[VOL_B];
	vol[VOL_C] = data->cur_efx.volume[VOL_C];
	efx_set_vols(&(data->cur_efx), vol);

}

static void app_print_efx_name_number_big(APP_typedef *data){
	char *name = (char*)data->cur_efx.fv1->name;
	int number = data->cur_efx.number;

	//print the name of efx
	glcd_set_font_c(FC_Tahoma11x13_AlphaNumber);
	glcd_draw_string(7, 5, name);

	//print the number of efx and inert it
	glcd_set_font_c(FC_Liberation_Sans15x21_Numbers);
	sprintf(str, "%.2d", number);
	glcd_draw_string(80, 33, str);
	//glcd_invert_area(75, 31, 40, 26);

}

static void app_print_efx_name_number_small(APP_typedef *data){
	char *name = (char*)data->cur_efx.fv1->name;
	int number = data->cur_efx.number;

	//print the name of efx
	glcd_set_font_c(FC_Tahoma11x13_AlphaNumber);
	glcd_draw_string(18, 9, name);

	//print the number of efx and inert it
	glcd_set_font_c(FC_Liberation_Sans15x21_Numbers);
	sprintf(str, "%.2d", number);
	glcd_draw_string(80, 4, str);
	glcd_invert_area(78, 4, 33, 22);

}

static void app_print_save_msg(APP_typedef *data){

	glcd_set_font_c(FC_Tekton_Pro_Ext27x28_AlphaNumber);
	glcd_draw_string(25, 20, "SAVE");
	glcd_invert_area(23, 17, 87, 26);
}

static void app_print_efx_vols(APP_typedef *data){
	uint16_t vol[VOL_MAX];
	vol[VOL_A] = ADC_TO_PERSENT(data->cur_efx.volume[VOL_A]);
	vol[VOL_B] = ADC_TO_PERSENT(data->cur_efx.volume[VOL_B]);
	vol[VOL_C] = ADC_TO_PERSENT(data->cur_efx.volume[VOL_C]);

	//print the volumes in number
	glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);
	glcd_draw_string(8,30, "REPEAT");
	sprintf(str, "%.2d", vol[VOL_A]);
	glcd_draw_string(55, 30, str);

	glcd_draw_string(8,40, "TIME");
	sprintf(str, "%.2d", vol[VOL_B]);
	glcd_draw_string(55, 40, str);

	glcd_draw_string(8,50, "REVERB");
	sprintf(str, "%.2d", vol[VOL_C]);
	glcd_draw_string(55, 50, str);


}
static void app_print_idle(APP_typedef *data){


	//clear and draw border
	app_draw_empty_frame();

	//print efx names and number on the screen
	app_print_efx_name_number_big(data);

	app_print_efx_vols(data);

	glcd_write();

}

static void app_print_vol(APP_typedef *data){

		/*uint16_t vol[VOL_MAX];
		vol[VOL_A] = app_data.cur_efx.volume[VOL_A];
		vol[VOL_B] = app_data.cur_efx.volume[VOL_B];
		vol[VOL_C] = app_data.cur_efx.volume[VOL_C];
	*/
	//clear and draw border
		app_draw_empty_frame();
		app_print_efx_name_number_small(data);

		app_print_efx_vols(data);

		//Change font
		glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);

		glcd_draw_string(10,30, "volA");
		if(data->vol_last_name == VOL_A ){
			//app_data.vol_last_name = VOL_MAX;
			data->cur_efx.volume[VOL_A] = data->vol_last_val;
			glcd_bar_graph_horizontal(40, 30, 70, 7, (data->vol_last_val >> 4));
		}else{
			sprintf(str, "%d", data->cur_efx.volume[VOL_A]>>6);//*vol_factor_persent);
			glcd_draw_string(40, 30, str);
		}

		glcd_draw_string(10,40, "volB");
		if(data->vol_last_name == VOL_B){
			//app_data.vol_last_name = VOL_MAX;
			data->cur_efx.volume[VOL_B] = data->vol_last_val;
			glcd_bar_graph_horizontal(40, 40, 70, 7, (data->vol_last_val >> 4));
		}else{
			sprintf(str, "%d", data->cur_efx.volume[VOL_B]>>6);//*vol_factor_persent);
			glcd_draw_string(40, 40, str);
		}

		glcd_draw_string(10,50, "volC");
		if(data->vol_last_name == VOL_C){
			//app_data.vol_last_name = VOL_MAX;
			data->cur_efx.volume[VOL_C] = data->vol_last_val;
			glcd_bar_graph_horizontal(40, 50, 70, 7, (data->vol_last_val >> 4));
		}else{
			sprintf(str, "%d", data->cur_efx.volume[VOL_C]>>6);//*vol_factor_persent);
			glcd_draw_string(40, 50, str);
		}


		glcd_write();
}


static void app_print_enc(APP_typedef *data){
	//static efx_node_t *node = NULL;
	 // HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);

	if (data->event.enc->dir == ENC_DIR_CCW)
		data->node_tmp = efx_next_node();

	else if (data->event.enc->dir == ENC_DIR_CW)
		data->node_tmp = efx_prev_node();

	if (data->node_tmp == NULL)
			return;

	//strcpy(&(data.cur_efx), (data.node_tmp));
	data->cur_efx = *(data->node_tmp);
	app_print_idle(data);

}
/*
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
*/


void Do_S_SET(void){

	switch (app_data.next_event) {
		case E_BTN_ENTER:
			switch (app_data.cur_efx.mode) {
				case EFX_MODE_USER:
					/*
					 * update the USER PRESET VOLUMES
					 * */
					app_update_preset_efx(&app_data);
					break;

				case EFX_MODE_PRESET:
					/* add new PRESET and add it to the rig and set it
					 * */
					app_add_new_efx_to_ring(&app_data);
					break;
			}
			break;

		case E_NOT:
				//clear and draw border
				app_draw_empty_frame();
				app_print_save_msg(&app_data);
				glcd_write();

			break;

		default:
			break;

	}

#if 0

		switch (app_data.pre_state) {
			case S_ENC:

				break;
			case S_IDLE:
			case S_VOL:
				/*change the */
				if(app_data.cur_efx.mode == EFX_MODE_PRESET){
					/* make a new efx and save it and set it. EFX_MODE_PRESET*/
					app_add_new_efx_to_ring(&app_data);

				}else{
					/* update the efx and set it. EFX_MODE_USER*/
					app_update_preset_efx(&app_data);
				}
				break;
#if STATE_SLEEP_ENABLE
			case S_SLEEP:
				/* recover from sleep or screen saver, do not change fv1 state*/

				break;
#endif

			default:
				break;
		}
#endif

}

void Do_S_IDLE(void){
	app_print_idle(&app_data);
}
void Do_S_ENC(void){
	if(app_data.state_changed == 1){
		app_data.state_changed = 0;
		app_print_enc(&app_data);

	}
	//print_on_screen("Do_S_ENC");
}
//#define vol_factor_persent	((float)((float)100/(float)4096))
void Do_S_VOL(void){
	app_print_vol(&app_data);
}

void Do_S_SLEEP(void){
	app_print_on_screen("Do_S_SLEEP");
}
void Do_S_BYPASS(void){
	//Do_S_IDLE();
	app_print_on_screen("Do_S_BYPASS");
}














