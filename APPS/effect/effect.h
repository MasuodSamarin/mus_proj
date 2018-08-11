/*
 * effect.h
 *
 *  Created on: Aug 9, 2018
 *      Author: sam
 */

#ifndef EFFECT_H_
#define EFFECT_H_

#include "main.h"
#include "stm32f1xx_hal.h"

#include "event.h"
#include  "fv1.h"



typedef enum {
	EFX_TYPE_FV1,
	EFX_TYPE_ISD
} efx_type_t;

typedef enum {
	EFX_MODE_USER,
	EFX_MODE_PRESET
}efx_mode_t;

typedef struct {
	// effect names	{from a list of effects}
	 const char *name;
	// effect comments {some explain to show in lcd}
	 const char *comments;


	// spins and eep's {4 pin for spin, 2 pind for power of eep's}
	 fv1_type_t *fv1;

} efx_fv1_base_t;


typedef struct {
	/*
	 * its a isd17xx effect properties*/
}efx_isd_base_t;

typedef struct {
	// effect number (0-99)
	uint8_t number;

	// effect mode {user-defined, system-preset}
	efx_mode_t mode;

	// effect types union {fv1, isd117xx}
	efx_type_t type;

	union{
		/*one of the 16 effect's of effect_preset.c*/
		efx_fv1_base_t *fv1_base;
		/*efx_isd_base_t*/
		efx_isd_base_t *isd_base;

	};

	// volumes and pwm's {input volume reading, output pwm's value}
	vol_node_t *volume[VOL_MAX];

	// effect status {enable, disable}
	uint8_t status;

}efx_ext_t;




/*
 * public interface
 *
 * 1. make a effect
 * 		1. efx_ext_t X EFX_PRESET_NUM, every time system start
 * 		2. efx_ext_t for every single that user makes effect
 * 	2. delete EFX_MODE_USER effect
 *
 * 	note:
 * 		to make any effect just need the X3 volume's values
 *
 * */



#endif /* EFFECT_H_ */
