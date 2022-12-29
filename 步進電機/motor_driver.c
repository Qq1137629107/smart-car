#include "public.h"

void step_motor_driver(bit drt)
{
    static u8 step=0;
    u8 i=step;
    if(drt==0)
    i=7-step;

    switch (i) 
    {
        case 0: {
            IN1 = 1;IN2 = 0;IN3 = 0; IN4 = 0;break;
        }
        case 1: {
            IN1 = 1;IN2 = 1;IN3 = 0;IN4 = 0;break;
        }
        case 2: {
            IN1 = 0;IN2 = 1;IN3 = 0;IN4 = 0;break;
        }
        case 3: {
            IN1 = 0;IN2 = 1;IN3 = 1;IN4 = 0;break;
        }
        case 4: {
            IN1 = 0;IN2 = 0;IN3 = 1;IN4 = 0;break;
        }
        case 5: {
            IN1 = 0;IN2 = 0;IN3 = 1;IN4 = 1;break;
        }
        case 6: {
            IN1 = 0;IN2 = 0;IN3 = 0;IN4 = 1;break;
        }
        case 7: {
            IN1 = 1;IN2 = 0;IN3 = 0;IN4 = 1;break;
        }
    }
    step++;
    if(step==7)step=0;
}