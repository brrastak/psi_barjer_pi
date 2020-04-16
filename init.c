// STM32F103
#include "stm32f10x.h"

// user
#include "init.h"
#include "main.h"
#include "gpio.h"

void InitRcc(void)
{
    // port A
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    // port B
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    // port C
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    // TIM4
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    // ADC1
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    // TIM2
    //RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    // TIM1
    //RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    // USART1
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    // AFIO
    //RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
}
void InitInterrupt(void)
{
    // USART1
    NVIC_EnableIRQ(USART1_IRQn);
}
void InitGpio(void)
{   
    // Remap USART
    //AFIO->MAPR |= AFIO_MAPR_USART1_REMAP;
    
    // Power control
    SetGpioMode(LEFT_POW_EN_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(LEFT_POW_CTRL_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(RIGHT_POW_EN_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(RIGHT_POW_CTRL_PIN, PIN_MODE_2MHZ_OPP);
    
    // Thyristor control
    SetGpioMode(LEFT_THYRISTOR1_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(LEFT_THYRISTOR2_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(LEFT_THYRISTOR3_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(RIGHT_THYRISTOR1_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(RIGHT_THYRISTOR2_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(RIGHT_THYRISTOR3_PIN, PIN_MODE_2MHZ_OPP);
                
    // Load control
    SetGpioMode(LEFT_LOW_LOAD_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(LEFT_HIGH_LOAD_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(RIGHT_LOW_LOAD_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(RIGHT_HIGH_LOAD_PIN, PIN_MODE_2MHZ_OPP);
    
    // Voltage and current measurement
    SetGpioMode(LEFT_V_PIN, PIN_MODE_IANALOG);
    SetGpioMode(LEFT_I_PIN, PIN_MODE_IANALOG);
    SetGpioMode(RIGHT_V_PIN, PIN_MODE_IANALOG);
    SetGpioMode(RIGHT_I_PIN, PIN_MODE_IANALOG);
    
    // Debug LED
    SetGpioMode(LED_PIN, PIN_MODE_2MHZ_OPP);
    
    // Tamper
    SetGpioMode(TAMPER_PIN, PIN_MODE_IFLOAT);
    
    // Mode switch
    SetGpioMode(MODE_SWITCH_PIN, PIN_MODE_IFLOAT);

    // LEDs
    SetGpioMode(LEFT_R_LED_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(LEFT_G_LED_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(RIGHT_R_LED_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(RIGHT_G_LED_PIN, PIN_MODE_2MHZ_OPP);
    
    // USART
    SetGpioMode(USART_TX_PIN, PIN_MODE_2MHZ_AFPP);
    SetGpioMode(USART_RX_PIN, PIN_MODE_IFLOAT);
    
}
