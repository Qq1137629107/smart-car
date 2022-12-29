#ifndef _SMG_H
#define _SMG_H

#include "public.h"

#define SMG_A_DP_PORT P0

sbit LSA =P2^2;
sbit LSB =P2^3;
sbit LSC =P2^4;

void smg_display(u8 dat[],u8 pos);

#endif