// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

//user
#include "hardware.h"
#include "main.h"
#include "gpio.h"
#include "adc.h"
#include "timer.h"


// Reset to start state
void ResetHardware(void)
{
    // Power on being tested boards turned off
    DisableLeftPower();
    DisableRightPower();
    // Power = 12V (not 16V)
    SetLeftPower12V();
    SetRightPower12V();
    // No load connected to being tested boards
    DisconnectLeftLoad();
    DisconnectRightLoad();
    // No thyristors at being tested boards disabled
    EnableLeftThyristor(3);
    EnableRightThyristor(3);
    // Switch all LEDs off
    SetLeftLedSwitchedOff();
    SetRightLedSwitchedOff();
}
// Power control
void EnableLeftPower(void)
{
    SetPin(LEFT_POW_EN_PIN);
}
void DisableLeftPower(void)
{
    ResetPin(LEFT_POW_EN_PIN);
}
void EnableRightPower(void)
{
    SetPin(RIGHT_POW_EN_PIN);
}
void DisableRightPower(void)
{
    ResetPin(RIGHT_POW_EN_PIN);
}

// Switch power 12V/16V
void SetLeftPower12V(void)
{
    SetPin(LEFT_POW_CTRL_PIN);
}
void SetLeftPower16V(void)
{
    ResetPin(LEFT_POW_CTRL_PIN);
}
void SetRightPower12V(void)
{
    SetPin(RIGHT_POW_CTRL_PIN);
}
void SetRightPower16V(void)
{
    ResetPin(RIGHT_POW_CTRL_PIN);
}

// Measurement of voltage and current
uint32_t GetLeftVoltageMv(void)
{
    uint32_t res;
    int i;

    // Get ADC value
    /*for (i = 0; i < 100; i++) {
        delay_us(1);
        res += ReadAdc(ADC_LEFT_V_CHANNEL);
    }
    res /= 100;*/
    res = ReadAdc(ADC_LEFT_V_CHANNEL);
    // Translate ADC value into mV
    res = res * V_REF_MV / ADC_MAX_VALUE;
    return res;
    // Calculate power voltage value, mV
    res = res * LEFT_VOLTAGE_DIV / 1000;

    return res;
}
uint32_t GetLeftCurrentUa(void)
{
    uint32_t res;
    int i;
    
    // Get ADC value
    /*for (i = 0; i < 100; i++) {
        delay_us(1);
        res += ReadAdc(ADC_LEFT_I_CHANNEL);
    }
    res /= 100;*/
    res = ReadAdc(ADC_LEFT_I_CHANNEL);
    // Translate ADC value into mV
    res = res * V_REF_MV / ADC_MAX_VALUE;
    return res;
    // Calculate current value, uA
    res = res * 100000 / LEFT_CURRENT_R_MOHM / LEFT_CURRENT_GAIN;
    
    return res;
}
uint32_t GetRightVoltageMv(void)
{
    uint32_t res;

    // Get ADC value
    res = ReadAdc(ADC_RIGHT_V_CHANNEL);
    // Translate ADC value into mV
    res = res * V_REF_MV / ADC_MAX_VALUE;
    return res;
}
uint32_t GetRightCurrentUa(void)
{
    uint32_t res;
    
    // Get ADC value
    res = ReadAdc(ADC_RIGHT_I_CHANNEL);
    // Translate ADC value into mV
    res = res * V_REF_MV / ADC_MAX_VALUE;
    return res;
}

// Thyristor control
void EnableLeftThyristor(int number)
{
    switch (number)
    {
    case 0:
        ResetPin(LEFT_THYRISTOR1_PIN);
        SetPin(LEFT_THYRISTOR2_PIN);
        SetPin(LEFT_THYRISTOR3_PIN);
        break;
    case 1:
        SetPin(LEFT_THYRISTOR1_PIN);
        ResetPin(LEFT_THYRISTOR2_PIN);
        SetPin(LEFT_THYRISTOR3_PIN);
        break;
    case 2:
        SetPin(LEFT_THYRISTOR1_PIN);
        SetPin(LEFT_THYRISTOR2_PIN);
        ResetPin(LEFT_THYRISTOR3_PIN);
        break;
    default:    // enable all thyristors
        ResetPin(LEFT_THYRISTOR1_PIN);
        ResetPin(LEFT_THYRISTOR2_PIN);
        ResetPin(LEFT_THYRISTOR3_PIN);
    }
}
void DisableLeftThyristors(void)
{
    SetPin(LEFT_THYRISTOR1_PIN);
    SetPin(LEFT_THYRISTOR2_PIN);
    SetPin(LEFT_THYRISTOR3_PIN);
}
void EnableRightThyristor(int number)
{
    switch (number)
    {
    case 0:
        ResetPin(RIGHT_THYRISTOR1_PIN);
        SetPin(RIGHT_THYRISTOR2_PIN);
        SetPin(RIGHT_THYRISTOR3_PIN);
        break;
    case 1:
        SetPin(RIGHT_THYRISTOR1_PIN);
        ResetPin(RIGHT_THYRISTOR2_PIN);
        SetPin(RIGHT_THYRISTOR3_PIN);
        break;
    case 2:
        SetPin(RIGHT_THYRISTOR1_PIN);
        SetPin(RIGHT_THYRISTOR2_PIN);
        ResetPin(RIGHT_THYRISTOR3_PIN);
        break;
    default:    // enable all thyristors
        ResetPin(RIGHT_THYRISTOR1_PIN);
        ResetPin(RIGHT_THYRISTOR2_PIN);
        ResetPin(RIGHT_THYRISTOR3_PIN);
    }
}
void DisableRightThyristors(void)
{
    SetPin(RIGHT_THYRISTOR1_PIN);
    SetPin(RIGHT_THYRISTOR2_PIN);
    SetPin(RIGHT_THYRISTOR3_PIN);
}

// Load control
void ConnectLeftLowLoad(void)
{
    SetPin(LEFT_LOW_LOAD_PIN);
    ResetPin(LEFT_HIGH_LOAD_PIN);
}
void ConnectLeftHighLoad(void)
{
    ResetPin(LEFT_LOW_LOAD_PIN);
    SetPin(LEFT_HIGH_LOAD_PIN);
}
void DisconnectLeftLoad(void)
{
    ResetPin(LEFT_LOW_LOAD_PIN);
    ResetPin(LEFT_HIGH_LOAD_PIN);
}
void ConnectRightLowLoad(void)
{
    SetPin(RIGHT_LOW_LOAD_PIN);
    ResetPin(RIGHT_HIGH_LOAD_PIN);
}
void ConnectRightHighLoad(void)
{
    ResetPin(RIGHT_LOW_LOAD_PIN);
    SetPin(RIGHT_HIGH_LOAD_PIN);
}
void DisconnectRightLoad(void)
{
    ResetPin(RIGHT_LOW_LOAD_PIN);
    ResetPin(RIGHT_HIGH_LOAD_PIN);
}

// Tamper
bool IsTamperPressed(void)
{
    return ! GetPinState(TAMPER_PIN);
}
// Mode switch
bool IsModeSwitchClosed(void)
{
    return ! GetPinState(MODE_SWITCH_PIN);
}

// LEDs control
void SetLeftLedRed(void)
{
    SetPin(LEFT_R_LED_PIN);
    ResetPin(LEFT_G_LED_PIN);
}
void SetLeftLedGreen(void)
{
    ResetPin(LEFT_R_LED_PIN);
    SetPin(LEFT_G_LED_PIN);
}
void SetLeftLedSwitchedOff(void)
{
    ResetPin(LEFT_R_LED_PIN);
    ResetPin(LEFT_G_LED_PIN);
}
void SetRightLedRed(void)
{
    SetPin(RIGHT_R_LED_PIN);
    ResetPin(RIGHT_G_LED_PIN);
}
void SetRightLedGreen(void)
{
    ResetPin(RIGHT_R_LED_PIN);
    SetPin(RIGHT_G_LED_PIN);
}
void SetRightLedSwitchedOff(void)
{
    ResetPin(RIGHT_R_LED_PIN);
    ResetPin(RIGHT_G_LED_PIN);
}
