/*
 * volume.c
 *
 *  Created on: Aug 7, 2018
 *      Author: sam
 */

#include "volume.h"


void vol_init(void){

}

event_node_t* vol_create_node(vol_name_t name, uint32_t val){
	event_node_t *node = malloc(sizeof(*node));
	vol_node_t *vol = malloc(sizeof(*vol));

	node->type = EVENT_VOL;
	node->vol = vol;

	return node;
}
