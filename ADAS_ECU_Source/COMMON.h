#ifndef COMMON_H_
#define COMMON_H_

#include "tm4c123gh6pm.h"
#include <stdlib.h>
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

typedef unsigned char E_Status;

#define PORTA 0U
#define PORTB 1U
#define PORTC 2U
#define PORTD 3U
#define PORTE 4U
#define PORTF 5U

#define UART0 6U
#define UART1 7U
#define UART2 8U
#define UART3 9U
#define UART4 10U
#define UART5 11U
#define UART6 12U
#define UART7 13U

#define SYSTEM       0x00000000U
#define PIOSC        0x00000005U

#define PIN0 0U
#define PIN1 1U
#define PIN2 2U
#define PIN3 3U
#define PIN4 4U
#define PIN5 5U
#define PIN6 6U
#define PIN7 7U

#define OUTPUT 0U
#define INPUT 1U
#define INPUT_PULLUP   2U
#define INPUT_PULLDOWN 3U
#define INPUT_CAN 4U
#define OUTPUT_CAN 5U

#define CAN_CH0 14U

#define CAN_TX 0U
#define CAN_RX 1U

#define TOKEN_ID       1U
#define STATECHANGE_ID 2U
#define DISTANCE_ID    3U

#define SWITCH_CH1 4U
#define SWITCH_CH2 0U

#define E_OK  0U
#define E_NOK 1U

#define LOW  0U
#define HIGH 1U

#define LAMP_RED 1U
#define LAMP_BLUE 2U
#define LAMP_GREEN 3U
#define LAMP_WHITE 4U

#define NO_OBSTCALE 4U
#define SENSOR_ERR 0U

/* BIT COLOUR MASKING
    ECU_3   ECU_2
  7 6 5 4 |3 2 1 0
  R G B W |R G B W */

#define ECU2_WHITE 1U<<0
#define ECU2_BLUE 1U<<1
#define ECU2_GREEN 1U<<2
#define ECU2_RED 1U<<3
#define ECU3_WHITE 1U<<4
#define ECU3_BLUE 1U<<5
#define ECU3_GREEN 1U<<6
#define ECU3_RED 1U<<7

/* BIT SWITCH MASKING
    ECU_3           ECU_2
7   6   5   4  |3   2   1   0
U   U  SW2 SW1 |U   U  SW2 SW1 */

#define DIR_RGB 1U
#define DIR_RBG 2U
#define DIR_BGR 3U
#define DIR_BRG 4U
#define DIR_GBR 5U
#define DIR_GRB 6U

#define GREEN2_RED3    0X84U
#define BLUE2_RED3     0X82U
#define WHITE2_RED3    0X81U

#define RED2_GREEN3    0X48U
#define BLUE2_GREEN3   0X42U
#define WHITE2_GREEN3  0X41U

#define RED2_BLUE3     0X28U
#define GREEN2_BLUE3   0X24U
#define WHITE2_BLUE3   0X21U

#define RED2_WHITE3    0X18U
#define BLUE2_WHITE3   0X12U
#define GREEN2_WHITE3  0X14U

#define ECU2_SW1 0x01U
#define ECU2_SW2 0X02U
#define ECU3_SW1 0X10U
#define ECU3_SW2 0X20U

#define ECU_NODE2 0U
#define ECU_NODE3 1U

#define RXFlag_DN 0U
#define RXFlag_UP 1U

#define TOKENPERIOD 16000000U
#define SENSORPERIOD 1600000U
#define BAUDRATE 115200U

uint8_t i;
uint8_t e;

int32_t UART_Data[2];
int32_t DC_Data;
uint32_t DST_Data;

#endif 
