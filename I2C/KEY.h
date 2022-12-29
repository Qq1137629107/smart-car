#ifndef _KEY_H
#define _KEY_H

#include "public.h"

sbit KEY1=P3^1;
sbit KEY2=P3^0;
sbit KEY3=P3^2;
sbit KEY4=P3^3;

u8 key_scan(u8 mode);

#define KEY1_PRESS   1
#define KEY2_PRESS   2
#define KEY3_PRESS   3
#define KEY4_PRESS   4
#define KEY_UNPRESS  0

#endif