/*
 * app.c
 *
 *  Created on: Oct 13, 2018
 *      Author: sam
 */


#include "app.h"


APP_typedef app_data;


EVENTS_typedef event_handle(void){
	app_data.event = event_pop_node();

	switch (app_data.event.type) {
		case EVENT_NOT:
			break;

		case EVENT_BTN:
			switch (app_data.event.btn->name) {
				case BTN_ENTER:
					return E_BTN_ENTER;
					break;
				case BTN_BYPASS:
					return E_BTN_BYPASS;
					break;
			}
			break;

		case EVENT_ENC:
			return E_ENC;
			break;

		case EVENT_VOL:
			return E_VOL;
			break;
	}

	if(app_data.timeout){
		app_data.timeout = 0;
		return E_TIMEOUT;
	}

	return E_NOT;

}

void On_Enter(STATES_typedef state){}
void Do(STATES_typedef state){}


void State_Machine(EVENTS_typedef event){
	STATES_typedef cur_state = app_data.cur_state;
	STATES_typedef next_state = cur_state;//app_data.cur_state;

	switch (cur_state) {
		/*state set and update*/
		case S_SET:
			next_state = S_IDLE;
			break;

		/*state IDLE*/
		case S_IDLE:
			switch (event) {
				case E_VOL:
					next_state = S_VOL;

					break;
				case E_ENC:
					next_state = S_ENC;

					break;
				case E_BTN_ENTER:
					next_state = S_SET;

					break;
				case E_BTN_BYPASS:
					next_state = S_BYPASS;

					break;
				case E_TIMEOUT:
					next_state = S_SLEEP;

					break;
			}
			break;

		/*state encoder, change programm*/
		case S_ENC:
			switch (event) {
				case E_VOL:
					next_state = S_VOL;

					break;

				case E_BTN_ENTER:
					next_state = S_SET;

					break;
				case E_BTN_BYPASS:
					next_state = S_BYPASS;

					break;
				case E_TIMEOUT:
					next_state = S_SET;

					break;
			}
			break;

		/*state VOL, show rect instead number front of volume*/
		case S_VOL:
			switch (event) {
				case E_ENC:
					next_state = S_ENC;

					break;
				case E_BTN_ENTER:
					next_state = S_SET;

					break;
				case E_BTN_BYPASS:
					next_state = S_BYPASS;

					break;
				case E_TIMEOUT:
					next_state = S_SET;

					break;
			}
			break;

		/*state sleep, show wav input*/
		case S_SLEEP:
			switch (event) {
				case E_VOL:
					next_state = S_SET;
					break;

				case E_ENC:
					next_state = S_SET;
					break;

				case E_BTN_ENTER:
					next_state = S_SET;
					break;

				case E_BTN_BYPASS:
					next_state = S_BYPASS;
					break;

			}
			break;

		/*state Bypass, turn off FV1, spin-1001 */
		case S_BYPASS:
			if(event == E_BTN_BYPASS)
				next_state = S_SET;
			break;

	}


    // The code below executes every time the state machine function
    //is called, and runs after the transition into the next state

    if (next_state != cur_state)	// NextState (NOT =) to Current_State
    {						//which should always be the case
        //OnExit(Current_State);		// Not used in this project
        app_data.pre_state = cur_state;
        app_data.cur_state = next_state;
        On_Enter(next_state);

    }
    else if( event != E_MAX)
    	{Do( cur_state );}
}
void App_Exec(void){

	while ( app_data.cur_state != S_MAX ){

		State_Machine(event_handle());


	}

}
