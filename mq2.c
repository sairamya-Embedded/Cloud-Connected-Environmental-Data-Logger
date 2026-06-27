#include <LPC214x.h>
#include "mq2.h"

#define MQ2_PIN 10      // P0.10 

void MQ2_Init(void)
{
    IODIR0 &= ~(1<<MQ2_PIN);    // Input
}

u8 MQ2_Read(void)
{
    return ((IOPIN0 >> MQ2_PIN) & 0x01);
}
