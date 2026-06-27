#include <LPC214x.h>
#include "interrupt.h"

volatile u8 SetPoint_Flag = 0;

/******** External Interrupt Initialization ********/
void EINT0_Init(void)
{
    PINSEL0 |= (1<<29);          // P0.14 -> EINT0

    EXTMODE = 0x01;              // Edge Triggered

    EXTPOLAR = 0x00;             // Falling Edge

    VICIntSelect = 0x00;

    VICVectAddr0 = (unsigned int)EINT0_ISR;

    VICVectCntl0 = 0x20 | 14;

    VICIntEnable = (1<<14);
}

/******** Interrupt Service Routine ********/
__irq void EINT0_ISR(void)
{
    SetPoint_Flag = 1;

    EXTINT = 0x01;               // Clear Interrupt Flag

    VICVectAddr = 0x00;
}
