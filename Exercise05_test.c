#include "msp.h"
#define S1BUT ((P1->IN&(1<<1))==0x00)
#define S2BUT ((P1->IN&(1<<4)))==0x00)
#define BS_INIT 1
#define BS_DOWN 2
#define BS_UP 3

/**
 * main.c
 */

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;      // stop watchdog timer

    int pos=0;
    P1->DIR&=~(1<<1|1<<4);
    P1->DIR |= 1<<0;
    P1->REN=1<<4|1<<1;
    P1->OUT=1<<4|1<<1;

    P2->DIR|=1<<2|1<<1|1<<0;
    P2->OUT=1<<pos;
    int s1but_bs = BS_INIT;
    int s2but_bs = BS_INIT;


    P2->OUT=1<<0;

    while(1){
        if(S1BUT){
            P1->OUT=1<<1|1<<4|1<<0;
            P2->OUT=1<<pos;
            if(pos==0)
                pos=1;
            else if(pos==1)
                pos=2;
            else if(pos==2)
                pos=0;
        }


        else{  // S2가 눌렸을 때 포함
            P1->OUT=0x00;
            P2->OUT=1<<pos;

            if(S2BUT){
                P1->OUT=1<<1|1<<4|1<<0;
                P2->OUT=1<<pos;
                if(pos==0)
                    pos=1;
                else if(pos==1)
                    pos=2;
                else if(pos==2)
                    pos=0;
            }

            else{
                P1->OUT=0x00;
                P2->OUT=1<<pos;
            }
        }



        if(S2BUT){
            P1->OUT=1<<1|1<<0&;
            P2->OUT=1<<pos;

            if(pos==0)
                pos=1;
            else if(pos==1)
                pos=2;
            else if(pos==2)
                pos=0;
        }

        else{
            P1->OUT=0x00;
            P2->OUT=1<<pos;

            if(S1BUT) {
                P1->OUT = 1 << 1 | 1 << 0;
                P2->OUT = 1 << pos;

                if (pos == 0)
                    pos = 1;
                else if (pos == 1)
                    pos = 2;
                else if (pos == 2)
                    pos = 0;
            }
            else{
                P1->OUT=0x00;
                P2->OUT=1<<pos;
            }
        }
    }
}
