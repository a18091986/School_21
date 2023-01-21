#ifndef SRC_S21_STRING_FIRST_TEN_H_
#define SRC_S21_STRING_FIRST_TEN_H_

#define s21_NULL ((void *) 0)

#include <stdlib.h>
#include <stdio.h>

typedef long unsigned s21_size_t;

void * s21_memchr(const void *str, int c, s21_size_t n);  // поиск первого вхождения символа с (беззнаковый) в первых n байтах строки
int s21_memcmp(const void *str1, const void *str2, s21_size_t n); // Сравнивает первые n байтов str1 и str2
void * s21_memcpy(void *dest, const void *src, s21_size_t n); // Копирует n символов из src в dest
void * s21_memmove(void *dest, const void *src, s21_size_t n); // Копирует n символов из src в dest
void * s21_memset(void *str, int c, s21_size_t n); // Копирует символ c (беззнаковый тип) в первые n символов строки, на которую указывает аргумент str
char * s21_strcat(char *dest, const char *src); // Добавляет строку, на которую указывает src, в конец строки, на которую указывает dest
char * s21_strncat(char *dest, const char *src, s21_size_t n); // Добавляет строку, на которую указывает src, в конец строки, на которую указывает dest, длиной до n символов
char * s21_strchr(const char *str, int c); // Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на которую указывает аргумент str
int s21_strcmp(const char *str1, const char *str2); // Сравнивает строку, на которую указывает str1, со строкой, на которую указывает str2
int s21_strncmp(const char *str1, const char *str2, s21_size_t n); // Сравнивает не более первых n байтов str1 и str2



#endif  // SRC_S21_STRING_FIRST_TEN_H_