/*
 * push_btn.c
 *
 *  Created on: Aug 7, 2018
 *      Author: sam
 */


//#include "push_btn.h"
#include "event.h"
#include "stm32f1xx_hal_gpio.h"

static btn_name_t btn_name = BTN_NOT;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch (GPIO_Pin){

		case PUSH_BTN_BYPASS_Pin:
			btn_name = BTN_BYPASS;
			break;
		case PUSH_BTN_ENTER_Pin:
			btn_name = BTN_ENTER;
			break;
		default:
			btn_name = BTN_NOT;
			break;
	}//END of switch (GPIO_Pin)
}



/*
 * button press and hold counter
 * */
//static uint32_t btn_cnt = 0;

/*
 * define states for button state-machine
 * btn_state track the state of state-machine
 * */
//#define BTN_STATE_A		0
//#define BTN_STATE_B		1
//#define BTN_STATE_C		2
//#define BTN_STATE_MAX	3
//static uint8_t btn_state = BTN_STATE_A;

/*
 * collect every button's do we have
 * btn_haldle track the btn in time
 * */
/*
btn_handle_t btn_buttons[2] = {

		{BTN_1, PUSH_BTN_1_GPIO_Port, PUSH_BTN_1_Pin},
		{BTN_2, PUSH_BTN_BYPASS_GPIO_Port, PUSH_BTN_BYPASS_Pin},
		{BTN_3, PUSH_BTN_3_GPIO_Port, PUSH_BTN_3_Pin},
		{BTN_4, PUSH_BTN_ENC_GPIO_Port, PUSH_BTN_ENC_Pin}

		{BTN_ENTER, PUSH_BTN_ENTER_GPIO_Port, PUSH_BTN_ENTER_Pin},
		{BTN_BYPASS, PUSH_BTN_BYPASS_GPIO_Port, PUSH_BTN_BYPASS_Pin},
};*/
//static btn_handle_t btn_handle = {0};

void btn_init(void){



}
/*
 * button process function
 * it must call in timer interrupt
 * if there's a button event it push that to the event-list
 *  */
void btn_process(void){

		switch (btn_name) {
			case BTN_NOT:
				btn_name = BTN_NOT;
				//event_push_node(event_create_btn_node(BTN_ENTER));//, BTN_HOLD_LONG));
			break;
			case BTN_ENTER:
				btn_name = BTN_NOT;
				event_push_node(event_create_btn_node(BTN_ENTER));//, BTN_HOLD_LONG));
				break;
			case BTN_BYPASS:
				btn_name = BTN_NOT;
				event_push_node(event_create_btn_node(BTN_BYPASS));//, BTN_HOLD_LONG));
				break;

		}

}


/*
	switch(btn_state){
		case BTN_STATE_A:
			if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(btn_buttons[BTN_1].port, btn_buttons[BTN_1].pin)){
				btn_handle = btn_buttons[BTN_1];
				btn_state = BTN_STATE_B;
			}
			else if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(btn_buttons[BTN_2].port, btn_buttons[BTN_2].pin)){
				btn_handle = btn_buttons[BTN_2];
				btn_state = BTN_STATE_B;
			}

			else if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(btn_buttons[BTN_3].port, btn_buttons[BTN_3].pin)){
				btn_handle = btn_buttons[BTN_3];
				btn_state = BTN_STATE_B;
			}
			else if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(btn_buttons[BTN_4].port, btn_buttons[BTN_4].pin)){
				btn_handle = btn_buttons[BTN_4];
				btn_state = BTN_STATE_B;
			}

			break;
		case BTN_STATE_B:
			if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(btn_handle.port, btn_handle.pin)	&& (btn_cnt <= BTN_HOLD_LONG_TIME))
				btn_cnt++;
			else
				btn_state = BTN_STATE_C;

			break;
		case BTN_STATE_C:
			if(btn_cnt >= BTN_HOLD_LONG_TIME)
				event_push_node(event_create_btn_node(btn_handle.name, BTN_HOLD_LONG));

			else if (btn_cnt >= BTN_HOLD_SHORT_TIME)
				event_push_node(event_create_btn_node(btn_handle.name, BTN_HOLD_SHORT));

			btn_state = BTN_STATE_A;
			btn_cnt = 0;
			break;
		}

*/





