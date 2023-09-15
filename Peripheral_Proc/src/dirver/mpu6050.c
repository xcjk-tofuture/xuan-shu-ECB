#include "mpu6050.h"
#include "stdio.h"
unsigned char I2C_Accel_Buf[6];
unsigned char I2C_Gyro_Buf[6];

//���ٶȼ�
signed short ax; 
signed short ay; 
signed short az; 

//������
signed short gx; 
signed short gy; 
signed short gz; 

//У׼
signed short ax_l=0; 
signed short ay_l=0; 
signed short az_l=0; 
signed short gx_l=0; 
signed short gy_l=0; 
signed short gz_l=0; 

//��дI2Cд��
void I2C_Write(unsigned char dev_addr,unsigned char mem_addr , unsigned char data)
{
	HAL_I2C_Mem_Write(&hi2c1,dev_addr,mem_addr,I2C_MEMADD_SIZE_8BIT,&data,1,2);
}

//��дI2C����
void I2C_Read(unsigned char dev_addr,unsigned char mem_addr , unsigned char *buf,unsigned char len)
{
	HAL_I2C_Mem_Read(&hi2c1,dev_addr,mem_addr,I2C_MEMADD_SIZE_8BIT,buf,len,2);
}

//��ʼ��MPU6050
void MPU_6050_Init(void)
{
	unsigned char temp=0;
  //reset_MPU6050:
	I2C_Write(MPU6050_Write_Addr,PowerMem_Register1_Addr,Set_PowerMen_Reset); 					//MPU��λ
	osDelay(50);
	I2C_Write(MPU6050_Write_Addr,PowerMem_Register1_Addr,Set_PowerMen_Start_XPPL);			//MPU����  ʹ��X����Ϊʱ��Դ
	I2C_Read(MPU6050_Write_Addr,MPU_Id_Addr,&temp,1);																//������ID
//	if(temp != 0x68)
//	{
//		goto reset_MPU6050;
//	}
	

	I2C_Write(MPU6050_Write_Addr,MPU_Gyro_Addr,(Set_Gyro_Range<<3));								//���������̷�Χ����     2000
	I2C_Write(MPU6050_Write_Addr,MPU_Accel_Addr,(Set_Accel_Range<<3));							//���ټ����̷�Χ����			��2G
	Set_Mpu_Rate(50);																																//�����ʷ�Ƶ
	I2C_Write(MPU6050_Write_Addr,MPU_Int_Pin_Addr,Set_Int_Enable);									//�ر������ж�
	I2C_Write(MPU6050_Write_Addr,MPU_User_Addr,Set_User_I2c);												//�ر�I2C��ģʽ
	I2C_Write(MPU6050_Write_Addr,MPU_Fifo_En_Addr,Set_Fifo_Enable);									//�ر�FIFO
	I2C_Write(MPU6050_Write_Addr,MPU_Int_Pin_Addr,Set_Int_Pin_L);									  //INT�͵�ƽ��Ч
	I2C_Write(MPU6050_Write_Addr,PowerMem_Register2_Addr,Sat_Start_Mpu);					  //MPU��ʼ����

}

//��ȡ�����ǵ�����
void Read_Mpu_Gyro(void)
{
	I2C_Read(MPU6050_Write_Addr,GYRO_Xout_H,I2C_Gyro_Buf,6);
	
	gx=	(I2C_Gyro_Buf[0]<<8)+I2C_Gyro_Buf[1]-gx_l;
	gy=	(I2C_Gyro_Buf[2]<<8)+I2C_Gyro_Buf[3]-gy_l;
	gz=	(I2C_Gyro_Buf[4]<<8)+I2C_Gyro_Buf[5]-gz_l;
}

//��ȡ���ٶȼƵ�����
void Read_Mpu_Accel(void)
{
	I2C_Read(MPU6050_Write_Addr,ACCEL_Xout_H,I2C_Accel_Buf,6);
	
	ax=	(I2C_Accel_Buf[0]<<8)+I2C_Accel_Buf[1]-ax_l;
	ay=	(I2C_Accel_Buf[2]<<8)+I2C_Accel_Buf[3]-ay_l;
	az=	(I2C_Accel_Buf[4]<<8)+I2C_Accel_Buf[5]-az_l;
}

//���ò���Ƶ��
//����ֵ:0,���óɹ�
//    ����,����ʧ��
void Set_Mpu_Rate(uint16_t rata)
{
	uint8_t data;
	if(rata>1000)
	rata=1000;
	if(rata<4)
	rata=4;
	data= 1000 /rata-1;
	I2C_Write(MPU6050_Write_Addr,MPU_Out_Fre_DIV_Addr,data);									//�����ʷ�Ƶ
	MPU_Set_LPF(rata/2);	//�Զ�����LPFΪ�����ʵ�һ��
}

//����MPU6050�����ֵ�ͨ�˲���
//����ֵ:0,���óɹ�
//    ����,����ʧ��
void MPU_Set_LPF(uint16_t lpf)
{
    uint8_t data=0;
    if(lpf>=188)data=1;
    else if(lpf>=98)data=2;
    else if(lpf>=42)data=3;
    else if(lpf>=20)data=4;
    else if(lpf>=10)data=5;
    else data=6;
   	I2C_Write(MPU6050_Write_Addr,MPU_Dlpf_Addr,data);		
}


/*��У׼ģʽ
MPU6050У׼����
��IMUˮƽ���ã�z������ʱ������У׼
˼·�Ǽ���N�����ڵ�ƽ��ֵ���õ�У׼����
*/
#define	CL_cnt	128
void MPU6050_calibrate(void)
{
	unsigned short i;	
	signed int temp[6] = {0};
	for(i=0; i<CL_cnt; i++)
	{
		HAL_Delay(10);
		Read_Mpu_Gyro();
		Read_Mpu_Accel();
		temp[0] += ax;
		temp[1] += ay;
		temp[2] += az;
		temp[3] += gx;
		temp[4] += gy;
		temp[5] += gz;
	}	
	ax_l = temp[0]/CL_cnt;
	ay_l = temp[1]/CL_cnt;
	az_l = temp[2]/CL_cnt - (0xffff>>2); //ƽ��ʱz�����������ٶ�g����ȥgֵ
	gx_l = temp[3]/CL_cnt;
	gy_l = temp[4]/CL_cnt;
	gz_l = temp[5]/CL_cnt;
}
