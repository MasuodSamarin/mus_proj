/*
 * effect.c
 *
 *  Created on: Aug 9, 2018
 *      Author: sam
 */

#include "stdlib.h"

#include "effect.h"
#include "effect_preset.h"
#include  "fv1.h"

#include "link_list.h"
#include "event.h"

list_t *efx_list;
list_iterator_t efx_list_iter;

/*
 * this is the init of the module, possible?
 * those efx_pushe_list func's must be call before list_make_iterator call
 * */

void efx_init_list(void){
	efx_list = list_create();
	//TODO: add system node, unless the iterator doesnt work.
	efx_list_iter = list_make_iterator(efx_list, NULL);

}


efx_ext_t* efx_create_fv1_node(uint8_t number, efx_mode_t mode, efx_fv1_preset prst){

	efx_ext_t *efx = malloc(sizeof(*efx));
	//TODO: check malloc
	efx_fv1_base_t *base = efx_preset_box[prst];

	efx->number = number;
	efx->type = EFX_TYPE_ISD;
	efx->mode = mode;
	efx->fv1_base = base;
	efx->status = DISABLE;
	efx->volume[0] = vol_create_node (VOL_A, 0);
	efx->volume[1] = vol_create_node (VOL_A, 0);
	efx->volume[2] = vol_create_node (VOL_A, 0);

	//efx->volume = (vol_node_t*){0};

	return (efx);
}

void efx_delete_fv1_node(efx_ext_t *efx){
	free(efx);
}

efx_ext_t* efx_create_isd_node(){

	return NULL;

}

void efx_push_effect(efx_ext_t *efx){

};
