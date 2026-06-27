#ifndef _UART0_H_
#define _UART0_H_

#include <LPC214x.h>
#include "types.h"

/******** Function Prototypes ********/

void UART0_Init(u32 baud);

void UART0_TxChar(u8 ch);

void UART0_TxString(s8 *str);

u8 UART0_RxChar(void);

void UART0_RxString(s8 *buf);

void UART0_TxNumber(u32 num);

#endif
