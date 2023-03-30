#ifndef _SRC_S21_DECIMAL_CONVERT_H_
#define _SRC_S21_DECIMAL_CONVERT_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define RED "\033[1;31m"
#define RESET   "\033[0m"


typedef struct 
{
    int bits[4];
} s21_decimal;


// usefull functions

int get_bit_in_position(int x, int bit_position) {  // bit_position - счет с 0 от младшего разряда к старшим (справа налево)
    int mask = 0b1 << bit_position;
    return (int) (x & mask ? 1 : 0);
}

int s21_get_bit(s21_decimal dst, int index) {
  int mask = 1u << (index % 32);
  return (dst.bits[index / 32] & mask) != 0;
}


int inverse_bit_in_position(int x, int bit_position) {
    return x ^ (1 << bit_position);
}

int set_bit_in_position(int x, int bit_value, int bit_position) {
    int result;
    if (bit_value)
            result = x | (1 << bit_position);
    else 
        result = x & ~(1 << bit_position);
    return result;
}

int s21_get_scale(s21_decimal dst) {
  int mask = 127 << 16;
  int scale = (mask & dst.bits[3]) >> 16;
  return scale;
}

// ---------------------------general functions---------------------------------

// initialization of zero decimal number
void init_decimal_number(s21_decimal * dec_num) {
    for (int i=0; i <=3; i++) {
        dec_num -> bits[i] = 0;
    }
}

void s21_set_sign(s21_decimal *dst) { 
    dst->bits[3] = dst->bits[3] | 1u << 31; 
    }

void show_decimal_binary_view(s21_decimal * dec_num) {
    for (int i = 2; i >= 0; i--)
        for (int j = 31; j >= 0; j--)
            printf("%d", get_bit_in_position(dec_num -> bits[i], j));
    printf(" ");
    for (int j = 31; j >= 16; j--)
        printf("%d", get_bit_in_position(dec_num -> bits[3], j));
    printf(" ");
    for (int j = 15; j >= 0; j--)
        printf("%d", get_bit_in_position(dec_num -> bits[3], j));
    printf("\n");
    printf("\n");
}


// convert functions

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  init_decimal_number(dst);
  int error = 0;
  if (src < 0) {
    s21_set_sign(dst);
    src = (-1) * src;
  }
  if (src > INT_MAX)
    error = 1;
  else
    dst->bits[0] = src;
  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  int scale = s21_get_scale(src);
  if (src.bits[1] || src.bits[2]) {
    error = 1;
  } else {
    *dst = src.bits[0];
    if (scale > 0 && scale <= 28) {
      *dst /= pow(10, scale);
    }
  }
  if (s21_get_bit(src, 127)) *dst = *dst * (-1);
//   if (get_bit_in_position(src, 127)) *dst = *dst * (-1);
  return error;
}

// char * get_number_in_binary_view(int x) {
//     // int mask = 0b10000000000000000000000000000000;
//     char * result =(char*) malloc(33*sizeof(char));

//     // for (int i=0; i < 32; i++) {
//     //     result[i] = (char) ((x & mask) ? '1' : '0');
//     //     mask >>= 1;
//     // }
//     unsigned i;
//     for (i = 1 << 31; i > 0; i = i / 2) {
//         (x & i) ? printf("1") : printf("0");    
//         result[i] = 1;
//     }

//     return result;
// }


// void get_decimal_number_in_binary_view(s21_decimal * dec_num) {
//     for (int i=0; i <=3; i++)
//         printf("%d_", dec_num -> bits[i]);
//     printf("\n");
//     for (int i=0; i <=3; i++) {
//         printf("%s", get_number_in_binary_view(dec_num->bits[i]));
//     }
// }


// char * get_number_in_binary_view(int x)
// {
//     char * result =(char*) malloc(33*sizeof(char));
//     unsigned i;
//     int k;
//     for (i = 1 << 31, k=0; i > 0; i = i / 2, k++) {
//         // (x & i) ? printf("1") : printf("0");
//         result[k] = (char) ((x & i) ? '1' : '0');
//     }
//     return result;
// }

#endif