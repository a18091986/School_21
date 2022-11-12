#include "s21_cat.h"

int main(int argc, char **argv) {
  options_struct_initialization();
  parse(argc, argv);
  print_result(argc, argv);
}

void options_struct_initialization() {
  short_option.b = 0;
  short_option.e = 0;
  short_option.v = 0;
  short_option.n = 0;
  short_option.s = 0;
  short_option.t = 0;
}

void parse(int argc, char **argv) {
  int opt;
  int long_option_index;
  const char *options_string = "+beEnstT";
  opterr = 0;
  while (1) {
    opt = getopt_long(argc, argv, options_string, long_option,
                      &long_option_index);
    if (opt == -1) break;
    switch (opt) {
      case 0:
        if (strcmp(long_option[long_option_index].name, "number-nonblank") == 0)
          short_option.b = 1;
        if (strcmp(long_option[long_option_index].name, "number") == 0)
          short_option.n = 1;
        if (strcmp(long_option[long_option_index].name, "squeeze-blank") == 0)
          short_option.s = 1;
        break;
      case 'b':
        short_option.b = 1;
        short_option.n = 0;
        break;
      case 'e':
        short_option.e = 1;
        short_option.v = 1;
        break;
      case 'E':
        short_option.e = 1;
        break;
      case 'n':
        if (!short_option.b) short_option.n = 1;
        break;
      case 's':
        short_option.s = 1;
        break;
      case 't':
        short_option.t = 1;
        short_option.v = 1;
        break;
      case 'T':
        short_option.t = 1;
        break;
      default:
        printf("Invalid option: %s. ", argv[optind - 1]);
        printf(
            "Valid_options: b, e, n, s, t, number-nonblank, number, "
            "squeeze-blank");
        exit(1);
    }
  }
}

void print_result(int argc, char **argv) {
  char ch;
  int empty_line_count = 0, line_start = 1, line_counter = 1;
  for (int i = optind; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (!f) {
      printf("s21_cat: %s: No such file or directory\n", argv[i]);
      continue;
    }
    while ((ch = fgetc(f)) != EOF) {
      if (short_option.s) {
        if (ch == '\n') {
          empty_line_count++;
          if (empty_line_count >= 3) continue;
        } else {
          empty_line_count = 0;
        }
      }
      if (short_option.n && line_start) {
        printf("%6d\t", line_counter);
        line_counter++;
        line_start = 0;
      }
      if (short_option.b && line_start && ch != '\n') {
        printf("%6d\t", line_counter);
        line_counter++;
        line_start = 0;
      }
      if (short_option.t && ch == '\t') {
        printf("^");
        ch = 'I';
      }
      if (short_option.e && ch == '\n') {
        printf("$");
      }
      if (short_option.v && ch != '\n' && ch != '\t') {
        if (ch >= 0 && ch <= 31) {  // управляющие символы
          printf("^");
          ch += 64;
        }
        if (ch == 127) {
          printf("^");
          ch -= 64;
        }
      }
      if (ch == '\n') line_start = 1;
      printf("%c", ch);
    }
    line_counter = 1;
  }
}
