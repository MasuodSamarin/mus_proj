/*
 * volume.h
 *
 *  Created on: Aug 7, 2018
 *      Author: sam
 */

#ifndef VOLUME_H_
#define VOLUME_H_


#ifdef __cplusplus
extern "C" {
#endif

/*
 * system includes
 * */
#include "main.h"
#include "stm32f1xx_hal.h"
#include "adc.h"
#include "dma.h"
//#include "spi.h"
#include "tim.h"
#include "gpio.h"
/*
 * user includes
 * */
//#include "event.h"

/*
 * conver adc to pwm factor
 * */
#define VOL_ADC_PWM_FACTOR	(1 << 4)
#define VOL_ADC_TO_PWM(x)	(x >> VOL_ADC_PWM_FACTOR)


/*
 * in efx we have 2 types of volume set
 * we have 2volumes or we have 3 volumes
 * */
typedef enum {
	vol_set_2,
	vol_set_3
}vol_set_t;

/*
 * there's 3 of volumes
 * */
typedef enum {
	//VOL_NOT,
	VOL_C,
	VOL_B,
	VOL_A,
	VOL_MAX
}vol_name_t;

/*
 * volume event element node to insert in event list
 * */
typedef struct {
	vol_name_t name;
	uint32_t val;
	uint32_t val_pwm;
}vol_node_t;

/*public interface:
 * 1. init volumes
 * 2. process the volumes
 *
 * */
void vol_init(void);
void vol_process(void);


vol_node_t* vol_create_node(vol_name_t name, uint32_t val);
void vol_delete_node(vol_node_t *node);

uint32_t vol_get_raw(vol_name_t name);
/*get all volumes in raw */
uint32_t* vol_get_all_raw(void);

#ifdef __cplusplus
}
#endif


#endif /* VOLUME_H_ */
