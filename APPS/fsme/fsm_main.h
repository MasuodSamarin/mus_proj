/*
 * fsm_main.h
 *
 *  Created on: Aug 15, 2018
 *      Author: sam
 */

#ifndef FSM_MAIN_H_
#define FSM_MAIN_H_

#include "effect.h"
#include "event.h"



/*
 * main staruct of application
 * it's hold every thing need base state machine
 * */
typedef struct {
	efx_node_t *efx;
	event_node_t *event;

}fsm_handle_t;
#endif /* FSM_MAIN_H_ */
