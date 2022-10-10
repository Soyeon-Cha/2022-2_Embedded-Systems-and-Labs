#include "msp.h"s


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	P1->DIR |= BIT0;
	P1->OUT = BIT0;

	while (1) {
		P1->OUT = 0;
		int i;
		for (i = 0; i < 100000; i++)
			;
		P1->OUT = BIT0;
		int i;
		for (i = 0; i < 100000; i++)
			;
	}
}
