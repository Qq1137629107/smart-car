#ifndef _PUBLIC_H
#define _PUBLIC_H
#include "REG51.H"

//------------------public

typedef unsigned char u8;
typedef unsigned int u16;
void Delay10ms();
//------------------public


//------------------setp_motor_driver
sbit IN1=P1^0;
sbit IN2=P1^1;
sbit IN3=P1^2;
sbit IN4=P1^3;

sbit K1=P3^1;
sbit K2=P3^0;
sbit K3=P3^2;
sbit K4=P3^3;
void step_motor_driver(bit drt);
//------------------setp_motor_driver



#endif