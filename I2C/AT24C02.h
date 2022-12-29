#ifndef _AT24C02_H
#define _AT24C02_H

#include "public.h"

void at24c02_send_one_byte(u8 addr,u8 dat);
u8 at24c02_read_one_byte(u8 addr);

#endif