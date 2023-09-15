#include "simplepid.h"
//����һ���ṹ����
tPid speed_left;
tPid speed_right;
tPid angel;
tPid position;
//���ṹ�������ֵ
void PID_speedinit()
{
	speed_left.target_val = 100;
	speed_left.actual_val = 0.0;
	speed_left.err = 0.0;
	speed_left.err_last = 0.0;
	speed_left.err_sum = 0.0;
	speed_left.kp = 6.5;
	speed_left.ki = 0.2;
	speed_left.kd = 0;
	speed_right.target_val = 100;
	speed_right.actual_val = 0.0;
	speed_right.err = 0.0;
	speed_right.err_last = 0.0;
	speed_right.err_sum = 0.0;
	speed_right.kp = 6.5;
	speed_right.ki = 0.2;
	speed_right.kd = 0;
}


void PID_angelInit()
{
	angel.target_val = 0.0;
	angel.actual_val = 0.0;
	angel.err = 0.0;
	angel.err_last = 0.0;
	angel.err_sum = 0.0;
	angel.kp = 1.5;
	angel.ki = 0;
	angel.kd = 0;
}

void PID_positionInit()
{
	position.target_val = 0.0;
	position.actual_val = 0.0;
	position.err = 0.0;
	position.err_last = 0.0;
	position.err_sum = 0.0;
	position.kp = 2;
	position.ki = 0;
	position.kd = 4;
}



float P_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;
	pid->err = pid->target_val - pid->actual_val;
	pid->actual_val = pid->kp*pid->err;
	return pid->actual_val;
}

float PI_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;
	pid->err = pid->target_val - pid->actual_val;
	pid->err_sum += pid->err;
	
	pid->actual_val = pid->kp*pid->err + pid->ki*pid->err_sum;
	
	return pid->actual_val;
}



float PID_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;
	pid->err = pid->target_val - pid->actual_val;
	pid->err_sum += pid->err;
	pid->actual_val = pid->kp*pid->err + pid->ki*pid->err_sum + pid->kd*(pid->err - pid->err_last);
	pid->err_last = pid->err;
	return pid->actual_val;
}
/**************************************************************************
�������ܣ�λ��ʽPID������
��ڲ���������������λ����Ϣ��Ŀ��λ��
����  ֵ�����PWM
����λ��ʽ��ɢPID��ʽ 
pwm=Kp*e(k)+Ki*��e(k)+Kd[e��k��-e(k-1)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  
��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;����kΪ1,2,,k;
pwm�������
**************************************************************************/
int Position_PID (tPid *pid,int target)
{ 	
	 static float Moto;
	 pid->err=pid->target_val-pid->actual_val;                                  //����ƫ��
	 pid->err_sum+=pid->err;	                                 //���ƫ��Ļ���
	 Moto=pid->kp*pid->err/100+pid->ki*pid->err_sum/100+pid->kd*(pid->err-pid->err_last)/100;       //λ��ʽPID������
	 pid->err_last=pid->err;                                       //������һ��ƫ�� 
	 return Moto;                                           //�������
}

