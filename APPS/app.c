/*
 * app.c
 *
 *  Created on: Oct 13, 2018
 *      Author: sam
 */


#include "app.h"


APP_typedef app_data;


EVENTS_typedef event_handle(void);
void State_Machine(EVENTS_typedef event);
void App_Exec(void);

void print_on_screen(char* msg);

void Enter_S_SET(void);
void Enter_S_IDLE(void);
void Enter_S_ENC(void);
void Enter_S_VOL(void);
void Enter_S_SLEEP(void);
void Enter_S_BYPASS(void);
void On_Enter(void);


void Do_S_SET(void);
void Do_S_IDLE(void);
void Do_S_ENC(void);
void Do_S_VOL(void);
void Do_S_SLEEP(void);
void Do_S_BYPASS(void);
void Do(void);


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"


/*
 *
 *
 * */
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


/*
 *
 *
 * */
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
        On_Enter();

    }
    else if( event != E_MAX){
    	app_data.pre_state = app_data.cur_state;
    	Do();
    }

}

/*
 *
 *
 * */
void App_Exec(void){

	while ( app_data.cur_state != S_MAX ){
		  HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);

		State_Machine(event_handle());


	}

}







/*
 *
 *
 * */
void On_Enter(void){
	STATES_typedef cur_state = app_data.cur_state;
	//STATES_typedef pre_state = app_data.pre_state;

	switch (cur_state) {
		/*state set and update*/
		case S_SET:
			Enter_S_SET();
			break;

		/*state IDLE*/
		case S_IDLE:
			Enter_S_IDLE();
			break;

		/*state encoder, change programm*/
		case S_ENC:
			Enter_S_ENC();
			break;

		/*state VOL, show rect instead number front of volume*/
		case S_VOL:
			Enter_S_VOL();
			break;

		/*state sleep, show wav input*/
		case S_SLEEP:
			Enter_S_SLEEP();
			break;

		/*state Bypass, turn off FV1, spin-1001 */
		case S_BYPASS:
			Enter_S_BYPASS();
			break;


	}

}




/*
 *
 *
 * */
void Do(void){
	STATES_typedef cur_state = app_data.cur_state;
	//STATES_typedef pre_state = app_data.pre_state;

	switch (cur_state) {
		/*state set and update*/
		case S_SET:
			Do_S_SET();
			break;

		/*state IDLE*/
		case S_IDLE:
			Do_S_IDLE();
			break;

		/*state encoder, change programm*/
		case S_ENC:
			Do_S_ENC();
			break;

		/*state VOL, show rect instead number front of volume*/
		case S_VOL:
			Do_S_VOL();
			break;

		/*state sleep, show wav input*/
		case S_SLEEP:
			Do_S_SLEEP();
			break;

		/*state Bypass, turn off FV1, spin-1001 */
		case S_BYPASS:
			Do_S_BYPASS();
			break;

	}

}
#pragma GCC diagnostic pop
