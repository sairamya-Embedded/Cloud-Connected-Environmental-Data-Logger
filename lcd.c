#include <LPC214x.h>
#include <stdio.h>

#include "lcd.h"
#include "delay.h"

#define RS_HIGH()   IOSET0=(1<<LCD_RS)
#define RS_LOW()    IOCLR0=(1<<LCD_RS)

#define EN_HIGH()   IOSET0=(1<<LCD_EN)
#define EN_LOW()    IOCLR0=(1<<LCD_EN)

void LCD_Enable(void)
{
    EN_HIGH();
    delay_ms(2);
    EN_LOW();
    delay_ms(2);
}

void LCD_Write4Bits(u8 data)
{
    IOCLR0 = (1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7);

    if(data & 0x01) IOSET0 |= (1<<LCD_D4);
    if(data & 0x02) IOSET0 |= (1<<LCD_D5);
    if(data & 0x04) IOSET0 |= (1<<LCD_D6);
    if(data & 0x08) IOSET0 |= (1<<LCD_D7);

    LCD_Enable();
}

void LCD_Command(u8 cmd)
{
    RS_LOW();

    LCD_Write4Bits(cmd>>4);

    LCD_Write4Bits(cmd&0x0F);

    delay_ms(2);
}

void LCD_Data(u8 data)
{
    RS_HIGH();

    LCD_Write4Bits(data>>4);

    LCD_Write4Bits(data&0x0F);

    delay_ms(2);
}

void LCD_Init(void)
{
    IODIR0 |= (1<<LCD_RS);
    IODIR0 |= (1<<LCD_EN);

    IODIR0 |= (1<<LCD_D4);
    IODIR0 |= (1<<LCD_D5);
    IODIR0 |= (1<<LCD_D6);
    IODIR0 |= (1<<LCD_D7);

    delay_ms(20);

    LCD_Write4Bits(0x03);
    LCD_Write4Bits(0x03);
    LCD_Write4Bits(0x03);
    LCD_Write4Bits(0x02);

    LCD_Command(0x28);
    LCD_Command(0x0C);
    LCD_Command(0x06);
    LCD_Command(0x01);
}

void LCD_String(char *str)
{
    while(*str)
    {
        LCD_Data(*str++);
    }
}

void LCD_Clear(void)
{
    LCD_Command(0x01);

    delay_ms(2);
}

void LCD_Integer(u32 num)
{
    char buf[10];

    sprintf(buf,"%lu",(unsigned long)num);

    LCD_String(buf);
}
