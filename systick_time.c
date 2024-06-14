#include "stm32f10x.h" 
#include "systick_time.h"

void systick_init(void)
{
	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
}
void DelayUs(unsigned long us)
{
    SysTick->LOAD = (72 * us) - 1;         
    SysTick->VAL = 0;                        
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; 


    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; 
}
void DelayMs(unsigned long  ms)
{
    SysTick->LOAD = 72000 - 1;                
    SysTick->VAL = 0;                         
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; 

    for (unsigned long  i = 0; i < ms; i++) {

        while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    }

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; 
}

