#ifndef LIB_COND_H_
#define LIB_COND_H_

int fifo_push(float data, float *buff, int buff_size);
int buf_copy(float *buff_src, float *buff_dst, int buff_size);
int buf_sort(float *buff, int buff_size );
float buf_wavg(float *buff_data, float *buff_weight, int buff_size );


int print_buff(float* buff, int buff_size);


#endif