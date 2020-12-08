#include "SYSTICK.H"
#include "UART.h"
#include "CONTROLSUB.h"

E_Status SYSTICK_Init(uint32_t value)
{
    static E_Status SYSTICKInit_Status;

    if(value <= TOKENPERIOD)
    {
        NVIC_ST_CTRL_R = 0U;
        NVIC_ST_RELOAD_R = value - 1U;
        NVIC_ST_CURRENT_R = 0U;
        NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFFU) | 0x40000000U;
        NVIC_ST_CTRL_R = 0x07U;

        SYSTICKInit_Status = E_OK;
    }

    else
    {
        SYSTICKInit_Status = E_NOK;
    }

    return SYSTICKInit_Status;
}
void SYSTICKIntHandler(void)
{
    PROXIMITY_Report();
}
