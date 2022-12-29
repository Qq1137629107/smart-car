#include "oled.h"
#include "bmp.h"


#define uchar unsigned char

sbit keydown = P3 ^ 0;

sbit keyenter = P3 ^ 2;

sbit keyup = P3 ^ 1;

uchar func_index = 0;

void (*current_operation_index)();

typedef struct

{

    uchar current;

    uchar up;//���Ϸ�������

    uchar down;//���·�������

    uchar enter;//ȷ��������

    void (*current_operation)();

} key_table;

void fun1()
{


    OLED_ShowString(0, 0, " ALL BREATH", 12);
    OLED_ShowString(0, 2, ">NIXIE TUBE", 12);
    OLED_ShowString(0, 4, " LEDS", 12);
    OLED_ShowString(0, 6, " MUSIC", 12);
}
void fun2()
{


    OLED_ShowString(0, 0, " ALL BREATH", 12);
    OLED_ShowString(0, 2, " NIXIE TUBE", 12);
    OLED_ShowString(0, 4, ">LEDS", 12);
    OLED_ShowString(0, 6, " MUSIC", 12);
}

key_table code table[30] =

{

        {0,3,1,4,(*fun1)},//��һ�㣬��ʾ���廪��ѧ����������ѧ��������ϿѧԺ������

         {1,0,2,8,(*fun2)},//��һ�㣬��ʾ�廪��ѧ����������ѧ����������ϿѧԺ������



};


void main()

{

    OLED_Init();
    OLED_Clear(); //��ʼ��LCDģ��  
OLED_ShowString(0, 0, " ALL BREATH", 12);
    OLED_ShowString(0, 2, " NIXIE TUBE", 12);
    OLED_ShowString(0, 4, " LEDS", 12);
    OLED_ShowString(0, 6, " MUSIC", 12);
    while (1)

    {

        /*******************find index****************************/

        if ((keyup == 0) || (keydown == 0) || (keyenter == 0))

        {

            delay_ms(10);//����

            if (keyup == 0)

            {

                func_index = table[func_index].up;    //���Ϸ�

                while (!keyup);//���ּ��
 (*current_operation_index)();
            }

            if (keydown == 0)

            {

                func_index = table[func_index].down;    //���·�

                while (!keydown);
 (*current_operation_index)();
            }

            if (keyenter == 0)

            {

                func_index = table[func_index].enter;    //ȷ��

                while (!keyenter);
 (*current_operation_index)();
            }


        }

        current_operation_index = table[func_index].current_operation;

       //ִ�е�ǰ��������

    }

}