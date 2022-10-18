#include "msp.h"
#define S1BUT ((P1->IN&(1<<1))==0x00)
#define S2BUT ((P1->IN&(1<<4))==0x00)

/**
 * main.c
 */

void main(void)
{
    P1->DIR&=~(1<<1|1<<4);
    P1->REN=(1<<4)|(1<<1); // pullup, pulldown 쓸 수 있게 허용. 이게 불빛 나오는 데랑은 상관 없음?
    P1->OUT=(1<<4)|(1<<1);


    P2->DIR|=1<<2|1<<1|1<<0;
    P2->OUT=1<<pos;

    P2->OUT=1<<0;

    int pos=0;

    while(1){
        if(S1BUT){  // S1을 누르는 동안 P1에 빨간 불빛
            P1->OUT=1<<1|1<<0;  // 빨간 불빛
            P2->OUT=1<<pos;  // P2 켜져 있는 불빛 색 유지

        }
        else{  // S2, S1 아예 따로 써야 됨. 독립적으로.
            P1->OUT=0x00;  // S1 button up P1의 빨간불 꺼짐
            if(pos==0)  // P2 색 바로 바꿈
                pos=1;
            else if(pos==1)
                pos=2;
            else if(pos==2)
                pos=0;
            P2->OUT=1<<pos;  // S1에서 눌렀을 때 바꾼 pos로 바뀐 색 P2에 반영
        }

        if(S2BUT){
            P1->OUT=1<<1|1<<4|1<<0;  // 여기에 있는 4는 왜 있는 건데? ren을 어떻게 쓰는 건지 모르겠음.
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
}
