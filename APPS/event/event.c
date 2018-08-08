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


/*
 * init event-list call it before other event func
 * */
void event_init(void){
	event_list = list_create();
}

/*
 * add the event to the end of the list
 * */
void event_push_back(event_node_t *node){
	list_push_back(event_list, (void*)node);
}

/*
 * get the first node from event list
 * */
event_node_t event_pop_front(void){
	event_node_t *np = list_pop_front(event_list);
	event_node_t n = *np;

	event_free_node(np);

	return (n);
}

/*
 * free the memory of recently deleted node
 * */
void event_free_node(event_node_t *node){
	switch (node->type) {
		case EVENT_BTN:

			break;
		case EVENT_ENC:

			break;
		case EVENT_VOL:

			break;

		default:
			break;
	}
}
