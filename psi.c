// cstd
#include <stdbool.h>

//user
#include "psi.h"
#include "hardware.h"
#include "timer.h"


// All functions return "true" in case of test error


// Wait for already tested board to unconnect
void WaitForUnconnectBoard(void)
{
    if (IsTamperPressed()) {
        while (IsTamperPressed())
            ;
        delay_ms(100);
    }
}
// Wait for being tested boards to connect
void WaitForConnectBoard(void)
{
    do {
        while (! IsTamperPressed())
            ;
        delay_ms(100);
    } while (! IsTamperPressed());
}
// Test zener diodes current at 12V
bool TestLeftZenerLeakage(void)
{
    bool res;
    
    // Switch on power
    SetLeftPower12V();
    EnableLeftPower();
    
    delay_ms(100);
    
    // Leakage current is too big -> error
    res = (GetLeftCurrentUa() > THRESHOLD_I);
    
    // Switch off power
    DisableLeftPower();
    
    return res;
}
bool TestRightZenerLeakage(void)
{
    
}
// Test zener diodes current at 16V
bool TestLeftZenerProtection(void)
{
    bool res;
    
    // Switch on power
    SetLeftPower16V();
    EnableLeftPower();
    
    delay_ms(100);
    
    // Voltage should be low because of current limitation by LM317
    res = (GetLeftVoltageMv() > THRESHOLD_V_16);
    
    // Switch off power
    DisableLeftPower();
    
    return res;
}
bool TestRightZenerProtection(void)
{
    
}
// Test thyristor switch on
bool TestLeftThyristor(int n)
{
    bool res;
    
    // Switch on power
    SetLeftPower12V();
    EnableLeftPower();
    
    // Choose tested thyristor (n = 3 enables all three thyristors together)
    EnableLeftThyristor(n);
    delay_ms(1);
    
    // Connect low load first (about 120mA)
    ConnectLeftLowLoad();
    delay_ms(100);
    
    
    // Thyristors should NOT be open so voltage should be = 12V
    if (GetLeftVoltageMv() < THRESHOLD_V_12_C) {
        // error
        // Switch off hardware
        DisableLeftPower();
        DisconnectLeftLoad();
        DisableLeftThyristors();
        
        return true;    // error
    }
    
    // Connect high load
    ConnectLeftHighLoad();
    delay_ms(100);
    
    
    // Thyristors should be open so
    // voltage should be low because of current limitation by LM317
    res = (GetLeftVoltageMv() > THRESHOLD_V_12_C);
    
    // Switch off hardware
    DisableLeftPower();
    DisconnectLeftLoad();
    DisableLeftThyristors();
    
    delay_ms(200);
    
    return res;
}
bool TestRightThyristor(int n)
{
    
}

// Check if there is connection to thyristor gate
bool CheckConnection()
{
    bool res;
    
    // Switch on power
    SetLeftPower12V();
    EnableLeftPower();
    
    // Disable all thyristors
    DisableLeftThyristors();
    delay_ms(1);
    
    // Connect low load first
    // Need for properly disable thyristors
    ConnectLeftLowLoad();
    delay_ms(100);
    
    // Connect high load
    ConnectLeftHighLoad();
    delay_ms(100);
    
    // Thyristors should NOT be open so voltage should be about 11V
    res = (GetLeftVoltageMv() < THRESHOLD_V_12_C);
    
    // Switch off hardware
    DisableLeftPower();
    DisconnectLeftLoad();
    DisableLeftThyristors();
    
    delay_ms(200);
    
    return res;
}
