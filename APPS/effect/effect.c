/*
 * effect.c
 *
 *  Created on: Aug 9, 2018
 *      Author: sam
 */

#include "stdlib.h"

#include "effect.h"
//#include "effect_preset.h"
#include  "fv1.h"

#include "link_list.h"
#include "event.h"


static list_t *efx_list;
static list_iterator_t efx_list_iter;

/*
 * this is the init of the module, possible?
 * those efx_pushe_list func's must be call before list_make_iterator call
 * */

void efx_init_list(void){
	efx_list = list_create();
	//TODO: add system node, unless the iterator doesnt work. and the lines in the for loop
	for (efx_fv1_preset pst = EFX_FV1_PRST_1; pst < EFX_FV1_PRST_MAX; ++pst) {
		efx_node_t *efx = efx_create_fv1_node((uint8_t)pst, EFX_MODE_PRESET, pst);
		efx_push_effect(efx);
	}
	for (efx_fv1_preset pst = EFX_FV1_PRST_1; pst < EFX_FV1_PRST_MAX; ++pst) {
		efx_node_t *efx = efx_create_fv1_node((uint8_t)pst+16, EFX_MODE_PRESET, pst);
		efx_push_effect(efx);
	}
	for (efx_fv1_preset pst = EFX_FV1_PRST_1; pst < EFX_FV1_PRST_MAX; ++pst) {
		efx_node_t *efx = efx_create_fv1_node((uint8_t)pst+32, EFX_MODE_PRESET, pst);
		efx_push_effect(efx);
	}
	for (efx_fv1_preset pst = EFX_FV1_PRST_1; pst < EFX_FV1_PRST_MAX; ++pst) {
		efx_node_t *efx = efx_create_fv1_node((uint8_t)pst+48, EFX_MODE_PRESET, pst);
		efx_push_effect(efx);
	}
	for (efx_fv1_preset pst = EFX_FV1_PRST_1; pst < EFX_FV1_PRST_MAX; ++pst) {
		efx_node_t *efx = efx_create_fv1_node((uint8_t)pst+64, EFX_MODE_PRESET, pst);
		efx_push_effect(efx);
	}
	for (efx_fv1_preset pst = EFX_FV1_PRST_1; pst < EFX_FV1_PRST_MAX; ++pst) {
		efx_node_t *efx = efx_create_fv1_node((uint8_t)pst+80, EFX_MODE_PRESET, pst);
		efx_push_effect(efx);
	}
	for (efx_fv1_preset pst = EFX_FV1_PRST_1; pst < EFX_FV1_PRST_MAX; ++pst) {
		efx_node_t *efx = efx_create_fv1_node((uint8_t)pst+96, EFX_MODE_PRESET, pst);
		efx_push_effect(efx);
	}
	efx_list_iter = list_make_iterator(efx_list, NULL);

}


efx_node_t* efx_create_fv1_node(uint8_t number, efx_mode_t mode, efx_fv1_preset pst){

	efx_node_t *efx = malloc(sizeof(*efx));
	//TODO: check malloc
	if(!efx){
		_Error_Handler(__FILE__, __LINE__);
		return (efx_node_t*)NULL;
	}
	//efx_fv1_base_t *base = efx_get_fv1_effect(pst);

	/*effect list number start from 1 not zero*/
	efx->number = number + 1;
	efx->type = EFX_TYPE_FV1;
	efx->mode = mode;
	efx->fv1 =  (efx_fv1_base_t*)efx_get_fv1_effect(pst);
	efx->status = DISABLE;
	efx->volume[0] = 0;
	efx->volume[1] = 0;
	efx->volume[2] = 0;


	return (efx);
}

void efx_delete_fv1_node(efx_node_t *efx){
	free(efx);
}

efx_node_t* efx_create_isd_node(){

	return NULL;

}

void efx_delete_isd_node(efx_node_t *efx){
	free(efx);
}


void efx_push_effect(efx_node_t *efx){

	list_push_back(efx_list, (void*)efx);
};

efx_node_t* efx_next_node(void){
	node_t *node = list_iterator_next(&efx_list_iter);

	return ((efx_node_t*)(node->element));
}

efx_node_t* efx_prev_node(void){
	node_t *node = list_iterator_prev(&efx_list_iter);

	return ((efx_node_t*)(node->element));
}
