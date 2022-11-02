#include "msp.h"


/**
 * main.c
 */


void SysTick_Init(void){
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->CTRL = 0x00000005;
}
void SysTick_Wait(uint32_t n){
        SysTick->LOAD = n-1;
        SysTick->VAL = 0;
        while((SysTick->CTRL & 0x00010000)==0){}
}

uint32_t i;
void SysTick_Wait3s(uint32_t delay){
    for(i=0; i<delay; i++){
        SysTick_Wait(1500000);
    }
}


void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	P1->DIR|=1<<0;

	while(1){
	    SysTick_Init();
	    P1->OUT=1<<0;
	    SysTick_Wait3s(6);
	    P1->OUT=0;
	    SysTick_Wait3s(6);
        P1->OUT=1<<0;
        SysTick_Wait3s(5);
        P1->OUT=0;
        SysTick_Wait3s(5);
        P1->OUT=1<<0;
        SysTick_Wait3s(4);
        P1->OUT=0;
        SysTick_Wait3s(4);
        P1->OUT=1<<0;
        SysTick_Wait3s(3);
        P1->OUT=0;
        SysTick_Wait3s(3);
        P1->OUT=1<<0;
        SysTick_Wait3s(2);
        P1->OUT=0;
        SysTick_Wait3s(2);

        int k;
        for(k=0; k<9;k++){
            P1->OUT=1<<0;
            SysTick_Wait3s(1);
            P1->OUT=0;
            SysTick_Wait3s(1);
        }
	}
}

