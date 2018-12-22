/*
 * app.c
 *
 *  Created on: Oct 13, 2018
 *      Author: sam
 */


#include "app.h"


//APP_typedef app_data;
#define STATE_SLEEP_ENABLE	0

SM_Handle_Typedef g_sm_handle;

SM_FP SM_FP_POOL[E_MAX][S_MAX] = {
		{fp_idle_not, 		fp_vol_not, 		fp_enc_not, 		fp_bypass_not},
		{fp_idle_vol, 		fp_vol_vol, 		fp_enc_vol, 		fp_bypass_vol},
		{fp_idle_enc, 		fp_vol_enc, 		fp_enc_enc, 		fp_bypass_enc},
		{fp_idle_enter, 	fp_vol_enter, 		fp_enc_enter, 		fp_bypass_enter},
		{fp_idle_bypass, 	fp_vol_bypass, 		fp_enc_bypass, 		fp_bypass_bypass},
		{fp_idle_timeout, 	fp_vol_timeout, 	fp_enc_timeout, 	fp_bypass_timeout}
};

void SM_init(void){
	g_sm_handle.cur_efx = efx_get_on_index(4);
	g_sm_handle.cur_event = E_NOT;
	g_sm_handle.cur_state = S_IDLE;
	g_sm_handle.event_node = NULL;
	g_sm_handle.state_chaned = 0;
	g_sm_handle.tmp_efx = NULL;
	g_sm_handle.has_event = 0;

}

void app_init(void){


	//efx_init_list();



	///come from main.c
	event_init();
	enc_init();
	vol_init();
	btn_init();

	glcd_init();
	//glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);
	//glcd_clear_buffer();
	//glcd_write();
	efx_init_list();
	SM_init();

}


void event_handle(SM_Handle_Typedef *handle){
	event_node_t *event;

	event = event_pop_node();
	if(event == NULL){
		handle->cur_event = E_NOT;
		//handle->event_node = NULL;
		return;
	}

	if(handle->event_node != NULL){
			free(handle->event_node);
			//handle->event_node = NULL;
	}
	handle->event_node = event;

	switch (event->type) {

		case EVENT_BTN:
			HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);
			if(event->btn.name == BTN_ENTER)
				handle->cur_event = E_BTN_ENTER;
			else if(event->btn.name == BTN_BYPASS)
				handle->cur_event = E_BTN_BYPASS;
			break;

		case EVENT_ENC:
			handle->cur_event = E_ENC;
			break;

		case EVENT_VOL:
			handle->cur_event = E_VOL;
			handle->last_vol = event->vol.name;
			break;

		case EVENT_NOT:
			handle->cur_event = E_NOT;
			//handle->event_node = NULL;
			break;

	}


}



void State_Machine(SM_Handle_Typedef *handle){
	SM_FP func;

	func = SM_FP_POOL[handle->cur_event][handle->cur_state];
	if(func){
		func(handle);

	}
}



void SM_Exec(void){
	State_Machine(&g_sm_handle);
	event_handle(&g_sm_handle);


}


#if 0
EVENTS_typedef event_handle(void);
void State_Machine(EVENTS_typedef event);
void SM_Exec(void);

//void print_on_screen(char* msg);

#if ON_ENTER_ENABLED
void Enter_S_SET(void);
void Enter_S_IDLE(void);
void Enter_S_ENC(void);
void Enter_S_VOL(void);
void Enter_S_SLEEP(void);
void Enter_S_BYPASS(void);
void On_Enter(void);
#endif

void Do_S_SET(void);
void Do_S_IDLE(void);
void Do_S_ENC(void);
void Do_S_VOL(void);
void Do_S_SLEEP(void);
void Do_S_BYPASS(void);
void Do(void);


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"





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
	event_node_t event = app_data.event;

	switch (event.type) {
		case EVENT_NOT:
			break;

		case EVENT_BTN:
			app_reset_timeout_timer();
			switch (event.btn.name) {
				case BTN_ENTER:
					return E_BTN_ENTER;
					break;
				case BTN_BYPASS:
					return E_BTN_BYPASS;
					break;
			}
			break;

		case EVENT_ENC:
			app_reset_timeout_timer();
			app_data.blink = 0;
			app_data.state_changed = 1;
			return E_ENC;
			break;

		case EVENT_VOL:
			app_reset_timeout_timer();
			app_data.vol_last_name = event.vol.name;
			app_data.vol_last_val = event.vol.val;
			app_data.cur_efx.volume[event.vol.name] = event.vol.val;
			return E_VOL;
			break;
	}
#if 0
	if(app_data.timeout == TO_LONG){
			app_data.timeout = TO_NOT;
			return E_TIMEOUT_LONG;
	}
#endif
	if(app_data.timeout == TO_SHORT){
		app_data.timeout = TO_NOT;
		return E_TIMEOUT;
	}

	return E_NOT;
}



/*
 *
 *
 * */
void State_Machine(EVENTS_typedef event){
	static int s_set_cnt = 0;

	STATES_typedef cur_state = app_data.cur_state;
	STATES_typedef next_state = cur_state;//app_data.cur_state;
	app_data.cur_event = event;
/*
	if(event==E_TIMEOUT_SHORT){

	}else if(event==E_TIMEOUT_LONG){

	}
*/
	switch (cur_state) {
		/*state set and update
		 * its run 10 times then goes stright to the IDLE state
		 * */
		/*case S_SET:
			if(s_set_cnt++ < 10){
				//s_set_cnt++;
				next_state = S_SET;
				//app_data.state_changed = 1;
			}
			else{
				s_set_cnt = 0;
				next_state = S_IDLE;

			}
			break;*/

		/*state IDLE*/
		case S_IDLE:
			switch (event) {
				case E_VOL:
					next_state = S_VOL;
					break;

				case E_ENC:
					next_state = S_ENC;
					break;

				//case E_BTN_ENTER:
					//next_state = S_SET;
					//break;

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
					//app_data.cur_efx = *(app_data.node_tmp);
					//next_state = S_SET;
					break;

				case E_BTN_BYPASS:
					next_state = S_BYPASS;
					break;

				case E_TIMEOUT:
					efx_set_cur_node(&(app_data.cur_efx));
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
					//next_state = S_SET;
					break;

				case E_BTN_BYPASS:
					next_state = S_BYPASS;
					break;

				case E_TIMEOUT:
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
				//next_state = S_SET;
			break;
	}

    // The code below executes every time the state machine function
    //is called, and runs after the transition into the next state

#if ON_ENTER_ENABLED
    if (next_state != cur_state)	// NextState (NOT =) to Current_State
    {						//which should always be the case
        //OnExit(Current_State);		// Not used in this project
        app_data.pre_state = cur_state;
        app_data.cur_state = next_state;
        ///On_Enter();

    }
#endif

    if(event < E_MAX){
    	app_data.pre_state = cur_state;
        app_data.cur_state = next_state;

    	Do();
    }

}

/*
 *
 *
 * */
void SM_Exec(void){

	if ( app_data.cur_state < S_MAX ){
		  //HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);

		/*
		 * run button handler*/
		/*if(app_data.run_btn_process == 1){
			app_data.run_btn_process = 0;
			btn_process();
		}*/
		/*
		 * run encoder handler
		 * */
		/*if(app_data.run_enc_process == 1){
			app_data.run_enc_process = 0;
			enc_process();
		}*/
		/*
		 * run volume handler
		 * TODO:
		 * 	temperatury run in the tim2 interrupt handler*/
		/*if(app_data.run_vol_process == 1){
			app_data.run_vol_process = 0;
			vol_process();

		}*/


		State_Machine(event_handle());


	}else{
		/*do not to get in there*/
		  Error_Handler();
	}

}





#if ON_ENTER_ENABLED
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
#endif



/*
 *
 *
 * */
void Do(void){
	STATES_typedef cur_state = app_data.cur_state;
	//STATES_typedef pre_state = app_data.pre_state;

	switch (cur_state) {
		/*state set and update*/
		//case S_SET:
			//Do_S_SET();
			//break;

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
		//case S_SLEEP:
			//Do_S_SLEEP();
			//break;

		/*state Bypass, turn off FV1, spin-1001 */
		case S_BYPASS:
			Do_S_BYPASS();
			break;

	}

}
#endif

#pragma GCC diagnostic pop
