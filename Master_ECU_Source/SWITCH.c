#include "SWITCH.h"
#include "DIO.h"
#include "COMMON.h"

E_Status SWITCH_Init(uint8_t switch_num)
{
    E_Status SWITCHInit_Status;

    if ((switch_num != SWITCH_CH1) && (switch_num != SWITCH_CH2))
    {
        SWITCHInit_Status = E_NOK;
    }
    else
    {
    if(switch_num == SWITCH_CH1)
    {
        SWITCHInit_Status |= DIO_InitPin(PORTF, SWITCH_CH1 ,INPUT_PULLUP);
    }
    if(switch_num == SWITCH_CH2)
    {
        SWITCHInit_Status |= DIO_InitPin(PORTF, SWITCH_CH2 ,INPUT_PULLUP);
    }
    SWITCHInit_Status = E_OK;
    }
    return SWITCHInit_Status;
}
E_Status SWITCH_GetStatus(uint8_t switch_num, uint8_t * status)
{
    uint8_t dataa = 5;
    uint8_t * d = &dataa;

    static E_Status SWITCHState_Status;

    if ((switch_num != SWITCH_CH1) && (switch_num != SWITCH_CH2))
    {
        SWITCHState_Status = E_NOK;
    }
    else
    {
    if (switch_num == SWITCH_CH1)
    {
        SWITCHState_Status |= DIO_PinRead(PORTF,SWITCH_CH1,d);
         *status = *d;
    }

    if (switch_num == SWITCH_CH2)
       {
        SWITCHState_Status |= DIO_PinRead(PORTF,SWITCH_CH2,d);
            *status = *d;
       }
    SWITCHState_Status = E_OK;
    }
    return SWITCHState_Status;
}
