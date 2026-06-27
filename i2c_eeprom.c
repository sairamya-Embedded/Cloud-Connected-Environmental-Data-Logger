#include <LPC214x.h>
#include "types.h"
#include "delay.h"
#include "i2c.h"
#include "i2c_eeprom.h"

/************ Write One Byte ************/
void EEPROM_Write_Byte(u16 memAddr, u8 data)
{
    I2C_Start();

    I2C_Write(EEPROM_ID);              // Device Address + Write

    I2C_Write(memAddr >> 8);           // Address High Byte

    I2C_Write(memAddr & 0xFF);         // Address Low Byte

    I2C_Write(data);                   // Data

    I2C_Stop();

    delay_ms(10);                      // EEPROM Write Delay
}

/************ Read One Byte ************/
u8 EEPROM_Read_Byte(u16 memAddr)
{
    u8 data;

    I2C_Start();

    I2C_Write(EEPROM_ID);

    I2C_Write(memAddr >> 8);

    I2C_Write(memAddr & 0xFF);

    I2C_Restart();

    I2C_Write(EEPROM_ID | 0x01);       // Read Mode

    data = I2C_ReadNACK();

    I2C_Stop();

    return data;
}

/************ Write Page ************/
void EEPROM_Write_Page(u16 memAddr, u8 *buf, u8 len)
{
    u8 i;

    I2C_Start();

    I2C_Write(EEPROM_ID);

    I2C_Write(memAddr >> 8);

    I2C_Write(memAddr & 0xFF);

    for(i=0;i<len;i++)
    {
        I2C_Write(buf[i]);
    }

    I2C_Stop();

    delay_ms(10);
}

/************ Read Page ************/
void EEPROM_Read_Page(u16 memAddr, u8 *buf, u8 len)
{
    u8 i;

    I2C_Start();

    I2C_Write(EEPROM_ID);

    I2C_Write(memAddr >> 8);

    I2C_Write(memAddr & 0xFF);

    I2C_Restart();

    I2C_Write(EEPROM_ID | 0x01);

    for(i=0;i<(len-1);i++)
    {
        buf[i] = I2C_ReadACK();
    }

    buf[len-1] = I2C_ReadNACK();

    I2C_Stop();
}
