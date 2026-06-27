#include <LPC214x.h>
#include "delay.h"
void delay_us(u32 us)
{
    u32 i;

    while(us--)
    {
        for(i = 0; i < 15; i++);
    }
}
void delay_ms(u32 ms)
{
    while(ms--)
    {
        delay_us(1000);
    }
}
