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

/*
 * in the each eep there's a 8 program, it start count from 0b000 to 0b111
 * */
typedef enum {
	FV1_CODE_0 = 0b000,
	FV1_CODE_1 = 0b001,
	FV1_CODE_2 = 0b010,
	FV1_CODE_3 = 0b011,
	FV1_CODE_4 = 0b100,
	FV1_CODE_5 = 0b101,
	FV1_CODE_6 = 0b110,
	FV1_CODE_7 = 0b111,
}fv1_pin_code_t;

/*
 * there is 2 eep, that just single of it must be on
 * */
typedef enum {
	FV1_EEP_A,
	FV1_EEP_B,
	FV1_EEP_MAX
}fv1_eep_t;


/*
 * fv1 struct consist all of needed that fv1 uses
 * */
typedef struct {
	fv1_pin_code_t pin;
	fv1_eep_t eep;
	vol_node_t vol[VOL_MAX];
}fv1_type_t;


void fv1_eep_set(fv1_type_t *fv1, fv1_eep_t eep){
	fv1->eep = eep;
}


#endif /* FV1_H_ */
