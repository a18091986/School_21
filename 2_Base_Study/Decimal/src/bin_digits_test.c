#include <stdio.h>
#include <stdlib.h>

#define RED "\033[1;31m"
#define RESET   "\033[0m"

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
  printf("%s------------------------------get_bit_function_check-------------------------------------------------%s\n", RED, RESET);
  printf("Number %d, in binary view: %s, bit on %d position is %d\n\n", number, print_number_in_binary_view(number), bit_position, get_bit_in_position(number, bit_position));
  printf("%s-----------------------------------------------------------------------------------------------------%s\n", RED, RESET);

  return 0;
}

// #include <stdio.h>

// #define RESET   "\033[0m"
// #define RED     "\033[1;31m"
// #define YELLOW  "\033[1;33m"
// #define WHITE   "\033[1;37m"

// int main() {
//     printf("%s00%s\n",    YELLOW, RESET);
//     printf("%s===3%s\n", RED,    RESET);
//     printf("%s-.%s\n",  WHITE,  RESET);
// }