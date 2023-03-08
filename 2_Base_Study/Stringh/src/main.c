#include <stdio.h>
#include <string.h>
#include "s21_string_first_ten.h"

int main() {
    // --------------------------------------memmchr---------------------------------------------------
    
    printf("----------------------memchr-------------------------------\n");    
    char str_memchr[11] = "TestString\0";
    char to_find = 't';
    char * memchr_result_my = s21_memchr(str_memchr, to_find, sizeof(str_memchr));
    char * memchr_result_base = memchr(str_memchr, to_find, sizeof(str_memchr));
    printf("String: %s \n", str_memchr);
    printf("My: %c found on position %lld\n", to_find, memchr_result_my - str_memchr + 1);
    printf("Built_in: %c found on position %lld\n", to_find, memchr_result_base - str_memchr + 1);

    // --------------------------------------memmcmp---------------------------------------------------
    
    printf("----------------------memcmp-------------------------------\n");    
    char memcmp_str_1[] = "Test_tasdas\0";
    char memcmp_str_2[] = "Test_sasdsdf_eq\0";
    for (s21_size_t compare_size=5; compare_size <= 6; compare_size++) {
        int memcmp_result_base = memcmp(memcmp_str_1, memcmp_str_2, compare_size);
        printf("Built_in: test_str_1: %s, test_str_2: %s, compare size: %lu, result: %d\n", memcmp_str_1, memcmp_str_2, compare_size, memcmp_result_base);
        int memcmp_result_base_swap = memcmp(memcmp_str_2, memcmp_str_1, compare_size);
        printf("Built_in: test_str_1: %s, test_str_2: %s, compare size: %lu, result: %d\n", memcmp_str_2, memcmp_str_1, compare_size, memcmp_result_base_swap);
        int memcmp_result_my = s21_memcmp(memcmp_str_1, memcmp_str_2, compare_size);
        printf("My: test_str_1: %s, test_str_2: %s, compare size: %lu, result: %d\n", memcmp_str_1, memcmp_str_2, compare_size, memcmp_result_my);
        int memcmp_result_my_swap = s21_memcmp(memcmp_str_2, memcmp_str_1, compare_size);
        printf("My: test_str_1: %s, test_str_2: %s, compare size: %lu, result: %d\n", memcmp_str_2, memcmp_str_1, compare_size, memcmp_result_my_swap);
    }

    // --------------------------------------memmcpy---------------------------------------------------
    
    printf("----------------------memcpy-------------------------------\n");    
    char memcpy_str[] = "Test_str_cpy\0";
    s21_size_t max_copy_size = 7;
    for (s21_size_t copy_size=3; copy_size <= max_copy_size; copy_size++) {
        char memcpy_dst_str[8]="";
        memcpy(memcpy_dst_str, memcpy_str, copy_size);
        printf("Built_in: source: %s, dest: %s, copy size: %lu\n", memcpy_str, memcpy_dst_str, copy_size);
        s21_memcpy(memcpy_dst_str, memcpy_str, copy_size);
        printf("My: source: %s, dest: %s, copy size: %lu\n", memcpy_str, memcpy_dst_str, copy_size);
    }

    s21_size_t n1 = 3;
    char s[1024] = "";
    char s_[1024] = "";
    char str_1_2[1024] = "";
    memcpy(s, str_1_2, n1);
    s21_memcpy(s_, str_1_2, n1);
    printf("%s: \n", s);
    printf("%s: \n", s_);

    // --------------------------------------memmmove---------------------------------------------------
    
    printf("----------------------memmove-------------------------------\n");    
    char source_memmove_str[] = "Test_str\0";
    s21_size_t max_move_size = 5;
    for (s21_size_t move_size=3; move_size <= max_move_size; move_size++) {
        char destination_memmove_str[10];// = source_memmove_str[3];
        memmove(destination_memmove_str, source_memmove_str, move_size);
        printf("Built_in: source: %s, dest: %s, move size: %lu\n", source_memmove_str, destination_memmove_str, move_size);
        s21_memmove(destination_memmove_str, source_memmove_str, move_size);
        printf("My: source: %s, dest: %s, move size: %lu\n", source_memmove_str, destination_memmove_str, move_size);
    }

    // unsigned char src_2[10]="1234567890";
    // printf("src_2 old: %s\n",src_2);
    // s21_memmove (&src_2[4], &src_2[3], 3);
    // printf ("src_2 new: %s\n",src_2);
    // unsigned char src_1[10]="1234567890";
    // printf("src_1 old: %s\n",src_1);
    // memmove (&src_1[4], &src_1[3], 3);
    // printf ("src_1 new: %s\n",src_1);

// --------------------------------------memset---------------------------------------------------
    
    printf("----------------------memset-------------------------------\n");    
    char sym = 's';
    for (s21_size_t n = 1; n <= 3; n++) {
        char memset_str[] = "Test_str\0";
        char memcpy_dst_str[9]="";
        char memcpy_dst_str_1[9]="";
        memcpy(memcpy_dst_str, memset_str, 8);
        memset(memcpy_dst_str, sym, n);
        printf("Built_in: source_in: %s, source_out: %s, n: %lu\n", memset_str, memcpy_dst_str, n);
        memcpy(memcpy_dst_str_1, memset_str, 8);
        s21_memset(memcpy_dst_str_1, sym, n);
        printf("My: source_in: %s, source_out: %s, n: %ld\n", memset_str, memcpy_dst_str_1, n);
    }

// --------------------------------------strcat---------------------------------------------------
    
    printf("----------------------strcat-------------------------------\n");    
    char source_str[] = "string\0";
    char dest_str_1[15] = "Test_\0";
    char dest_str_2[15] = "Test_\0";
    strcat(dest_str_1, source_str);
    printf("Built_in: destination: %s, source: %s\n", dest_str_1, source_str);
    s21_strcat(dest_str_2, source_str);
    printf("My: destination: %s, source: %s\n", dest_str_2, source_str);

// --------------------------------------strncat---------------------------------------------------
    
    printf("----------------------strncat-------------------------------\n");    
    char source_str_strncat[] = "string\0";
    for (s21_size_t n = 5; n <= 7; n++) {
        char dest_str_1[15] = "Test_\0";
        char dest_str_2[15] = "Test_\0";
        strncat(dest_str_1, source_str_strncat, n);
        printf("Built_in: destination: %s, source: %s, n: %ld\n", dest_str_1, source_str_strncat, n);
        s21_strncat(dest_str_2, source_str, n);
        printf("My: destination: %s, source: %s, n: %ld\n", dest_str_2, source_str_strncat, n);
    }

// --------------------------------------strchr---------------------------------------------------
    
    printf("----------------------strchr-------------------------------\n");    
    char source_strchr[] = "strings";
    char ch_1 = 's';
    char ch_2 = 'r';
    printf("Built_in: %c: source: %s, n: %s\n", ch_1, source_strchr, strchr(source_strchr, ch_1));
    printf("My: %c: source: %s, n: %s\n", ch_1, source_strchr, s21_strchr(source_strchr, ch_1));
    printf("Built_in: %c: source: %s, n: %s\n", ch_2, source_strchr, strchr(source_strchr, ch_2));
    printf("My: %c: source: %s, n: %s\n", ch_2, source_strchr, s21_strchr(source_strchr, ch_2));

// --------------------------------------strcmp---------------------------------------------------
    
    printf("----------------------strcmp-------------------------------\n");    
    char source_strcmp_1[] = "strings";
    char source_strcmp_2_low[] = "str";
    char source_strcmp_2_hi[] = "stringss";
    char source_strcmp_2_eq[] = "strings";

    int neg_built_in = strcmp(source_strcmp_1, source_strcmp_2_low);
    int pos_built_in = strcmp(source_strcmp_1, source_strcmp_2_hi);
    int eq_built_in = strcmp(source_strcmp_1, source_strcmp_2_eq);

    int neg_my = s21_strcmp(source_strcmp_1, source_strcmp_2_low);
    int pos_my = s21_strcmp(source_strcmp_1, source_strcmp_2_hi);
    int eq_my = s21_strcmp(source_strcmp_1, source_strcmp_2_eq);

    printf("Built_in: source_1: %s, source_2: %s, res: %d\n", source_strcmp_1, source_strcmp_2_low, neg_built_in);
    printf("Built_in: source_1: %s, source_2: %s, res: %d\n", source_strcmp_1, source_strcmp_2_hi, pos_built_in);
    printf("Built_in: source_1: %s, source_2: %s, res: %d\n", source_strcmp_1, source_strcmp_2_eq, eq_built_in);
    
    printf("My: source_1: %s, source_2: %s, res: %d\n", source_strcmp_1, source_strcmp_2_low, neg_my);
    printf("My: source_1: %s, source_2: %s, res: %d\n", source_strcmp_1, source_strcmp_2_hi, pos_my);
    printf("My: source_1: %s, source_2: %s, res: %d\n", source_strcmp_1, source_strcmp_2_eq, eq_my);

// --------------------------------------strncmp---------------------------------------------------
    
    printf("----------------------strncmp-------------------------------\n");    
    char source_strncmp_1[] = "strings";
    char source_strncmp_2[] = "stringss";

    for (size_t i = 7; i <= 8; i++) {
        int result_builtin = strncmp(source_strncmp_1, source_strncmp_2, i);
        int result_my = s21_strncmp(source_strncmp_1, source_strncmp_2, i);
        printf("Built_in: source_1: %s, source_2: %s, n: %lld, res: %d\n", source_strncmp_1, source_strncmp_2, i, result_builtin);
        printf("Built_in: source_1: %s, source_2: %s, n: %lld, res: %d\n", source_strncmp_1, source_strncmp_2, i, result_my);
    }




// --------------------------------------to_upper&to_lower---------------------------------------------------
    
    printf("----------------------to_upper&to_lower-------------------------------\n");    
    char source_string[] = "sTrInGs";
    char * upper = s21_to_upper(source_string);
    char * lower = s21_to_lower(source_string);
    
    printf("%s\n", source_string);
    printf("%s\n", lower);
    printf("%s\n", upper);
    
    

    return 0;
}