#include "UART.h"
#include "CLK.h"

E_Status UART_Init(uint8_t port,uint32_t baud,uint32_t clksrc,bool xInt)
{
    static E_Status UARTInit_Status;
    if((port <= UART7) && (port >= UART0) && ((clksrc == PIOSC) || (clksrc == SYSTEM)))
    {
        switch(port)
        {
        case UART0:
               UARTInit_Status = CLK_Init(PORTA);
               GPIOPinConfigure((uint32_t)GPIO_PA0_U0RX);
               GPIOPinConfigure((uint32_t)GPIO_PA1_U0TX);
               UARTInit_Status |= CLK_Init(port);
               UARTClockSourceSet((uint32_t)UART0_BASE,clksrc);
               GPIOPinTypeUART((uint32_t)GPIO_PORTA_BASE, (uint8_t)GPIO_PIN_0 | (uint8_t)GPIO_PIN_1);
               UARTStdioConfig(0U, baud, 16000000U);
               if(xInt)
               {
                   UARTIntEnable((uint32_t)UART0_BASE,(uint32_t)UART_INT_RX);
                   UARTIntRegister((uint32_t)UART0_BASE,&UARTIntHandler);
                   UARTFIFOLevelSet((uint32_t)UART0_BASE,(uint32_t)UART_FIFO_TX1_8,(uint32_t)UART_FIFO_RX1_8);
               }

               UARTInit_Status = E_OK;
               break;

        case UART1:
               UARTInit_Status = CLK_Init(PORTB);
               GPIOPinConfigure((uint32_t)GPIO_PB0_U1RX);
               GPIOPinConfigure((uint32_t)GPIO_PB1_U1TX);
               UARTInit_Status |= CLK_Init(port);
               UARTClockSourceSet((uint32_t)UART1_BASE,clksrc);
               GPIOPinTypeUART((uint32_t)GPIO_PORTB_BASE, (uint8_t)GPIO_PIN_0 | (uint8_t)GPIO_PIN_1);
               UARTStdioConfig(0U, baud, 16000000U);
               if(xInt)
               {
                   UARTIntEnable((uint32_t)UART1_BASE,(uint32_t)UART_INT_RX);
                   UARTIntRegister((uint32_t)UART1_BASE,&UARTIntHandler);
                   UARTFIFOLevelSet((uint32_t)UART1_BASE,(uint32_t)UART_FIFO_TX1_8,(uint32_t)UART_FIFO_RX1_8);
               }

               UARTInit_Status = E_OK;
               break;

        case UART2:
               UARTInit_Status = CLK_Init(PORTD);
               GPIOPinConfigure((uint32_t)GPIO_PD6_U2RX);
               GPIOPinConfigure((uint32_t)GPIO_PD7_U2TX);
               UARTInit_Status |= CLK_Init(port);
               UARTClockSourceSet((uint32_t)UART2_BASE,clksrc);
               GPIOPinTypeUART((uint32_t)GPIO_PORTD_BASE, (uint8_t)GPIO_PIN_6 | (uint8_t)GPIO_PIN_7);
               UARTStdioConfig(0U, baud, 16000000U);
               if(xInt)
               {
                   UARTIntEnable((uint32_t)UART2_BASE,(uint32_t)UART_INT_RX);
                   UARTIntRegister((uint32_t)UART2_BASE,&UARTIntHandler);
                   UARTFIFOLevelSet((uint32_t)UART2_BASE,(uint32_t)UART_FIFO_TX1_8,(uint32_t)UART_FIFO_RX1_8);
               }

               UARTInit_Status = E_OK;
               break;

        case UART3:
               UARTInit_Status = CLK_Init(PORTC);
               GPIOPinConfigure((uint32_t)GPIO_PC6_U3RX);
               GPIOPinConfigure((uint32_t)GPIO_PC7_U3TX);
               UARTInit_Status |= CLK_Init(port);
               UARTClockSourceSet((uint32_t)UART3_BASE,clksrc);
               GPIOPinTypeUART((uint32_t)GPIO_PORTC_BASE, (uint8_t)GPIO_PIN_6 | (uint8_t)GPIO_PIN_7);
               UARTStdioConfig(0U, baud, 16000000U);
               if(xInt)
               {
                   UARTIntEnable((uint32_t)UART3_BASE,(uint32_t)UART_INT_RX);
                   UARTIntRegister((uint32_t)UART3_BASE,&UARTIntHandler);
                   UARTFIFOLevelSet((uint32_t)UART3_BASE,(uint32_t)UART_FIFO_TX1_8,(uint32_t)UART_FIFO_RX1_8);
               }

               UARTInit_Status = E_OK;
               break;

        case UART4:
               UARTInit_Status = CLK_Init(PORTC);
               GPIOPinConfigure((uint32_t)GPIO_PC4_U4RX);
               GPIOPinConfigure((uint32_t)GPIO_PC5_U4TX);
               UARTInit_Status |= CLK_Init(port);
               UARTClockSourceSet((uint32_t)UART4_BASE,clksrc);
               GPIOPinTypeUART((uint32_t)GPIO_PORTC_BASE, (uint8_t)GPIO_PIN_4 | (uint8_t)GPIO_PIN_5);
               UARTStdioConfig(0U, baud, 16000000U);
               if(xInt)
               {
                   UARTIntEnable((uint32_t)UART4_BASE,(uint32_t)UART_INT_RX);
                   UARTIntRegister((uint32_t)UART4_BASE,&UARTIntHandler);
                   UARTFIFOLevelSet((uint32_t)UART4_BASE,(uint32_t)UART_FIFO_TX1_8,(uint32_t)UART_FIFO_RX1_8);
               }
               UARTInit_Status = E_OK;
               break;

        case UART5:
               UARTInit_Status = CLK_Init(PORTE);
               GPIOPinConfigure((uint32_t)GPIO_PE4_U5RX);
               GPIOPinConfigure((uint32_t)GPIO_PE5_U5TX);
               UARTInit_Status |= CLK_Init(port);
               UARTClockSourceSet((uint32_t)UART5_BASE,clksrc);
               GPIOPinTypeUART((uint32_t)GPIO_PORTE_BASE, (uint8_t)GPIO_PIN_4 | (uint8_t)GPIO_PIN_5);
               UARTStdioConfig(0U, baud, 16000000U);
               if(xInt)
               {
                   UARTIntEnable((uint32_t)UART5_BASE,(uint32_t)UART_INT_RX);
                   UARTIntRegister((uint32_t)UART5_BASE,&UARTIntHandler);
                   UARTFIFOLevelSet((uint32_t)UART5_BASE,(uint32_t)UART_FIFO_TX1_8,(uint32_t)UART_FIFO_RX1_8);
               }
               UARTInit_Status = E_OK;
               break;

        case UART6:
               UARTInit_Status = CLK_Init(PORTD);
               GPIOPinConfigure((uint32_t)GPIO_PD4_U6RX);
               GPIOPinConfigure((uint32_t)GPIO_PD5_U6TX);
               UARTInit_Status |= CLK_Init(port);
               UARTClockSourceSet((uint32_t)UART6_BASE,clksrc);
               GPIOPinTypeUART((uint32_t)GPIO_PORTD_BASE, (uint8_t)GPIO_PIN_4 | (uint8_t)GPIO_PIN_5);
               UARTStdioConfig(0U, baud, 16000000U);
               if(xInt)
               {
                   UARTIntEnable((uint32_t)UART6_BASE,(uint32_t)UART_INT_RX);
                   UARTIntRegister((uint32_t)UART6_BASE,&UARTIntHandler);
                   UARTFIFOLevelSet((uint32_t)UART6_BASE,(uint32_t)UART_FIFO_TX1_8,(uint32_t)UART_FIFO_RX1_8);
               }
               UARTInit_Status = E_OK;
               break;

        case UART7:
               UARTInit_Status = CLK_Init(PORTE);
               GPIOPinConfigure((uint32_t)GPIO_PE0_U7RX);
               GPIOPinConfigure((uint32_t)GPIO_PE1_U7TX);
               UARTInit_Status |= CLK_Init(port);
               UARTClockSourceSet((uint32_t)UART7_BASE,clksrc);
               GPIOPinTypeUART((uint32_t)GPIO_PORTE_BASE, (uint8_t)GPIO_PIN_0 | (uint8_t)GPIO_PIN_1);
               UARTStdioConfig(0U, baud, 16000000U);
               if(xInt)
               {
                   UARTIntEnable((uint32_t)UART7_BASE,(uint32_t)UART_INT_RX);
                   UARTIntRegister((uint32_t)UART7_BASE,&UARTIntHandler);
                   UARTFIFOLevelSet((uint32_t)UART7_BASE,(uint32_t)UART_FIFO_TX1_8,(uint32_t)UART_FIFO_RX1_8);
               }
               UARTInit_Status = E_OK;
               break;
        default:
            break;
        }
    }
    else
    {
        UARTInit_Status = E_NOK;
    }
    return UARTInit_Status;
}

void UARTIntHandler(void){}

