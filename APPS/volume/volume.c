/*
 * volume.c
 *
 *  Created on: Aug 7, 2018
 *      Author: sam
 */

//#include "volume.h"
#include "event.h"


/*
 * when volume turn by user:
 * 	first it must turn more then a tiny timer start to mesuare time
 * 	in few ms later it can work even by little, in below max define first turn
 * 	and min is the later turn
 * 	*/
#define VOL_MAX_TOLERANCE	120
#define VOL_MIN_TOLERANCE	40

//#define VOL_RATIO	4


/*
 * the volume process used a tiny state machine
 * this is a 2 state for it
 * state keep track of state changes
 * */
typedef enum {
	VOL_STATE_A,
	VOL_STATE_B
}vol_state;

/*
 * tiny timer value
 * */
#define VOL_STATE_TIME 50

/*
 * raw data means a data that comes dma
 * vol data is old and saved values
 * */
/*
 * this is tiny timer we speak ealier in first of this file
 * and it's predefine values, it takes VOL_STATE_TIME cycle to
 * take back to the first state
 * */
/*
 * keep track of the which volume check on it
 * */
typedef struct {
	uint32_t vol_raw_data[VOL_MAX];
	uint32_t vol_data[VOL_MAX];
	vol_state state;
	uint8_t vol_state_timer;
	vol_name_t vol_name;

}vol_handle_t;
static vol_handle_t vol_handle;


/*
 * the heart of this module is the process the volumes
 * it's must run periodically in timer interupt
 * the raw data's comes from dma then process it and result
 * put on vol_data
 * */
void vol_process(void){
	__IO int32_t delta;

	switch (vol_handle.state) {
		case VOL_STATE_A:
			delta = vol_handle.vol_raw_data[vol_handle.vol_name] - vol_handle.vol_data[vol_handle.vol_name];
			vol_handle.vol_name = vol_handle.vol_name + 1;
			if (abs(delta) >= VOL_MAX_TOLERANCE){
				//vol_old_data[vol_name] = vol_raw_data[vol_name];
				vol_handle.state = VOL_STATE_B;
				vol_handle.vol_state_timer = VOL_STATE_TIME;
			}
			break;

		case VOL_STATE_B:
			delta = vol_handle.vol_data[vol_handle.vol_name] = vol_handle.vol_raw_data[vol_handle.vol_name];
			if (abs(delta) >= VOL_MIN_TOLERANCE){
				event_push_node(event_create_vol_node(vol_handle.vol_name, vol_handle.vol_raw_data[vol_handle.vol_name]));
			}

			if (vol_handle.vol_state_timer){
				vol_handle.state = VOL_STATE_A;
			}
			vol_handle.vol_state_timer = vol_handle.vol_state_timer - 1;
			break;
	}


}

void vol_handle_init(vol_handle_t *handle){
	handle->state = VOL_STATE_A;
	handle->vol_state_timer = 0;
	handle->vol_name = VOL_A;
	  HAL_ADC_Start_DMA(&hadc1, handle->vol_raw_data, VOL_MAX);

}
/*
 * initialize the volume module
 * it must be call first of other functions
 * */
void vol_init(void){
	  MX_DMA_Init();
	  MX_ADC1_Init();
	  vol_handle_init(&vol_handle);

}

/*
 * return the raw value of the volume
 * */
uint32_t vol_get_raw(vol_name_t name){
	return (vol_handle.vol_raw_data[name]);
}

