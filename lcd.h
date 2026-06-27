#ifndef _LCD_H_
#define _LCD_H_

#include "types.h"

/************ LCD Control Pins ************/
#define LCD_RS   8     // Change later
#define LCD_EN   9     // Change later

/************ LCD Data Pins ************/
#define LCD_D4   4     // Change later
#define LCD_D5   5     // Change later
#define LCD_D6   6     // Change later
#define LCD_D7   7     // Change later

/************ Function Prototypes ************/
void LCD_Init(void);
void LCD_Command(u8 cmd);
void LCD_Data(u8 data);
void LCD_String(char *str);
void LCD_Integer(u32 num);
void LCD_Clear(void);

#endif
