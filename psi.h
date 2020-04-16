/*

*/

// cstd
#include <stdbool.h>

#ifndef __PSI_H__
#define __PSI_H__


// All functions return "true" in case of test error

// Wait for already tested board to unconnect
void WaitForUnconnectBoard(void);
// Wait for being tested boards to connect
void WaitForConnectBoard(void);
// Test zener diodes current at 12V
bool TestLeftZenerLeakage(void);
bool TestRightZenerLeakage(void);
// Test zener diodes current at 16V
bool TestLeftZenerProtection(void);
bool TestRightZenerProtection(void);
// Test thyristor switch on
bool TestLeftThyristor(int n);
bool TestRightThyristor(int n);
// Check if there is connection to thyristor gate
bool CheckConnection(void);

#endif
