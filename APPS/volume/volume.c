/*
 * volume.c
 *
 *  Created on: Aug 7, 2018
 *      Author: sam
 */

//#include "volume.h"
#include "event.h"

#define VOL_MAX_TOLERANCE	120
#define VOL_MIN_TOLERANCE	40
//#define VOL_RATIO	4

static  uint32_t vol_raw_data[VOL_MAX];
static  uint32_t vol_data[VOL_MAX];
//static __IO uint8_t vol_data[VOL_MAX];

typedef enum {
	VOL_STATE_A,
	VOL_STATE_B
}vol_state;

static vol_state state = VOL_STATE_A;

#define VOL_STATE_TIME 50
static uint8_t vol_state_timer = 0;

static vol_name_t vol_name = VOL_A;

void vol_process(void){
	__IO int32_t delta;

	switch (state) {
		case VOL_STATE_A:
			delta = vol_raw_data[vol_name] - vol_data[vol_name];
			++vol_name;
			if (abs(delta) >= VOL_MAX_TOLERANCE){
				//vol_old_data[vol_name] = vol_raw_data[vol_name];
				state = VOL_STATE_B;
				vol_state_timer = VOL_STATE_TIME;
			}
			break;

		case VOL_STATE_B:
			delta = vol_data[vol_name] = vol_raw_data[vol_name];
			if (abs(delta) >= VOL_MIN_TOLERANCE){
				event_push_node(event_create_vol_node(vol_name, vol_raw_data[vol_name]));
			}

			if (--vol_state_timer)
				state = VOL_STATE_A;
			break;
	}


}

void vol_init(void){
	  MX_DMA_Init();
	  MX_ADC1_Init();
	  HAL_ADC_Start_DMA(&hadc1, vol_raw_data, VOL_MAX);
}

uint32_t vol_get_raw(vol_name_t name){
	return (vol_raw_data[name]);
}

