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
//#include "spi.h"
#include "tim.h"

#include "stdlib.h"
/*
 * user includes
 * */
#include "link_list.h"
#include "push_btn.h"
#include "encoder.h"
#include "volume.h"



/*
 * add the event to the end of the list
 * */
#define EVENT_QEUE_SIZE 10


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


/*public interface:
 * 1. init  event-list
 * 2. create and delete event-nodes (vol, btn, enc)
 * 3. push the event node to back of the list
 * 4. pop the event node from front of the list
 * 5. get size of the event-list
 *
 * */
void event_init(void);
event_node_t event_pop_node(void);
size_t event_get_size(void);

void event_push_node(event_node_t *node);
event_node_t* event_create_vol_node(vol_name_t name, uint32_t val);
event_node_t* event_create_btn_node(btn_name_t name);//, btn_hold_t hold);
event_node_t* event_create_enc_node(enc_dir_t dir, uint32_t val);


#ifdef __cplusplus
}
#endif

#endif /* EVENT_H_ */
