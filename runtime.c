#include "device_driver.h"

char * _sbrk(int inc)
{
	extern unsigned char __ZI_LIMIT__;
	static char * heap = (char *)0;

	char * prevHeap;
	char * nextHeap;

	if(heap == (char *)0) heap = (char *)HEAP_BASE;

	prevHeap = heap;
	nextHeap = (char *)((((unsigned int)heap + inc) + 0x7) & ~0x7);

	if((unsigned int)nextHeap >= HEAP_LIMIT) return (char *)0;

	heap = nextHeap;
	return prevHeap;
}

void System_Init(void)
{
	// Device 초기화
	Uart1_Init(115200); // Uart1 장치 초기화
	Uart1_RX_Interrupt_Enable(1); // Uart1 RX 이벤트 interrupt 활성화

	Key_Poll_Init();	// Key(LCD 보드의 키) 초기화
	Key_ISR_Enable(1);	// Key push 이벤트  interrupt 활성화

	Lcd_Init();	// LCD 초기화

	LED_Init();	// LED 초기화

	SCB->VTOR = 0x08003000;
	SCB->SHCSR = 7<<16;
	SCB->AIRCR = 0x05FA0000;
}
