#include <stdio.h>
#include <stdlib.h>

#define RED "\033[1;31m"
#define RESET   "\033[0m"

typedef struct 
{
    int bits[4];
} s21_decimal;


void init_decimal_number(s21_decimal * dec_num) {
    for (int i=0; i <=3; i++) {
        dec_num -> bits[i] = 0;
        // printf("%d", dec_num -> bits[i]);
    }
}


char * get_number_in_binary_view(int x)
{
    char * result =(char*) malloc(33*sizeof(char));
    unsigned i;
    int k;
    for (i = 1 << 31, k=0; i > 0; i = i / 2, k++) {
        // (x & i) ? printf("1") : printf("0");
        result[k] = (char) ((x & i) ? '1' : '0');
    }
    return result;
}


// void get_decimal_number_in_binary_view(s21_decimal * dec_num) {
//     for (int i=0; i <=3; i++)
//         printf("%d", dec_num -> bits[i]);
//     printf("\n");
//     for (int i=0; i <=3; i++) {
//         printf("%s ", get_number_in_binary_view(dec_num->bits[i]));
//     }
// }


int get_bit_in_position(int x, int bit_position) {  // bit_position - счет с 0 от младшего разряда к старшим (справа налево)
    int mask = 0b1 << bit_position;
    return (int) (x & mask ? 1 : 0);
}

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

int main() {

// ####################################################################################################################################################################################################
  int number = 256;
  int bit_position = 8;
//   int bit_position_to_set_value = 5;
//   int zero_bit_value = 0;
//   int one_bit_value = 1;


printf("Number %d, in binary view: %s\n", 2147483647, get_number_in_binary_view(2147483647));  
// printf("Number %ld, in binary view: %s\n", -2147483648, get_number_in_binary_view(-2147483648));  

  printf("%s------------------------------get_bit_function_check-------------------------------------------------%s\n", RED, RESET);
  printf("Number %d, in binary view: %s, bit on %d position is %d\n", number, get_number_in_binary_view(number), bit_position, get_bit_in_position(number, bit_position));
  printf("%s*****************************************************************************************************%s\n\n", RED, RESET);


//   printf("%s------------------------------set_bit_function_check-------------------------------------------------%s\n", RED, RESET);
//   printf("Set bit in number %d (%s) on position %d on value %d results in:\t", number, get_number_in_binary_view(number), bit_position_to_set_value, one_bit_value);
//   int number_1 = set_bit_in_position(number, one_bit_value, bit_position_to_set_value);
//   printf("Number %d (%s)\n", number_1, get_number_in_binary_view(number_1));
//   printf("Set bit in number %d (%s) on position %d on value %d results in:\t", number, get_number_in_binary_view(number), bit_position_to_set_value, zero_bit_value);
//   int number_2 = set_bit_in_position(number, zero_bit_value, bit_position_to_set_value);
//   printf("Number %d (%s)\n", number_2, get_number_in_binary_view(number_2));
//   printf("%s*****************************************************************************************************%s\n\n", RED, RESET);

// // ####################################################################################################################################################################################################

//   s21_decimal test_decimal = {.bits = {255, 255, 255, 255}};
// //   init_decimal_number(&test_decimal);
//   get_decimal_number_in_binary_view(&test_decimal);

//   return 0;
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