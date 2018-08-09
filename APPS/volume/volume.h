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
#include "spi.h"
#include "tim.h"
#include "gpio.h"
/*
 * user includes
 * */
//#include "event.h"



/*
 * there's 3 of volumes
 * */
typedef enum {
	VOL_A,
	VOL_B,
	VOL_C,
	VOL_MAX
}vol_name_t;

/*
 * volume event element node to insert in event list
 * */
typedef struct {
	vol_name_t name;
	uint32_t val_adc;
	uint32_t val_pwm;
}vol_node_t;

/*public interface:
 * 1. init volumes
 * 2. create and delete vol node
 *
 * */
void vol_init(void);

#ifdef __cplusplus
}
#endif


#endif /* VOLUME_H_ */
