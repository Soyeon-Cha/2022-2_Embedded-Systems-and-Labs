/* Driver configuration */
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/drivers/Board.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/msp432p4111_classic.h"

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

/* function prototypes */
void Task1( void *pvParameters );
void Task2( void *pvParameters );

/* global variables */
Graphics_Context g_sContext;
SemaphoreHandle_t s1but_sem;

/* macros */
#define S1BUT ((P1->IN & (1<<1)) == 0x00)
#define BS_INIT 1
#define BS_DOWN 2
#define BS_UP 3


void main(void)
{

    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    /* Initializes graphics context */
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
    Graphics_clearDisplay(&g_sContext);


    /* Configuring S1 & S2 buttons / Red LED & RGB LED in mainboard */
    P1->DIR = BIT0;
    P1->DIR &= ~(BIT1|BIT4);
    P2->DIR |= 1<<2 | 1<< 1 | 1<<0;
    P1->REN |= (BIT1|BIT4);
    P1->OUT |= (BIT1|BIT4);
    P2->OUT = 0x00;

    xTaskCreate( Task1,                   /* The function that implements the task. */
                 "Task 1",                /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                 configMINIMAL_STACK_SIZE,/* The size of the stack to allocate to the task. */
                 ( void * ) 0,            /* The parameter passed to the task - just to check the functionality. */
                 5,                      /* The priority assigned to the task. */
                 NULL );                  /* The task handle is not required, so NULL is passed. */

    xTaskCreate( Task2,                   /* The function that implements the task. */
                 "Task 2",                /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                 configMINIMAL_STACK_SIZE,/* The size of the stack to allocate to the task. */
                 ( void * ) 0,            /* The parameter passed to the task - just to check the functionality. */
                 4,                      /* The priority assigned to the task. */
                 NULL );                  /* The task handle is not required, so NULL is passed. */

    s1but_sem=xSemaphoreCreateBinary();
    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    while (1)
    {
    }
}



void Task1( void *pvParameters )
{
    int s1but_bs=BS_INIT;

    while (1) {
         if (S1BUT) { // button down
             s1but_bs=BS_DOWN;
         } else { // button up
             if (s1but_bs==BS_DOWN)
                 xSemaphoreGive(s1but_sem);
            s1but_bs=BS_UP;
         }
      }

}

void Task2( void *pvParameters )
{
    while (1)
    {
        xSemaphoreTake(s1but_sem, portMAX_DELAY);
        P1->OUT^=BIT0;
    }
}
