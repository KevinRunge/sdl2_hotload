/*
 * Really simple library code
 */

#include "libcode.h"
#include <stdio.h>

// Expects a c style string (no error checking)
void PrintMessage(const char* msg)
{
    printf("msg = %s\n", msg);
}

//
// The export API
//
extern "C" void GetLibCodeAPI(LibCodeFncTable* libCode)
{
    // fill the struct
    libCode->PrintMessage = &PrintMessage;
    // other function pointers here
}
