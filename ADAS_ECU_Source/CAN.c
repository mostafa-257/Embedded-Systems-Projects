#include <stdlib.h>
#include "CAN.h"
#include "CLK.h"
#include "DIO.h"
#include "uartstdio.h"

E_Status CAN_Init(uint8_t channel)
{
    static E_Status CANInit_Status;
    if(channel == CAN_CH0)
    {
        /*Port number for CAN0 peripheral is MCU dependent.
        In the case of a TM4C123GH6PM MCU the peripheral is attached to GPIO port B.*/
        CANInit_Status = CLK_Init(PORTB);
        CANInit_Status |= CLK_Init(CAN_CH0);
        CANInit_Status |= DIO_InitPort(PORTB);
        CANInit_Status |= DIO_InitPin(PORTB, PIN4, INPUT_CAN);
        CANInit_Status |= DIO_InitPin(PORTB, PIN5, OUTPUT_CAN);

        /* PORTB Port Control to allow for CAN0 functionality.*/
        GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFF00FFFFU) + 0x00880000U;

        /*CAN Interrupt Initialization."Using TivaWare"*/
        CANInit((uint32_t)CAN0_BASE);
        CANBitRateSet((uint32_t)CAN0_BASE, SysCtlClockGet(), 500000U);
        CANIntEnable((uint32_t)CAN0_BASE, (uint32_t)CAN_INT_MASTER | (uint32_t)CAN_INT_ERROR | (uint32_t)CAN_INT_STATUS);
        IntEnable((uint32_t)INT_CAN0);
        CANEnable((uint32_t)CAN0_BASE);
    }
    else
    {
        CANInit_Status = E_NOK;
    }
    return CANInit_Status;
}
E_Status CANObject_Init(tCANMsgObject * CANObj, uint8_t * msgData, uint8_t MODE, uint32_t MSG_ID, uint32_t OBJ_ID)
{
    rxFlag = 0U;
    rxFlag_d = 0U;
    errFlag = 0U;

    /*The MSG_ID object is user defined(1-32) and there are no preset macros for it.*/
    static E_Status CANObjectInit_Status;
    if(MODE == CAN_TX)
    {
        (*CANObj).ui32MsgID = MSG_ID;
        (*CANObj).ui32MsgIDMask = 0xfffffU;
        (*CANObj).ui32Flags = ((uint32_t)MSG_OBJ_TX_INT_ENABLE | (uint32_t)MSG_OBJ_USE_ID_FILTER | (uint32_t)MSG_OBJ_EXTENDED_ID);
        (*CANObj).ui32MsgLen = 8U;
        (*CANObj).pui8MsgData = msgData;

        CANObjectInit_Status = E_OK;
    }
    else if(MODE == CAN_RX)
    {
        (*CANObj).ui32MsgID = MSG_ID;
        (*CANObj).ui32MsgIDMask = 0xfffffU;
        (*CANObj).ui32Flags = ((uint32_t)MSG_OBJ_RX_INT_ENABLE | (uint32_t)MSG_OBJ_USE_ID_FILTER | (uint32_t)MSG_OBJ_EXTENDED_ID);
        (*CANObj).ui32MsgLen = 8U;
        (*CANObj).pui8MsgData = msgData;
        CANMessageSet((uint32_t)CAN0_BASE, OBJ_ID, CANObj, MSG_OBJ_TYPE_RX);
        CANObjectInit_Status = E_OK;
    }
    else
    {
        CANObjectInit_Status = E_NOK;
    }
    return CANObjectInit_Status;
}
E_Status CAN_Send(tCANMsgObject CANObj, uint32_t OBJ_ID)
{
    static E_Status CANSend_Status;
    if(CANObj.pui8MsgData != NULL)
    {
        CANMessageSet((uint32_t)CAN0_BASE, OBJ_ID, &CANObj, MSG_OBJ_TYPE_TX);
        UARTprintf("\nSending >> Msg ID = 0x%08X len = %u data = %d",CANObj.ui32MsgID, CANObj.ui32MsgLen , *CANObj.pui8MsgData);
        CANSend_Status = E_OK;
    }
    else if(CANObj.pui8MsgData == NULL)
    {
        UARTprintf("\nError Sending CAN Message !");
        CANSend_Status = E_NOK;
    }
    else
    {}
    return CANSend_Status;
}
E_Status CAN_Recieve(tCANMsgObject CANObj, uint32_t OBJ_ID)
{
    static E_Status CANRecieve_Status;
    if(CANObj.pui8MsgData != NULL)
    {
        CANMessageGet((uint32_t)CAN0_BASE, OBJ_ID, &CANObj, 0U);
        UARTprintf("\nRecieving >> Msg ID = 0x%08X len = %u data = %d",CANObj.ui32MsgID, CANObj.ui32MsgLen , *CANObj.pui8MsgData);
        CANRecieve_Status = E_OK;
    }
    else if(CANObj.ui32Flags & (uint32_t)MSG_OBJ_DATA_LOST)
    {
        UARTprintf("CAN message loss detected\n");
        CANRecieve_Status = E_NOK;
    }
    else
    {
        UARTprintf("\nError Recieving CAN Message !");
        CANRecieve_Status = E_NOK;
    }

    return CANRecieve_Status;
}

void CANIntHandler(void)
{
    uint32_t intCause;
    intCause = CANIntStatus((uint32_t)CAN0_BASE, CAN_INT_STS_CAUSE);

    if(intCause == (uint32_t)CAN_INT_INTID_STATUS)
    {
        intCause = CANStatusGet((uint32_t)CAN0_BASE, CAN_STS_CONTROL);
        errFlag = 1U;
    }

    else if(intCause == TOKEN_ID)
    {
        CANIntClear((uint32_t)CAN0_BASE, TOKEN_ID);
        rxFlag = 1U;
        errFlag = 0U;
    }

    else if(intCause == STATECHANGE_ID)
    {
        CANIntClear((uint32_t)CAN0_BASE, STATECHANGE_ID);
        errFlag = 0U;
    }
    else if((intCause == DISTANCE_ID) && (e == ECU_NODE2))
        {
            CANIntClear((uint32_t)CAN0_BASE, DISTANCE_ID);
            errFlag = 0U;
        }
    else if((intCause == DISTANCE_ID) && (e == ECU_NODE3))
           {
               CANIntClear((uint32_t)CAN0_BASE, DISTANCE_ID);
               errFlag = 0U;
               rxFlag_d = 1U;
           }

    else{}
}

