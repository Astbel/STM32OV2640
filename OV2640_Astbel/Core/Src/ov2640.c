/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  _____ ___   _____ 
// |_   _|__ \ / ____|
//   | |    ) | |     
//   | |   / /| |     
//  _| |_ / /_| |____ 
// |_____|____|\_____|
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "ov2640.h"


/* Write command */
#define OV2640_WRITECOMMAND(command)      ov2640_I2C_Write(SSD1306_I2C_ADDR, 0x00, (command))
/* Write data */
#define OV2640_WRITEDATA(data)            ov2640_I2C_Write(SSD1306_I2C_ADDR, 0x40, (data))
/* Absolute value */
#define ABS(x)   ((x) > 0 ? (x) : -(x))

void ov2640_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) 
{
    uint8_t dt[256];
    dt[0] = reg;
    uint8_t i;
    for(i = 0; i < count; i++)
    dt[i+1] = data[i];
    HAL_I2C_Master_Transmit(&hi2c2, address, dt, count+1, 10);
}


void ov2640_I2C_Write(uint8_t address, uint8_t reg, uint8_t data) 
{
	uint8_t dt[2];
	dt[0] = reg;
	dt[1] = data;
	HAL_I2C_Master_Transmit(&hi2c2, address, dt, 2, 10);
}






