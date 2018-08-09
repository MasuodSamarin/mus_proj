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
	char *name;
	// effect comments {some explain to show in lcd}
	char *comments;
	// effect types union {spin, isd117xx}
	// just this is enum
	efx_type_t type;


	// spins and eep's {4 pin for spin, 2 pind for power of eep's}
	//spin pins

} efx_base_t;

typedef struct {
	efx_base_t base;
	// effect number (0-99)
	uint8_t number;
	// effect status {enable, disable}
	uint8_t status;
	// volumes and pwm's {input volume reading, output pwm's value}
	vol_node_t volume[VOL_MAX];
	// effect mode {user-defined, system-preset}
	efx_mode_t mode;
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
