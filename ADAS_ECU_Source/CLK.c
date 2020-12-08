#include "CLK.h"

E_Status CLK_Init(uint8_t port)
{
    static E_Status CLKInit_Status;

    if(port <= PORTF)

       {
         SYSCTL_RCGCGPIO_R |= (uint32_t)((uint32_t)1 << (uint32_t)port);
         while((SYSCTL_PRGPIO_R & (uint32_t)((uint32_t)1 << (uint32_t)port)) == 0U){}

         CLKInit_Status = E_OK;
       }

    else if(port == CAN_CH0)
    {
        SYSCTL_RCGC0_R |= 0x01000000U;
        while((SYSCTL_RCGC0_R & 0x01000000U) == LOW){};

        CLKInit_Status = E_OK;
    }

    else if((port >= UART0) && (port <= UART7))
    {
        SYSCTL_RCGCUART_R |= (uint32_t)((uint32_t)1 << ((uint32_t)port - 6U));
        while((SYSCTL_RCGCUART_R & (uint32_t)((uint32_t)1 << ((uint32_t)port - 6U))) == LOW){};

        CLKInit_Status = E_OK;
    }

    else
    {
        CLKInit_Status = E_NOK;
    }
    return CLKInit_Status;
}



