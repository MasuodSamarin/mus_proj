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
	BTN_NOT,
	BTN_ENTER,
	BTN_BYPASS,
/*	BTN_3,
	BTN_4,*/
	//BTN_MAX
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



/*
 * from tm lib
 * */

/************************************************************************************************************/

typedef enum {
	TM_GPIO_PuPd_NOPULL = 0x00, /*!< No pull resistor */
	TM_GPIO_PuPd_UP = 0x01,     /*!< Pull up resistor enabled */
	TM_GPIO_PuPd_DOWN = 0x02    /*!< Pull down resistor enabled */
} TM_GPIO_PuPd_t;

/**
 * @defgroup TM_BUTTON_Macros
 * @brief    Library defines
 * @{
 */

/* Number of maximal supported buttons */
#ifndef BUTTON_MAX_BUTTONS
#define BUTTON_MAX_BUTTONS        2
#endif

/* Time for debounce */
#ifndef BUTTON_DEBOUNCE_TIME
#define BUTTON_DEBOUNCE_TIME      5
#endif

/* Number of milliseconds for normal press detection */
#ifndef BUTTON_NORMAL_PRESS_TIME
#define BUTTON_NORMAL_PRESS_TIME  100
#endif

/* Number of milliseconds for long press detection */
#ifndef BUTTON_LONG_PRESS_TIME
#define BUTTON_LONG_PRESS_TIME    1500
#endif

/* Library allocation function */
#ifndef LIB_ALLOC_FUNC
#define LIB_ALLOC_FUNC            malloc
#endif

/* Library free function */
#ifndef LIB_FREE_FUNC
#define LIB_FREE_FUNC             free
#endif

/**
 * @}
 */

/**
 * @defgroup TM_BUTTON_Typedefs
 * @brief    Library Typedefs
 * @{
 */

/**
 * @brief  Button possible press types
 */
typedef enum {
  TM_BUTTON_PressType_OnPressed = 0x00, /*!< Button pressed */
  TM_BUTTON_PressType_Debounce,         /*!< Button debounce */
  TM_BUTTON_PressType_Normal,           /*!< Normal press type, released */
  TM_BUTTON_PressType_Long              /*!< Long press type */
} TM_BUTTON_PressType_t;

/**
 * @brief  Button structure
 */
typedef struct _TM_BUTTON_t {
	GPIO_TypeDef* GPIOx;                                                /*!< GPIOx PORT for button */
	uint16_t GPIO_Pin;                                                  /*!< GPIO pin for button */
	btn_name_t name;
	uint8_t GPIO_State;                                                 /*!< GPIO state for pin when pressed */
	//void (*ButtonHandler)(struct _TM_BUTTON_t*, TM_BUTTON_PressType_t); /*!< Button function handler */
	uint32_t StartTime;                                                 /*!< Time when button was pressed */
	uint8_t LastStatus;                                                 /*!< Button status on last check */
	uint8_t State;                                                      /*!< Current button state */
	uint16_t PressDebounceTime;                                         /*!< Time in ms for normal press for button */
	uint16_t PressNormalTime;                                           /*!< Time in ms for normal press for button */
	uint16_t PressLongTime;                                             /*!< Time in ms for long press for button */
} TM_BUTTON_t;

/**
 * @}
 */

/**
 * @defgroup TM_BUTTON_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Initializes a new button to library
 * @note   This library uses @ref malloc() to allocate memory, so make sure you have enough heap memory
 * @param  *GPIOx: Pointer to GPIOx where button is located
 * @param  GPIO_Pin: GPIO pin where button is located
 * @param  ButtonState: Button state when it is pressed.
 *            - 0: Button is low when pressed
 *            - > 0: Button is high when pressed
 * @param  *ButtonHandler:
 * @retval Button creation status:
 *            - 0: Button was not created
 *            - > 0: Button created and saved to library, button pointer is returned
 */
TM_BUTTON_t* TM_BUTTON_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t ButtonState, btn_name_t name);//, void (*ButtonHandler)(TM_BUTTON_t*, TM_BUTTON_PressType_t));

/**
 * @brief  Sets press timing values
 * @param  *ButtonStruct: Pointer to @ref TM_BUTTON_t structure for button used
 * @param  Normal: Time that button must be pressed to indicate normal press. Value is in milliseconds
 * @param  Normal: Time that button must be pressed to indicate long press. Value is in milliseconds
 * @retval Pointer to @ref TM_BUTTON_t
 */
TM_BUTTON_t* TM_BUTTON_SetPressTime(TM_BUTTON_t* ButtonStruct, uint16_t Normal, uint16_t Long);

/**
 * @brief  Updates buttons. This function have to be called periodically
 * @note   Function will automatically call callback functions for buttons if needed
 * @param  None
 * @retval None
 */
void TM_BUTTON_Update(void);


/**************************************************************************************************************/
#ifdef __cplusplus
}
#endif


#endif /* PUSH_BTN_H_ */
