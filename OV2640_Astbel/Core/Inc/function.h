#ifndef __FUNCTION_H_
#define __FUNCTION_H_
/************************include**************/
/*RTOS Sub Function */
void start_task(void *pvParameters);
void Task_1(void *pvParameters);
void Task_2(void *pvParameters);

/*Task scheduler for mian loop*/
void start_task(void *pvParameters);
void RTOS_Initliaze(void);
/*Nethod for uart display at C# GUI*/
#endif
