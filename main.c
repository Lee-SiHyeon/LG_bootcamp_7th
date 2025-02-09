#include "device_driver.h"
#include "OS.h"

void Task1(void *para)
{
	volatile int i;
	for(;;)
	{
		LED_0_Toggle();
		for(i=0;i<0x50000;i++);
	}
}

void Task2(void *para)
{
	volatile int i;
	for(;;)
	{
		LED_1_Toggle();
		for(i=0;i<0x100000;i++);
	}
}

void Task3(void *para)
{
	volatile int i;
	int cnt = 0;
	for(;;)
	{
		Uart_Printf("Task3 : %d\n", cnt++);
		for(i=0;i<0x100000;i++);
	}
}

void Main(void)
{
	// 참고 : Main 함수에 들어온 시점의 모드 관련 정보
	// Thread mode
	// Thread mode의 권한 : Priviliged
	// Thread mode의 MSP 사용 : 아직 RTOS의 초기화 과정이 남아 있으므로 MSP 사용하며 진행, 추후 Task 코드 실행 시 PSP 사용으로 전환

	Uart_Printf("M3-Mini RTOS\n");

	OS_Init();	// OS 자료구조 초기화

	OS_Create_Task_Simple(Task2, (void*)0, 5, 128); // Task 생성

	OS_Scheduler_Start();	// Scheduler Start (지금은 첫번째 Task의 실행만 하고 있음)

	for(;;)
	{

	}
}
