#include "motor_proc.h"
#include "simplepid.h"
#include "niming.h"

//*****************************
//ע��1���pwm���� �õ��� ��ʱ��7  10usһ���ж� ��Ϊ1000�� ���ɲ�ͬռ�ձȵ�1khz�Ĳ������������
//*****************************
//*****************************
//ע��2��������Ǿ������ �����з����� ����  �ֲ���ǿ�ƶ��� ����A CΪ��������   B DΪ�������� ����ǿ��ȡ������  �ʰ�װ���ʱ ���� ǰ��ΪC Dһ�� ���� Ϊ A B һ��İ�װ
//*****************************

osThreadId MotorTaskHandle;
osThreadId EncoderTaskHandle;
int motor1;
int motor2;
extern int change_output;
extern int change_x;
extern tPid speed_left;
extern tPid speed_right;
u32 TIM7Count;
extern int angle;
extern int change_output;
extern int change_x;
extern int x;
MOTOR MotorA, MotorB;  //��Ŷ�Ӧ 0 1 

void xianfu_angle(int * motor)
{
	if(*motor < 30)
		*motor = -30;
}


//void xianfu_position(int x,int* change_x)
//{
//	if(x<=10  &&  x>=-10)
//		*change_x = 0;
//}


//void xianfu_chasu()
//{
//	if(fabs(change_output*2 - change_x*2) > 200)
//		
//}
void ditongfilter(int* motor,int target)
{
	*motor = *motor * 0.4 + target * 0.6;
}
void Motor_Task_Proc(void const * argument)   //�����������
{
	
	Motor_Init();
	//PID_speedinit();
  s16 Count = 0;
	for(;;)
	{
		
		Motor_Speed_Set(&MotorA, 950);
	
//		Motor_Speed_Set(&MotorA, -500);
//		osDelay(1000);
		Motor_Speed_Set(&MotorB, 950);
//		if(++Count > 9)
//			Count = -9;
//		TIM4->ARR = 999;
//		HAL_GPIO_WritePin(MOTORA_IN1_GPIO_Port, MOTORA_IN1_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(MOTORA_IN2_GPIO_Port, MOTORA_IN2_Pin, GPIO_PIN_RESET);
//		TIM4->CCR3 = 800;
//		
//		HAL_GPIO_WritePin(MOTORB_IN1_GPIO_Port, MOTORB_IN1_Pin, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(MOTORB_IN2_GPIO_Port, MOTORB_IN2_Pin, GPIO_PIN_SET);
//		TIM4->CCR4 = 600;
		printf("num:%d, speed:%.2f, direction: %d\r\n",MotorA.Num, MotorA.Speed, MotorA.direction);
		printf("num:%d, speed:%.2f, direction: %d\r\n",MotorB.Num, MotorB.Speed, MotorB.direction);

		osDelay(100);

	}


}

void Encoder_Task_Proc(void const * argument)		//��������ȡ����
{

		Motor_Encoder_Init();//��������ʼ��
		for(;;)
	{
		Motor_Get_Value(&MotorA);
		Motor_Get_Value(&MotorB);
		osDelay(10);
	}
}



//�����������ʼ��
/******************************************************************************
      ����˵���������������ʼ������������ģʽ�����壩
      ������ݣ���    
      ����ֵ��  ��
******************************************************************************/
void Motor_Encoder_Init()
{

	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1); 
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_2);
																									//����������ģʽ
  HAL_TIM_Base_Start_IT(&htim2);                  //�������������ж�
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1); //����������ģʽ
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_Base_Start_IT(&htim3);                  //�������������ж�
                 //�������������ж�
	MotorA.Num = 0;
	MotorB.Num = 1;
}

//��ȡ���������ֵ ����  ��ת��Ϊ�ٶ� ��� A B C D ��Ӧ 0 1 2 3
/******************************************************************************
      ����˵�����ı�Ƶ�ⲿ�жϷ� M���ٷ� ��ȡ���������ֵ ����  ��ת��Ϊ�ٶ� ��� A B C D ��Ӧ 0 1 2 3
      ������ݣ�����ṹ��ָ��    
      ����ֵ��  ��
******************************************************************************/
void Motor_Get_Value(MOTOR  *motor)
{
	switch(motor->Num)
	{
		case 0: motor->Trig = __HAL_TIM_GetCounter(&htim2);//��ȡ����ֵ  
						__HAL_TIM_SetCounter(&htim2, 0);//��ռ���ֵ
						motor->direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2);//��ȡ����		
						motor->direction = !motor->direction;  
						motor->Speed = motor->Trig * 3.25 ;
						break;
		case 1: motor->Trig = (short)__HAL_TIM_GetCounter(&htim3);//��ȡ����ֵ  
						__HAL_TIM_SetCounter(&htim3, 0);//��ռ���ֵ
						motor->direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3);//��ȡ����		
						motor->direction = !motor->direction;  //ǿ��ȡ��
						motor->Trig = -motor->Trig;						//ǿ��ȡ��
						motor->Speed = motor->Trig * 3.25 ;
						break;
	}
					
}

/******************************************************************************
      ����˵����������pwm��ʼ��
      ������ݣ���    
      ����ֵ��  ��
******************************************************************************/
void Motor_Init()
{

	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);  //MOTORA_PWM
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);	 //MOTORB_PWM

	HAL_GPIO_WritePin(MOTORB_IN1_GPIO_Port, MOTORB_IN1_Pin, 0);
	HAL_GPIO_WritePin(MOTORB_IN2_GPIO_Port, MOTORB_IN2_Pin, 0);
	HAL_GPIO_WritePin(MOTORA_IN1_GPIO_Port, MOTORA_IN1_Pin, 0);
	HAL_GPIO_WritePin(MOTORA_IN2_GPIO_Port, MOTORA_IN2_Pin, 0);
	
}


/******************************************************************************
      ����˵��������ֵ����
      ������ݣ���ֵ    
      ����ֵ��  ��
******************************************************************************/
int ABS(int a)
{
	a = a>0?a:(-a);
	return a;

}

/******************************************************************************
      ����˵����PWM1-4�����������  �ٶ����ú��� ���õ���ٶ�  ��Χ -999 - +999
      ������ݣ�����ṹ��ָ��   �ٶ�    
      ����ֵ��  ��
******************************************************************************/
//void Motor_Speed_Set_Extra(MOTOR *motor, s16 speed)
//{

//	if(speed >= 1000 ) speed = 999;
//	if(speed <= -1000 ) speed = -999;   //�޷�
//switch(motor->Num)
//{
//	case 0: motor->SetSpeedRange = speed;
//				motor->SetDirection =  motor->SetSpeedRange >= 0 ? 0 : 1;  //�жϷ���   0Ϊ�� 1Ϊ��
//				if(!motor->SetDirection) //����
//				{
//						TIM1->CCR1 = 0;
//						TIM1->CCR2 = ABS((motor->SetSpeedRange   + 1)* 2 -1) ; 
//						 
//				
//				}
//				else if(motor->SetDirection)
//				{
//						TIM1->CCR2 = 0;
//						TIM1->CCR1 = ABS((motor->SetSpeedRange   + 1) * 2 -1) ; 
//				}
//				break;
//	case 1: motor->SetSpeedRange = speed;
//				motor->SetDirection =  motor->SetSpeedRange >= 0 ? 0 : 1;  //�жϷ���
//				if(!motor->SetDirection) //����
//				{
//						TIM1->CCR4 = 0;
//						TIM1->CCR3 = ABS((motor->SetSpeedRange + 1) * 2 -1) ; 
//						 
//				
//				}
//				else if(motor->SetDirection)
//				{
//						TIM1->CCR3 = 0;
//						TIM1->CCR4 = ABS((motor->SetSpeedRange + 1) * 2 -1); 
//				}
//				break;
//}	
//	
//	
//	
//}


/******************************************************************************
      ����˵��������ٶ����ú��� ���õ���ٶ�  ��Χ -999 - +999
      ������ݣ�����ṹ��ָ��   �ٶ�    
      ����ֵ��  ��
******************************************************************************/
void Motor_Speed_Set(MOTOR *motor, s16 speed)
{

	if(speed >= 1000 ) speed = 999;
	if(speed <= -1000 ) speed = -999;   //�޷�
	switch(motor->Num)
	{
		case 0: motor->SetSpeedRange = speed;
						motor->SetDirection =  motor->SetSpeedRange >= 0 ? 0 : 1;  //�жϷ���   0Ϊ�� 1Ϊ��
						if(!motor->SetDirection) //����
						{
							HAL_GPIO_WritePin(MOTORA_IN1_GPIO_Port, MOTORA_IN1_Pin, 1);
							HAL_GPIO_WritePin(MOTORA_IN2_GPIO_Port, MOTORA_IN2_Pin, 0);
							TIM4->CCR3 = ABS(motor->SetSpeedRange) ; 
								 
						
						}
					else if(motor->SetDirection) //����
					{
							HAL_GPIO_WritePin(MOTORA_IN1_GPIO_Port, MOTORA_IN1_Pin, 0);
							HAL_GPIO_WritePin(MOTORA_IN2_GPIO_Port, MOTORA_IN2_Pin, 1);
							TIM4->CCR3 = ABS(motor->SetSpeedRange) ; 
						}
						break;
		case 1: motor->SetSpeedRange = speed;
						motor->SetDirection =  motor->SetSpeedRange >= 0 ? 0 : 1;  //�жϷ���
						if(!motor->SetDirection) //����
						{
							HAL_GPIO_WritePin(MOTORB_IN1_GPIO_Port, MOTORB_IN1_Pin, 0);
							HAL_GPIO_WritePin(MOTORB_IN2_GPIO_Port, MOTORB_IN2_Pin, 1);
							TIM4->CCR4 = ABS(motor->SetSpeedRange) ; 
						}
					else if(motor->SetDirection) //����
					{
							HAL_GPIO_WritePin(MOTORB_IN1_GPIO_Port, MOTORB_IN1_Pin, 1);
							HAL_GPIO_WritePin(MOTORB_IN2_GPIO_Port, MOTORB_IN2_Pin,  0);
							TIM4->CCR4 = ABS(motor->SetSpeedRange) ; 
					
					}
						break;
	}
					

}
