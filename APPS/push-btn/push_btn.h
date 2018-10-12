/*
 * push_btn.h
 *
 *  Created on: Aug 7, 2018
 *      Author: sam
 */

#ifndef PUSH_BTN_H_
#define PUSH_BTN_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * system includes
 * */
#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
/*
 * user includes
 * */
//#include "event.h"

/*
 * we use 4 button's in the app
 * one of it related to encoder BTN_4
 * other 3 is normal push button
 * */
typedef enum {
	BTN_1,
	BTN_2,
/*	BTN_3,
	BTN_4,*/
	BTN_MAX
}btn_name_t;

/*
 * each button can hold short or long time
 * we react to the proper condition
 * */
typedef enum {
	BTN_HOLD_LONG,
	BTN_HOLD_SHORT
}btn_hold_t;
#define BTN_HOLD_LONG_TIME (100)
#define BTN_HOLD_SHORT_TIME (20)
typedef struct {
	btn_name_t name;
	btn_hold_t hold;
}btn_node_t;


typedef struct {
	btn_name_t name;
	GPIO_TypeDef *port;
	uint16_t pin;
}btn_handle_t;

/*public interface:
 * 1. init button
 * 2. create and delete btn_node
 * 3. button process
 * */
void btn_init(void);
void btn_process(void);

#ifdef __cplusplus
}
#endif


#endif /* PUSH_BTN_H_ */
