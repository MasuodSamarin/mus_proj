/*
 * encoder.c
 *
 *  Created on: Aug 7, 2018
 *      Author: sam
 */


//#include "encoder.h"
#include "event.h"



/*
 * static variables
 * */
static uint32_t enc_old_val = 0;

void enc_init(void){
	MX_TIM4_Init();
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
	enc_set_span(15);
}

void enc_set_span(uint32_t span){
	__HAL_TIM_SET_AUTORELOAD(&htim4, span);
}

uint32_t enc_get_span(void){
	return(__HAL_TIM_GET_AUTORELOAD(&htim4));
}

void enc_set_val(uint32_t val){
	__HAL_TIM_SET_COUNTER(&htim4, val);
}

uint32_t enc_get_val(void){
	return(__HAL_TIM_GET_COUNTER(&htim4));
}

void enc_process(void){
	int32_t cnt, h_span, delta;
	enc_dir_t dir;

	cnt = enc_get_val();
	delta = enc_old_val - cnt;

	if (delta == 0)
		return;

	h_span = enc_get_span() / 2;
	enc_old_val = cnt;

	if (delta > 0){
		if (delta >= h_span)
			dir = ENC_DIR_CCW;
		else
			dir = ENC_DIR_CW;
	}
	else{
		delta = abs(delta);
		if (delta >= h_span)
			dir = ENC_DIR_CW;
		else
			dir = ENC_DIR_CCW;
	}
	event_push_node(event_create_enc_node(dir, delta));
}


