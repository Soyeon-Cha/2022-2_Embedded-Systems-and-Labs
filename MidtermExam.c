#include "msp.h"

#define BS_INIT 1
#define BS_UP 2
#define BS_DOWN 3


/**
 * main.c
 */
void main(void)
{


	int s1_bs=BS_INIT;
	int s2_bs=BS_INIT;
	int pos=0;

	P1->DIR&=~(1<<1|1<<4);  // input
	P1->DIR|=1<<0;  // P1  »¡°£ºÒ
	P1->REN=1<<1|1<<4;
	P2->DIR|=1<<2|1<<1|1<<0;  // P2 0,1,2  output

	int i;

	while(1){
	    if(((P1->IN)&(1<<1))==0x00){  // P1.1 ´­·¶À» ¶§
	        P1->OUT=1<<4|1<<1|1<<0;  // À¯ÁöÇÏ¸é¼­ P1 ÄÑÁü
	        s1_bs==BS_DOWN;
	    }

	    else{
	        if(s1_bs==BS_DOWN){  // P1.4 ´­·¶´Ù ¶¼¾úÀ» ¶§
	            P1->OUT=1<<4|1<<1|1<<0;
	            for(i=0; i<100000;i++);
	            P1->OUT=1<<4|1<<1;  // À¯ÁöÇÏ¸é¼­ P1 ²û
	            s1_bs=BS_UP;
	            }
	        P1->OUT=1<<4|1<<1;
	    }

	    if(((P1->IN)&(1<<4))==0x00){ // P1.4 ´­·¶À» ¶§
	        pos=0;
	        while(((P1->IN)&(1<<4))==0x00){
	            P2->OUT=1<<pos;
	            for(i=0; i<100000;i++)
	                ;
	            if(pos==0){
	                pos=1;
	            }
	            else if(pos==1){
	                pos=2;
	            }
	            else
	                pos=0;
	        }
	        s2_bs=BS_DOWN;
	    }

	    else
	        if(s2_bs==BS_DOWN){  // P1.4 ´­·¶´Ù ¶¼¾úÀ» ¶§
	            P2->OUT=1<<pos;
	            for(i=0; i<100000;i++) // ¸¶Áö¸·²¨ ÄÒ »óÅÂ·Î À¯ÁöÇÏ´Ù°¡
	                ;
	            P2->OUT=0x00;
	            s2_bs=BS_UP;
	        }
	}
}
