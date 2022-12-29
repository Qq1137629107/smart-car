#include "menu.h"
#include "oled.h"
#include "beepled.h"
#include "smg.h"
u8 func_index = 0;
u8 s0;
u8 s1;
u8 s2;
u8 s3=150;
u8 k4;
u8 s4=5;
void (*current_operation_index)();

typedef struct
{
    u8 current;
    u8 up;
    u8 down;
    u8 enter;
    void (*current_operation)();
} key_table;

void fun_0()
{
	OLED_Clear();
	OLED_ShowString(0, 0, ">PRASS");
	OLED_ShowString(0, 2, ">MENU");
	OLED_ShowString(0, 4, ">TO");
	OLED_ShowString(0, 6, ">CONTINUE");
}
void fun_a1()
{
	OLED_Clear();
	OLED_ShowString(0, 0, ">ALL BREATH");
  OLED_ShowString(0, 2, " NIXIE TUBE");
	OLED_ShowString(0, 4, " LEDS");
	OLED_ShowString(0, 6, " MUSIC");
}void fun_b1()
{
	OLED_Clear();
	OLED_ShowString(0, 0, " ALL BREATH");
	OLED_ShowString(0, 2, ">NIXIE TUBE");
	OLED_ShowString(0, 4, " LEDS");
	OLED_ShowString(0, 6, " MUSIC");
}
void fun_c1()
{
	OLED_Clear();
	OLED_ShowString(0, 0, " ALL BREATH");
  OLED_ShowString(0, 2, " NIXIE TUBE");
	OLED_ShowString(0, 4, ">LEDS");
	OLED_ShowString(0, 6, " MUSIC");
}
void fun_d1()
{
	OLED_Clear();
	OLED_ShowString(0, 0, " ALL BREATH");
	OLED_ShowString(0, 2, " NIXIE TUBE");
	OLED_ShowString(0, 4, " LEDS");
	OLED_ShowString(0, 6, ">MUSIC");
}
void fun_a21()
{
	OLED_Clear();
	OLED_ShowString(0, 0, ">ON");
  OLED_ShowString(0, 2, " OFF");
	OLED_ShowString(0, 4, " RETURN");

}
void fun_a22()
{
	OLED_Clear();
	OLED_ShowString(0, 0, " ON");
  OLED_ShowString(0, 2, ">OFF");
	OLED_ShowString(0, 4, " RETURN");
}
void fun_a23()
{
	OLED_Clear();
	OLED_ShowString(0, 0, " ON");
  OLED_ShowString(0, 2, " OFF");
	OLED_ShowString(0, 4, ">RETURN");
}
void fun_b21()
{
	OLED_Clear();
	OLED_ShowString(0, 0, ">TIMER");
  OLED_ShowString(0, 2, " COUNTDOWN");
	OLED_ShowString(0, 4, " RETURN");

}
void fun_b22()
{
	OLED_Clear();
	OLED_ShowString(0, 0, " TIMER");
  OLED_ShowString(0, 2, ">COUNTDOWN");
	OLED_ShowString(0, 4, " RETURN");
	s1=0;
}
void fun_b23()
{
	OLED_Clear();
	OLED_ShowString(0, 0, " TIMER");
  OLED_ShowString(0, 2, " COUNTDOWN");
	OLED_ShowString(0, 4, ">RETURN");
}
void fun_c21()
{
	OLED_Clear();
  OLED_ShowString(0, 0, ">NEON LAMP");
	OLED_ShowString(0, 2, " OFF");
	OLED_ShowString(0, 4, " CHANGE SPEED");
	OLED_ShowString(0, 6, " RETURN");
}
void fun_c22()
{
	OLED_Clear();
  OLED_ShowString(0, 0, " NEON LAMP");
	OLED_ShowString(0, 2, ">OFF");
	OLED_ShowString(0, 4, " CHANGE SPEED");
	OLED_ShowString(0, 6, " RETURN");
}	
void fun_c23()
{
	OLED_Clear();
  OLED_ShowString(0, 0, " NEON LAMP");
	OLED_ShowString(0, 2, " OFF");
	OLED_ShowString(0, 4, ">CHANGE SPEED");
	OLED_ShowString(0, 6, " RETURN");
}	
void fun_c24()
{
	OLED_Clear();
  OLED_ShowString(0, 0, " NEON LAMP");
	OLED_ShowString(0, 2, " OFF");
	OLED_ShowString(0, 4, " CHANGE SPEED");
	OLED_ShowString(0, 6, ">RETURN");
}	
void fun_d21()
{
	OLED_Clear();
  OLED_ShowString(0, 0, ">MUSIC");
	OLED_ShowString(0, 2, " VOL+");
	OLED_ShowString(0, 4, " VOL-");
	OLED_ShowString(0, 6, " RETURN");
}
void fun_d22()
{
	OLED_Clear();
  OLED_ShowString(0, 0, " MUSIC");
	OLED_ShowString(0, 2, ">VOL+");
	OLED_ShowString(0, 4, " VOL-");
	OLED_ShowString(0, 6, " RETURN");
}	
void fun_d23()
{
	OLED_Clear();
  OLED_ShowString(0, 0, " MUSIC");
	OLED_ShowString(0, 2, " VOL+");
	OLED_ShowString(0, 4, ">VOL-");
	OLED_ShowString(0, 6, " RETURN");
}	
void fun_d24()
{
	OLED_Clear();
  OLED_ShowString(0, 0, " MUSIC");
	OLED_ShowString(0, 2, " VOL+");
	OLED_ShowString(0, 4, " VOL-");
	OLED_ShowString(0, 6, ">RETURN");
}
void fun_a31()
{
	s0=1;
	k4=0;
}
void fun_a32()
{
	s0=0;Hc595_Send_Dat2(0xff);
	Hc595_Send_Dat1(0xff);
}
void fun_b31()
{
	OLED_Clear();
	OLED_ShowString(0,3,"     S+P=EXIT");
	OLED_ShowString(0,6," M      S      P");
	s1=1;
	jishiqi();
}
void fun_b32()
{
	s1=0;
	Hc595_Send_Dat1(0xff);
}
void fun_c311()
{
	s2=1;
	s0=0;
}
void fun_c321()
{
	s2=0;Hc595_Send_Dat1(0xff);
}
void fun_c331()
{
	OLED_Clear();
	OLED_ShowString(0,0,">SPEED+");
	OLED_ShowString(0,2," SPEED-");
	OLED_ShowString(0,4," RETURN");
}
void fun_c332()
{
	OLED_Clear();
	OLED_ShowString(0,0," SPEED+");
	OLED_ShowString(0,2,">SPEED-");
	OLED_ShowString(0,4," RETURN");
}
void fun_c333()
{
	OLED_Clear();
	OLED_ShowString(0,0," SPEED+");
	OLED_ShowString(0,2," SPEED-");
	OLED_ShowString(0,4,">RETURN");
}
void fun_c3111()
{
	while(!SW3);
		s3=s3-10;
		if(s3==50)s3=50;
}
void fun_c3211()
{
	while(!SW3);
		s3=s3+10;
	if(s3==500)s3=500;
}

void fun_d3211()
{
	s0=0;
	while(!SW3);
	k4=!k4;
}
void fun_d3221()
{
	while(!SW3);
	s4++;
	if(s4==20)s4=20;
}
void fun_d3331()
{
	while(!SW3);
	s4--;
	if(s4==0)s4=0;
}
	
key_table code table[] =
{      
{0,0,0,1,(*fun_0)},//0

{1,4,2,5,(*fun_a1)},
{2,1,3,8,(*fun_b1)},        
{3,2,4,11,(*fun_c1)},
{4,3,1,15,(*fun_d1)},//1------------------------------------

{5,7,6,19,(*fun_a21)}, 
{6,5,7,20,(*fun_a22)},        
{7,6,5,1,(*fun_a23)},//a2----------------------------------

{8,10,9,21,(*fun_b21)},
{9,8,10,22,(*fun_b22)},        
{10,9,8,2,(*fun_b23)},//b2------------------------------------

{11,14,12,23,(*fun_c21)},
{12,11,13,24,(*fun_c22)},        
{13,12,14,25,(*fun_c23)},
{14,13,11,3,(*fun_c24)},//c2

{15,18,16,28,(*fun_d21)},
{16,15,17,29,(*fun_d22)},        
{17,16,18,30,(*fun_d23)},
{18,17,15,4,(*fun_d24)},//d2

{19,7,6,19,(*fun_a31)},
{20,5,7,20,(*fun_a32)},//a3-----------------------------------------

{21,10,9,21,(*fun_b31)},
{22,8,10,22,(*fun_b32)},//b3-------------------------------------

{23,14,12,23,(*fun_c311)},
{24,11,13,24,(*fun_c321)},

{25,27,26,31,(*fun_c331)},
{26,25,27,32,(*fun_c332)},
{27,26,25,13,(*fun_c333)},

{28,18,16,28,(*fun_d3211)},
{29,15,17,29,(*fun_d3221)},
{30,16,18,30,(*fun_d3331)},

{31,27,26,31,(*fun_c3111)},
{32,25,27,32,(*fun_c3211)},

};

void key_scan()
{
	if ((SW1 == 0) || (SW2 == 0) || (SW3 == 0))   

	{
		Delay10ms();
    if (SW1 == 0)
		{
			func_index = table[func_index].up;   
			table[func_index].current_operation();			//向上翻
			while (!SW1);
			
			(*current_operation_index)();
		}
		if (SW2 == 0)
		{
			func_index = table[func_index].down; 
			current_operation_index = table[func_index].current_operation;			//向下翻
			while (!SW2);
			
			(*current_operation_index)();
		}
		if (SW3 == 0)
		{
			func_index = table[func_index].enter;   
			current_operation_index = table[func_index].current_operation;			//确认
			while (!SW3);
			
			(*current_operation_index)();
		}
		
	}
	
}
