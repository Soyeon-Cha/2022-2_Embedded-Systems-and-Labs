#include "msp.h"


/**
 * main.c
 */


void PORT1_IRQHandler(void){
    if(P1->IFG&BIT1){  // S1�� ������ ��
        P2->OUT = 0x02;
        P1->IFG &= ~BIT1;
    }

    if(P1->IFG&BIT4){  // S2�� ������ ��
        P2->OUT = 0x04;
        P1->IFG &= ~BIT4;
    }
}


void main(void)
{

	P1->DIR &= ~(1<<1|1<<4);  // pin1,4�� input ����
	P1->OUT |= (1<<4)|(1<<1);  // pullup ����
	P1->REN = (1<<4)|(1<<1);  // pull enable
	P1->IES = BIT1|BIT4;  // �����ٰ� ���� ��  interrupt �߻��ϵ���
	P1->IFG = 0;  //  P1�� ��� interrupt flag ����
	P1->IE = BIT1|BIT4;  // P1.1 interrupt enable
    P2->DIR = 0x07;
    P2->OUT = 1<<0;
	NVIC->ISER[1] = 1<<((PORT1_IRQn)&31);  // Enable Port1 interrupt on the NVIC
	while(1){}
}
