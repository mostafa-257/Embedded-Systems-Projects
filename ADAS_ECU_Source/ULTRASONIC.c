#include "ULTRASONIC.h"
#include "CONTROLSUB.h"

E_Status ULTRASONIC_Init(void)
{
    static E_Status ULTRASONICInit_Status;
    ULTRASONICInit_Status = UART_Init(UART0,BAUDRATE,PIOSC,1U);
    return ULTRASONICInit_Status;
}

E_Status CALCULATE_Distance(void)
{
    static E_Status CALCDistance_Status;

    DC_Data = (int32_t)(UART_Data[0]*10) + (int32_t)UART_Data[1];

    if(DC_Data <= 10)
    {
        DST_Data = SENSOR_ERR;
        CALCDistance_Status = E_OK;
    }
    else if((DC_Data > 10) && (DC_Data <= 20))
    {
        DST_Data = 1U;
        CALCDistance_Status = E_OK;
    }

    else if((DC_Data > 20) && (DC_Data <= 40))
    {
        DST_Data = 2U;
        CALCDistance_Status = E_OK;
    }

    else if((DC_Data > 40) && (DC_Data <= 60))
    {
        DST_Data = 3U;
        CALCDistance_Status = E_OK;
    }

    else if((DC_Data > 60) && (DC_Data <= 99))
    {
        DST_Data = NO_OBSTCALE;
        CALCDistance_Status = E_OK;
    }
    else
    {
        CALCDistance_Status = E_NOK;
    }

    return CALCDistance_Status;
}
