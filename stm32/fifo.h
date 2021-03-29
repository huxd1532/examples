#ifndef _FIFO_H_
#define _FIFO_H_
//https://blog.csdn.net/jdh99/article/details/83789431
#include "stdlib.h"
#include "stdio.h"
#include "stdarg.h"
#include "stdbool.h"
#include "string.h"
#include "math.h"



typedef struct
{
    int m_head;
    int m_tail;
    bool m_is_full;
    int m_item_num;
    int m_item_size;
    void *p_buff;
} Fifo;


Fifo *fifo_create(int item_num, int item_size)
{

}


#endif