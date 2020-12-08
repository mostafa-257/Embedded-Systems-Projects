#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "COMMON.h"

extern E_Status SYSTICK_Init(uint32_t value);
extern E_Status MASTER_SYSTICKIntHandler(void);

#endif
