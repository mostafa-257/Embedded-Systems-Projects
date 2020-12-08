#ifndef LAMP_H_
#define LAMP_H_
#include "COMMON.h"
#include "DIO.h"

E_Status LAMP_Init(uint8_t lamp_ch_num);
E_Status LAMP_On(uint8_t lamp_ch_num);
E_Status LAMP_Off(uint8_t lamp_ch_num);



#endif
