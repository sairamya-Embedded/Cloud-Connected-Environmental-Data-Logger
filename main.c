#include <LPC214x.h>
#include <stdio.h>

#include "types.h"
#include "defines.h"
#include "delay.h"
#include "lcd.h"
#include "uart0.h"
#include "adc.h"
#include "i2c.h"
#include "i2c_eeprom.h"
#include "esp01.h"
#include "interrupt.h"
#include "mq2.h"

#define BUZZER_PIN    21

f32 voltage;
u16 temperature;
u8 gas_status;
u8 set_point;

void Hardware_Init(void);
void Read_Sensors(void);
void Display_Data(void);
void Alarm_Check(void);

int main(void)
{
    Hardware_Init();

    while(1)
    {
        Read_Sensors();

        Display_Data();

        Alarm_Check();

        if(SetPoint_Flag)
        {
            SetPoint_Flag = 0;

            set_point++;

            EEPROM_Write_Byte(0x0000, set_point);
        }

        delay_ms(1000);
    }
}

/**************** Hardware Initialization ****************/

void Hardware_Init(void)
{
    LCD_Init();

    UART0_Init(9600);

    Init_ADC();

    I2C_Init();


    ESP01_Init();

    MQ2_Init();

    EINT0_Init();

    IODIR0 |= (1<<BUZZER_PIN);

    IOCLR0 = (1<<BUZZER_PIN);

    set_point = EEPROM_Read_Byte(0x0000);

    if(set_point == 0xFF)
    {
        set_point = 30;

        EEPROM_Write_Byte(0x0000, set_point);
    }
}

/**************** Read Sensors ****************/

void Read_Sensors(void)
{
    voltage = Read_ADC(1);

    temperature = (u16)(voltage * 100);

    gas_status = MQ2_Read();
}

/**************** Display Data ****************/

void Display_Data(void)
{
    LCD_Command(0x80);
    LCD_String("Temp:");
    LCD_Integer(temperature);

    LCD_Command(0xC0);
    LCD_String("Gas:");

    if(gas_status)
        LCD_String("YES ");
    else
        LCD_String("NO  ");
}

/**************** Alarm Check ****************/

void Alarm_Check(void)
{
    if((temperature > set_point) || (gas_status))
    {
        IOSET0 = (1<<BUZZER_PIN);

        ESP01_SendThingSpeak(temperature, gas_status);

        delay_ms(500);

        IOCLR0 = (1<<BUZZER_PIN);
    }
}
