#ifndef _SRC_S21_DECIMAL_CONVERT_H_
#define _SRC_S21_DECIMAL_CONVERT_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define RED "\033[1;31m"
#define RESET   "\033[0m"

// ----------------------------------------------- VAR 3 (100) ----------------------------------------

// typedef struct 
// {
//     int bits[4];
// } s21_decimal;


// int s21_abs(int x) {
//   if (x < 0) {
//     x *= -1;
//   }
//   return x;
// }

// void cut_zeros(s21_decimal *value) {
//   int scale = get_exp(value);
//   int sign = get_sign(value);
//   s21_decimal ten = {{10, 0, 0, 0}};
//   s21_decimal temp = {{0}};
//   s21_decimal result = {{0}};
//   for (int out = -1; out < 0;) {
//     temp = s21_whole(*value, ten, &result);
//     if (is_zero(&temp) && (scale != 0)) {
//       *value = result;
//       set_zero(&result);
//       set_zero(&temp);
//       scale--;
//     } else if (!is_zero(&temp) || (scale == 0)) {
//       out = 1;
//     }
//   }
//   if (sign == 1) {
//     set_sign(value, 1);
//   }
//   set_exp(value, scale);
// }

// s21_decimal s21_whole(s21_decimal value_1, s21_decimal value_2,
//                       s21_decimal *result) {
//   s21_decimal temp = {{0}};
//   set_zero(result);
//   value_1.bits[3] = 0;
//   value_2.bits[3] = 0;

//   for (int i = 95; i > -1; i--) {
//     left_shift(&temp);
//     if (get_bit(value_1, i)) {
//       set_bit(&temp, 0, 1);
//     }
//     if (s21_is_greater_or_equal(temp, value_2)) {
//       set_bit(result, i, 1);
//       sub_bitwise(temp, value_2, &temp);
//     }
//   }

//   value_1 = temp;
//   return value_1;
// }

// int s21_from_int_to_decimal(int src, s21_decimal *dst) {
//   // заполненение массива указанными символами = 0
//   int err = 0;
//   if (dst != NULL) {
//     set_zero(dst);
//     if (src < 0) {
//       set_sign(dst, 1);
//       src *= -1;
//     }
//     dst->bits[0] = src;
//   } else {
//     err = 1;
//   }
//   return err;
// }

// int s21_from_decimal_to_int(s21_decimal src, int *dest) {
//   int error = 0;
//   int sign = get_sign(&src);
//   if (src.bits[2] == 0 && src.bits[1] == 0 && (dest != NULL) &&
//       (((src.bits[0] <= (unsigned int)INT_MAX) && (sign == 0)) ||
//        ((src.bits[0] <= (unsigned int)s21_abs(INT_MIN)) && (sign == 1))) &&
//       (get_exp(&src) < 29)) {
//     *dest = 0;
//     if (get_exp(&src) != 0) {
//       s21_truncate(src, &src);
//     }
//     *dest = (sign == 1) ? -(int)src.bits[0] : (int)src.bits[0];
//   } else {
//     if (dest != NULL) {
//       *dest = 0;
//     }
//     error = 1;
//   }
//   return error;
// }

// int s21_from_decimal_to_float(s21_decimal src, float *dst) {
//   int scale = get_exp(&src);
//   int sign = get_sign(&src);
//   int error = 0;

//   if ((dst != NULL) && (scale < 29)) {
//     *dst = 0.0;
//     long double temp_dest = 0.0;
//     for (int i = 0; i < 96; i++) {
//       if (get_bit(src, i) == 1) {
//         temp_dest += powl(2.0, (long double)i);
//       }
//     }
//     if (sign != 0) {
//       temp_dest *= -1.0;
//     }
//     if (scale != 0) {
//       temp_dest /= powl(10.0, (long double)scale);
//     }
//     *dst = (float)temp_dest;
//   } else {
//     error = 1;
//   }
//   return error;
// }

// int s21_from_float_to_decimal(float src, s21_decimal *dest) {
//   int error = 0;
//   set_zero(dest);
//   if ((dest != NULL) && (error == 0) &&
//       (((fabs(src) < 79228162514264337593543950335.0) &&
//         (fabs(src) > 1.0e-28)) ||
//        (src == 0.0))) {
//     int scale = 0;
//     unsigned int temp_src = 0;
//     long double not_src = src;

//     if (!!((*((unsigned int *)&src)) & 2147483648u) == 1) {
//       set_sign(dest, 1);
//       src *= -1;
//     }

//     not_src = (long double)src;
//     if (src < 1000000.0) {
//       while ((ceil(not_src) != not_src) && (not_src < 1000000.0) &&
//              scale < 28) {
//         not_src *= 10;
//         scale++;
//       }
//       src *= powf(10.0, scale);
//     } else if (src >= 10000000.0) {
//       for (; not_src > 10000000.0; not_src /= 10.0, scale--) {
//       }
//     }
//     temp_src = (unsigned int)round(not_src);
//     for (int i = 0; temp_src && i < 96; i++, (temp_src /= 2)) {
//       if (i < 32) {
//         if ((temp_src % 2) == 1) {
//           dest->bits[0] |= (1u << i);
//         }
//       } else if (i > 31 && i < 64) {
//         if ((temp_src % 2) == 1) {
//           dest->bits[1] |= (1u << i);
//         }
//       } else if (i > 63 && i < 96) {
//         if ((temp_src % 2) == 1) {
//           dest->bits[2] |= (1u << i);
//         }
//       }
//     }
//     if (scale < 0) {
//       while (scale < 0) {
//         *dest = mul_by_10(dest);
//         scale++;
//       }
//     } else if (scale > 0) {
//       set_exp(dest, scale);
//       cut_zeros(dest);
//     }
//     error = 0;
//   } else {
//     error = 1;
//   }
//   return error;
// }




// ----------------------------------------------- VAR 1 ----------------------------------------

typedef struct 
{
    int bits[4];
} s21_decimal;

#define START_INFO 96
#define MAX_VAL powl(2.0, 96)

int get_bit_in_position(int x, int bit_position) {
    int mask = 0b1 << bit_position;
    return (int) (x & mask ? 1 : 0);
}

int s21_get_bit(s21_decimal dec_num, int index) {
  int dec_part = index / 32;
  int pos_in_part = index % 32;
  return (dec_num.bits[dec_part] & (1u << pos_in_part)) >> pos_in_part;
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

void s21_set_bit(s21_decimal* dec_num, int index, int bit_position) {
  int dec_part = index / 32;
  int pos_in_part = index % 32;
  if (bit_position == 1)
    dec_num->bits[dec_part] |= (1u << pos_in_part);
  else 
    dec_num->bits[dec_part] &= (~((1u) << pos_in_part));
  return;
}

void s21_set_sign(s21_decimal *dec_num, int sign) {
  s21_set_bit(dec_num, 127, sign);
  return;
}

void s21_set_scale(s21_decimal* dec_num, int scale) {
  for (int i = START_INFO + 16; i < START_INFO + 23; i++) {
    s21_set_bit(dec_num, i, scale & 1);
    scale >>= 1;
  }
}

int s21_get_scale(s21_decimal dec_num) {
  int scale = 0;
  for (int i = START_INFO + 23; i >= START_INFO + 16; i--) {
    scale <<= 1;
    scale |= s21_get_bit(dec_num, i);
  }
  return scale;
}

void s21_dec_num_to_null(s21_decimal *dec_num) {
  for (int i = 0; i < 128; ++i)
    s21_set_bit(dec_num, i, 0);
}

int s21_get_sign(s21_decimal dec_num) { 
  return s21_get_bit(dec_num, 127); 
}

void s21_from_decimal_to_float(s21_decimal src, float *dst) {
    *dst = 0.0;
    int current_scale = s21_get_scale(src);
    for (int i = 0; i < START_INFO; i++)
        if (s21_get_bit(src, i)) 
            *dst += pow (2, i);
    while (current_scale) {
        *dst /= 10;
        current_scale--;
    }
    if (s21_get_sign(src))
        *dst = *dst*(-1);
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int flag = 0;
    int data = 0;
    int scale = s21_get_scale(src);

    if (scale + 31 < 95) 
        for (int i = scale + 31; i <= 95; ++i) 
            if (s21_get_bit(src, i)) 
                flag = 1;

    if (!flag) {
        for (int i = scale + 30; i >= scale; --i) {
            data <<= 1;
            data |= s21_get_bit(src, i);
        }
        if (s21_get_sign(src))
            data = -data;
        *dst = data;
    }
    return flag;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) { 
  int result_code = 0;
  s21_dec_num_to_null(dst);
  if (fabs(src) < powl(10.0, -28)) 
    result_code = 1;
  else if (src >= MAX_VAL)
    result_code = 1;
  else if (src <= -1 * MAX_VAL)
    result_code = 1;
  else {
    s21_dec_num_to_null(dst);
    int scale = 0;
    if (src < 0.0)
      s21_set_sign(dst, 1);
    src = fabsl(src);
    for(; !(int)src && scale < 28; src *=10)
        scale++;
    int i = 0;
    for (; src < MAX_VAL && scale < 28 && i < 7; i++) {
      src *= (long double)10.0;
      scale++;
    }
    for (i = 0; src >= powl(10.0, -8) && i < START_INFO; i++) {
      src = floorl(src) / 2;
      if (src - floorl(src) > powl(10.0, -8))
        s21_set_bit(dst, i, 1);
    }
    s21_set_scale(dst, scale);
  }
  return result_code;
}

void s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int sign = 0;
    s21_dec_num_to_null(dst);
    if (src != 0) {
        if (src < 0) {
            sign = 1;
            src = -src;
        }
        dst->bits[0] = src;
        s21_set_scale(dst, 0);
        s21_set_sign(dst, sign);
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