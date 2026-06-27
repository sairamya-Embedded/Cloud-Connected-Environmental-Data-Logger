#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "types.h"

/******** Function Prototypes ********/

void EINT0_Init(void);

__irq void EINT0_ISR(void);

extern volatile u8 SetPoint_Flag;

#endif
