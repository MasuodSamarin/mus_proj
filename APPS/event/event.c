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


void event_push_node(event_node_t *node){
	if(event_get_size() > EVENT_QEUE_SIZE)
		return;
	list_push_back(event_list, (void*)node);
}




/*
 * get the first node from event list
 * */
event_node_t* event_pop_node(void){
	return ((event_node_t*)list_pop_front(event_list));
}

void event_free_nodes_element(event_node_t* element){
	if(element)
		free(element);

}

/*
 * create event node consist volume event
 * */

event_node_t* event_create_vol_node(vol_name_t name){//, uint32_t val){
	event_node_t *node = malloc(sizeof(node));
	//vol_node_t vol;// = malloc(sizeof(*vol));
/*TODO: check the malloc */
	if(!node){
		_Error_Handler(__FILE__, __LINE__);
		return (event_node_t*)NULL;
	}

	node->type = EVENT_VOL;
	node->vol.name = name;
	//node->vol.val = val;
	//node->vol.val_pwm = val << VOL_ADC_PWM_FACTOR;
	return node;
}
/*
 * create event node consist button event
 * */
event_node_t* event_create_btn_node(btn_name_t name, btn_hold_t hold){
	event_node_t *node = malloc(sizeof(node));
	//btn_node_t btn;// = malloc(sizeof(*btn));
/*TODO: check the malloc */
	if(!node){
		_Error_Handler(__FILE__, __LINE__);
		return (event_node_t*)NULL;
	}
	//btn->name = name;
	//btn->hold = hold;

	node->type = EVENT_BTN;
	node->btn.name = name;
	node->btn.hold = hold;
	return node;
}
/*
 * create event node consist encoder event
 * */
event_node_t* event_create_enc_node(enc_dir_t dir, uint32_t val){
	event_node_t *node = malloc(sizeof(node));
	//enc_node_t enc;// = malloc(sizeof(*enc));
/*TODO: check the malloc */
	if(!node){
		_Error_Handler(__FILE__, __LINE__);
		return (event_node_t*)NULL;
	}

	node->type = EVENT_ENC;
	node->enc.dir = dir;
	node->enc.val = val;

	return node;
}

