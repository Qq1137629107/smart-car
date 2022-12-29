#ifndef _I2C_H
#define _I2C_H

#include "public.h"

sbit SCL=P2^1;
sbit SDA=P2^0;

void i2c_start(void);
void i2c_stop(void);
void i2c_ack(void);
void i2c_nack(void);
u8 i2c_wait_ack(void);
void i2c_send_byte(u8 dat);
u8 i2c_read_byte(u8 ack);

#endif