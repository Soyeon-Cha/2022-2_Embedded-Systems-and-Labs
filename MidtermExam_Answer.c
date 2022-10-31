#include "msp.h"
#define S1BUT ((P1->IN&(1<<1))==0x00)
#define S2BUT ((P1->IN&(1<<4))==0x00)

/**
 * main.c
 */

void main(void)
{
    P1->DIR&=~(1<<1|1<<4);
    P1->DIR|=(1<<0);
    P2->DIR=(1<<0|1<<1|1<<2);
    P1->REN=(1<<1|1<<4);
    P1->OUT=(1<<1|1<<4);
    int i;
    int pos=0;

    while(1){
        if(S1BUT){
            P1->OUT=(1<<1|1<<4|1<<0);
            for(i=0;i<100000;i++);
            P1->OUT=(1<<1|1<<4);
            for(i=0;i<100000;i++);
        }
        else{
            P1->OUT=(1<<1|1<<4);
        }

        if(S2BUT){
            P2->OUT=(1<<pos);
            if(pos==2)pos=0;
            else pos++;
            for(i=0;i<100000;i++);
        }
        else{
            P2->OUT=0x00;
            pos=0;
        }
    }
}
