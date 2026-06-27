#ifndef _I2C_EEPROM_H_
#define _I2C_EEPROM_H_

#include "types.h"

/************* AT24C256 EEPROM Address *************/
#define EEPROM_ID 0xA0

/************* Function Prototypes *************/

void EEPROM_Write_Byte(u16 memAddr, u8 data);

u8 EEPROM_Read_Byte(u16 memAddr);

void EEPROM_Write_Page(u16 memAddr, u8 *buf, u8 len);

void EEPROM_Read_Page(u16 memAddr, u8 *buf, u8 len);

#endif
