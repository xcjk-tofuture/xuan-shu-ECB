#include "pc_proc.h"



//���ڶ��ڵ���usart1  ��Ӧ�Ļ�������Ϊ Uart1_Rx, Uart1_Tx



osThreadId PCTaskHandle;
extern u8 TaskListFlag;
extern u8 RunTimeFlag;
extern char InfoBuffer[1000];
extern u8 Uart1Rx[MAX_UART_RX_NUM];
extern u8 Uart1Tx[MAX_UART_TX_NUM];

void PC_Task_Proc(void const * argument)
{
	for(; ;)
	{
 if(TaskListFlag)
 {
	 
	TaskListFlag = 0;
	memset(InfoBuffer,0,1000);	 
	vTaskList(InfoBuffer);
	printf("\r\n�������� ����״̬ ���ȼ� ʣ���ջ �������\r\n");
	printf("%s\r\n", InfoBuffer);
	printf("B : ����, R : ����, D : ɾ��, S : ��ͣ\r\n"); 
 }
 if(RunTimeFlag)
 {
	RunTimeFlag = 0; 
	memset(InfoBuffer,0,1000);				//��Ϣ����������
	vTaskGetRunTimeStats(InfoBuffer);		//��ȡ��������ʱ����Ϣ
	printf("������\t\t\t����ʱ��\t������ռ�ٷֱ�\r\n");
	printf("%s\r\n",InfoBuffer);

 }
	osDelay(10);
	}

}