#include <LPC214x.h>
#include "types.h"
#include "i2c.h"

void I2C_Init(void)
{
    PINSEL0 |= 0x00000050;      // P0.2=SCL0, P0.3=SDA0

    I2C0SCLH = 75;
    I2C0SCLL = 75;

    I2C0CONSET = (1<<6);        // Enable I2C
}

void I2C_Start(void)
{
    I2C0CONSET = (1<<5);        // STA
    I2C0CONCLR = (1<<3);        // Clear SI

    while(!(I2C0CONSET & (1<<3)));
}

void I2C_Stop(void)
{
    I2C0CONSET = (1<<4);        // STO
    I2C0CONCLR = (1<<3);
}

void I2C_Restart(void)
{
    I2C0CONSET = (1<<5);
    I2C0CONCLR = (1<<3);

    while(!(I2C0CONSET & (1<<3)));
}

void I2C_Write(u8 data)
{
    I2C0DAT = data;

    I2C0CONCLR = (1<<5);        // Clear STA
    I2C0CONCLR = (1<<3);        // Clear SI

    while(!(I2C0CONSET & (1<<3)));
}

u8 I2C_ReadACK(void)
{
    I2C0CONSET = (1<<2);        // AA
    I2C0CONCLR = (1<<3);

    while(!(I2C0CONSET & (1<<3)));

    return I2C0DAT;
}

u8 I2C_ReadNACK(void)
{
    I2C0CONCLR = (1<<2);        // AA
    I2C0CONCLR = (1<<3);

    while(!(I2C0CONSET & (1<<3)));

    return I2C0DAT;
}

u8 I2C_GetStatus(void)
{
    return I2C0STAT;
}
