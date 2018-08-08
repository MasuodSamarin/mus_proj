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
 * user includes
 * */
//#include "event.h"

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
	uint32_t val;
}enc_node_t;

/*public interface:
 * 1. init encoder
 * 2. create and delete enc node
 *
 * */
void enc_init(void);
void enc_set_span(uint32_t span);
uint32_t enc_get_span(void);
uint32_t enc_get_val(void);
void enc_process(void);

#ifdef __cplusplus
}
#endif

#endif /* ENCODER_H_ */
