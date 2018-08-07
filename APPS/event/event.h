/*
 * event.h
 *
 *  Created on: Aug 7, 2018
 *      Author: sam
 */

#ifndef EVENT_H_
#define EVENT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * system includes
 * */
#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"

/*
 * user includes
 * */
#include "link_list.h"
#include "push_btn.h"
#include "encoder.h"
#include "volume.h"


/*
 * event types enum
 * there's 3 types of event nodes we can created
 * 	1. push_btn
 * 	2. encoder
 * 	3. volume
 * 	*/
typedef enum {
	EVENT_NOT = 0,
	EVENT_BTN,
	EVENT_ENC,
	EVENT_VOL
}event_types_t;

/*
 * event node struct
 * make a list of this nodes for event driven strategy
 * */
typedef struct {
	event_types_t type;
	union {
		enc_node_t *enc;
		btn_node_t *btn;
		vol_node_t *vol;
	};
}event_node_t;


#ifdef __cplusplus
}
#endif

#endif /* EVENT_H_ */
