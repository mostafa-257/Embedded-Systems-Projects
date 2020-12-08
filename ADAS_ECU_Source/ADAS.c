#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "COMMON.h"
#include "CLK.h"
#include "DIO.h"
#include "LAMP.h"
#include "SWITCH.h"
#include "tm4c123gh6pm.h"
#include "CAN.h"
#include "CONTROLSUB.h"

void main(void);

void main(void)
{
    E_Status MAIN_Status;

    e = ECU_NODE3;
    MAIN_Status = CONTROLSUB_Init(e);

    while(!MAIN_Status)
    {
        MAIN_Status = CONTROLSUB(e);
    }

}
