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
/*
 * adc to graph calculator:
 * 	4096	255
 * 	ADC		 X = (ADC * 255) / 4096
 * 	so:	X = ADC * 0.062255859
 * 	*/
#define ADC_TO_GRAPH(ADC)	(ADC * 0.062255859 + 1)

void app_print_on_screen(char* msg){
	glcd_clear_buffer();
	glcd_set_font_c(FC_Tahoma11x13_AlphaNumber);
	glcd_draw_string(10, 20, msg);
	glcd_write();
	HAL_Delay(2000);
}

void app_update_vols_from_raw(APP_typedef *data){

	data->cur_efx.volume[VOL_A] = vol_get_raw(VOL_A);
	data->cur_efx.volume[VOL_B] = vol_get_raw(VOL_B);
	data->cur_efx.volume[VOL_C] = vol_get_raw(VOL_C);
}

void app_update_node_tmp_vols_from_raw(APP_typedef *data){

	data->node_tmp->volume[VOL_A] = vol_get_raw(VOL_A);
	data->node_tmp->volume[VOL_B] = vol_get_raw(VOL_B);
	data->node_tmp->volume[VOL_C] = vol_get_raw(VOL_C);
}


static void app_draw_empty_frame(void){
	int x = 0;
	int y = 0;
	int tx = 2;
	int ty = 2;
	int w = 128;
	int h = 64;

	glcd_clear_buffer();
	glcd_draw_rect_thick(x, y, w, h, tx, ty, BLACK);
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

static void app_set_preset_efx(APP_typedef *data){


	(data->cur_efx) = *(data->node_tmp);

}
#define HORIZ_SIZE_A	60

#define POSITION_X_VOLA_B_C_NAME	10
#define POSITION_X_VOLA_B_C_VAL		55

#define POSITION_Y_VOLA_NAME	25
#define POSITION_Y_VOLB_NAME	38
#define POSITION_Y_VOLC_NAME	51



static void app_print_2_vols_enc(efx_node_t *efx){
#if 1


	glcd_draw_string(POSITION_X_VOLA_B_C_NAME, POSITION_Y_VOLA_NAME, (char*)efx->fv1->volA_name);
	sprintf(str, "%d", (uint16_t)ADC_TO_PERSENT(efx->volume[VOL_A]));//*vol_factor_persent);
	glcd_draw_string(POSITION_X_VOLA_B_C_VAL, POSITION_Y_VOLA_NAME, str);

	glcd_draw_string(POSITION_X_VOLA_B_C_NAME, POSITION_Y_VOLB_NAME, (char*)efx->fv1->volB_name);
	sprintf(str, "%d", (uint16_t)ADC_TO_PERSENT(efx->volume[VOL_B]));//*vol_factor_persent);
	glcd_draw_string(POSITION_X_VOLA_B_C_VAL, POSITION_Y_VOLB_NAME, str);
#endif

#if 0
	glcd_bar_graph_horizontal(10, 30, HORIZ_SIZE_A, 5, ADC_TO_GRAPH(efx->volume[VOL_A]));
	glcd_bar_graph_horizontal(10, 40, HORIZ_SIZE_A, 5, ADC_TO_GRAPH(efx->volume[VOL_B]));


#endif

#if 0

	glcd_bar_graph_horizontal_no_border(10, 30, HORIZ_SIZE_A, 5, ADC_TO_GRAPH(efx->volume[VOL_A]));
	glcd_bar_graph_horizontal_no_border(10, 40, HORIZ_SIZE_A, 5, ADC_TO_GRAPH(efx->volume[VOL_B]));


#endif

}

static void app_print_3_vols_enc(efx_node_t *efx){
#if 1

	glcd_draw_string(POSITION_X_VOLA_B_C_NAME, POSITION_Y_VOLA_NAME, (char*)efx->fv1->volA_name);
	sprintf(str, "%d", (uint16_t)ADC_TO_PERSENT(efx->volume[VOL_A]));//*vol_factor_persent);
	glcd_draw_string(POSITION_X_VOLA_B_C_VAL, POSITION_Y_VOLA_NAME, str);


	glcd_draw_string(POSITION_X_VOLA_B_C_NAME, POSITION_Y_VOLB_NAME, (char*)efx->fv1->volB_name);
	sprintf(str, "%d", (uint16_t)ADC_TO_PERSENT(efx->volume[VOL_B]));//*vol_factor_persent);
	glcd_draw_string(POSITION_X_VOLA_B_C_VAL, POSITION_Y_VOLB_NAME, str);


	glcd_draw_string(POSITION_X_VOLA_B_C_NAME, POSITION_Y_VOLC_NAME, (char*)efx->fv1->volC_name);
	sprintf(str, "%d", (uint16_t)ADC_TO_PERSENT(efx->volume[VOL_C]));//*vol_factor_persent);
	glcd_draw_string(POSITION_X_VOLA_B_C_VAL, POSITION_Y_VOLC_NAME, str);
#endif

#if 0
	glcd_bar_graph_horizontal(10, 30, HORIZ_SIZE_A, 5, ADC_TO_GRAPH(efx->volume[VOL_A]));
	glcd_bar_graph_horizontal(10, 40, HORIZ_SIZE_A, 5, ADC_TO_GRAPH(efx->volume[VOL_B]));
	glcd_bar_graph_horizontal(10, 50, HORIZ_SIZE_A, 5, ADC_TO_GRAPH(efx->volume[VOL_C]));


#endif

#if 0

	glcd_bar_graph_horizontal_no_border(10, 30, HORIZ_SIZE_A, 5, ADC_TO_GRAPH(efx->volume[VOL_A]));
	glcd_bar_graph_horizontal_no_border(10, 40, HORIZ_SIZE_A, 5, ADC_TO_GRAPH(efx->volume[VOL_B]));
	glcd_bar_graph_horizontal_no_border(10, 50, HORIZ_SIZE_A, 5, ADC_TO_GRAPH(efx->volume[VOL_C]));

#endif
}
#define SPRINTF_FORMAT_NUMBERS	"%.2d"
static void app_print_2_vols_idle(efx_node_t *efx){
#if 1


	glcd_draw_string(POSITION_X_VOLA_B_C_NAME, POSITION_Y_VOLA_NAME, (char*)efx->fv1->volA_name);
	sprintf(str, SPRINTF_FORMAT_NUMBERS, (uint16_t)ADC_TO_PERSENT(efx->volume[VOL_A]));//*vol_factor_persent);
	glcd_draw_string(POSITION_X_VOLA_B_C_VAL, POSITION_Y_VOLA_NAME, str);

	glcd_draw_string(POSITION_X_VOLA_B_C_NAME, POSITION_Y_VOLB_NAME, (char*)efx->fv1->volB_name);
	sprintf(str, SPRINTF_FORMAT_NUMBERS, (uint16_t)ADC_TO_PERSENT(efx->volume[VOL_B]));//*vol_factor_persent);
	glcd_draw_string(POSITION_X_VOLA_B_C_VAL, POSITION_Y_VOLB_NAME, str);

#else
	glcd_bar_graph_horizontal(10, 30, 20, 5, ADC_TO_GRAPH(efx->volume[VOL_A]));
	glcd_bar_graph_horizontal(10, 40, 20, 5, ADC_TO_GRAPH(efx->volume[VOL_B]));


#endif


}

static void app_print_3_vols_idle(efx_node_t *efx){
#if 1
	glcd_draw_string(POSITION_X_VOLA_B_C_NAME, POSITION_Y_VOLA_NAME, (char*)efx->fv1->volA_name);
	sprintf(str, "%d", (uint16_t)ADC_TO_PERSENT(efx->volume[VOL_A]));//*vol_factor_persent);
	glcd_draw_string(POSITION_X_VOLA_B_C_VAL, POSITION_Y_VOLA_NAME, str);


	glcd_draw_string(POSITION_X_VOLA_B_C_NAME, POSITION_Y_VOLB_NAME, (char*)efx->fv1->volB_name);
	sprintf(str, "%d", (uint16_t)ADC_TO_PERSENT(efx->volume[VOL_B]));//*vol_factor_persent);
	glcd_draw_string(POSITION_X_VOLA_B_C_VAL, POSITION_Y_VOLB_NAME, str);


	glcd_draw_string(POSITION_X_VOLA_B_C_NAME, POSITION_Y_VOLC_NAME, (char*)efx->fv1->volC_name);
	sprintf(str, "%d", (uint16_t)ADC_TO_PERSENT(efx->volume[VOL_C]));//*vol_factor_persent);
	glcd_draw_string(POSITION_X_VOLA_B_C_VAL, POSITION_Y_VOLC_NAME, str);
#else
	glcd_bar_graph_horizontal(10, 30, 20, 5, ADC_TO_GRAPH(efx->volume[VOL_A]));
	glcd_bar_graph_horizontal(10, 40, 20, 5, ADC_TO_GRAPH(efx->volume[VOL_B]));
	glcd_bar_graph_horizontal(10, 50, 20, 5, ADC_TO_GRAPH(efx->volume[VOL_C]));


#endif
}


static void app_print_2_vols_graph(APP_typedef *data){

	glcd_draw_string(10,30, (char*)data->cur_efx.fv1->volA_name);
	if(data->vol_last_name == VOL_A ){
		//app_data.vol_last_name = VOL_MAX;
		//data->cur_efx.volume[VOL_A] = ADC_TO_PERSENT(data->vol_last_val);
		glcd_bar_graph_horizontal(47, 30, 70, 5, ADC_TO_GRAPH(data->cur_efx.volume[VOL_A]));
	}else{
		sprintf(str, "%d", (uint16_t)ADC_TO_PERSENT(data->cur_efx.volume[VOL_A]));//*vol_factor_persent);
		glcd_draw_string(47, 30, str);
	}

	glcd_draw_string(10,40, (char*)data->cur_efx.fv1->volB_name);
	if(data->vol_last_name == VOL_B){
		//app_data.vol_last_name = VOL_MAX;
		//data->cur_efx.volume[VOL_B] = ADC_TO_PERSENT(data->vol_last_val);
		glcd_bar_graph_horizontal(47, 40, 70, 5, ADC_TO_GRAPH(data->cur_efx.volume[VOL_B]));
	}else{
		sprintf(str, "%d", (uint16_t)ADC_TO_PERSENT(data->cur_efx.volume[VOL_B]));//*vol_factor_persent);
		glcd_draw_string(47, 40, str);
	}

}

static void app_print_3_vols_graph(APP_typedef *data){

	glcd_draw_string(10,30, (char*)data->cur_efx.fv1->volA_name);
	if(data->vol_last_name == VOL_A ){
		//app_data.vol_last_name = VOL_MAX;
		//data->cur_efx.volume[VOL_A] = ADC_TO_PERSENT(data->vol_last_val);
		glcd_bar_graph_horizontal(47, 30, 70, 5, ADC_TO_GRAPH(data->cur_efx.volume[VOL_A]));
	}else{
		sprintf(str, "%d", (uint16_t)ADC_TO_PERSENT(data->cur_efx.volume[VOL_A]));//*vol_factor_persent);
		glcd_draw_string(47, 30, str);
	}

	glcd_draw_string(10,40, (char*)data->cur_efx.fv1->volB_name);
	if(data->vol_last_name == VOL_B){
		//app_data.vol_last_name = VOL_MAX;
		//data->cur_efx.volume[VOL_B] = ADC_TO_PERSENT(data->vol_last_val);
		glcd_bar_graph_horizontal(47, 40, 70, 5, ADC_TO_GRAPH(data->cur_efx.volume[VOL_B]));
	}else{
		sprintf(str, "%d", (uint16_t)ADC_TO_PERSENT(data->cur_efx.volume[VOL_B]));//*vol_factor_persent);
		glcd_draw_string(47, 40, str);
	}

	glcd_draw_string(10,50, (char*)data->cur_efx.fv1->volC_name);
	if(data->vol_last_name == VOL_C){
		//app_data.vol_last_name = VOL_MAX;
		//data->cur_efx.volume[VOL_C] = ADC_TO_PERSENT(data->vol_last_val);
		glcd_bar_graph_horizontal(47, 50, 70, 5, ADC_TO_GRAPH(data->cur_efx.volume[VOL_C]));
	}else{
		sprintf(str, "%d", (uint16_t)ADC_TO_PERSENT(data->cur_efx.volume[VOL_C]));//*vol_factor_persent);
		glcd_draw_string(47, 50, str);
	}
}

static void app_print_clear_vols_box(void){
	glcd_draw_rect_fill(10, 30, 50, 20, 0);
}

static void app_print_efx_vols_enc(APP_typedef *data){
	glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);
	app_print_clear_vols_box();

	if(data->node_tmp->mode == EFX_MODE_PRESET)
		app_update_node_tmp_vols_from_raw(data);

	//glcd_draw_rect(7, 28, 67, 30, 1);
	if(data->node_tmp->fv1->vol_nums == 2){
		app_print_2_vols_enc(data->node_tmp);
	}else if(data->node_tmp->fv1->vol_nums == 3){
		app_print_3_vols_enc(data->node_tmp);

	}
}


/*used in the idle state*/
static void app_print_efx_vols_idle(APP_typedef *data){
#if 0

	uint16_t vol[VOL_MAX];
	/*
	 * TODO:
	 * 	this if else is bullshit
	 * 	we need if we lunch preset efx -> load volus from adc
	 * 	and if we set the user efx -> load volus from eep*/
	if(data->cur_efx.mode == EFX_MODE_PRESET){
		/*load volume from adcs*/
		vol[VOL_A] = ADC_TO_PERSENT(data->cur_efx.volume[VOL_A]);
		vol[VOL_B] = ADC_TO_PERSENT(data->cur_efx.volume[VOL_B]);
		vol[VOL_C] = ADC_TO_PERSENT(data->cur_efx.volume[VOL_C]);

	}else{
		/*load volumes from memory*/
		vol[VOL_A] = data->cur_efx.volume[VOL_A];
		vol[VOL_B] = data->cur_efx.volume[VOL_B];
		vol[VOL_C] = data->cur_efx.volume[VOL_C];
	}

	vol[VOL_A] = ADC_TO_PERSENT(data->cur_efx.volume[VOL_A]);
	vol[VOL_B] = ADC_TO_PERSENT(data->cur_efx.volume[VOL_B]);
	vol[VOL_C] = ADC_TO_PERSENT(data->cur_efx.volume[VOL_C]);
#endif


	glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);

	if(data->cur_efx.fv1->vol_nums == 2){
		app_print_2_vols_idle(&data->cur_efx);
	}else if(data->cur_efx.fv1->vol_nums == 3){
		app_print_3_vols_idle(&data->cur_efx);

	}
#if 0
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
#endif

}

static void app_print_efx_name_number_small(APP_typedef *data){
	//char *name = (char*)data->cur_efx.fv1->name;
	int number = data->cur_efx.number;

	//print the name of efx
	//glcd_set_font_c(FC_Tahoma11x13_AlphaNumber);
	//glcd_draw_string(18, 9, name);

	//print the number of efx and inert it
	glcd_set_font_c(FC_Liberation_Sans11x14_Numbers);
	sprintf(str, "%.2d", number);
	glcd_draw_string(57, 6, str);
	glcd_invert_area(54, 6, 27, 18);

}

static void app_print_vol_graph(APP_typedef *data){

	app_draw_empty_frame();
	app_print_efx_name_number_small(data);


	glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);

	if(data->cur_efx.fv1->vol_nums == 2){
		app_print_2_vols_graph(data);
	}else if(data->cur_efx.fv1->vol_nums == 3){
		app_print_3_vols_graph(data);

	}

#if 0

	//Change font
	glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);

	glcd_draw_string(10,30, (char*)data->cur_efx.fv1->volA_name);
	if(data->vol_last_name == VOL_A ){
		//app_data.vol_last_name = VOL_MAX;
		//data->cur_efx.volume[VOL_A] = ADC_TO_PERSENT(data->vol_last_val);
		glcd_bar_graph_horizontal(40, 30, 70, 5, ADC_TO_GRAPH(data->cur_efx.volume[VOL_A]));
	}else{
		sprintf(str, "%d", (uint16_t)ADC_TO_PERSENT(data->cur_efx.volume[VOL_A]));//*vol_factor_persent);
		glcd_draw_string(40, 30, str);
	}

	glcd_draw_string(10,40, (char*)data->cur_efx.fv1->volB_name);
	if(data->vol_last_name == VOL_B){
		//app_data.vol_last_name = VOL_MAX;
		//data->cur_efx.volume[VOL_B] = ADC_TO_PERSENT(data->vol_last_val);
		glcd_bar_graph_horizontal(40, 40, 70, 5, ADC_TO_GRAPH(data->cur_efx.volume[VOL_B]));
	}else{
		sprintf(str, "%d", (uint16_t)ADC_TO_PERSENT(data->cur_efx.volume[VOL_B]));//*vol_factor_persent);
		glcd_draw_string(40, 40, str);
	}

	glcd_draw_string(10,50, (char*)data->cur_efx.fv1->volC_name);
	if(data->vol_last_name == VOL_C){
		//app_data.vol_last_name = VOL_MAX;
		//data->cur_efx.volume[VOL_C] = ADC_TO_PERSENT(data->vol_last_val);
		glcd_bar_graph_horizontal(40, 50, 70, 5, ADC_TO_GRAPH(data->cur_efx.volume[VOL_C]));
	}else{
		sprintf(str, "%d", (uint16_t)ADC_TO_PERSENT(data->cur_efx.volume[VOL_C]));//*vol_factor_persent);
		glcd_draw_string(40, 50, str);
	}

#endif

	glcd_write();
}

static void app_print_efx_number_blink(efx_node_t *efx){
	char *name = (char*)efx->fv1->name;
	int number = efx->number;
	sprintf(str, "%.2d", number);
	glcd_set_font_c(FC_Tahoma11x13_AlphaNumber);
	glcd_draw_string(7, 7, name);
	if((app_data.blink)<5){
		app_data.blink += 1;
		glcd_set_font_c(FC_Bebas_Neue18x36_Numbers);
		glcd_draw_string(80, 23, str);


		//glcd_draw_circle_fill(120, 10, 3, 1);

	}else if(app_data.blink<10){
		app_data.blink += 1;
		glcd_draw_rect_fill(79, 22, 10, 10, 0);
		//glcd_draw_rect_fill(6, 6, 100, 10, 0);
	}else{
		app_data.blink = 0;

	}
	//print the name of efx
	//glcd_set_font_c(FC_Tahoma11x13_AlphaNumber);
	//glcd_draw_string(7, 7, name);

	//print the number of efx and inert it

	//glcd_invert_area(75, 31, 40, 26);

}

static void app_print_efx_name_number_big(efx_node_t *efx){
	char *name = (char*)efx->fv1->name;
	int number = efx->number;

	//print the name of efx
	glcd_set_font_c(FC_Tahoma11x13_AlphaNumber);
	glcd_draw_string(7, 7, name);

	//print the number of efx and inert it
	glcd_set_font_c(FC_Bebas_Neue18x36_Numbers);
	sprintf(str, "%.2d", number);
	glcd_draw_string(80, 23, str);
	//glcd_invert_area(75, 31, 40, 26);

}

static void app_print_update_msg(APP_typedef *data){

	glcd_set_font_c(FC_Tekton_Pro_Ext27x28_AlphaNumber);
	glcd_draw_string(25, 20, "SET");
	glcd_invert_area(23, 17, 87, 26);
}
static void app_print_save_msg(APP_typedef *data){

	glcd_set_font_c(FC_Tekton_Pro_Ext27x28_AlphaNumber);
	glcd_draw_string(25, 20, "SAVE");
	glcd_invert_area(23, 17, 87, 26);
}


static void app_print_idle(APP_typedef *data){


	//clear and draw border
	app_draw_empty_frame();

	//print efx names and number on the screen
	app_print_efx_name_number_big(&data->cur_efx);

	app_update_vols_from_raw(data);
	app_print_efx_vols_idle(data);
	//glcd_draw_string(10,40, "hey you");

	glcd_write();

}
static void app_print_vol_numbers(APP_typedef *data){
	uint16_t vol[VOL_MAX];
	if(data->cur_efx.mode == EFX_MODE_PRESET){
		/*load volume from adcs*/
		vol[VOL_A] = ADC_TO_PERSENT(data->cur_efx.volume[VOL_A]);
		vol[VOL_B] = ADC_TO_PERSENT(data->cur_efx.volume[VOL_B]);
		vol[VOL_C] = ADC_TO_PERSENT(data->cur_efx.volume[VOL_C]);

	}else{
		/*load volumes from memory*/
		vol[VOL_A] = data->cur_efx.volume[VOL_A];
		vol[VOL_B] = data->cur_efx.volume[VOL_B];
		vol[VOL_C] = data->cur_efx.volume[VOL_C];
	}

	//print the volumes in number
	glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);

	//we have 2 volumes
	if(data->cur_efx.fv1->vol_nums == 2){

		glcd_draw_string(8,30, (char*)data->cur_efx.fv1->volA_name);
		sprintf(str, "%.2d", vol[VOL_A]);
		glcd_draw_string(55, 30, str);

		glcd_draw_string(8,50, (char*)data->cur_efx.fv1->volB_name);
		sprintf(str, "%.2d", vol[VOL_B]);
		glcd_draw_string(55, 50, str);

	//we have 3 volumes
	}else if(data->cur_efx.fv1->vol_nums == 3){
		glcd_draw_string(8,30, (char*)data->cur_efx.fv1->volA_name);
		sprintf(str, "%.2d", vol[VOL_A]);
		glcd_draw_string(55, 30, str);

		glcd_draw_string(8,40, (char*)data->cur_efx.fv1->volB_name);
		sprintf(str, "%.2d", vol[VOL_B]);
		glcd_draw_string(55, 40, str);

		glcd_draw_string(8,50, (char*)data->cur_efx.fv1->volC_name);
		sprintf(str, "%.2d", vol[VOL_C]);
		glcd_draw_string(55, 50, str);
	}





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

		//app_print_efx_vols(data);

		//Change font
		glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);

		glcd_draw_string(10,30, "volA");
		if(data->vol_last_name == VOL_A ){
			//app_data.vol_last_name = VOL_MAX;
			data->cur_efx.volume[VOL_A] = data->vol_last_val;
			glcd_bar_graph_horizontal(40, 30, 70, 5, (data->vol_last_val >> 4));
		}else{
			sprintf(str, "%d", data->cur_efx.volume[VOL_A]>>6);//*vol_factor_persent);
			glcd_draw_string(40, 30, str);
		}

		glcd_draw_string(10,40, "volB");
		if(data->vol_last_name == VOL_B){
			//app_data.vol_last_name = VOL_MAX;
			data->cur_efx.volume[VOL_B] = data->vol_last_val;
			glcd_bar_graph_horizontal(40, 40, 70, 5, (data->vol_last_val >> 4));
		}else{
			sprintf(str, "%d", data->cur_efx.volume[VOL_B]>>6);//*vol_factor_persent);
			glcd_draw_string(40, 40, str);
		}

		glcd_draw_string(10,50, "volC");
		if(data->vol_last_name == VOL_C){
			//app_data.vol_last_name = VOL_MAX;
			data->cur_efx.volume[VOL_C] = data->vol_last_val;
			glcd_bar_graph_horizontal(40, 50, 70, 5, (data->vol_last_val >> 4));
		}else{
			sprintf(str, "%d", data->cur_efx.volume[VOL_C]>>6);//*vol_factor_persent);
			glcd_draw_string(40, 50, str);
		}


		glcd_write();
}


static void app_print_enc(APP_typedef *data){
	//static efx_node_t *node = NULL;
	 // HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);

	data->node_tmp = NULL;
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

#if ON_ENTER_ENABLED
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
#endif

/*
 * functions run on every single time the state-machine kicked
 *
 */

void Do_S_SET(void){
	/*
	 * TODO:
	 * 	vaqti dakhel state set mishim chand massale hast:
	 * 		age state qabli enc ya vol bashe va enter ro zade bashe mikhad update kone
	 * 		age idle bashe va enter ro save mikhad kone
	 * 		taggrat ro bayad eslah konim
	 * 		*/

	switch (app_data.cur_event) {
		case E_BTN_ENTER:
			switch (app_data.pre_state) {
				case S_VOL:
					app_update_preset_efx(&app_data);
					app_data.select = 1;
					break;
				case S_ENC:
					app_set_preset_efx(&app_data);
					app_data.select = 2;

					break;
				case S_IDLE:
					/*change the */
					if(app_data.cur_efx.mode == EFX_MODE_PRESET){
						/* make a new efx and save it and set it. EFX_MODE_PRESET*/
						app_add_new_efx_to_ring(&app_data);
						app_data.select = 3;


					}else{
						/* update the efx and set it. EFX_MODE_USER*/
						app_update_preset_efx(&app_data);
						app_data.select = 1;

					}
					break;
				default:
					break;
			}
			//app_draw_empty_frame();
			//app_print_save_msg(&app_data);
			//glcd_write();
			break;
		case E_NOT:
			//if(app_data.pre_state != app_data.cur_state){
			//clear and draw border
			switch (app_data.select) {
				case 0:

					break;
				case 1:
					app_draw_empty_frame();
					app_print_update_msg(&app_data);
					glcd_write();
					break;
				case 2:
					app_draw_empty_frame();
					app_print_update_msg(&app_data);
					glcd_write();
					break;
				case 3:
					app_draw_empty_frame();
					app_print_save_msg(&app_data);
					glcd_write();
					break;


			}
			break;


		default:
			break;
	}
}


void Do_S_IDLE(void){

	//clear and draw border
		app_draw_empty_frame();

		//print efx names and number on the screen
		app_print_efx_name_number_big(&(app_data.cur_efx));

		app_update_vols_from_raw(&app_data);
		app_print_efx_vols_idle(&app_data);
		//glcd_draw_string(10,40, "hey you");

		glcd_write();
	//app_print_idle(&app_data);

}




void Do_S_ENC(void){
	if(app_data.state_changed == 1){
		app_data.state_changed = 0;
		//app_print_enc(&app_data);
		app_data.node_tmp = NULL;
			if (app_data.event.enc->dir == ENC_DIR_CCW)
				app_data.node_tmp = efx_next_node();

			else if (app_data.event.enc->dir == ENC_DIR_CW)
				app_data.node_tmp = efx_prev_node();

			if (app_data.node_tmp == NULL)
					return;
			//app_data.cur_efx = *(app_data.node_tmp);


	}
	//clear and draw border
		app_draw_empty_frame();

		//print efx names and number on the screen
		app_print_efx_number_blink(app_data.node_tmp);

		app_print_efx_vols_enc(&app_data);

		//glcd_draw_string(47, 40, (char*)app_data.node_tmp->fv1->volA_name);

	//glcd_draw_circle_fill(80, 10, 3, 1);
	glcd_write();



	//strcpy(&(data.cur_efx), (data.node_tmp));
	//print_on_screen("Do_S_ENC");
}
//#define vol_factor_persent	((float)((float)100/(float)4096))
void Do_S_VOL(void){
	app_print_vol_graph(&app_data);
}

void Do_S_SLEEP(void){
	app_print_on_screen("Do_S_SLEEP");
}
void Do_S_BYPASS(void){
	//Do_S_IDLE();
	app_print_on_screen("Do_S_BYPASS");
}














