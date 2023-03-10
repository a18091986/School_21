#include <stdio.h>
#include <stdlib.h>

#define RED "\033[1;31m"
#define RESET   "\033[0m"

char * get_number_in_binary_view(int x) {
    int mask = 0b10000000;
    // char * result = "00000000";
    // printf("%lld", sizeof(result));
    char * result =(char*) malloc(10*sizeof(char));

    for (int i=0; i < 8; i++) {
        // printf("%c", (x & mask) ? '1' : '0');
        result[i] = (char) ((x & mask) ? '1' : '0');
        mask >>= 1;
    }
    // printf("\n");
    return result;
}

int get_bit_in_position(int x, int bit_position) {  // bit_position - счет с 0 от младшего разряда к старшим (справа налево)
    int mask = 0b00000001 << bit_position;
    return (int) (x & mask ? 1 : 0);
}

int inverse_bit_in_position(int x, int bit_position) {
    return x ^ (1 << bit_position);
}

int set_bit_in_position(int x, int bit_value, int bit_position) {
    int result;
    if (bit_value) {
            result = x | (1 << bit_position);
            // printf("\n%d | (%d << %d): %d\n", x, bit_value, bit_position, x | (1 << bit_position));
            // printf("%d & (%d << %d): %d\n", x, bit_value, bit_position, x & (1 << bit_position));
    }
    else {
        result = x & ~(1 << bit_position);
        // printf("\n%d & ~(%d << %d): %d\n", x, bit_value, bit_position, x & ~(1 << bit_position));
        // printf("%d & (%d << %d): %d\n", x, bit_value, bit_position, x & (0 << bit_position));
    }
    return result;
}

int main() {
  int number = 48;
  int bit_position = 5;
  int bit_position_to_set_value = 5;
  int zero_bit_value = 0;
  int one_bit_value = 1;

  printf("%s------------------------------get_bit_function_check-------------------------------------------------%s\n", RED, RESET);
  printf("Number %d, in binary view: %s, bit on %d position is %d\n", number, get_number_in_binary_view(number), bit_position, get_bit_in_position(number, bit_position));
  printf("%s*****************************************************************************************************%s\n\n", RED, RESET);


  printf("%s------------------------------set_bit_function_check-------------------------------------------------%s\n", RED, RESET);
  printf("Set bit in number %d (%s) on position %d on value %d results in:\t", number, get_number_in_binary_view(number), bit_position_to_set_value, one_bit_value);
  int number_1 = set_bit_in_position(number, one_bit_value, bit_position_to_set_value);
  printf("Number %d (%s)\n", number_1, get_number_in_binary_view(number_1));
  printf("Set bit in number %d (%s) on position %d on value %d results in:\t", number, get_number_in_binary_view(number), bit_position_to_set_value, zero_bit_value);
  int number_2 = set_bit_in_position(number, zero_bit_value, bit_position_to_set_value);
  printf("Number %d (%s)\n", number_2, get_number_in_binary_view(number_2));
  printf("%s*****************************************************************************************************%s\n\n", RED, RESET);

  return 0;
}

