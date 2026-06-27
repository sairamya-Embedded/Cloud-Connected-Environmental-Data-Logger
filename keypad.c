#include <LPC214x.h>

#include "types.h"
#include "delay.h"
#include "KeyPad.h"
#include "KeyPdDefines.h"

/************ Initialize Keypad ************/
void KeyPdInit(void)
{
    /* Rows as Output */
    IODIR1 |= ((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));

    /* Columns as Input */
    IODIR1 &= ~((1<<C0)|(1<<C1)|(1<<C2)|(1<<C3));

    /* Rows LOW */
    IOCLR1 = ((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));
}

/************ Check Column Status ************/
u8 ColStat(void)
{
    if(((IOPIN1>>20)&0x0F)==0x0F)
        return 1;
    else
        return 0;
}

/************ Read Key ************/
u8 KeyVal(void)
{
    u8 row_val=0,col_val=0;

    IOCLR1=(1<<R0);
    IOSET1=((1<<R1)|(1<<R2)|(1<<R3));

    if(((IOPIN1>>20)&0x0F)!=0x0F)
    {
        row_val=0;
        goto COLCHECK;
    }

    IOCLR1=(1<<R1);
    IOSET1=((1<<R0)|(1<<R2)|(1<<R3));

    if(((IOPIN1>>20)&0x0F)!=0x0F)
    {
        row_val=1;
        goto COLCHECK;
    }

    IOCLR1=(1<<R2);
    IOSET1=((1<<R0)|(1<<R1)|(1<<R3));

    if(((IOPIN1>>20)&0x0F)!=0x0F)
    {
        row_val=2;
        goto COLCHECK;
    }

    IOCLR1=(1<<R3);
    IOSET1=((1<<R0)|(1<<R1)|(1<<R2));

    if(((IOPIN1>>20)&0x0F)!=0x0F)
    {
        row_val=3;
    }

COLCHECK:

    if(((IOPIN1>>C0)&1)==0)
        col_val=0;
    else if(((IOPIN1>>C1)&1)==0)
        col_val=1;
    else if(((IOPIN1>>C2)&1)==0)
        col_val=2;
    else
        col_val=3;

    IOCLR1=((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));

    delay_ms(20);

    return LUT[row_val][col_val];
}
