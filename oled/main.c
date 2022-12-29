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

    uchar up;//向上翻索引号

    uchar down;//向下翻索引号

    uchar enter;//确认索引号

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

        {0,3,1,4,(*fun1)},//第一层，显示【清华大学】、北京大学、重庆三峡学院、返回

         {1,0,2,8,(*fun2)},//第一层，显示清华大学、【北京大学】、重庆三峡学院、返回



};


void main()

{

    OLED_Init();
    OLED_Clear(); //初始化LCD模块  
OLED_ShowString(0, 0, " ALL BREATH", 12);
    OLED_ShowString(0, 2, " NIXIE TUBE", 12);
    OLED_ShowString(0, 4, " LEDS", 12);
    OLED_ShowString(0, 6, " MUSIC", 12);
    while (1)

    {

        /*******************find index****************************/

        if ((keyup == 0) || (keydown == 0) || (keyenter == 0))

        {

            delay_ms(10);//消抖

            if (keyup == 0)

            {

                func_index = table[func_index].up;    //向上翻

                while (!keyup);//松手检测
 (*current_operation_index)();
            }

            if (keydown == 0)

            {

                func_index = table[func_index].down;    //向下翻

                while (!keydown);
 (*current_operation_index)();
            }

            if (keyenter == 0)

            {

                func_index = table[func_index].enter;    //确认

                while (!keyenter);
 (*current_operation_index)();
            }


        }

        current_operation_index = table[func_index].current_operation;

       //执行当前操作函数

    }

}