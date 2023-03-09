#include <stdio.h>
#include <stdlib.h>

// int main() {

//     unsigned int d1 = 0b111;
//     printf("d1: %d\n", ~d1);

//     return 0;
// }

// Вывод байта в двоичном виде

typedef unsigned char byte;

char * print_number_in_binary_view(int x) {
    int mask = 0b10000000;
    // char * result = "00000000";
    // printf("%lld", sizeof(result));
    char * result =(char*) malloc(10*sizeof(char));

    for (int i=0; i < 8; i++) {
        printf("%c", (x & mask) ? '1' : '0');
        result[i] = (char) ((x & mask) ? '1' : '0');
        mask >>= 1;
    }
    printf("\n");
    return result;
}

int get_bit_in_position(int x, int bit_position) {
    int mask = 0b10000000 >> bit_position;
    return (int) (x & mask ? 1 : 0);
}

int main() {
  int number = 93;
  int bit_position = 2;
  printf("--------------get_bit_function_check--------------------")
  printf("Number %d, in binary view: %s, bit on %d position is %d\n", number, print_number_in_binary_view(number), bit_position, get_bit_in_position(number, bit_position));
  return 0;
}