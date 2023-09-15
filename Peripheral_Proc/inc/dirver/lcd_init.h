#ifndef __LCD_INIT_H
#define __LCD_INIT_H

//#include "sys.h"

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "gpio.h"
#include "spi.h"
#define USE_HORIZONTAL 1  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 128
#endif



//-----------------LCD�˿ڶ���---------------- 

//#define LCD_SCLK_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_RESET)//SCL=SCLK
//#define LCD_SCLK_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_SET)

//#define LCD_MOSI_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_RESET)//SDA=MOSI
//#define LCD_MOSI_Set() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_SET)

#define LCD_RES_Clr()  HAL_GPIO_WritePin(GPIOE, TFT_RES_Pin, GPIO_PIN_RESET)//GPIO_ResetBits(GPIOE,GPIO_Pin_0)//RES
#define LCD_RES_Set()  HAL_GPIO_WritePin(GPIOE, TFT_RES_Pin, GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(GPIOE, TFT_DC_Pin, GPIO_PIN_RESET)//GPIO_ResetBits(GPIOE,GPIO_Pin_1)//DC
#define LCD_DC_Set()   HAL_GPIO_WritePin(GPIOE, TFT_DC_Pin, GPIO_PIN_SET)//GPIO_SetBits(GPIOE,GPIO_Pin_1)
 		     
#define LCD_CS_Clr()   HAL_GPIO_WritePin(GPIOE, SPI1_TFT_Pin, GPIO_PIN_RESET)//GPIO_ResetBits(GPIOE,GPIO_Pin_2)//CS
#define LCD_CS_Set()   HAL_GPIO_WritePin(GPIOE, SPI1_TFT_Pin, GPIO_PIN_SET)//GPIO_SetBits(GPIOE,GPIO_Pin_2)

#define LCD_BLK_Clr()  HAL_GPIO_WritePin(GPIOE, TFT_BL_Pin, GPIO_PIN_RESET)//PIO_ResetBits(GPIOE,GPIO_Pin_3)//BLK
#define LCD_BLK_Set()  HAL_GPIO_WritePin(GPIOE, TFT_BL_Pin, GPIO_PIN_SET)//GPIO_SetBits(GPIOE,GPIO_Pin_3)



void LCD_WriteData(uint8_t *buff, size_t buff_size); //д��һ������
void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(u8 dat);//ģ��SPIʱ��
void LCD_WR_DATA8(u8 dat);//д��һ���ֽ�
void LCD_WR_DATA(u16 dat);//д�������ֽ�
void LCD_WR_REG(u8 dat);//д��һ��ָ��
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif




