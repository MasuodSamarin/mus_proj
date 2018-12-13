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

#include "glcd.h"

 list_t *efx_list;
 list_iterator_t efx_list_iter;







efx_node_t* efx_create_fv1_node(uint8_t number, efx_type_t type, efx_fv1_preset pst, uint16_t *vols){

	efx_node_t *efx = malloc(sizeof(*efx));
	//TODO: check malloc
	if(!efx){
		_Error_Handler(__FILE__, __LINE__);
		return (efx_node_t*)NULL;
	}

	efx->number = number;
	efx->pst = pst;
	efx->type = type;
	efx->fv1 = efx_get_fv1_base(pst);
	efx->vols = vols;

	return efx;
}




/*
 * this is the init of the module, possible?
 * those efx_pushe_list func's must be call before list_make_iterator call
 * */
void efx_init_list(void){
	efx_list = list_create();
	//TODO: add system node, unless the iterator doesnt work. and the lines in the for loop
	uint16_t vols[VOL_MAX] = {0};
	for (efx_fv1_preset pst = EFX_FV1_PRST_1; pst < EFX_FV1_PRST_MAX; ++pst) {
		efx_node_t *efx = (efx_node_t *)efx_create_fv1_node((uint8_t)pst+1, EFX_TYPE_PRESET, pst, vols);
		efx_push_effect(efx);

	}

	//efx_list_iter = list_make_iterator(efx_list, NULL);

}

efx_node_t* efx_get_on_index(uint8_t index){


	node_t *efx = list_iter_from_head(efx_list, index);

	return (efx->element);
}

void efx_push_effect(efx_node_t *efx){

	list_push_back(efx_list, (void*)efx);
	//list_iterator_set_current(&efx_list_iter);
};

uint8_t efx_get_number(efx_node_t *efx){
	return efx->number;
}
efx_type_t efx_get_type(efx_node_t *efx){
	return efx->type;

}

efx_fv1_base_t* efx_get_fv1(efx_node_t *efx){
	return efx->fv1;

}

uint16_t* efx_get_vols(efx_node_t *efx){
	return efx->vols;

}

size_t efx_get_list_size(void){
	return list_get_size(efx_list);
}

void efx_set_vols(efx_node_t *efx, uint16_t vols[VOL_MAX]){
	 efx->vols = vols;
}

#if 0

int efx_find_node_in_list(size_t index, node_t* node, void* data){

	if(node->element == data)
		return 1;
	else
		return 0;
}


void efx_set_cur_node(efx_node_t *efx){
	//node_t *node =list_find_node(efx_list, (void*)efx);
	node_t *find = list_find_node_if(efx_list, efx_find_node_in_list, (void*)efx);

	if(find)
		efx_list_iter.current = (void*)find;
	else
		list_iterator_set_current(&efx_list_iter);
}





efx_node_t* efx_create_fv1_node(uint8_t number, efx_mode_t mode, efx_fv1_preset pst, uint16_t vol1, uint16_t vol2, uint16_t vol3){

	efx_node_t *efx = malloc(sizeof(*efx));
	//TODO: check malloc
	if(!efx){
		_Error_Handler(__FILE__, __LINE__);
		return (efx_node_t*)NULL;
	}
	//efx_fv1_base_t *base = efx_get_fv1_effect(pst);

	/*effect list number start from 1 not zero*/
	efx->number = number;
	efx->type = EFX_TYPE_FV1;
	efx->mode = mode;
	efx->fv1 =  (efx_fv1_base_t*)efx_get_fv1_effect(pst);
	efx->status = DISABLE;
	efx->volume[0] = vol1;
	efx->volume[1] = vol2;
	efx->volume[2] = vol3;


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




efx_node_t* efx_next_node(void){
	node_t *node = list_iterator_next(&efx_list_iter);

	return ((efx_node_t*)(node->element));
}

efx_node_t* efx_prev_node(void){
	node_t *node = list_iterator_prev(&efx_list_iter);

	return ((efx_node_t*)(node->element));
}
#endif
