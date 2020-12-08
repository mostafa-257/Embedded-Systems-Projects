#ifndef DIO_H_
#define DIO_H_

#include "COMMON.h"

extern E_Status DIO_InitPort(uint8_t port);
extern E_Status DIO_InitPin(uint8_t port, uint8_t pin, uint8_t mode);
extern E_Status DIO_PinRead(uint8_t port, uint8_t pin, uint8_t* data);
extern E_Status DIO_PinWrite(uint8_t port, uint8_t pin, uint8_t data);

#endif
