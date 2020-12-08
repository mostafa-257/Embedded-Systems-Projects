#include "DIO.h"
#include "tm4c123gh6pm.h"
#include <stdlib.h>
#include <stdbool.h>
#include "COMMON.h"

static volatile uint32_t * PUR[6] = {&GPIO_PORTA_PUR_R, &GPIO_PORTB_PUR_R, &GPIO_PORTC_PUR_R, &GPIO_PORTD_PUR_R, &GPIO_PORTE_PUR_R, &GPIO_PORTF_PUR_R};
static volatile uint32_t * PDR[6] = {&GPIO_PORTA_PDR_R, &GPIO_PORTB_PDR_R, &GPIO_PORTC_PDR_R, &GPIO_PORTD_PDR_R, &GPIO_PORTE_PDR_R, &GPIO_PORTF_PDR_R};
static volatile uint32_t * DATA[6] = {&GPIO_PORTA_DATA_R, &GPIO_PORTB_DATA_R, &GPIO_PORTC_DATA_R, &GPIO_PORTD_DATA_R, &GPIO_PORTE_DATA_R, &GPIO_PORTF_DATA_R};

E_Status DIO_InitPort(uint8_t port)
{
    static E_Status INITPort_Status;

    static volatile uint32_t * LOCK[6] = {&GPIO_PORTA_LOCK_R, &GPIO_PORTB_LOCK_R, &GPIO_PORTC_LOCK_R, &GPIO_PORTD_LOCK_R, &GPIO_PORTE_LOCK_R, &GPIO_PORTF_LOCK_R};
    static volatile uint32_t * ClockRelease[6] = {&GPIO_PORTA_CR_R, &GPIO_PORTB_CR_R, &GPIO_PORTC_CR_R, &GPIO_PORTD_CR_R, &GPIO_PORTE_CR_R, &GPIO_PORTF_CR_R};

      if(port > PORTF)
      {
          INITPort_Status = E_NOK;
      }
      else
      {
      *LOCK[port] = 0x4C4F434BU;
      *ClockRelease[port] = 0x1FU;

      INITPort_Status = E_OK;
      }
      return INITPort_Status;
}

E_Status DIO_InitPin(uint8_t port, uint8_t pin, uint8_t mode)
{
    static E_Status INITPin_Status;

    static volatile uint32_t * DIR[6] = {&GPIO_PORTA_DIR_R, &GPIO_PORTB_DIR_R, &GPIO_PORTC_DIR_R, &GPIO_PORTD_DIR_R, &GPIO_PORTE_DIR_R, &GPIO_PORTF_DIR_R};
    static volatile uint32_t * DEN[6] = {&GPIO_PORTA_DEN_R, &GPIO_PORTB_DEN_R, &GPIO_PORTC_DEN_R, &GPIO_PORTD_DEN_R, &GPIO_PORTE_DEN_R, &GPIO_PORTF_DEN_R};

    if((port > PORTF) || (pin > PIN7) || (mode > OUTPUT_CAN))
    {
        INITPin_Status = E_NOK;
    }
    else
    {
    switch(mode)
    {
      case OUTPUT:
          *DIR[port] |= (uint32_t)((uint32_t)1 << (uint32_t)pin);
          *DEN[port] |= (uint32_t)((uint32_t)1 << (uint32_t)pin);
          *DATA[port] &= (uint32_t)~((uint32_t)1 << (uint32_t)pin);
          break;

      case INPUT:
          *DIR[port] |= (uint32_t)((uint32_t)0 << (uint32_t)pin);
          *DEN[port] |= (uint32_t)((uint32_t)1 << (uint32_t)pin);
          break;

      case INPUT_PULLUP:
          *DIR[port] |= (uint32_t)((uint32_t)0 << (uint32_t)pin);
          *DEN[port] |= (uint32_t)((uint32_t)1 << (uint32_t)pin);
          *PUR[port] |= (uint32_t)((uint32_t)1 << (uint32_t)pin);
          break;

      case INPUT_PULLDOWN:
          *DIR[port] |= (uint32_t)((uint32_t)0 << (uint32_t)pin);
          *DEN[port] |= (uint32_t)((uint32_t)1 << (uint32_t)pin);
          *PDR[port] |= (uint32_t)((uint32_t)1 << (uint32_t)pin);
          break;

      case INPUT_CAN:
          *DIR[port] |= (uint32_t)((uint32_t)0 << (uint32_t)pin);
          *DEN[port] |= (uint32_t)((uint32_t)1 << (uint32_t)pin);
          GPIO_PORTB_AFSEL_R |= (uint32_t)((uint32_t)1 << (uint32_t)pin);
          break;

      case OUTPUT_CAN:
          *DIR[port] |= (uint32_t)((uint32_t)1 << (uint32_t)pin);
          *DEN[port] |= (uint32_t)((uint32_t)1 << (uint32_t)pin);
          *DATA[port] &= (uint32_t)~((uint32_t)1 << (uint32_t)pin);
          GPIO_PORTB_AFSEL_R |= (uint32_t)((uint32_t)1 << (uint32_t)pin);
          break;
      default:
          break;
    }
    INITPin_Status = E_OK;
  }
    return INITPin_Status;
}
E_Status DIO_PinRead(uint8_t port, uint8_t pin, uint8_t* data)
{
    static E_Status PINRead_Status;

    if((port > PORTF) || (pin > PIN7) || (data == NULL))
    {
        PINRead_Status = E_NOK;
    }
    else
    {
    if ((*PUR[port] & (uint32_t)((uint32_t)1 << (uint32_t)pin)) == (uint32_t)((uint32_t)1 << (uint32_t)pin))
    {
        if ((*DATA[port] & (uint32_t)((uint32_t)1 << (uint32_t)pin)) == (uint32_t)((uint32_t)1 << (uint32_t)pin))
        {
            *data = LOW;
        }
        else
        {
            *data = HIGH;
        }
    }
    else if ((*PDR[port] & (uint32_t)((uint32_t)1 << (uint32_t)pin)) == (uint32_t)((uint32_t)1 << (uint32_t)pin))
    {
        if ((*DATA[port] & (uint32_t)((uint32_t)1 << (uint32_t)pin)) == (uint32_t)((uint32_t)1 << (uint32_t)pin))
        {
            *data = HIGH;
        }
        else
        {
            *data = LOW;
        }
    }
    else
    {
        PINRead_Status = E_NOK;
    }
    PINRead_Status = E_OK;
  }
   return PINRead_Status;
}

E_Status DIO_PinWrite(uint8_t port, uint8_t pin, uint8_t data)
{
    static E_Status PINWrite_Status;

    if((port > PORTF) || (pin > PIN7))
     {
        PINWrite_Status = E_NOK;
     }
    else
    {
    if (data == HIGH)
    {
        *DATA[port] |= (uint32_t)((uint32_t)1 << (uint32_t)pin);
    }
    else if (data == LOW)
    {
        *DATA[port] &= (uint32_t)~((uint32_t)1 << (uint32_t)pin);
    }
    else{}

    PINWrite_Status = E_OK;
    }
    return PINWrite_Status;
}
