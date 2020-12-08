#include <LAMP.h>
#include "COMMON.h"

E_Status LAMP_Init(uint8_t lamp_ch_num)
{
    static E_Status LAMPInit_Status;
    if((lamp_ch_num < LAMP_RED) || (lamp_ch_num > LAMP_WHITE))
    {
        LAMPInit_Status = E_NOK;
    }
    else
    {
    switch (lamp_ch_num)
    {
        case LAMP_RED:
            LAMPInit_Status |= DIO_InitPin(PORTF,LAMP_RED,OUTPUT);
            break;
        case LAMP_BLUE:
            LAMPInit_Status |= DIO_InitPin(PORTF,LAMP_BLUE,OUTPUT);
            break;
        case LAMP_GREEN:
            LAMPInit_Status |= DIO_InitPin(PORTF,LAMP_GREEN,OUTPUT);
            break;
        case LAMP_WHITE:
            LAMPInit_Status |= DIO_InitPin(PORTF,LAMP_RED,OUTPUT);
            LAMPInit_Status |= DIO_InitPin(PORTF,LAMP_BLUE,OUTPUT);
            LAMPInit_Status |= DIO_InitPin(PORTF,LAMP_GREEN,OUTPUT);
            break;
        default:
            break;
    }
        LAMPInit_Status = E_OK;
    }
    return LAMPInit_Status;
}
E_Status LAMP_On(uint8_t lamp_ch_num)
{
    static E_Status LAMPOn_Status;

       if((lamp_ch_num < LAMP_RED) || (lamp_ch_num > LAMP_WHITE))
       {
           LAMPOn_Status = E_NOK;
       }
       else
       {
       switch (lamp_ch_num)
       {
           case LAMP_RED:
               LAMPOn_Status |= DIO_PinWrite(PORTF,LAMP_RED,HIGH);
               break;
           case LAMP_BLUE:
               LAMPOn_Status |= DIO_PinWrite(PORTF,LAMP_BLUE,HIGH);
               break;
           case LAMP_GREEN:
               LAMPOn_Status |= DIO_PinWrite(PORTF,LAMP_GREEN,HIGH);
               break;
           case LAMP_WHITE:
               LAMPOn_Status |= DIO_PinWrite(PORTF,LAMP_RED,HIGH);
               LAMPOn_Status |= DIO_PinWrite(PORTF,LAMP_BLUE,HIGH);
               LAMPOn_Status |= DIO_PinWrite(PORTF,LAMP_GREEN,HIGH);
               break;
           default:
               break;
        }
       LAMPOn_Status = E_OK;
       }
       return LAMPOn_Status;
}
E_Status LAMP_Off(uint8_t lamp_ch_num)
{
    static E_Status LAMPOff_Status;

       if((lamp_ch_num < LAMP_RED) || (lamp_ch_num > LAMP_WHITE))
       {
           LAMPOff_Status = E_NOK;
       }
       else
       {
       switch (lamp_ch_num)
       {
           case LAMP_RED:
               LAMPOff_Status |= DIO_PinWrite(PORTF,LAMP_RED,LOW);
               break;
           case LAMP_BLUE:
               LAMPOff_Status |= DIO_PinWrite(PORTF,LAMP_BLUE,LOW);
               break;
           case LAMP_GREEN:
               LAMPOff_Status |= DIO_PinWrite(PORTF,LAMP_GREEN,LOW);
               break;
           case LAMP_WHITE:
               LAMPOff_Status |= DIO_PinWrite(PORTF,LAMP_RED,LOW);
               LAMPOff_Status |= DIO_PinWrite(PORTF,LAMP_BLUE,LOW);
               LAMPOff_Status |= DIO_PinWrite(PORTF,LAMP_GREEN,LOW);
               break;
           default:
               break;
        }
       LAMPOff_Status = E_OK;
       }
       return LAMPOff_Status;
}


