#ifndef _ESP01_H_
#define _ESP01_H_

#include <LPC214x.h>
#include "types.h"

/******** Function Prototypes ********/

void ESP01_Init(void);

void ESP01_SendCmd(s8 *cmd);

void ESP01_SendString(s8 *str);

void ESP01_ClearBuffer(void);

void ESP01_ConnectWiFi(void);

void ESP01_StartTCP(void);

void ESP01_StopTCP(void);

void UART0_TxNumber(u32 num);

void ESP01_SendThingSpeak(u16 temp, u8 gas);

#endif
