#ifndef CAN_H_
#define CAN_H_

#include "COMMON.h"
#include "tm4c123gh6pm.h"

volatile bool rxFlag;
volatile bool errFlag;
volatile bool rxFlag_d;

extern E_Status CAN_Init(uint8_t channel);
extern E_Status CANObject_Init(tCANMsgObject * CANObj, uint8_t * msgData, uint8_t MODE, uint32_t MSG_ID, uint32_t OBJ_ID);
extern E_Status CAN_Send(tCANMsgObject CANObj, uint32_t OBJ_ID);
extern E_Status CAN_Recieve(tCANMsgObject CANObj, uint32_t OBJ_ID);
extern void CANIntHandler(void);

#endif /* CAN_H_ */
