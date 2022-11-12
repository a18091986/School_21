#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct short_options {
  int b;
  int e;
  int v;
  int n;
  int s;
  int t;
} short_option;

struct option long_option[] = {{"number-nonblank", no_argument, 0, 0},
                               {"number", no_argument, 0, 0},
                               {"squeeze-blank", no_argument, 0, 0},
                               {0, 0, 0, 0}};

void options_struct_initialization();
void parse(int argc, char **argv);
void print_result(int argc, char **argv);

#endif  // SRC_CAT_S21_CAT_H_
