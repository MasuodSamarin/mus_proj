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


//#include "event.h"

/*
uint16_t fv1_eep_pins[FV1_EEP_MAX] = {
		FV1_EEP1_Pin,
		FV1_EEP2_Pin,
};

#define FV1_CODE_PIN_MAX	4
uint16_t fv1_code_pins[FV1_CODE_PIN_MAX] = {
		FV1_CODE_A_Pin,
		FV1_CODE_B_Pin,
		FV1_CODE_C_Pin,
		FV1_CODE_L_Pin
};
*/


/*
 * in the each eep there's a 8 program, it start count from 0b000 to 0b111
 * like this:
 * 			0bLABC
 * 			0b1001
 * 	that means first effect of eep A
 * */
typedef enum {
	FV1_CODE_0 = 0b0000,
	FV1_CODE_1 = 0b0001,
	FV1_CODE_2 = 0b0010,
	FV1_CODE_3 = 0b0011,
	FV1_CODE_4 = 0b0100,
	FV1_CODE_5 = 0b0101,
	FV1_CODE_6 = 0b0110,
	FV1_CODE_7 = 0b0111,
}fv1_code_t;

#define FV1_PIN_A_BIT	0b0001
#define FV1_PIN_B_BIT	0b0010
#define FV1_PIN_C_BIT	0b0100
#define FV1_PIN_L_BIT	0b1000

/*
 * there is 2 eep, that just single of it must be on each time
 * */
typedef enum {
	FV1_EEP_RESET,
	FV1_EEP_A,
	FV1_EEP_B
}fv1_eep_t;


/*
 * fv1 struct consist all of needed that fv1 uses
 * */
typedef struct {
	fv1_code_t pin;
	fv1_eep_t eep;
	//vol_node_t vol[VOL_MAX];
}fv1_type_t;



void fv1_latch_reset(fv1_type_t *fv1);
void fv1_latch_set(fv1_type_t *fv1);
void fv1_code_set(fv1_type_t *fv1, fv1_code_t code);
fv1_code_t fv1_code_get(fv1_type_t *fv1);
void fv1_eep_off(fv1_type_t *fv1);
void fv1_eep_on(fv1_type_t *fv1, fv1_eep_t eep);
fv1_eep_t fv1_eep_get(fv1_type_t *fv1);

#endif /* FV1_H_ */
