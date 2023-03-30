#include "s21_decimal_convert.h"

int main() {

// ####################################################################################################################################################################################################
    // int number = 290;
    // int bit_position = 20;
    // int bit_position_to_set_value = 25;
    // int zero_bit_value = 0;
    // int one_bit_value = 1;

    int test_int = 10;
    s21_decimal test;
    
    s21_from_int_to_decimal(test_int, &test);
    show_decimal_binary_view(&test);
    
    s21_from_decimal_to_int(test, &test_int);
    printf("%d\n", test_int);
    
//     printf("Number %d, in binary view: %s\n", 2147483647, get_number_in_binary_view(2147483647));  
//     printf("Number %ld, in binary view: %s\n", -2147483648, get_number_in_binary_view(-2147483648));
     

//     printf("%s------------------------------get_bit_function_check-------------------------------------------------%s\n", RED, RESET);
//     printf("Number %d, in binary view: %s, bit on %d position is %d\n", number, get_number_in_binary_view(number), bit_position, get_bit_in_position(number, bit_position));
//     printf("%s*****************************************************************************************************%s\n\n", RED, RESET);


//     printf("%s------------------------------set_bit_function_check-------------------------------------------------%s\n", RED, RESET);
//     printf("Set bit in number %d (%s) on position %d on value %d results in:\t", number, get_number_in_binary_view(number), bit_position_to_set_value, one_bit_value);
//     int number_1 = set_bit_in_position(number, one_bit_value, bit_position_to_set_value);
//     printf("Number %d (%s)\n", number_1, get_number_in_binary_view(number_1));

//     printf("Set bit in number %d (%s) on position %d on value %d results in:\t", number, get_number_in_binary_view(number), bit_position_to_set_value, zero_bit_value);
//     int number_2 = set_bit_in_position(number, zero_bit_value, bit_position_to_set_value);
//     printf("Number %d (%s)\n", number_2, get_number_in_binary_view(number_2));
//     printf("%s*****************************************************************************************************%s\n\n", RED, RESET);

// // ####################################################################################################################################################################################################

//     s21_decimal test_decimal = {.bits = {2147483647, 2147483647, 2147483647, 2147483647}};
//     get_decimal_number_in_binary_view(&test_decimal);
//     printf("\n");
//     show_decimal_binary_view(&test_decimal);
//     printf("\n");

    return 0;
}


