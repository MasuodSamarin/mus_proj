/*
 * effect.c
 *
 *  Created on: Aug 9, 2018
 *      Author: sam
 */


#include "effect.h"
#include "effect_preset.h"
#include  "fv1.h"

#include "link_list.h"

list_t *efx_list;



void efx_init_list(void){
	efx_list = list_create();
}



