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
/*
 * using in the efx_preset array to point to preset effects
 * */
typedef enum {
	EFX_FV1_PRST_1,
	EFX_FV1_PRST_2,
	EFX_FV1_PRST_3,
	EFX_FV1_PRST_4,
	EFX_FV1_PRST_5,
	EFX_FV1_PRST_6,
	EFX_FV1_PRST_7,
	EFX_FV1_PRST_8,
	EFX_FV1_PRST_9,
	EFX_FV1_PRST_10,
	EFX_FV1_PRST_11,
	EFX_FV1_PRST_12,
	EFX_FV1_PRST_13,
	EFX_FV1_PRST_14,
	EFX_FV1_PRST_15,
	EFX_FV1_PRST_16,
	EFX_FV1_PRST_MAX
} efx_fv1_effects;

/*
 * complete preset effects box
 * */
extern efx_fv1_base_t efx_preset_box[EFX_FV1_PRST_MAX];




#endif /* EFFECT_PRESET_H_ */
