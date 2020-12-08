#include <CONTROLSUB.h>
#include "CLK.h"
#include "LAMP.h"
#include "SWITCH.h"
#include "CAN.h"
#include "COMMON.h"
#include "UART.h"
#include "ULTRASONIC.h"
#include "SYSTICK.h"

tCANMsgObject colourCANMsg;
tCANMsgObject switchCANMsg;
tCANMsgObject distanceCANMsg;

uint32_t CLR_Data;
uint32_t SW_Data;

static uint8_t * CLRMsgData = (uint8_t*)&CLR_Data;
static uint8_t * DSTMsgData = (uint8_t*)&DST_Data;

E_Status CONTROLSUB_Init(uint8_t ecu)
{
    E_Status CTLSUBInit_Status;

    static uint8_t * SWMsgData = (uint8_t*)&SW_Data;

    SysCtlClockSet((uint32_t)SYSCTL_SYSDIV_1 | (uint32_t)SYSCTL_USE_OSC | (uint32_t)SYSCTL_OSC_MAIN | (uint32_t)SYSCTL_XTAL_16MHZ);
    CTLSUBInit_Status = CLK_Init(PORTF);
    CTLSUBInit_Status |= DIO_InitPort(PORTF);
    CTLSUBInit_Status |= LAMP_Init(LAMP_RED);
    CTLSUBInit_Status |= LAMP_Init(LAMP_BLUE);
    CTLSUBInit_Status |= LAMP_Init(LAMP_GREEN);
    CTLSUBInit_Status |= SWITCH_Init(SWITCH_CH1);
    CTLSUBInit_Status |= SWITCH_Init(SWITCH_CH2);
    CTLSUBInit_Status |= CAN_Init(CAN_CH0);
    CTLSUBInit_Status |= CANObject_Init(&colourCANMsg, CLRMsgData, CAN_RX, 1001U, TOKEN_ID);
    CTLSUBInit_Status |= CANObject_Init(&switchCANMsg, SWMsgData, CAN_TX, 2002U, STATECHANGE_ID);

    if(ecu == ECU_NODE2)
    {
        CTLSUBInit_Status |= ULTRASONIC_Init();
        CTLSUBInit_Status |= CANObject_Init(&distanceCANMsg,DSTMsgData,CAN_TX,3003U,DISTANCE_ID);
        CTLSUBInit_Status |= SYSTICK_Init(SENSORPERIOD);
    }

    else if(ecu == ECU_NODE3)
    {
        CTLSUBInit_Status |= UART_Init(UART0,BAUDRATE,PIOSC,0U);
        CTLSUBInit_Status |= CANObject_Init(&distanceCANMsg,DSTMsgData,CAN_RX,3003U,DISTANCE_ID);
    }
    else
    {
        CTLSUBInit_Status = E_NOK;
    }

    return CTLSUBInit_Status;
}

E_Status PROXIMITY_Report(void)
{
    static E_Status PROXIMITYReport_Status;
    PROXIMITYReport_Status |= CALCULATE_Distance();
    while(errFlag){}
    PROXIMITYReport_Status |= CAN_Send(distanceCANMsg,DISTANCE_ID);

    return PROXIMITYReport_Status;
}

E_Status ADAS_Control(void)
{
    static E_Status ADASControl_Status;

    while(!rxFlag_d){}

    distanceCANMsg.pui8MsgData = DSTMsgData;
    ADASControl_Status |= CAN_Recieve(distanceCANMsg,DISTANCE_ID);

    rxFlag_d = 0U;

    if(DST_Data == SENSOR_ERR)
    {
        UARTprintf("\nSTOP");
    }

    else if(DST_Data == 1U)
    {
        UARTprintf("\nTurn");
    }

    else if(DST_Data == 2U)
    {
        UARTprintf("\nmoving FWD & decreasing Speed");
    }

    else if(DST_Data == 3U)
    {
        UARTprintf("\nmoving FWD");
    }

    else if(DST_Data == NO_OBSTCALE)
    {
        UARTprintf("\nmoving FWD & increasing Speed");
    }
    else{}

    return ADASControl_Status;
}


E_Status CONTROLSUB(uint8_t node)
{

    uint8_t data1 = 0;
    uint8_t data2 = 0;
    uint8_t * SW1_State = &data1;
    uint8_t * SW2_State = &data2;

        static E_Status CTL_Status;

        while(!rxFlag)
        {
            if(node == ECU_NODE3)
            {
            ADAS_Control();
            }
        }
        colourCANMsg.pui8MsgData = CLRMsgData;
        CTL_Status |= CAN_Recieve(colourCANMsg, TOKEN_ID);

        rxFlag = RXFlag_DN;

            if(node == ECU_NODE2)
            {
                while(((CLR_Data & (uint32_t)ECU2_WHITE) == (uint32_t)ECU2_WHITE))
                {

                    CTL_Status |= SWITCH_GetStatus(SWITCH_CH1, SW1_State);
                    CTL_Status |= SWITCH_GetStatus(SWITCH_CH2, SW2_State);

                    LAMP_On(LAMP_WHITE);

                    if(data1 == HIGH)
                    {
                        UARTprintf("\nECU2_SW1");
                        SW_Data = ECU2_SW1;
                        CTL_Status |= CAN_Send(switchCANMsg, STATECHANGE_ID);
                    }
                    if(data2 == HIGH)
                    {
                        UARTprintf("\nECU2_SW2");
                        SW_Data = ECU2_SW2;
                        CTL_Status |= CAN_Send(switchCANMsg, STATECHANGE_ID);
                    }
                    break;
                }
                while((CLR_Data & (uint32_t)ECU2_RED) == (uint32_t)ECU2_RED)
                {
                    rxFlag = RXFlag_DN;
                    LAMP_Off(LAMP_WHITE);
                    LAMP_On(LAMP_RED);
                    break;
                }
                while((CLR_Data & (uint32_t)ECU2_GREEN) == (uint32_t)ECU2_GREEN)
                {
                    rxFlag = RXFlag_DN;
                    LAMP_Off(LAMP_WHITE);
                    LAMP_On(LAMP_GREEN);
                    break;
                }
                while((CLR_Data & (uint32_t)ECU2_BLUE) == (uint32_t)ECU2_BLUE)
                {
                    rxFlag = RXFlag_DN;
                    LAMP_Off(LAMP_WHITE);
                    LAMP_On(LAMP_BLUE);
                    break;
                }
            }
            if(node == ECU_NODE3)
            {
                while(((CLR_Data & (uint32_t)ECU3_WHITE) == (uint32_t)ECU3_WHITE))
                {

                    CTL_Status |= SWITCH_GetStatus(SWITCH_CH1, SW1_State);
                    CTL_Status |= SWITCH_GetStatus(SWITCH_CH2, SW2_State);

                    LAMP_On(LAMP_WHITE);

                    if(data1 == HIGH)
                    {
                        UARTprintf("\nECU3_SW1");
                        SW_Data = ECU3_SW1;
                        CTL_Status |= CAN_Send(switchCANMsg, STATECHANGE_ID);
                    }
                    if(data2 == HIGH)
                    {
                        UARTprintf("\nECU3_SW2");
                        SW_Data = ECU3_SW2;
                        CTL_Status |= CAN_Send(switchCANMsg, STATECHANGE_ID);
                    }
                    break;
                }
                while((CLR_Data & (uint32_t)ECU3_RED) == (uint32_t)ECU3_RED)
                {
                    rxFlag = RXFlag_DN;
                    LAMP_Off(LAMP_WHITE);
                    LAMP_On(LAMP_RED);
                    break;
                }
                while((CLR_Data & (uint32_t)ECU3_GREEN) == (uint32_t)ECU3_GREEN)
                {
                    rxFlag = RXFlag_DN;
                    LAMP_Off(LAMP_WHITE);
                    LAMP_On(LAMP_GREEN);
                    break;
                }
                while((CLR_Data & (uint32_t)ECU3_BLUE) == (uint32_t)ECU3_BLUE)
                {
                    rxFlag = RXFlag_DN;
                    LAMP_Off(LAMP_WHITE);
                    LAMP_On(LAMP_BLUE);
                    break;
                }
            }
            return CTL_Status;
}
