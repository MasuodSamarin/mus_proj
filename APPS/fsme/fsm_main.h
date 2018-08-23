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
 * it's hold every thing need base fsm
 * */
typedef struct {
	efx_node_t *efx;
	event_node_t *event;
	uint8_t status;
	uint32_t timer;

}fsm_handle_t;


#endif /* FSM_MAIN_H_ */
