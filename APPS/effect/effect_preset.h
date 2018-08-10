/*
 * effect_preset.h
 *
 *  Created on: Aug 9, 2018
 *      Author: sam
 */

#ifndef EFFECT_PRESET_H_
#define EFFECT_PRESET_H_

#include "main.h"
#include "stm32f1xx_hal.h"

/*
 * there's only 16 fv1 preset in the eeps
 * */
#define EFX_PRESET_NUM	16

/*
 * using in the efx_preset array to point to preset effects
 * */
typedef enum {
	efx_fv1_prst_1,
	efx_fv1_prst_2,
	efx_fv1_prst_3,
	efx_fv1_prst_4,
	efx_fv1_prst_5,
	efx_fv1_prst_6,
	efx_fv1_prst_7,
	efx_fv1_prst_8,
	efx_fv1_prst_9,
	efx_fv1_prst_10,
	efx_fv1_prst_11,
	efx_fv1_prst_12,
	efx_fv1_prst_13,
	efx_fv1_prst_14,
	efx_fv1_prst_15,
	efx_fv1_prst_16,
} efx_fv1_effects;

/*
 * complete preset effects
 * */
extern efx_fv1_base_t efx_preset[EFX_PRESET_NUM];




#endif /* EFFECT_PRESET_H_ */
