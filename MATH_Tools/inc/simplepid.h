#ifndef __PID_H
#define __PID_H

//����һ���ṹ������
typedef struct
{
	float target_val;//Ŀ��ֵ
	float actual_val;//ʵ��ֵ
	float err;//��ǰƫ��
	float err_last;//�ϴ�ƫ��
	float err_sum;//��ʷ�ۼ�ƫ��
	float kp,ki,kd;//���������֣�΢��ϵ��
} tPid;

float P_realize(tPid * pid,float actual_val);
void PID_speedinit(void);
void PID_angelInit();
void PID_positionInit();
float PI_realize(tPid * pid,float actual_val);
float PID_realize(tPid * pid,float actual_val);
int Position_PID (tPid *pid,int target);


#endif

