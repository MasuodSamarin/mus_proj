/*
 * push_btn.c
 *
 *  Created on: Aug 7, 2018
 *      Author: sam
 */


//#include "push_btn.h"
#include "event.h"
#include "stm32f1xx_hal_gpio.h"
#include "push_btn.h"
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


/*
 * button process function
 * it must call in timer interrupt
 * if there's a button event it push that to the event-list
 *  */
void btn_process(void){

		switch (btn_name) {
			case BTN_NOT:
				//btn_name = BTN_NOT;
				//event_push_node(event_create_btn_node(BTN_ENTER));//, BTN_HOLD_LONG));
			break;
			case BTN_ENTER:
				btn_name = BTN_NOT;
				event_push_node(event_create_btn_node(BTN_ENTER, BTN_HOLD_SHORT));//, BTN_HOLD_LONG));
				break;
			case BTN_BYPASS:
				btn_name = BTN_NOT;
				event_push_node(event_create_btn_node(BTN_BYPASS, BTN_HOLD_SHORT));//, BTN_HOLD_LONG));
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


/************************************************************************************************************/
/* Button states */
#define BUTTON_STATE_START        0
#define BUTTON_STATE_DEBOUNCE     1
#define BUTTON_STATE_PRESSED      2
#define BUTTON_STATE_WAITRELEASE  3

/* Internal structure */
typedef struct {
	TM_BUTTON_t* Buttons[BUTTON_MAX_BUTTONS];
	uint16_t ButtonsCount;
} TM_BUTTON_INT_t;
static TM_BUTTON_INT_t Buttons;

/* Internal functions */
static void TM_BUTTON_INT_CheckButton(TM_BUTTON_t* ButtonStruct);

TM_BUTTON_t* TM_BUTTON_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t ButtonState, btn_name_t name){//, void (*ButtonHandler)(TM_BUTTON_t*, TM_BUTTON_PressType_t)) {
	TM_BUTTON_t* ButtonStruct;
	//TM_GPIO_PuPd_t P;

	/* Init delay function */
	//TM_DELAY_Init();

	/* Check if available */
	if (Buttons.ButtonsCount >= BUTTON_MAX_BUTTONS) {
		return NULL;
	}

	/* Allocate memory for button */
	ButtonStruct = (TM_BUTTON_t *) malloc(sizeof(TM_BUTTON_t));

	/* Check if allocated */
	if (ButtonStruct == NULL) {
		return NULL;
	}

	/* Save settings */
	ButtonStruct->GPIOx = GPIOx;
	ButtonStruct->GPIO_Pin = GPIO_Pin;
	ButtonStruct->GPIO_State = ButtonState ? 1 : 0;
	ButtonStruct->name = name;
	//ButtonStruct->ButtonHandler = ButtonHandler;
	ButtonStruct->State = BUTTON_STATE_START;

	/* Set default values */
	ButtonStruct->PressNormalTime = BUTTON_NORMAL_PRESS_TIME;
	ButtonStruct->PressLongTime = BUTTON_LONG_PRESS_TIME;
	ButtonStruct->PressDebounceTime = BUTTON_DEBOUNCE_TIME;

	/* Init pin with pull resistor */
	//if (ButtonStruct->GPIO_State) {
		/* Pulldown */
		//P = TM_GPIO_PuPd_DOWN;
	//} else {
		/* Pullup */
		//P = TM_GPIO_PuPd_UP;
	//}

	/* Init GPIO pin as input with proper pull resistor */
	//TM_GPIO_Init(GPIOx, GPIO_Pin, TM_GPIO_Mode_IN, TM_GPIO_OType_PP, P, TM_GPIO_Speed_Low);

	/* Save button */
	Buttons.Buttons[Buttons.ButtonsCount++] = ButtonStruct;

	/* Return button pointer */
	return ButtonStruct;
}

TM_BUTTON_t* TM_BUTTON_SetPressTime(TM_BUTTON_t* ButtonStruct, uint16_t Normal, uint16_t Long) {
	/* Set values */
	ButtonStruct->PressNormalTime = Normal;
	ButtonStruct->PressLongTime = Long;

	/* Return pointer */
	return ButtonStruct;
}

void TM_BUTTON_Update(void) {
	uint16_t i;

	/* Go through all buttons */
	for (i = 0; i < Buttons.ButtonsCount; i++) {
		/* Check button */
		TM_BUTTON_INT_CheckButton(Buttons.Buttons[i]);
	}
}

/* Internal functions */
static void TM_BUTTON_INT_CheckButton(TM_BUTTON_t* ButtonStruct) {
	uint32_t now, status;

	/* Read values */
	now = HAL_GetTick();
	status = HAL_GPIO_ReadPin(ButtonStruct->GPIOx, ButtonStruct->GPIO_Pin);

	/* First stage */
	if (ButtonStruct->State == BUTTON_STATE_START) {
		/* Check if pressed */
		if (status == ButtonStruct->GPIO_State) {
			/* Button pressed, go to stage BUTTON_STATE_START */
			ButtonStruct->State = BUTTON_STATE_DEBOUNCE;

			/* Save pressed time */
			ButtonStruct->StartTime = now;
		}
	}

	if (ButtonStruct->State == BUTTON_STATE_DEBOUNCE) {
		/* Button still pressed */
		/* Check for debounce */
		if (status == ButtonStruct->GPIO_State) {
			if ((now - ButtonStruct->StartTime) > ButtonStruct->PressDebounceTime) {
				/* Button debounce OK, Goto Normal Press */
				ButtonStruct->State = BUTTON_STATE_PRESSED;

				/* Try to call user function */
				//if (ButtonStruct->ButtonHandler) {
					/* Call function callback */
					//ButtonStruct->ButtonHandler(ButtonStruct, TM_BUTTON_PressType_OnPressed);
				//}
			}
		} else if (status != ButtonStruct->GPIO_State) {
			/* Not pressed */
			/* It was bounce, start over */
			/* Go to state BUTTON_STATE_START */
			ButtonStruct->State = BUTTON_STATE_START;
		}
	}

	if (ButtonStruct->State == BUTTON_STATE_PRESSED) {
		/* Button still pressed */
		/* Check for long press */
		if (status == ButtonStruct->GPIO_State) {
			if ((now - ButtonStruct->StartTime) > ButtonStruct->PressLongTime) {
				/* Button pressed OK, call function */
				//if (ButtonStruct->ButtonHandler) {
					/* Call function callback */
					//ButtonStruct->ButtonHandler(ButtonStruct, TM_BUTTON_PressType_Long);
				//}
				event_push_node(event_create_btn_node(ButtonStruct->name, BTN_HOLD_LONG));//, BTN_HOLD_LONG));

				/* Go to stage BUTTON_STATE_WAITRELEASE */
				ButtonStruct->State = BUTTON_STATE_WAITRELEASE;
			}
		} else if (status != ButtonStruct->GPIO_State) {
			/* Not pressed */
			if ((now - ButtonStruct->StartTime) > ButtonStruct->PressNormalTime) {
				/* Button pressed OK, call function */
				//if (ButtonStruct->ButtonHandler) {
					/* Call function callback */
					//ButtonStruct->ButtonHandler(ButtonStruct, TM_BUTTON_PressType_Normal);
				//}
				event_push_node(event_create_btn_node(ButtonStruct->name, BTN_HOLD_SHORT));//, BTN_HOLD_LONG));

				/* Go to stage BUTTON_STATE_WAITRELEASE */
				ButtonStruct->State = BUTTON_STATE_WAITRELEASE;
			} else {
				/* Go to state BUTTON_STATE_START */
				ButtonStruct->State = BUTTON_STATE_START;
			}
		} else {
			/* Go to state BUTTON_STATE_START */
			ButtonStruct->State = BUTTON_STATE_START;
		}
	}

	if (ButtonStruct->State == BUTTON_STATE_WAITRELEASE) {
		/* Wait till button released */
		if (status != ButtonStruct->GPIO_State) {
			/* Go to stage 0 again */
			ButtonStruct->State = BUTTON_STATE_START;
		}
	}

	/* Save current status */
	ButtonStruct->LastStatus = status;
}
/************************************************************************************************************/

void btn_init(void){

	TM_BUTTON_Init(PUSH_BTN_BYPASS_GPIO_Port, PUSH_BTN_BYPASS_Pin, 0, BTN_BYPASS);
	TM_BUTTON_Init(PUSH_BTN_ENTER_GPIO_Port, PUSH_BTN_ENTER_Pin, 0, BTN_ENTER);

}


void btn_update(btn_node_t *btn, btn_name_t name, btn_hold_t hold){

	//event->type = EVENT_BTN;
	btn->name = name;
	btn->hold = hold;


}

