#include "s21_math.h"

int main() {
    // проверка работы abs
    int num_abs;
    printf("Введи число для проверки работы abs: ");
    scanf("%d", &num_abs);
    printf("-------------------------------------------ABS-------------------------------------------\n\n");
    printf("Введено число: %d, результат работы функции abs: %d\n\n", num_abs, s21_abs(num_abs));
    printf("-------------------------------------------ABS-------------------------------------------\n\n");
    
    return 0;
}