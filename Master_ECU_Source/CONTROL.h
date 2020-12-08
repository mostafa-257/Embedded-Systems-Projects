#ifndef CONTROL_H_
#define CONTROL_H_

#include "COMMON.h"
#include "LAMP.h"
#include "SWITCH.h"

extern E_Status CONTROL_Init(void);
extern E_Status CONTROL_Token(void);
extern E_Status CONTROL_Lamps(void);

#endif /* CONTROL_H_ */
