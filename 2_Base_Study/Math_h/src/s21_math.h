#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <stdio.h>

int s21_abs(int num) {
    return num >= 0 ? num : num * (-1);  
}

#endif  // SRC_S21_MATH_H