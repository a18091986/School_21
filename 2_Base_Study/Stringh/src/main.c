#include <stdio.h>
#include "s21_string_first_ten.h"

int main() {
    unsigned char test_str[15] = "1234567890";
    char * out_char;
    out_char = s21_memchr(test_str, '4', 3);
    printf("%p", out_char);
    return 0;
}