#ifndef S21_GREP_H_
#define S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define buf 1024

struct short_options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  // int files_counter = 0;
  // int empty_line = 0;
} short_option;

void options_struct_initialization();
void parse(int argc, char** argv, char* template, int* empty_line);
void flag_e_processing(int* flag_e_counter, char* template, int* empty_line);
void flag_f_processing(int* e_count, char* template, int* empty_line);
void work_with_files(int argc, char** argv, char* template, int* files_counter);
void output(char** argv, char* template, FILE* f, int* files_counter);

#endif