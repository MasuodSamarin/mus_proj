/*
 * fsm_main.c
 *
 *  Created on: Aug 15, 2018
 *      Author: sam
 */

#include "fsme.h"
#include "fsm_main.h"
#include "effect.h"
#include "event.h"


#include <stdio.h>
#include <stdlib.h>
#include "glcd.h"

char str[10];
extern char *unit_btn_name[];
extern char *unit_btn_hold[];
//extern char *unit_enc_dir[];
extern char *unit_vol_name[];



static fsm_handle_t fsm_handle = {0};

/*
 * states of the base fsm
 * */
typedef enum {

    FSM1_S0_INIT = 0,
	FSM1_S1_READY,
    FSM1_S2_ENC,
    FSM1_S3_VOL,
    FSM1_S4_BTN,
    FSM1_MAX_STATE

}FSM1_STATES;


/*
 * inputs (events) prototype
 */
static uint8_t fsm1_events_init( void );
static uint8_t fsm1_events_enc( void );
static uint8_t fsm1_events_vol( void );
static uint8_t fsm1_events_btn( void );
static uint8_t fsm1_events_timeout( void );

/*
 * outputs (actions) prototype
 */
static void fsm1_action_sys_init( void );
static void fsm1_action_ready( void );
static void fsm1_action_enc( void );
static void fsm1_action_vol( void );
static void fsm1_action_btn( void );



// state transitions for each state

static FSME_TRANS FSM1_S0_INIT_TRANS[] =
{
	{ fsm1_events_init, FSM1_S1_READY },

};

static FSME_TRANS FSM1_S1_READY_TRANS[] =
{
	{ fsm1_events_enc, FSM1_S2_ENC },
	{ fsm1_events_vol, FSM1_S3_VOL },
	{ fsm1_events_btn, FSM1_S4_BTN }
};

static FSME_TRANS FSM1_S2_ENC_TRANS[] =
{
	{ fsm1_events_timeout, FSM1_S1_READY },
	{ fsm1_events_vol, FSM1_S3_VOL },
	{ fsm1_events_btn, FSM1_S4_BTN }
};

static FSME_TRANS FSM1_S3_VOL_TRANS[] =
{
	{ fsm1_events_timeout, FSM1_S1_READY },
	{ fsm1_events_enc, FSM1_S2_ENC },
	{ fsm1_events_btn, FSM1_S4_BTN }
};

static FSME_TRANS FSM1_S4_BTN_TRANS[] =
{
	{ fsm1_events_timeout, FSM1_S1_READY },
	{ fsm1_events_enc, FSM1_S2_ENC },
	{ fsm1_events_vol, FSM1_S3_VOL },
};



// state outputs and transitions; entire table
static FSME_STATE FSM1_STATES_TABLE[] =
{
    { fsm1_action_sys_init, 1, FSM1_S0_INIT_TRANS },
    { fsm1_action_ready, 3, FSM1_S1_READY_TRANS },
    { fsm1_action_enc, 2, FSM1_S2_ENC_TRANS },
    { fsm1_action_vol, 2, FSM1_S3_VOL_TRANS },
    { fsm1_action_btn, 2, FSM1_S4_BTN_TRANS }
};


/*
 * instance of FSM
 * wrap all data which handle by FSM_Run
 */
static FSME_FSM FSM1 =  {
    .Enable = FSME_ENABLE,
    .CurrentState = FSM1_S0_INIT,
    .StateChanged = FSME_STATE_CHANGED,
    .StatesNO = FSM1_MAX_STATE,
    .States = FSM1_STATES_TABLE,
    .TransNO = 1,
    .Trans = FSM1_S0_INIT_TRANS
};



/*
 * inputs (events) implant
 */
static uint8_t fsm1_events_init( void ){
	return ((fsm_handle.status != 1) ? 0 : 1);
}

static uint8_t fsm1_events_enc( void ){
	return ((fsm_handle.event->type == EVENT_ENC));
}

static uint8_t fsm1_events_vol( void ){
	return ((fsm_handle.event->type == EVENT_VOL));
}

static uint8_t fsm1_events_btn( void ){
	return ((fsm_handle.event->type == EVENT_BTN));
}

static uint8_t fsm1_events_timeout( void ){
	if (fsm_handle.timer <= 0)
		return 1;
	else
		fsm_handle.timer = fsm_handle.timer - 1;
	return 0;
}

/*
 * outputs (actions) implant
 */
static void fsm1_action_sys_init( void ){
	fsm_handle.status = 0; // deinit

	glcd_init();
	unit_test_init();

	event_init();
	enc_init();
	vol_init();
	btn_init();

	HAL_TIM_Base_Start_IT(&htim2);

	efx_init_list();
	glcd_set_font_c(FC_Default_Font_5x8_AlphaNumber);
	glcd_clear_buffer();
	glcd_write();


	fsm_handle.status = 1; //init success
}

static void fsm1_action_ready( void ){
	if ( FSM1.StateChanged == FSME_STATE_CHANGED )
	    {
	        //actions to be executed only once in this state at the state change

	    //     printf("\n\e[1;34min:%d\tout:%d\e[0m", in, out);
	         printf("\n->ActionClr ----> state change");
	         // reset state changed flag
	         FSM1.StateChanged = FSME_STATE_NOT_CHANGED;
	    }
	    else
	    {
	     // actions to be executed continuously in this state
	         printf("\nActionClr ----------------> executed continouslly");
	    }
}

void fsm1_action_enc_print(efx_node_t *node){

	if (node == NULL)
		return;

	glcd_clear_buffer();
	glcd_write();

	glcd_draw_string(2,5, "EFFECTS");

	sprintf(str, "%d", node->number);
	glcd_draw_string(5,15, "num:");
	glcd_draw_string(55,15, str);

	glcd_draw_string(5,25, (char*)node->fv1->name);
	glcd_draw_string(55,25, (char*)node->fv1->comments);

	sprintf(str, "%d", node->fv1->fv1->eep);
	glcd_draw_string(5,35, "eep:");
	glcd_draw_string(55,35, str);

	sprintf(str, "%d", node->fv1->fv1->pin);
	glcd_draw_string(5,45, "pin:");
	glcd_draw_string(55,45, str);

	glcd_write();
}

static void fsm1_action_enc( void ){

	enc_node_t *enc = fsm_handle.event->enc;
	efx_node_t *node;

	if (enc->dir == ENC_DIR_CCW)
		node = efx_next_node();

	else if (enc->dir == ENC_DIR_CW)
		node = efx_prev_node();

	fsm1_action_enc_print(node);
}

static void fsm1_action_vol( void ){
	vol_node_t *vol = fsm_handle.event->vol;
	glcd_clear_buffer();
	glcd_draw_string(5,5, "VOLUME");
	glcd_draw_string(5,15, unit_vol_name[vol->name]);
	glcd_draw_string(5,25, (char*)utoa(vol->val_adc, str, 10));
	sprintf(str, "%p", vol);
	glcd_draw_string(5,35, str);
	glcd_write();
}

static void fsm1_action_btn( void ){
	btn_node_t *btn = fsm_handle.event->btn;
	glcd_clear_buffer();
	glcd_draw_string(5,5, "BUTTON");
	glcd_draw_string(5,15, unit_btn_name[btn->name]);
	glcd_draw_string(5,25, unit_btn_hold[btn->hold]);
	sprintf(str, "%p", btn);
	glcd_draw_string(5,35, str);
	glcd_write();

}


