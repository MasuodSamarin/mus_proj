/*
 * event.c
 *
 *  Created on: Aug 7, 2018
 *      Author: sam
 */


#include "event.h"

/*
 * static variables
 * */
static list_t *event_list;
//static event_node_t *event_node_rec;

/*
 * init event-list call it before other event func
 * */
void event_init(void){
	event_list = list_create();
}

/*
 * get the size of event-list
 * number of event to be waiting to processing
 * */
size_t event_get_size(void){
	return(list_get_size(event_list));
}

/*
 * add the event to the end of the list
 * */
void event_push_node(event_node_t *node){
	list_push_back(event_list, (void*)node);
}


/*
 * free the memory of recently deleted node
 * */
void event_free_event_node(event_node_t *node){
	switch (node->type) {
		case EVENT_BTN:
			free(node->btn);
			break;
		case EVENT_ENC:
			free(node->enc);
			break;
		case EVENT_VOL:
			free(node->vol);
			break;

		default:
			break;
	}
	free(node);
}


/*
 * get the first node from event list
 * */
event_node_t event_pop_node(void){
	event_node_t *np = NULL;
	event_node_t n = {0};
	size_t size;

	size = event_get_size();
	if(size == 0)
		return (n);

	np = (event_node_t*)list_pop_front(event_list);
	if (np != NULL){
		n = *np;
		event_free_event_node(np);
	}
	//return (event_node_t*)(NULL);
	return (n);
}


/*
 * create event node consist volume event
 * */

event_node_t* event_create_vol_node(vol_name_t name, uint32_t val){
	event_node_t *node = malloc(sizeof(*node));
	vol_node_t *vol = malloc(sizeof(*vol));
/*TODO: check the malloc */
	vol->name = name;
	vol->val_adc = val;

	node->type = EVENT_VOL;
	node->vol = vol;

	return node;
}
/*
 * create event node consist button event
 * */
event_node_t* event_create_btn_node(btn_name_t name, btn_hold_t hold){
	event_node_t *node = malloc(sizeof(*node));
	btn_node_t *btn = malloc(sizeof(*btn));
/*TODO: check the malloc */
	btn->name = name;
	btn->hold = hold;

	node->type = EVENT_BTN;
	node->btn = btn;

	return node;
}
/*
 * create event node consist encoder event
 * */
event_node_t* event_create_enc_node(enc_dir_t dir, uint32_t val){
	event_node_t *node = malloc(sizeof(*node));
	enc_node_t *enc = malloc(sizeof(*enc));
/*TODO: check the malloc */
	enc->dir = dir;
	enc->val = val;

	node->type = EVENT_ENC;
	node->enc = enc;

	return node;
}

