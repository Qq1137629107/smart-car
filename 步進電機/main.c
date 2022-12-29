#include "public.h"


void pwm_col(u16 i)
{
    while(--i);
}


void main()
{
    bit drt;

    while (1) 
    {
        if(K1==0)
        {
            while(!K1);
              drt=!drt;
        }
        step_motor_driver(drt);
        Delay10ms();
    }
}