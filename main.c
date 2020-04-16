// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
//#include <stdlib.h>

//user
#include "main.h"
#include "init.h"
#include "GPIO.h"
#include "timer.h"
#include "UART.h"
#include "adc.h"
#include "debug_led.h"
//#include "button.h"
#include "hardware.h"
#include "psi.h"

//void SendVI(void);


int main()
{    
    
    // System init
    InitRcc();
    InitGpio();
    InitSysTick();
    //InitUart();
    InitAdc();
    InitInterrupt();
    

    // Test result
    bool    left_error  = false,
            right_error = false;
    
    // Reset hardware to start state
    ResetHardware();
    
    
    
    while (true) { 
        
        // Wait for already tested board to unconnect
        WaitForUnconnectBoard();
        
        // Reset hardware to start state
        ResetHardware();
        
        // Reset last test result
        left_error = false;
        right_error = false;
        SetLeftLedSwitchedOff();
        SetRightLedSwitchedOff();
        
        // Wait for being tested boards to connect
        WaitForConnectBoard();
        
        delay_ms(100);
        

        // Test zener diodes current at 12V (have to be 0)
        left_error = TestLeftZenerLeakage();
        //right_error = TestRightZenerLeakage();
        // Error indication
        if (left_error == true)
            SetLeftLedRed();
        /*if (right_error == true)
            SetRightLedRed();*/
        // End test in case of test error
        if ((left_error == true) || (right_error == true))
            continue;
        
        // Test zener diodes current at 16V (have to be >150mA)
        left_error = TestLeftZenerProtection();
        //right_error = TestRightZenerProtection();
        // Error indication
        if (left_error == true)
            SetLeftLedRed();
        /*if (right_error == true)
            SetRightLedRed();*/
        // End test in case of test error
        if ((left_error == true) || (right_error == true))
            continue;
        
        // Check if there is connection to thyristor gate
        // (only if mode switch opened)
        if (! IsModeSwitchClosed())
            right_error = CheckConnection();
        if (right_error == true)
            SetRightLedRed();
        // End test in case of test error
        if ((left_error == true) || (right_error == true))
            continue;
        
        // Test 3 thyristors one by one (have to open if I > 130 mA)
        // and then test all 3 thyristors together
        int i;
        for (i = 0; i < 4; i++) {   // i = 3 means test for all 3 thyristors together
            
            left_error = TestLeftThyristor(i);
            //right_error = TestRightThyristor(i);
            
            // End test in case of test error
            if ((left_error == true) || (right_error == true))
                break;
        }

        // End error indication
        if (left_error == true)
            SetLeftLedRed();
        else
            SetLeftLedGreen();
        /*if (right_error == true)
            SetRightLedRed();
        else
            SetRightLedGreen();*/
        
    }
        
}

/*void SendVI()
{
    char buf[70];
    uint32_t v, i;
    
    v = GetLeftVoltageMv();
    i = GetLeftCurrentUa();
    
    sprintf(buf, "voltage: %i mV current: %i mV\n\r", v, i);
    TransmitUart(buf, strlen(buf));
    WaitForTransmitUart();
}*/

