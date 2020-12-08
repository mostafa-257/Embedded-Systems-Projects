#ifndef SWITCH_H_
#define SWITCH_H_

#include "COMMON.h"

E_Status SWITCH_Init(uint8_t switch_num);
E_Status SWITCH_GetStatus(uint8_t switch_num, uint8_t * status);

#endif
