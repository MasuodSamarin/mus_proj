/*
 * fv1.c
 *
 *  Created on: Aug 9, 2018
 *      Author: sam
 */


#include  "fv1.h"


/*
 * turn off latch pin of fv1
 * */
void fv1_latch_reset(fv1_type_t *fv1){
	HAL_GPIO_WritePin(FV1_CODE_L_GPIO_Port, FV1_CODE_L_Pin, GPIO_PIN_RESET);
	CLEAR_BIT(fv1->pin, FV1_PIN_L_BIT);
}
/*
 * turn on latch pin of fv1
 * */
void fv1_latch_set(fv1_type_t *fv1){
	HAL_GPIO_WritePin(FV1_CODE_L_GPIO_Port, FV1_CODE_L_Pin, GPIO_PIN_SET);
	SET_BIT(fv1->pin, FV1_PIN_L_BIT);
}


/*
 * set the code to the fv1 pins
 * there's 8 code
 * */
void fv1_code_set(fv1_type_t *fv1, fv1_code_t code){

	HAL_GPIO_WritePin(FV1_CODE_L_GPIO_Port, FV1_CODE_L_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(FV1_CODE_A_GPIO_Port, FV1_CODE_A_Pin || FV1_CODE_B_Pin
			|| FV1_CODE_C_Pin , GPIO_PIN_RESET);

	if (READ_BIT(code, FV1_PIN_A_BIT))
		HAL_GPIO_WritePin(FV1_CODE_A_GPIO_Port, FV1_CODE_A_Pin, GPIO_PIN_SET);
	if (READ_BIT(code, FV1_PIN_B_BIT))
		HAL_GPIO_WritePin(FV1_CODE_B_GPIO_Port, FV1_CODE_B_Pin, GPIO_PIN_SET);
	if (READ_BIT(code, FV1_PIN_C_BIT))
		HAL_GPIO_WritePin(FV1_CODE_C_GPIO_Port, FV1_CODE_C_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(FV1_CODE_L_GPIO_Port, FV1_CODE_L_Pin, GPIO_PIN_SET);

	SET_BIT(fv1->pin, code || FV1_PIN_L_BIT);
}

/*
 * get the value of the fv1 code
 * */
fv1_code_t fv1_code_get(fv1_type_t *fv1){
	return (READ_REG(fv1->pin));
}

/*
 * turn of the eep's
 * */
void fv1_eep_off(fv1_type_t *fv1){
	HAL_GPIO_WritePin(FV1_EEP1_GPIO_Port, FV1_EEP1_Pin || FV1_EEP2_Pin, GPIO_PIN_RESET);
	CLEAR_BIT(fv1->eep, FV1_EEP_A || FV1_EEP_B) ;
}

/*
 * turn on the one of eep in time
 * */
void fv1_eep_set(fv1_type_t *fv1, fv1_eep_t eep){

	HAL_GPIO_WritePin(FV1_EEP1_GPIO_Port, FV1_EEP1_Pin || FV1_EEP2_Pin, GPIO_PIN_RESET);

	if (READ_BIT(eep, FV1_EEP_A))
		HAL_GPIO_WritePin(FV1_EEP1_GPIO_Port, FV1_EEP1_Pin, GPIO_PIN_SET);
	if (READ_BIT(eep, FV1_EEP_B))
		HAL_GPIO_WritePin(FV1_EEP2_GPIO_Port, FV1_EEP2_Pin, GPIO_PIN_SET);

	SET_BIT(fv1->eep, eep);
}

/*
 * read the status of the eep's
 * */
fv1_eep_t fv1_eep_get(fv1_type_t *fv1){
	return (READ_REG(fv1->eep));
}

