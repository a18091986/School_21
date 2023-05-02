#ifndef _SRC_S21_DECIMAL_CONVERT_H_
#define _SRC_S21_DECIMAL_CONVERT_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define RED "\033[1;31m"
#define RESET   "\033[0m"

// ----------------------------------------------- VAR 1 ----------------------------------------

typedef struct 
{
    int bits[4];
} s21_decimal;

#define START_INFO 96
#define MAX_DECIMAL powl(2.0, 96)
#define MIN_DECIMAL -1 * MAX_DECIMAL
#define MAX_POW 28
#define FLOAT_ACCURACY 7

int get_bit_in_position(int x, int bit_position) {  // bit_position - счет с 0 от младшего разряда к старшим (справа налево)
    int mask = 0b1 << bit_position;
    return (int) (x & mask ? 1 : 0);
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

void s21_set_bit(s21_decimal* decl, int index, int bit) {
  int num_int = index / 32;
  int num_bit = index % 32;
  if (bit == 1) {
    decl->bits[num_int] |= (1u << num_bit);
  } else {
    decl->bits[num_int] &= (~((1u) << num_bit));
  }
  return;
}

void s21_set_sign(s21_decimal *decl, int sign) {
  s21_set_bit(decl, 127, sign);
  return;
}

void s21_set_scale(s21_decimal* decl, int scale) {
  for (int i = START_INFO + 16; i < START_INFO + 23; i++) {
    s21_set_bit(decl, i, scale & 1);
    scale >>= 1;
  }
}

int s21_get_bit(s21_decimal decl, int index) {
  int num_int = index / 32;
  int num_bit = index % 32;
  return (decl.bits[num_int] & (1u << num_bit)) >> num_bit;
}

int s21_get_scale(s21_decimal decl) {
  int scale = 0;
  for (int i = START_INFO + 23; i >= START_INFO + 16; i--) {
    scale <<= 1;
    scale |= s21_get_bit(decl, i);
  }
  return scale;
}

void s21_decl_to_null(s21_decimal *decl) {
  for (int i = 0; i < 128; ++i) {
    s21_set_bit(decl, i, 0);
  }
}

int s21_get_sign(s21_decimal decl) { return s21_get_bit(decl, 127); }

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int return_val = 0;
    *dst = 0.0;
    // if (src.state == S21_PLUS_INF || src.state == S21_MINUS_INF
    // || src.state == S21_NAN) {
    //     return_val = 1;
    // } else {
        int scale = s21_get_scale(src);
        for (int i = 0; i < START_INFO; i++) {
            if (s21_get_bit(src, i)) {
                *dst += pow (2, i);
            }
        }
        while (scale) {
            *dst /= 10;
            scale--;
        }
        if (s21_get_sign(src)) {
            *dst = *dst*(-1);
        }
    // }
    return return_val;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int flag = 0;
    int data = 0;
    int scale = s21_get_scale(src);

    if (scale + 31 < 95) {
        for (int i = scale + 31; i <= 95; ++i) {
            if (s21_get_bit(src, i)) {
                flag = 1;
            }
        }

    }

    if (!flag) {
        for (int i = scale + 30; i >= scale; --i) {
            data <<= 1;
            data |= s21_get_bit(src, i);
        }
        if (s21_get_sign(src)) {
            data = -data;
        }
        *dst = data;
    }
    return flag;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) { 
  int return_val = 0;
  s21_decl_to_null(dst);
  if (fabs(src) < powl(10.0, -1 * MAX_POW)) {
    return_val = 1;
    // dst->state = S21_NULL;
  } else if (src >= MAX_DECIMAL) {
    return_val = 1;
    // dst->state = S21_PLUS_INF;
  } else if (src <= MIN_DECIMAL) {
    return_val = 1;
    // dst->state = S21_MINUS_INF;
  } else {
    s21_decl_to_null(dst);
    int scale = 0;
    if (src < 0.0)
      s21_set_sign(dst, 1);
    src = fabsl(src);
    for(; !(int)src && scale < MAX_POW; src *=10)  // normalize
        scale++;
    int i = 0;
    for (; src < MAX_DECIMAL && scale < MAX_POW && i < FLOAT_ACCURACY; i++) {
      src *= (long double)10.0;
      scale++;
    }
    for (i = 0; src >= powl(10.0, -1 * (FLOAT_ACCURACY + 1)) && i < START_INFO; i++) {
      src = floorl(src) / 2;
      if (src - floorl(src) > powl(10.0, -1 * (FLOAT_ACCURACY + 1))) {
        s21_set_bit(dst, i, 1);
      } 
    }
    s21_set_scale(dst, scale);
    // dst->state = S21_NORMAL;
  }
  return return_val;
}

void s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int sign = 0;

    s21_decl_to_null(dst);

    if (src != 0) {
    //     dst->state = S21_NULL;
    // } else {
        if (src < 0) {
            sign = 1;
            src = -src;
        }
        dst->bits[0] = src;
        s21_set_scale(dst, 0);
        s21_set_sign(dst, sign);
        // dst->state = S21_NORMAL;
    }
}


// ----------------------------------------------- VAR 2 ----------------------------------------

// typedef struct 
// {
//     int bits[4];
// } s21_decimal;


// typedef union {
//   int ui;
//   float fl;
// } floatbits;

// // usefull functions

// int get_bit_in_position(int x, int bit_position) {  // bit_position - счет с 0 от младшего разряда к старшим (справа налево)
//     int mask = 0b1 << bit_position;
//     return (int) (x & mask ? 1 : 0);
// }

// int s21_get_bit(s21_decimal dst, int index) {
//   int mask = 1u << (index % 32);
//   return (dst.bits[index / 32] & mask) != 0;
// }


// int inverse_bit_in_position(int x, int bit_position) {
//     return x ^ (1 << bit_position);
// }

// int set_bit_in_position(int x, int bit_value, int bit_position) {
//     int result;
//     if (bit_value)
//             result = x | (1 << bit_position);
//     else 
//         result = x & ~(1 << bit_position);
//     return result;
// }

// int s21_get_scale(s21_decimal dst) {
//   int mask = 127 << 16;
//   int scale = (mask & dst.bits[3]) >> 16;
//   return scale;
// }

// // ---------------------------general functions---------------------------------

// // initialization of zero decimal number
// void init_decimal_number(s21_decimal * dec_num) {
//     for (int i=0; i <=3; i++) {
//         dec_num -> bits[i] = 0;
//     }
// }

// void s21_set_sign(s21_decimal *dst) { 
//     dst->bits[3] = dst->bits[3] | 1u << 31; 
//     }

// void show_decimal_binary_view(s21_decimal * dec_num) {
//     for (int i = 2; i >= 0; i--)
//         for (int j = 31; j >= 0; j--)
//             printf("%d", get_bit_in_position(dec_num -> bits[i], j));
//     printf(" ");
//     for (int j = 31; j >= 16; j--)
//         printf("%d", get_bit_in_position(dec_num -> bits[3], j));
//     printf(" ");
//     for (int j = 15; j >= 0; j--)
//         printf("%d", get_bit_in_position(dec_num -> bits[3], j));
//     printf("\n");
//     printf("\n");
// }


// // --------------------------------------convert functions-----------------------------------------

// int s21_from_int_to_decimal(int src, s21_decimal *dst) {
//   init_decimal_number(dst);
//   int error = 0;
//   if (src < 0) {
//     s21_set_sign(dst);
//     src = (-1) * src;
//   }
//   if (src > INT_MAX)
//     error = 1;
//   else
//     dst->bits[0] = src;
//   return error;
// }

// int s21_from_decimal_to_int(s21_decimal src, int *dst) {
//   int error = 0;
//   int scale = s21_get_scale(src);
//   if (src.bits[1] || src.bits[2]) {
//     error = 1;
//   } else {
//     *dst = src.bits[0];
//     if (scale > 0 && scale <= 28) {
//       *dst /= pow(10, scale);
//     }
//   }
//   if (s21_get_bit(src, 127)) *dst = *dst * (-1);
// //   if (get_bit_in_position(src, 127)) *dst = *dst * (-1);
//   return error;
// }

// int s21_from_float_to_decimal(float src, s21_decimal *dst) {
//   init_decimal_number(dst);
//   int return_value = 0;
//   if (isinf(src) || isnan(src)) {
//     return_value = 1;
//   } else {
//     if (src != 0) {
//       int sign = *(int *)&src >> 31;
//       int exp = ((*(int *)&src & ~0x80000000) >> 23) - 127;
//       double temp = (double)fabs(src);
//       int off = 0;
//       for (; off < 28 && (int)temp / (int)pow(2, 21) == 0; temp *= 10, off++) {
//       }
//       temp = round(temp);
//       if (off <= 28 && (exp > -94 && exp < 96)) {
//         floatbits mant = {0};
//         temp = (float)temp;
//         for (; fmod(temp, 10) == 0 && off > 0; off--, temp /= 10) {
//         }
//         mant.fl = temp;
//         exp = ((*(int *)&mant.fl & ~0x80000000) >> 23) - 127;
//         dst->bits[exp / 32] |= 1 << exp % 32;
//         for (int i = exp - 1, j = 22; j >= 0; i--, j--)
//           if ((mant.ui & (1 << j)) != 0) dst->bits[i / 32] |= 1 << i % 32;
//         dst->bits[3] = (sign << 31) | (off << 16);
//       }
//     }
//   }
//   return return_value;
// }

// int s21_from_decimal_to_float(s21_decimal src, float *dst) {
//   double temp = (double)*dst;
//   for (int i = 0; i < 96; i++) {
//     temp += s21_get_bit(src, i) * pow(2, i);
//   }
//   temp = temp * pow(10, -s21_get_scale(src));
//   if (s21_get_bit(src, 127)) temp = temp * (-1);
//   *dst = temp;
//   return 0;
// }


// ------------------------------------------HZ---------------------------------

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