 /*
 * app.h
 *
 *  Created on: Oct 13, 2018
 *      Author: sam
 */

#ifndef APP_H_
#define APP_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "glcd.h"
#include "unit_tests.h"
#include "event.h"

#include "eeprom.h"

/* USER CODE BEGIN Includes */


/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

///extern __IO int g_timeout;


typedef enum {
	S_IDLE,
	S_VOL,
	S_ENC,
	S_BYPASS,
	S_MAX
}STATES_typedef;

typedef enum {
	E_NOT,
	E_VOL,
	E_ENC,
	E_BTN_ENTER,
	E_BTN_BYPASS,
	E_TIMEOUT,
	E_MAX
}EVENTS_typedef;

typedef struct {
	/*
	 * the state machine handler
	 * its hold the state machine properties and pass to all func
	 * related to the SM*/
	//current effect pointer
	//temp effect pointer
	//current state
	//current event
	//event actual node pointer
	//state is changed?

	efx_node_t *cur_efx;
	efx_node_t *tmp_efx;

	event_node_t *event_node;

	STATES_typedef 	cur_state;
	//STATES_typedef 	pre_state;
	EVENTS_typedef 	cur_event;

	uint8_t state_chaned;

}SM_Handle_Typedef;

/*func pointer for SM for every single state*/
typedef void (*SM_FP)(SM_Handle_Typedef*);

/*
 * declare of SM-funcs*/

/*
 * state idle, and 6 of events*/
void fp_idle_not(SM_Handle_Typedef*);
void fp_idle_vol(SM_Handle_Typedef*);
void fp_idle_enc(SM_Handle_Typedef*);
void fp_idle_enter(SM_Handle_Typedef*);
void fp_idle_bypass(SM_Handle_Typedef*);
void fp_idle_timeout(SM_Handle_Typedef*);

void fp_vol_not(SM_Handle_Typedef*);
void fp_vol_vol(SM_Handle_Typedef*);
void fp_vol_enc(SM_Handle_Typedef*);
void fp_vol_enter(SM_Handle_Typedef*);
void fp_vol_bypass(SM_Handle_Typedef*);
void fp_vol_timeout(SM_Handle_Typedef*);

void fp_enc_not(SM_Handle_Typedef*);
void fp_enc_vol(SM_Handle_Typedef*);
void fp_enc_enc(SM_Handle_Typedef*);
void fp_enc_enter(SM_Handle_Typedef*);
void fp_enc_bypass(SM_Handle_Typedef*);
void fp_enc_timeout(SM_Handle_Typedef*);

void fp_bypass_not(SM_Handle_Typedef*);
void fp_bypass_vol(SM_Handle_Typedef*);
void fp_bypass_enc(SM_Handle_Typedef*);
void fp_bypass_enter(SM_Handle_Typedef*);
void fp_bypass_bypass(SM_Handle_Typedef*);
void fp_bypass_timeout(SM_Handle_Typedef*);



void SM_init(void);
void SM_Exec(void);

void State_Machine(SM_Handle_Typedef *handle);
void event_handle(SM_Handle_Typedef *handle);


/*a transition box */
/*states   	idle			vol			enc			bypass*/
/*events
   not
   vol
   enc
   enter
   bypass
   timeout*/
#if 0

typedef enum{
	TO_NOT,
	TO_SHORT,
	TO_LONG
}TimeOut_typedef;


typedef struct {

	STATES_typedef 	cur_state;
	STATES_typedef 	pre_state;

	EVENTS_typedef 	cur_event;

	__IO uint16_t			timeout_long_time;
	__IO uint16_t			timeout_short_time;
	__IO TimeOut_typedef 	timeout;
	__IO uint32_t			ticks;

	efx_node_t 		*node_tmp;
	efx_node_t		cur_efx;

	event_node_t	event;

	__IO vol_name_t			vol_last_name;
	__IO uint16_t			vol_last_val;

	__IO uint8_t			state_changed;

	__IO uint8_t			run_btn_process;
	__IO uint8_t			run_vol_process;
	__IO uint8_t			run_enc_process;

	__IO uint8_t			blink;
	__IO uint8_t			select;


}APP_typedef;

#define TIMEOUT_LONG_TIME	1000
#define TIMEOUT_SHORT_TIME	200

void app_reset_timeout_timer(void);
void app_set_timeout_short(uint16_t interval);
void app_set_timeout_long(uint16_t interval);


extern APP_typedef app_data;

void app_init(void);

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


#endif

/*just to test*/
//void app_draw_frame(void);




#endif /* APP_H_ */








