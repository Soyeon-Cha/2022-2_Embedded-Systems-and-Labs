#include "msp.h"

/**

 * main.c

 */

void main(void)
{
    volatile unsigned char *gpio_p2dir, *gpio_p2out;
    gpio_p2dir = (unsigned char*)(0x40004C05);
    gpio_p2out = (unsigned char *)(0x40004C03);
    
    int i;
    *gpio_p2dir = 0x07;

    while(1){

        *gpio_p2out = 0x02;
        for(i=0; i<100000;i++)
            ;

        *gpio_p2out = 0x06;
        for(i=0; i<100000;i++)
            ;

        *gpio_p2out = 0x04;
        for(i=0; i<100000;i++)
            ;

        *gpio_p2out = 0x05;
        for(i=0; i<100000;i++)
            ;

        *gpio_p2out = 0x01;
        for(i=0; i<100000;i++)
            ;

        *gpio_p2out = 0x03;
        for(i=0; i<100000;i++)
            ;

        *gpio_p2out = 0x07;
        for(i=0; i<100000;i++)
            ;
    }
}
