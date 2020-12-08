#include <CONTROL.h>
#include "CLK.h"
#include "LAMP.h"
#include "SWITCH.h"
#include "CAN.h"
#include "COMMON.h"
#include "UART.h"
#include "SYSTICK.h"
#include "uartstdio.h"

tCANMsgObject colourCANMsg;
tCANMsgObject switchCANMsg;

uint32_t CLR_Data;
uint32_t SW_Data;

static uint8_t * CLRMsgData = (uint8_t*)&CLR_Data;
static uint8_t * SWMsgData = (uint8_t*)&SW_Data;

static uint8_t ECU1_state;
static uint8_t DIRECTION;
static uint8_t Flag;

E_Status CONTROL_Init(void)
{
        static E_Status CTLInit_Status;

        ECU1_state = LAMP_RED;
        DIRECTION = DIR_RGB;
        Flag = 0U;

        SysCtlClockSet((uint32_t)SYSCTL_SYSDIV_1 | (uint32_t)SYSCTL_USE_OSC | (uint32_t)SYSCTL_OSC_MAIN | (uint32_t)SYSCTL_XTAL_16MHZ);

        CTLInit_Status = CLK_Init(PORTF);
        CTLInit_Status |= DIO_InitPort(PORTF);
        CTLInit_Status |= LAMP_Init(LAMP_RED);
        CTLInit_Status |= LAMP_Init(LAMP_BLUE);
        CTLInit_Status |= LAMP_Init(LAMP_GREEN);
        CTLInit_Status |= SWITCH_Init(SWITCH_CH1);
        CTLInit_Status |= SWITCH_Init(SWITCH_CH2);
        CTLInit_Status |= CAN_Init(CAN_CH0);
        CTLInit_Status |= UART_Init(UART0,BAUDRATE,PIOSC,0U);
        CTLInit_Status |= SYSTICK_Init(TOKENPERIOD);
        CTLInit_Status |= CANObject_Init(&colourCANMsg,CLRMsgData,CAN_TX,1001U,TOKEN_ID);
        CTLInit_Status |= CANObject_Init(&switchCANMsg,SWMsgData,CAN_RX,2002U,STATECHANGE_ID);

        return CTLInit_Status;
}

E_Status CONTROL_Token(void)
{
        static E_Status CONTROLToken_Status;
        if(Flag == 0U)
            {
                Flag=1U;
                switch(ECU1_state)
                {
                    case LAMP_RED:
                      if(DIRECTION == DIR_RGB)
                      {
                         CLR_Data=GREEN2_BLUE3;
                         CONTROLToken_Status|= CAN_Send(colourCANMsg,TOKEN_ID);
                      }
                      else if (DIRECTION == DIR_RBG)
                      {
                         CLR_Data=BLUE2_GREEN3;
                         CONTROLToken_Status|=CAN_Send(colourCANMsg,TOKEN_ID);
                      }
                      else{}
                      break;
                    case LAMP_GREEN:
                      if(DIRECTION == DIR_GBR)
                      {
                          CLR_Data=BLUE2_RED3;
                          CONTROLToken_Status|=CAN_Send(colourCANMsg,TOKEN_ID);
                      }
                      else if (DIRECTION == DIR_GRB)
                      {
                          *CLRMsgData=RED2_BLUE3;
                          CONTROLToken_Status|=CAN_Send(colourCANMsg,TOKEN_ID);
                      }
                      else{}
                      break;
                    case LAMP_BLUE:
                      if(DIRECTION == DIR_BGR)
                      {
                          CLR_Data=GREEN2_RED3;
                          CONTROLToken_Status|=CAN_Send(colourCANMsg,TOKEN_ID);
                      }
                      else if(DIRECTION == DIR_BRG)
                      {
                           CLR_Data=RED2_GREEN3;
                           CONTROLToken_Status|=CAN_Send(colourCANMsg,TOKEN_ID);
                      }
                      else{}
                      break;
                    default:
                        break;
                }
            }
            else if(Flag==1U)
            {
                Flag=2U;
                switch(ECU1_state)
                 {
                        case LAMP_RED:
                           if(DIRECTION == DIR_RGB)
                           {
                               CLR_Data=WHITE2_BLUE3;
                               CONTROLToken_Status|= CAN_Send(colourCANMsg,TOKEN_ID);
                           }
                           else if (DIRECTION == DIR_RBG )
                           {
                               CLR_Data=WHITE2_GREEN3;
                               CONTROLToken_Status|=CAN_Send(colourCANMsg,TOKEN_ID);
                           }
                           else{}
                            break;
                         case LAMP_GREEN:
                             if(DIRECTION == DIR_GBR)
                             {
                                  CLR_Data=WHITE2_RED3;
                                  CONTROLToken_Status|=CAN_Send(colourCANMsg,TOKEN_ID);
                             }
                             else if (DIRECTION == DIR_GRB)
                             {
                                   CLR_Data=WHITE2_BLUE3;
                                   CONTROLToken_Status|=CAN_Send(colourCANMsg,TOKEN_ID);
                             }
                             else{}
                          break;
                         case LAMP_BLUE:
                             if(DIRECTION == DIR_BGR)
                             {
                                  CLR_Data=WHITE2_RED3;
                                  CONTROLToken_Status|=CAN_Send(colourCANMsg,TOKEN_ID);
                             }
                             else if(DIRECTION == DIR_BRG)
                             {
                                   CLR_Data=WHITE2_GREEN3;
                                   CONTROLToken_Status|=CAN_Send(colourCANMsg,TOKEN_ID);
                             }
                             else{}
                             break;
                         default:
                             break;
                  }
            }
            else if(Flag==2U)
            {
                   Flag=0U;
                   switch(ECU1_state)
                    {
                          case LAMP_RED:
                              if(DIRECTION == DIR_RGB)
                              {
                                    CLR_Data=GREEN2_WHITE3;
                                    CONTROLToken_Status|=CAN_Send(colourCANMsg,TOKEN_ID);
                              }
                              else if (DIRECTION == DIR_RBG )
                              {
                                     CLR_Data=BLUE2_WHITE3;
                                     CONTROLToken_Status|=CAN_Send(colourCANMsg,TOKEN_ID);
                              }
                              else{}
                              break;
                          case LAMP_GREEN:
                              if(DIRECTION == DIR_GBR)
                              {
                                      CLR_Data=BLUE2_WHITE3;
                                      CONTROLToken_Status|=CAN_Send(colourCANMsg,TOKEN_ID);
                              }
                              else if (DIRECTION == DIR_GRB)
                              {
                                       CLR_Data=RED2_WHITE3;
                                       CONTROLToken_Status|=CAN_Send(colourCANMsg,TOKEN_ID);
                              }
                              else{}
                               break;
                          case LAMP_BLUE:
                              if(DIRECTION == DIR_BGR)
                              {
                                       CLR_Data=GREEN2_WHITE3;
                                       CONTROLToken_Status|=CAN_Send(colourCANMsg,TOKEN_ID);
                              }
                              else if(DIRECTION == DIR_BRG)
                              {
                                        CLR_Data=RED2_WHITE3;
                                        CONTROLToken_Status|=CAN_Send(colourCANMsg,TOKEN_ID);
                              }
                              else{}
                               break;
                          default:
                              break;
                           }
            }
            else{}
        return CONTROLToken_Status;
}

E_Status CONTROL_Lamps(void)
{
               static E_Status CONTROLLamps_Status;

               static uint8_t SW1_State;
               static uint8_t SW2_State;

               uint8_t * SW1_Ptr = &SW1_State;
               uint8_t * SW2_Ptr = &SW2_State;

               CONTROLLamps_Status  = SWITCH_GetStatus(SWITCH_CH1, SW1_Ptr);
               CONTROLLamps_Status |= SWITCH_GetStatus(SWITCH_CH2, SW2_Ptr);

               if(Flag == 1U)
                       {
                           if(SW1_State == HIGH)
                           {
                               ECU1_state=LAMP_RED;
                               DIRECTION = DIR_RGB;
                           }
                           else if (SW2_State == HIGH)
                           {
                               ECU1_state=LAMP_BLUE;
                               DIRECTION = DIR_BGR;
                           }
                           else{}
                           CONTROLLamps_Status |= LAMP_On(LAMP_WHITE);
                       }
                       else if((Flag == 0U) || (Flag == 2U))
                       {
                           if(rxFlag)
                           {
                               switchCANMsg.pui8MsgData = SWMsgData;
                               CONTROLLamps_Status  = CAN_Recieve(switchCANMsg,STATECHANGE_ID);
                           }
                           if(((SW_Data & ECU2_SW1) == ECU2_SW1))
                           {
                               ECU1_state = LAMP_BLUE;
                               DIRECTION = DIR_BRG;
                               UARTprintf("ECU2 (SW1)\n");
                               CONTROLLamps_Status |= LAMP_Off(LAMP_WHITE);
                               CONTROLLamps_Status |= LAMP_On(LAMP_BLUE);
                               SW_Data=0U;
                               rxFlag = 0U;
                           }
                           else if (((SW_Data & ECU2_SW2) == ECU2_SW2))
                           {
                               ECU1_state = LAMP_RED;
                               DIRECTION = DIR_RBG;
                               UARTprintf("ECU2 (SW2)\n");
                               CONTROLLamps_Status |= LAMP_Off(LAMP_WHITE);
                               CONTROLLamps_Status |= LAMP_On(LAMP_RED);
                               SW_Data=0U;
                               rxFlag = 0U;
                            }
                           else if (((SW_Data & ECU3_SW1) == ECU3_SW1))
                           {
                               ECU1_state = LAMP_GREEN;
                               DIRECTION = DIR_GBR;
                               UARTprintf("ECU3 (SW1)\n");
                               CONTROLLamps_Status |= LAMP_Off(LAMP_WHITE);
                               CONTROLLamps_Status |= LAMP_On(LAMP_GREEN);
                               SW_Data=0U;
                               rxFlag = 0U;
                           }
                           else if (((SW_Data & ECU3_SW2) == ECU3_SW2))
                           {
                               ECU1_state = LAMP_GREEN;
                               DIRECTION = DIR_GRB;
                               UARTprintf("ECU3 (SW2)\n");
                               CONTROLLamps_Status |= LAMP_Off(LAMP_WHITE);
                               CONTROLLamps_Status |= LAMP_On(LAMP_GREEN);
                               SW_Data=0U;
                               rxFlag = 0U;
                           }
                           else if(ECU1_state ==  LAMP_RED)
                           {
                               CONTROLLamps_Status |= LAMP_Off(LAMP_WHITE);
                               CONTROLLamps_Status |= LAMP_On(LAMP_RED);
                           }
                           else if (ECU1_state == LAMP_BLUE)
                           {
                               CONTROLLamps_Status |= LAMP_Off(LAMP_WHITE);
                               CONTROLLamps_Status |= LAMP_On(LAMP_BLUE);
                           }
                           else if (ECU1_state == LAMP_GREEN)
                           {
                               CONTROLLamps_Status |= LAMP_Off(LAMP_WHITE);
                               CONTROLLamps_Status |= LAMP_On(LAMP_GREEN);
                           }
                           else
                           {}
                      }
                       else{}
               return CONTROLLamps_Status;
}
