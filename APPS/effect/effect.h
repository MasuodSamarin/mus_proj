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

//////////////////////////////////////////////////////////////////////////////
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
} efx_fv1_preset;

/*
 * complete preset effects box
 * */
//#ifdef EFX_PRESET_STATIC

//extern efx_fv1_base_t *efx_preset_box[EFX_FV1_PRST_MAX];

//#else

//extern efx_fv1_base_t *efx_preset_box;

//#endif


///////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum {
	EFX_TYPE_FV1,
	EFX_TYPE_ISD
} efx_mode_t;

typedef enum {
	EFX_TYPE_USER,
	EFX_TYPE_PRESET
}efx_type_t;


// effect names	{from a list of effects}
// effect comments {some explain to show in lcd}
// spins and eep's {4 pin for spin, 2 pind for power of eep's}

typedef struct {
	char 		*name;
	fv1_code_t 	pin;
	fv1_eep_t 	eep;
	vol_set_t vol_set;

	char *volA_name;
	char *volB_name;
	char *volC_name;

} efx_fv1_base_t;


typedef struct {
	/*
	 * its a isd17xx effect properties*/
}efx_isd_base_t;


// effect number (0-99)
// effect mode {user-defined, system-preset}
// effect types union {fv1, isd117xx}
/*one of the 16 effect's of effect_preset.c*/
/*efx_isd_base_t*/
// volumes and pwm's {input volume reading, output pwm's value}
// effect status {enable, disable}
#if 0
typedef struct {
	uint8_t number;
	efx_mode_t mode;
	efx_type_t type;
	uint8_t status;
	union{
		efx_fv1_base_t *fv1;
		efx_isd_base_t *isd;

	};
	uint16_t volume[VOL_MAX];
}efx_node_t;

#endif



typedef struct {
	uint8_t		number;
	efx_fv1_preset pst;
	efx_fv1_base_t *fv1;

	efx_type_t 	type;

	uint16_t vols[VOL_MAX];

}efx_node_t;


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
efx_node_t* efx_create_fv1_node(uint8_t number, efx_type_t type, efx_fv1_preset pst, uint16_t vols[VOL_MAX]);
void efx_push_effect(efx_node_t *efx);
void efx_init_list(void);
efx_node_t* efx_next_node(void);
efx_node_t* efx_prev_node(void);
/////////////////////////////////////////////////////////

efx_fv1_base_t* efx_get_fv1_effect(efx_fv1_preset pst);

///////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t efx_get_number(efx_node_t *efx);
efx_type_t efx_get_type(efx_node_t *efx);
efx_mode_t efx_get_mode(efx_node_t *efx);
efx_fv1_base_t* efx_get_fv1(efx_node_t *efx);
uint8_t efx_get_status(efx_node_t *efx);
uint16_t* efx_get_vols(efx_node_t *efx);
void efx_set_vols(efx_node_t *efx, uint16_t vol[VOL_MAX]);
size_t efx_get_list_size(void);

void efx_set_cur_node(efx_node_t *efx);

#endif /* EFFECT_H_ */
