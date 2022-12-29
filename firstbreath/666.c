
#include<reg51.h>

sbit LED1=P2^0;
sbit LED2=P2^1;

sbit key1=P3^1;
unsigned char a;
unsigned char b;
unsigned char c;
unsigned char d;
unsigned char e;
unsigned int f;
unsigned char g;

void Delay1us()		//@11.0592MHz
{
}

void delay_n_us(unsigned int n) 
{
        while(n)         
        {
                Delay1us();
                n=n-1;
        }    
}


main()
{
        e=0;
        
        while(1)    
        {
			
				
				a=a+1;
                if(a==70)
				{
				        a=0;
						b=b+1;
						if(b==10)
						{
						        b=0;
								if(c==70)
								{
								        d=1;
								}
								if(c==0)
								{
								        d=0;
								}
								if(d==1)
								{
								        c=c-1;
								}
								else
								{
										c=c+1;
										if(c==71)
										{
										        c=0;
										}
								}
						}

				} 
				if(c>a)
				{
				        LED1=0;
				}       
				else
				{
				        LED1=1;
				}

				delay_n_us(1);
        }

        
}