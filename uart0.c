#include <LPC214x.h>
#include "types.h"
#include "uart0.h"

/* UART0 Initialization */
void UART0_Init(u32 baud)
{
    PINSEL0 |= 0x00000005;      // P0.0 = TXD0, P0.1 = RXD0

    U0LCR = 0x83;               // 8-bit, 1 Stop bit, No parity, DLAB = 1

    switch(baud)
    {
        case 9600:
            U0DLL = 97;
            U0DLM = 0;
            break;

        case 19200:
            U0DLL = 48;
            U0DLM = 0;
            break;

        case 38400:
            U0DLL = 24;
            U0DLM = 0;
            break;

        default:
            U0DLL = 97;
            U0DLM = 0;
            break;
    }

    U0LCR = 0x03;               // DLAB = 0
}

/* Transmit One Character */
void UART0_TxChar(u8 ch)
{
    while(!(U0LSR & (1<<5)));
    U0THR = ch;
}

/* Transmit String */
void UART0_TxString(s8 *str)
{
    while(*str)
    {
        UART0_TxChar(*str++);
    }
}

/* Receive One Character */
u8 UART0_RxChar(void)
{
    while(!(U0LSR & 0x01));
    return U0RBR;
}

/* Receive String */
void UART0_RxString(s8 *buf)
{
    u8 ch;

    while(1)
    {
        ch = UART0_RxChar();

        if(ch == '\r')
            break;

        *buf++ = ch;
    }

    *buf = '\0';
}

/* Transmit Number */
void UART0_TxNumber(u32 num)
{
    char buf[10];
    int i = 0;
    if(num == 0)
    {
        UART0_TxChar('0');
        return;
    }

    while(num)
    {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }

    while(i)
    {
        UART0_TxChar(buf[--i]);
    }
}
