#ifndef CONTROLSUB_H_
#define CONTROLSUB_H_

#include "COMMON.h"
#include "LAMP.h"
#include "SWITCH.h"
#include "CAN.h"


extern E_Status CONTROLSUB_Init(uint8_t ecu);
extern E_Status PROXIMITY_Report(void);
extern E_Status ADAS_Control(void);
extern E_Status CONTROLSUB(uint8_t node);

#endif
