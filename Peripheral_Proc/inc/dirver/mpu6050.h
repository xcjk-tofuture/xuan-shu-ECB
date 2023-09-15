#ifndef __MPU6050_H
#define __MPU6050_H

#include  "main.h"
#include  "i2c.h"

#define  MPU6050_Write_Addr           0xd0     //Ĭ��״̬ ��ַΪ0X69 ֻ����λ���� ʹ��IC7λѰַ  ������λ����MPU6050����AD0���ж�  AD0=0 ����λ0  AD0=1 ����λ1   �ڰ�λI2C��1 д0  ������ʹ��AD0=0�͵�ƽ
#define  MPU6050_Read_Addr            0xd1
#define  MPU_Out_Fre_DIV_Addr         0x19      //����Ƶ�ʵ�ַ   Ĭ��8Khz  ������˵�ͨ�˲��� ���Ϊ1Khz
#define  MPU_Dlpf_Addr                0x1A		//��ͨ�˲�����ַ 
#define  MPU_Gyro_Addr			      0x1B		//���������ݵ�ַ    �ڰ�����λ  XYZ���Լ��1  ���Լ��0  ��������λ ���ڸ����������̷�Χ  00-0~250  01-0~500 10-0~1000  11-0~2000  ����λ0
#define  MPU_Accel_Addr               0x1C		//���ټ����ݵ�ַ    �ڰ�����λ  XYZ���Լ��1  ���Լ��0  ��������λ ���ڸ����������̷�Χ  00-��2G   01-��4G 	10-��8G  	 11-��16G ����λ0
#define  MPU_Id_Addr                  0x75      //MPU ID�ĵ�ַ
#define  MPU_Int_Addr				  0X38		//mpu�ж�ʹ�ܵ�ַ
#define  MPU_User_Addr				  0x6A      //MPU�û����Ƶ�ַ  ���ڿ���FIFO  I2C��ģʽ
#define  MPU_Fifo_En_Addr			  0x23		//MPU��FIFOʹ�ܵ�ַ
#define  MPU_Int_Pin_Addr			  0x37      //INT�жϵ�ַ
#define  PowerMem_Register1_Addr      0x6B		//��Դ����1�ĵ�ַ
#define  PowerMem_Register2_Addr      0x6C		//��Դ����2�ĵ�ַ





#define  Set_PowerMen_Reset           0x80		//�ڵ�Դ���� ���� ������� ΪMPU ��λ
#define  Set_PowerMen_Start_XPPL	  0x01      //�ڵ�Դ���� ���� ������� ΪMPU���� ��ʹ��X���ʱ��Դ
#define  Set_Smplrt_Div				  0x00      //������Ƶ
#define  Set_Dlpf_Div				  0x00      //��ͨ�˲���ģʽ
#define  Set_Gyro_Range               0x11      //���������ǵ����̷�Χ
#define  Set_Accel_Range              0x00      //���ü��ټƵ����̷�Χ
#define  Set_Int_Enable				  0x00      //���ùر�ȫ���ж�
#define  Set_User_I2c				  0x00		//��ֹFIFO  I2C��ģʽ
#define  Set_Fifo_Enable			  0x00      //��ֹFIFOģʽ
#define  Set_Int_Pin_L				  0x80      //INT�ŵ͵�ƽ��Ч
#define  Sat_Start_Mpu				  0x00		//��������MPU������

//���ٶȼ� ���ݼĴ�����ַ
#define ACCEL_Xout_H				  0x3B
#define ACCEL_Xout_L				  0x3C
#define ACCEL_Yout_H				  0x3D
#define ACCEL_Yout_L  				  0x3E
#define ACCEL_Zout_H				  0x3F
#define ACCEL_Zout_L				  0x40

//������  ���ݼĴ�����ַ
#define GYRO_Xout_H					  0x43
#define GYRO_Xout_L					  0x44
#define GYRO_Yout_H				      0x45
#define GYRO_Yout_L					  0x46
#define GYRO_Zout_H					  0x47
#define GYRO_Zout_L					  0x48


extern signed short ax;
extern signed short ay;
extern signed short az;

extern signed short gx;
extern signed short gy;
extern signed short gz;

extern signed short ax_l;
extern signed short ay_l;
extern signed short az_l;

extern signed short gx_l;
extern signed short gy_l;
extern signed short gz_l;

void I2C_Write(unsigned char dev_addr,unsigned char mem_addr , unsigned char data);
void I2C_Read(unsigned char dev_addr,unsigned char mem_addr , unsigned char *buf,unsigned char len);
void MPU_Set_LPF(uint16_t lpf);
void Set_Mpu_Rate(uint16_t rata);
void MPU_6050_Init(void);
void Read_Mpu_Gyro(void);
void Read_Mpu_Accel(void);
void MPU6050_calibrate(void);
#endif