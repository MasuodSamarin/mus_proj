/*
 * fv1.h
 *
 *  Created on: Aug 9, 2018
 *      Author: sam
 */

#ifndef FV1_H_
#define FV1_H_

#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"


typedef struct {
	//spin codes pins
	//eep codes pin
	vol_node_t vol[VOL_MAX];
}fv1_type_t;



#endif /* FV1_H_ */
