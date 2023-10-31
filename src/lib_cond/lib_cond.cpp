

#include "lib_cond.h"
#include <Arduino.h>

int fifo_push(float data, float *buff, int buff_size)
{

    for (int i = buff_size - 1; i >= 0; i--)
    {
        buff[i] = buff[i - 1];
    }

    buff[0] = data;
    return data;
}

int buf_copy(float *buff_src, float *buff_dst, int buff_size)
{

    for (int i = 0; i < buff_size; i++)
    {
        buff_dst[i] = buff_src[i];
    }
    return 0;
}

int cmp_func(float a, float b)
{
    return a - b;
}

int compare(const void *a, const void *b)
{
    const float *x = (float *)a;
    const float *y = (float *)b;

    if (*x > *y)
        return 1;
    else if (*x < *y)
        return -1;

    return 0;
}

int buf_sort(float *buff, int buff_size)
{

    qsort(buff, buff_size, sizeof(float), compare);
    return 0;
}

int print_buff(float *buff, int buff_size)
{
    for (int i = 0; i < buff_size; i++)
    {
        Serial.print(" | ");   /* code */
        Serial.print(buff[i]); /* code */
    }
    Serial.println("|");
    return 0;
}

float buf_wavg(float *buff_data, float *buff_weight, int buff_size)
{
    float s_up = 0;
    float s_dn = 0;
    float wavg = 0;

    for (int i = 0; i < buff_size; i++)
    {
        s_up += buff_weight[i] * buff_data[i];
        s_dn += buff_weight[i];
    }

    wavg = s_up/s_dn;
    return wavg;
}
