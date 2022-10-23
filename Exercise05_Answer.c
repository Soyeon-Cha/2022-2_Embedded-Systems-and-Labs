#include "msp.h"
#define S1BUT ((P1->IN&(1<<1))==0x00)  // S1이 눌러져 있을 때 1, 떼어져 있을 때 0
#define S2BUT ((P1->IN&(1<<4)))==0x00)  // S2가 눌러져 있을 때 1, 떼어져 있을 때 0
#define BS_INIT 1
#define BS_DOWN 2
#define BS_UP 3

/**
 * main.c
 */

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;      // stop watchdog timer

    P1->DIR&=~(1<<1|1<<4);  // P1의 pin#1,4를 input으로 설정
    P1->DIR |= 1<<0;
    P1->REN=(1<<4)|(1<<1);  // pullup or pulldown enabled
    P1->OUT=(1<<4)|(1<<1);  // pullup으로 설정

    P2->DIR|=1<<2|1<<1|1<<0;
    int pos=0;
    P2->OUT=1<<pos;

    int s1but_bs = BS_INIT;
    int s2but_bs = BS_INIT;

    P2->OUT=1<<0; // P2 빨간 불 켜두기

    while(1){
        if(S1BUT){ // S1이 눌러져 있을 때. P1.0 켜기.
            s1but_bs = BS_DOWN;  // S1 눌린 상태로 설정
            P1->OUT=1<<1|1<<4|1<<0;  // registor pullup 유지하면서(1<<1|1<<4) P1.0 켜기(1<<0)
        }
        else{  // S1이 떼어졌을 때.
            P1->OUT=1<<1|1<<4;  // P1 불 끄기
            if(s1but_bs==BS_DOWN){  // Button Down State에 갔다 왔으면
                if(pos==0)  // P2 빨->파->초. pin# 0->2->1
                    pos=2;
                else if(pos==2)
                    pos=1;
                else
                    pos=0;
                P2->OUT=1<<pos;  // 바뀐 P2 색 반영
                s1but_bs=BS_UP;  // S1 떼어진 상태로 설정
            }
        }

        if(S2BUT){ // S2가 눌러져 있을 때. P1.0 켜기.
            s2but_bs = BS_DOWN;  // S2 눌린 상태로 설정
            P1->OUT=1<<1|1<<4|1<<0;  // pullup 유지하면서 P1.0 켜기
        }
        else{  // S1이 떼어졌을 때.
            P1->OUT=1<<1|1<<4;  // P1 불 끄기
            if(s1but_bs==BS_DOWN){  // Button Down State에 갔다 왔으면
                if(pos<2)  // P2 빨->초->파. pin# 0->1->2
                    pos++;
                else
                    pos=0;
                P2->OUT=1<<pos;  // 바뀐 P2 색 반영
                s2but_bs=BS_UP;  // S2 떼어진 상태로 설정
            }
        }
    }
}
