#include "k210_proc.h"



//���ڶ��ڵ���usart5  ��Ӧ�Ļ�������Ϊ Uart5_Rx, Uart5_Tx



osThreadId K210TaskHandle;

extern u8 Uart5Rx[MAX_UART_RX_NUM];
extern u8 Uart5Tx[MAX_UART_TX_NUM];

void K210_Task_Proc(void const * argument)
{
	for(; ;)
	{
	
	osDelay(200);
	}




}
