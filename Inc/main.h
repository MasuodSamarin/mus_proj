/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define PUSH_BTN_1_Pin GPIO_PIN_13
#define PUSH_BTN_1_GPIO_Port GPIOC
#define PUSH_BTN_2_Pin GPIO_PIN_14
#define PUSH_BTN_2_GPIO_Port GPIOC
#define PUSH_BTN_3_Pin GPIO_PIN_15
#define PUSH_BTN_3_GPIO_Port GPIOC
#define VOL_ADC1_IN0_Pin GPIO_PIN_0
#define VOL_ADC1_IN0_GPIO_Port GPIOA
#define VOL_ADC1_IN1_Pin GPIO_PIN_1
#define VOL_ADC1_IN1_GPIO_Port GPIOA
#define VOL_ADC1_IN2_Pin GPIO_PIN_2
#define VOL_ADC1_IN2_GPIO_Port GPIOA
#define ISD_GPIO_OUTPUT_Pin GPIO_PIN_3
#define ISD_GPIO_OUTPUT_GPIO_Port GPIOA
#define ISD_SPI1_NSS_Pin GPIO_PIN_4
#define ISD_SPI1_NSS_GPIO_Port GPIOA
#define ISD_SPI1_SCK_Pin GPIO_PIN_5
#define ISD_SPI1_SCK_GPIO_Port GPIOA
#define ISD_SPI1_MISO_Pin GPIO_PIN_6
#define ISD_SPI1_MISO_GPIO_Port GPIOA
#define ISD_SPI1_MOSI_Pin GPIO_PIN_7
#define ISD_SPI1_MOSI_GPIO_Port GPIOA
#define ISD_INT_INPUT_Pin GPIO_PIN_0
#define ISD_INT_INPUT_GPIO_Port GPIOB
#define FV1_CODE_L_Pin GPIO_PIN_1
#define FV1_CODE_L_GPIO_Port GPIOB
#define FV1_CODE_C_Pin GPIO_PIN_2
#define FV1_CODE_C_GPIO_Port GPIOB
#define FV1_CODE_B_Pin GPIO_PIN_10
#define FV1_CODE_B_GPIO_Port GPIOB
#define FV1_CODE_A_Pin GPIO_PIN_11
#define FV1_CODE_A_GPIO_Port GPIOB
#define LCD_CS_Pin GPIO_PIN_12
#define LCD_CS_GPIO_Port GPIOB
#define LCD_SCK_Pin GPIO_PIN_13
#define LCD_SCK_GPIO_Port GPIOB
#define LCD_A0_Pin GPIO_PIN_14
#define LCD_A0_GPIO_Port GPIOB
#define LCD_DATA_Pin GPIO_PIN_15
#define LCD_DATA_GPIO_Port GPIOB
#define LCD_RESET_Pin GPIO_PIN_8
#define LCD_RESET_GPIO_Port GPIOA
#define VOL_TIM1_CH2_Pin GPIO_PIN_9
#define VOL_TIM1_CH2_GPIO_Port GPIOA
#define VOL_TIM1_CH3_Pin GPIO_PIN_10
#define VOL_TIM1_CH3_GPIO_Port GPIOA
#define VOL_TIM1_CH4_Pin GPIO_PIN_11
#define VOL_TIM1_CH4_GPIO_Port GPIOA
#define LED_STATUS_Pin GPIO_PIN_4
#define LED_STATUS_GPIO_Port GPIOB
#define PUSH_BTN_ENC_Pin GPIO_PIN_5
#define PUSH_BTN_ENC_GPIO_Port GPIOB
#define ENC_TIM4_CH1_Pin GPIO_PIN_6
#define ENC_TIM4_CH1_GPIO_Port GPIOB
#define ENC_TIM4_CH2_Pin GPIO_PIN_7
#define ENC_TIM4_CH2_GPIO_Port GPIOB
#define FV1_EEP2_Pin GPIO_PIN_8
#define FV1_EEP2_GPIO_Port GPIOB
#define FV1_EEP1_Pin GPIO_PIN_9
#define FV1_EEP1_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
