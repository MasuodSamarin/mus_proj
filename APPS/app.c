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

//void print_on_screen(char* msg);

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


void app_test_init(void){
	  unit_test_init();

	app_data.cur_efx = *(efx_next_node());
	app_set_timeout_long(TIMEOUT_LONG_TIME);
	app_set_timeout_short(TIMEOUT_SHORT_TIME);

	///come from main.c
	  event_init();

}

void app_reset_timeout_timer(void){
	app_data.ticks = 0;

}

void app_set_timeout_short(uint16_t interval){
	app_data.timeout_short_time = interval;
}
void app_set_timeout_long(uint16_t interval){
	app_data.timeout_long_time = interval;

}
/*
 *
 *
 * */
EVENTS_typedef event_handle(void){
	//static int timeout_cnt = 0;
	app_data.event = event_pop_node();



	if(app_data.timeout == TO_LONG){
		app_data.timeout = TO_NOT;
		return E_TIMEOUT_LONG;
	}
	if(app_data.timeout == TO_SHORT){
		app_data.timeout = TO_NOT;
		return E_TIMEOUT_SHORT;
	}


	switch (app_data.event.type) {
		case EVENT_NOT:
			break;

		case EVENT_BTN:
			app_reset_timeout_timer();

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
			app_data.state_changed = 1;
			app_reset_timeout_timer();
			return E_ENC;
			break;

		case EVENT_VOL:
			app_reset_timeout_timer();
			app_data.vol_last_name = app_data.event.vol->name;
			app_data.vol_last_val = app_data.event.vol->val_adc;
			//app_data.cur_efx.volume[app_data.event.vol->name] = app_data.event.vol->val_adc;
			return E_VOL;
			break;
	}


	return E_NOT;

}


#define STATE_SLEEP_ENABLE	0

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
#if STATE_SLEEP_ENABLE
				case E_TIMEOUT_LONG:
					next_state = S_SLEEP;
					break;
#endif
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

				case E_TIMEOUT_SHORT:
					next_state = S_IDLE;
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

				case E_TIMEOUT_SHORT:
					next_state = S_IDLE;
					break;
			}
			break;

#if STATE_SLEEP_ENABLE
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
#endif

		/*state Bypass, turn off FV1, spin-1001 */
		case S_BYPASS:
			if(event == E_BTN_BYPASS)
				next_state = S_SET;
			break;

	}


    // The code below executes every time the state machine function
    //is called, and runs after the transition into the next state
	app_data.next_event = event;


    if (next_state != cur_state)	// NextState (NOT =) to Current_State
    {						//which should always be the case
        //OnExit(Current_State);		// Not used in this project
        app_data.pre_state = cur_state;
        app_data.cur_state = next_state;
        //On_Enter();

    }
    if( event != E_MAX){
    	app_data.pre_state = cur_state;
    	Do();
    }

}

/*
 *
 *
 * */
void App_Exec(void){

	while ( app_data.cur_state != S_MAX ){
		  //HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);

		if(app_data.run_btn_process == 1){
			app_data.run_btn_process = 0;
			btn_process();
		}
		if(app_data.run_enc_process == 1){
			app_data.run_enc_process = 0;
			enc_process();
		}
		if(app_data.run_vol_process == 1){
			app_data.run_vol_process = 0;
			vol_process();

		}

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
