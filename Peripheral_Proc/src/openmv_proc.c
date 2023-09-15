#include "openmv_proc.h"
#include "simplepid.h"
#include "math.h"
//���ڶ��ڵ���usart4  ��Ӧ�Ļ�������Ϊ Uart4_Rx, Uart4_Tx
extern tPid angel;
extern tPid position;
int change_output;
int change_x;
int x;
int angle;
osThreadId OpenMVTaskHandle;

extern u8 Uart4Rx[MAX_UART_RX_NUM];
extern u8 Uart4Tx[MAX_UART_TX_NUM];

void OpenMV_Task_Proc(void const * argument)
{
	PID_angelInit();
	PID_positionInit();
	for(; ;)
	{
	x = Uart4Rx[3];//��ȡ��ǰ�����꣬����������С����������ߵľ���
	x -= 80;
	angle = Uart4Rx[2];
	change_output = change_x = 0;
	change_output = PID_realize(&angel,angle);
	if(!Uart4Rx[4])
		change_output *= -1;
	change_x = PID_realize(&position,x);
//	printf("angle:%d,position:%d,signal:%d,changeoupput:%d\r\n",Uart4Rx[2],x,Uart4Rx[4],change_output);

	
	
	osDelay(100);
	}
}

