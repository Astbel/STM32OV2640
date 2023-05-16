#ifndef __OV2640_H_
#define __OV2640_H_

#include "main.h"
/*I2C function*/

extern void ov2640_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) ;
extern void ov2640_I2C_Write(uint8_t address, uint8_t reg, uint8_t data) ;



#endif
