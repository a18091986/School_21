#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int scale = get_exp(&src);
  int sign = get_sign(&src);
  int error = 0;

  if ((dst != NULL) && (scale < 29)) {
    *dst = 0.0;
    long double temp_dest = 0.0;
    for (int i = 0; i < 96; i++) {
      if (get_bit(src, i) == 1) {
        temp_dest += powl(2.0, (long double)i);
      }
    }
    if (sign != 0) {
      temp_dest *= -1.0;
    }
    if (scale != 0) {
      temp_dest /= powl(10.0, (long double)scale);
    }
    *dst = (float)temp_dest;
  } else {
    error = 1;
  }
  return error;
}
