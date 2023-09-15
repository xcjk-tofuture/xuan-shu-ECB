#ifndef __RGB_PROC_H

#define __RGB_PROC_H



#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "usart.h"





void RGB_Task_Proc(void const * argument);		//RGB����������
void RGB_Show_Proc(u8 ucled);                 //RGB������
#endif