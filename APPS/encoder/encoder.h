/*
 * encoder.h
 *
 *  Created on: Aug 7, 2018
 *      Author: sam
 */

#ifndef ENCODER_H_
#define ENCODER_H_


#ifdef __cplusplus
extern "C" {
#endif

/*
 * system includes
 * */
#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "tim.h"


/*
 * the encoder can turn ccw or cw
 * and we use double way link-list
 * */
typedef enum {
	ENC_DIR_CCW,
	ENC_DIR_CW
}enc_dir_t;

/*
 * to insert in event list struct
 * */
typedef struct {
	enc_dir_t dir;
	uint32_t value;
}enc_node_t;



#ifdef __cplusplus
}
#endif

#endif /* ENCODER_H_ */
