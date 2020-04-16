// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

#ifndef __MAIN_H__
#define __MAIN_H__

// ADC coefficients
#define LEFT_VOLTAGE_DIV        5100ul      // Rup / Rdown * 1000
#define LEFT_CURRENT_R_MOHM     430ul       // Ri, mOhm
#define LEFT_CURRENT_GAIN       151ul       // OA gain
#define RIGHT_VOLTAGE_DIV       5100ul      // Rup / Rdown * 1000
#define RIGHT_CURRENT_R_MOHM    4300ul      // Ri, mOhm
#define RIGHT_CURRENT_GAIN      151ul       // OA gain

#define V_REF_MV                3341ul      // ADC reference voltage, mV
#define ADC_MAX_VALUE           0x0fff      // 12 bit

// Test thresholds (mV)
#define THRESHOLD_I             1000//930
#define THRESHOLD_V_12          1600        // zener protection
#define THRESHOLD_V_12_C        800         // thyristor closed
#define THRESHOLD_V_12_O        1400        // thyristor opened
#define THRESHOLD_V_16          2700

// Ports and pin numbers
// Power control
#define LEFT_POW_EN_PIN         GPIOB, 1
#define LEFT_POW_CTRL_PIN       GPIOB, 10
#define RIGHT_POW_EN_PIN        GPIOA, 0
#define RIGHT_POW_CTRL_PIN      GPIOA, 1
// Thyristor control
#define LEFT_THYRISTOR1_PIN     GPIOB, 14
#define LEFT_THYRISTOR2_PIN     GPIOB, 7
#define LEFT_THYRISTOR3_PIN     GPIOA, 8
//#define LEFT_THYRISTOR2_PIN     GPIOB, 15
#define RIGHT_THYRISTOR1_PIN    GPIOB, 6
#define RIGHT_THYRISTOR2_PIN    GPIOB, 7
#define RIGHT_THYRISTOR3_PIN    GPIOB, 9
// Load control
#define LEFT_LOW_LOAD_PIN       GPIOB, 13
#define LEFT_HIGH_LOAD_PIN      GPIOB, 12
#define RIGHT_LOW_LOAD_PIN      GPIOB, 5
#define RIGHT_HIGH_LOAD_PIN     GPIOA, 12
// Voltage and current measurement
#define LEFT_V_PIN              GPIOB, 0
#define LEFT_I_PIN              GPIOA, 7
#define RIGHT_V_PIN             GPIOA, 5
#define RIGHT_I_PIN             GPIOA, 4
// Tamper
#define TAMPER_PIN              GPIOA, 11
// Mode switch
#define MODE_SWITCH_PIN         GPIOB, 8
// LEDs
#define LEFT_R_LED_PIN          GPIOB, 11
#define LEFT_G_LED_PIN          GPIOA, 6
#define RIGHT_R_LED_PIN         GPIOA, 3
#define RIGHT_G_LED_PIN         GPIOA, 2

// Onboard LED
#define LED_PIN                 GPIOC, 13
// USART
#define USART_TX_PIN            GPIOA, 9
#define USART_RX_PIN            GPIOA, 10

// ADC channel numbers
#define ADC_LEFT_V_CHANNEL      8
#define ADC_LEFT_I_CHANNEL      7
#define ADC_RIGHT_V_CHANNEL     5
#define ADC_RIGHT_I_CHANNEL     4


#endif
