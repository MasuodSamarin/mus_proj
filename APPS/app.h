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

extern __IO int g_timeout;


typedef enum {
	S_SET,
	S_IDLE,
	S_ENC,
	S_VOL,
	S_SLEEP,
	S_BYPASS,
	S_MAX
}STATES_typedef;

typedef enum {
	E_NOT,
	E_VOL,
	E_ENC,
	E_BTN_ENTER,
	E_BTN_BYPASS,
	E_TIMEOUT_SHORT,
	E_TIMEOUT_LONG,
	E_MAX
}EVENTS_typedef;

typedef enum{
	TO_NOT,
	TO_SHORT,
	TO_LONG
}TimeOut_typedef;


typedef struct {

	STATES_typedef 	cur_state;
	STATES_typedef 	pre_state;

	EVENTS_typedef 	next_event;

	uint16_t		timeout_long_time;
	uint16_t		timeout_short_time;
	TimeOut_typedef timeout;
	uint32_t		ticks;

	efx_node_t 		*node_tmp;
	efx_node_t		cur_efx;

	event_node_t	event;

	vol_name_t		vol_last_name;
	uint16_t		vol_last_val;

	uint8_t			state_changed;

	uint8_t			run_btn_process;
	uint8_t			run_vol_process;
	uint8_t			run_enc_process;


}APP_typedef;

#define TIMEOUT_LONG_TIME	3000
#define TIMEOUT_SHORT_TIME	30

void app_reset_timeout_timer(void);
void app_set_timeout_short(uint16_t interval);
void app_set_timeout_long(uint16_t interval);


extern APP_typedef app_data;

void app_test_init(void);

EVENTS_typedef event_handle(void);
void State_Machine(EVENTS_typedef event);
void App_Exec(void);

//void print_on_screen(char* msg);
/*
void Enter_S_SET(void);
void Enter_S_IDLE(void);
void Enter_S_ENC(void);
void Enter_S_VOL(void);
void Enter_S_SLEEP(void);
void Enter_S_BYPASS(void);
void On_Enter(void);
*/

void Do_S_SET(void);
void Do_S_IDLE(void);
void Do_S_ENC(void);
void Do_S_VOL(void);
void Do_S_SLEEP(void);
void Do_S_BYPASS(void);
void Do(void);



/*just to test*/
//void app_draw_frame(void);




#endif /* APP_H_ */








