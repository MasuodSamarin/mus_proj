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

list_t *efx_list;
list_iterator_t efx_list_iter;


void efx_init_list(void){
	efx_list = list_create();
	//TODO: add system node, unless the iterator doesnt work.
	efx_list_iter = list_make_iterator(efx_list, NULL);

}


efx_ext_t* efx_create_fv1_node(){

	return NULL;
}

efx_ext_t* efx_create_isd_node(){

	return NULL;

}

void efx_push_effect(efx_ext_t *efx){

};
