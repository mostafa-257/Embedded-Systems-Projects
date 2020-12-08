#ifndef UART_H_
#define UART_H_

#include "COMMON.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

extern E_Status UART_Init(uint8_t port,uint32_t baud,uint32_t clksrc,bool xInt);
extern void UARTIntHandler(void);


#endif
