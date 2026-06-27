#include <LPC214x.h>

#include "types.h"
#include "defines.h"
#include "adc_defines.h"
#include "delay.h"

#define ADC_FUNC 0x01

void Init_ADC(void)
{
    PINSEL1 |= (ADC_FUNC << 24);      // Configure P0.28 as AD0.1

    AD0CR = PDN_BIT | CLKDIV | CHANNEL_SEL;
}

f32 Read_ADC(u8 chNo)
{
    u16 adcVal = 0;
    f32 eAR;

    WRITEBYTE(AD0CR, 0, chNo);        // Select ADC Channel

    SETBIT(AD0CR, ADC_START_BIT);     // Start Conversion

    delay_us(3);

    while(!READBIT(AD0GDR, DONE_BIT));

    CLRBIT(AD0CR, ADC_START_BIT);     // Stop Conversion

    adcVal = (AD0GDR >> 6) & 0x3FF;

    eAR = ((adcVal * 3.3) / 1023);

    return eAR;
}

