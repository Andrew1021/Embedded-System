/*********************************************************************
 *
 *                    Simple Delay Routines
 *
 *********************************************************************
 * FileName:        Delay.c
 * Dependencies:    Delay.h
 * Processor:       tm4c129exl
 * Compiler:        TI v20.2.3.LTS
 *
 * Institution:     HTWG Konstanz
 *
 * Author                                         Date       Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Andreas Roth, Kevin Schultz, Sebastian Hofmaier 21.20.2020 Define prototype delay functions
* Andreas Roth, Kevin Schultz, Sebastian Hofmaier 12.01.2020 Adapted delay function for TM4C platform
 ********************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "../header/Delay.h"

//*******************************************************
// \brief Delay for specified time
// \param  ui32time :uint32_t
// \return void
//*******************************************************
int Delay(uint32_t ui32time)
{
    // 1 clock cycle = 1 / SysCtlClockGet() second
    // 1 SysCtlDelay = 3 clock cycle = 3 / SysCtlClockGet() second
    // 1 second = SysCtlClockGet() / 3
    // 0.001 second = 1 ms = SysCtlClockGet() / 3 / 1000
    // 0,000001 second = 1 us = SysCtlClockGet() / 3 / 1000000
    SysCtlDelay(ui32time);

    return (1); // Success
}

//*******************************************************
// \brief Delay for specified milliseconds
// \param  ui32ms :uint32_t
// \return void
//*******************************************************
int Delay_Ms(uint32_t ui32ms)
{
    // 1 clock cycle = 1 / SysCtlClockGet() second
    // 1 SysCtlDelay = 3 clock cycle = 3 / SysCtlClockGet() second
    // 1 second = SysCtlClockGet() / 3
    // 0.001 second = 1 ms = SysCtlClockGet() / 3 / 1000
    SysCtlDelay(ui32ms * (SysCtlClockGet() / 3 / 1000));

    return (1); // Success
}

//*******************************************************
// \brief Delay for specified microseconds
// \param  ui32us :uint32_t
// \return void
//*******************************************************
int Delay_Us(uint32_t ui32us)
{
    // 1 clock cycle = 1 / SysCtlClockGet() second
    // 1 SysCtlDelay = 3 clock cycle = 3 / SysCtlClockGet() second
    // 1 second = SysCtlClockGet() / 3
    // 0,000001 second = 1 us = SysCtlClockGet() / 3 / 1000000
    SysCtlDelay(ui32us * (SysCtlClockGet() / 3 / 1000000));

    return (1); // Success
}
