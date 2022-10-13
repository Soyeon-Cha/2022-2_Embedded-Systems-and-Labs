#include "msp.h"

/**

 * main.c

 */

void main(void)
{
	volatile unsigned char *gpio_p1dir, *gpio_p1out;
             int i;
             gpio_p1dir = (unsigned char*)(0x40004C04);
	gpio_p1out = (unsigned char*)(0x40004C02);
	*gpio_p1dir=0x01;
    
	while(1){
	    *gpio_p1out=0x01;
	    for(i=0; i<100000; i++);

	    *gpio_p1out=0x00;
	    for(i=0; i<100000; i++);
	}
}
