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


#endif /* APP_H_ */
