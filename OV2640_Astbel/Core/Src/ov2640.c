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
#include "ov2640cfg.h"
#include "stdio.h"

/* Write command */
#define OV2640_WRITECOMMAND(command)      ov2640_I2C_Write(SSD1306_I2C_ADDR, 0x00, (command))
/* Write data */
#define OV2640_WRITEDATA(data)            ov2640_I2C_Write(SSD1306_I2C_ADDR, 0x40, (data))
/* Absolute value */
#define ABS(x)   ((x) > 0 ? (x) : -(x))

/***********************************************************************************
 * 函數名:   uint8_t I2C_Read(uint8_t reg,uint8_t address)  
 * 函數功能: 讀取Device 回傳值
 * 輸入參數:  reg 地址,address 地址
 * 輸出:      返回數據
***********************************************************************************/
uint8_t I2C_Read(uint8_t reg,uint8_t address)
{
  uint8_t value = 0;
  HAL_I2C_Master_Transmit(&hi2c2, address, &reg, 1, HAL_MAX_DELAY); // 发送要读取的寄存器地址
  HAL_I2C_Master_Receive(&hi2c2, address, &value, 1, HAL_MAX_DELAY); // 读取寄存器值
  return value;
}
/***********************************************************************************
 * 函數名:    void ov2640_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count)  
 * 函數功能:  寫入多組數據至device
 * 輸入參數:  address 地址,reg 佔存, data資料,count 計數
 * 輸出:      無回傳型
***********************************************************************************/
void ov2640_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) 
{
    uint8_t dt[256];
    dt[0] = reg;
    uint8_t i;
    for(i = 0; i < count; i++)
    dt[i+1] = data[i];
    HAL_I2C_Master_Transmit(&hi2c2, address, dt, count+1, 10);
}
/***********************************************************************************
 * 函數名:    void ov2640_I2C_Write(uint8_t address, uint8_t reg, uint8_t data)  
 * 函數功能:  I2C 寫入device 功能
 * 輸入參數:  address device 地址,reg device 佔存位置,data要寫入的資料
 * 輸出:      無回傳型
***********************************************************************************/

void ov2640_I2C_Write(uint8_t address, uint8_t reg, uint8_t data) 
{
	uint8_t dt[2];
	dt[0] = reg;
	dt[1] = data;
	HAL_I2C_Master_Transmit(&hi2c2, address, dt, 2, 100);
}
/***********************************************************************************
 * 函數名:    OV2640_RD_REG()  
 * 函數功能:  SCCB 讀取一個字節
 * 輸入參數:  reg 地址
 * 輸出:      返回數據
***********************************************************************************/
unsigned char OV2640_RD_REG(unsigned char reg)
{
    unsigned char val=0;
    /*SCCB開始*/
    /*連動ID*/
    HAL_Delay(100);
    /*確定要讀取的佔存*/
    HAL_Delay(100);
    /*SCCB STOP*/
    HAL_Delay(100);
    //開始讀取REG
    /*SCCB START*/
    /*SCCB 發送命令*/
    HAL_Delay(100);
    /*讀取數據*/
    /*ACK*/
    /*STOP*/
    return val;
}

/***********************************************************************************
 * 函數名:    uint8_t OV2640_Init(void) 
 * 函數功能:  ov2640初始化參數
 * 輸入參數:  無輸入參數
 * 輸出:      0x00回傳則代表初始化成功如果途中回傳1或是2代表device id錯誤
***********************************************************************************/
uint8_t OV2640_Init(void)
{
    //硬體復位
    HAL_GPIO_WritePin(OV2640_PWDN_GPIO_Port, OV2640_PWDN_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(OV2640_RESET_GPIO_Port, OV2640_RESET_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(OV2640_RESET_GPIO_Port, OV2640_RESET_Pin, GPIO_PIN_SET);
    HAL_Delay(10);

    // 开始通过I2C配置OV2640
    ov2640_I2C_Write(SCCB_ID_Write, OV2640_DSP_RA_DLMT, 0x01);  // 操作sensor寄存器
    ov2640_I2C_Write(SCCB_ID_Write, OV2640_SENSOR_COM7, 0x80);  // 软复位OV2640
    HAL_Delay(50);

   // 读取厂家ID验证OV2640是否正常连接
    // uint16_t reg_ID = ov2640_I2C_Read16(SCCB_ID_Write, OV2640_SENSOR_MIDH);
    // if (reg_ID != OV2640_MID)
    // {
    //     // 厂家ID验证失败
    //     return 1;
    // }
    // printf("MID: %d\r\n", reg_ID);

    // // 读取厂商ID验证OV2640是否正常连接
    // reg_ID = ov2640_I2C_Read16(SCCB_ID_Write, OV2640_SENSOR_PIDH);
    // if (reg_ID != OV2640_PID)
    // {
    //     // 厂商ID验证失败
    //     return 2;
    // }
    // printf("HID: %d\r\n", reg_ID);


    /*uart write message ov2640 iD*/

    /*uart write message ov2640  iD*/

    // 初始化 OV2640，采用SXGA分辨率(1600*1200)
    uint8_t i;
    for (i = 0; i < sizeof(ov2640_sxga_init_reg_tbl) / 2; i++)
    {
        uint8_t reg = ov2640_sxga_init_reg_tbl[i][0];
        uint8_t data = ov2640_sxga_init_reg_tbl[i][1];
        ov2640_I2C_Write(SCCB_ID_Write, reg, data);
    }


    return 0x00; 	//ok
}




