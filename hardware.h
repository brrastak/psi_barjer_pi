/*
    
*/

// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

// usr
#include "main.h"

#ifndef __HARDWARE_H__
#define __HARDWARE_H__

extern volatile bool led_blinking;

// Reset to start state
void ResetHardware(void);
// Power control
void EnableLeftPower(void);
void DisableLeftPower(void);
void EnableRightPower(void);
void DisableRightPower(void);
// Switch power 12V/16V
void SetLeftPower12V(void);
void SetLeftPower16V(void);
void SetRightPower12V(void);
void SetRightPower16V(void);
// Measurement of voltage and current
uint32_t GetLeftVoltageMv(void);
uint32_t GetLeftCurrentUa(void);
uint32_t GetRightVoltageMv(void);
uint32_t GetRightCurrentUa(void);
// Thyristor control
void EnableLeftThyristor(int number);
void DisableLeftThyristors(void);
void EnableRightThyristor(int number);
void DisableRightThyristors(void);
// Load control
void ConnectLeftLowLoad(void);
void ConnectLeftHighLoad(void);
void DisconnectLeftLoad(void);
void ConnectRightLowLoad(void);
void ConnectRightHighLoad(void);
void DisconnectRightLoad(void);
// LEDs control
void SetLeftLedRed(void);
void SetLeftLedGreen(void);
void SetLeftLedSwitchedOff(void);
void SetRightLedRed(void);
void SetRightLedGreen(void);
void SetRightLedSwitchedOff(void);
void EnableBlinking(void);
void DisableBlinking(void);
void BlinkRightLed(void);
// Tamper
bool IsTamperPressed(void);
// Mode switch
bool IsModeSwitchClosed(void);


#endif
