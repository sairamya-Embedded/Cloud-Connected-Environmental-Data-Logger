#ifndef _I2C_H_
#define _I2C_H_

#include "types.h"

/************ Function Prototypes ************/

void I2C_Init(void);

void I2C_Start(void);

void I2C_Stop(void);

void I2C_Restart(void);

void I2C_Write(u8 data);

u8 I2C_ReadACK(void);

u8 I2C_ReadNACK(void);

u8 I2C_GetStatus(void);

#endif
