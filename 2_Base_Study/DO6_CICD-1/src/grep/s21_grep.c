#include "s21_grep.h"

int main(int argc, char** argv) {
  char template[buf] = {0};
  int files_counter = 0;
  int empty_line = 0;
  options_struct_initialization();
  if (argc != 1) {
    parse(argc, argv, template, &empty_line);
    work_with_files(argc, argv, template, &files_counter);
  } else
    printf("error");
  return 0;
}

void options_struct_initialization() {
  short_option.e = 0;
  short_option.i = 0;
  short_option.v = 0;
  short_option.c = 0;
  short_option.l = 0;
  short_option.n = 0;
  short_option.h = 0;
  short_option.s = 0;
  short_option.f = 0;
  short_option.o = 0;
}

void flag_e_processing(int* flag_e_counter, char* template, int* empty_line) {
  if (*flag_e_counter) {
    strcat(template, "|");
  }
  if (!*optarg) {
    optarg = ".";
    *empty_line += 1;
  }
  strcat(template, optarg);
  *flag_e_counter += 1;
}

void flag_f_processing(int* e_count, char* template, int* empty_line) {
  FILE* fp = NULL;
  char line[buf] = {0};
  if ((fp = fopen(optarg, "r"))) {
    fseek(fp, 0, SEEK_SET);
    while (fgets(line, buf, fp) != NULL) {
      if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = 0;
      if (*e_count > 0) strcat(template, "|");
      if (*line == '\0') {
        *empty_line = 1;
        strcat(template, ".");
      } else {
        strcat(template, line);
      }
      *e_count += 1;
    }
    fclose(fp);
  } else {
    printf("s21_grep: %s: No such file\n", optarg);
    exit(1);
  }
}

void parse(int argc, char** argv, char* template, int* empty_line) {
  int opt, flag_e_counter = 0;
  // opterr = 0;
  const char* options_string = "e:ivclnhsf:o";
  while (1) {
    opt = getopt(argc, argv, options_string);
    if (opt == -1) break;
    switch (opt) {
      case 'e':
        short_option.e = 1;
        flag_e_processing(&flag_e_counter, template, empty_line);
        break;
      case 'i':
        short_option.i = 1;
        break;
      case 'v':
        short_option.v = 1;
        break;
      case 'c':
        short_option.c = 1;
        break;
      case 'l':
        short_option.l = 1;
        break;
      case 'n':
        short_option.n = 1;
        break;
      case 'h':
        short_option.h = 1;
        break;
      case 's':
        short_option.s = 1;
        break;
      case 'f':
        short_option.f = 1;
        flag_f_processing(&flag_e_counter, template, empty_line);
        break;
      case 'o':
        short_option.o = 1;
        break;
      default:
        printf("Invalid option: %s. ", argv[optind - 1]);
        printf("Valid_options: e, i, v, c, l, n, h, s, f, o");
        exit(1);
    }
  }
  if (*empty_line) short_option.o = 0;
  if (!short_option.e && !short_option.f) {
    if (!*argv[optind]) argv[optind] = ".";
    strcat(template, argv[optind]);
    optind += 1;
  }
}

void work_with_files(int argc, char** argv, char* template,
                     int* files_counter) {
  *files_counter = argc - optind;

  for (; optind < argc; optind++) {
    FILE* f;
    if ((f = fopen(argv[optind], "r")) != NULL) {
      output(argv, template, f, files_counter);
      fclose(f);
    } else {
      if (!short_option.s) {
        printf("s21_grep: %s: No such file or directory\n", argv[optind]);
      }
    }
  }
}

void output(char** argv, char* template, FILE* f, int* files_counter) {
  regex_t regular;  // структура для хранения скомпилированного рег выражения
  int find_match = 0;
  int regflag = REG_EXTENDED;  // расширенные регулярные выражения
  char str[buf] = {0};
  int line_number = 1;
  int lines_counter = 0;
  int counter = 0;
  int sum_counter = 0;
  regmatch_t pmatch[1] = {
      0};  // структура c результатом сравнения строки с регулярным выражением
  if (short_option.i) regflag |= REG_ICASE;  // игноририрование регистра
  regcomp(&regular, template, regflag);  // компиляция регулярного выражения
  while (!feof(f)) {
    if (fgets(str, buf, f)) {
      int new_line_o_flag_counter = 1;
      find_match = regexec(&regular, str, 1, pmatch, 0);
      if (short_option.v) find_match = find_match ? 0 : 1;
      if (find_match != REG_NOMATCH) {  // 0?
        sum_counter++;
        if (!short_option.c && !short_option.l) {
          if (*files_counter > 1 && !short_option.h) {
            printf("%s:", argv[optind]);
          }
          if (short_option.n) {
            printf("%d:", line_number);
          }
          if (short_option.o && !short_option.v) {
            new_line_o_flag_counter = 0;
            char* ptr = str;
            while (!find_match) {
              if (pmatch[0].rm_eo == pmatch[0].rm_so) break;
              if (counter != 0 && !short_option.h && *files_counter > 1) {
                printf("%s:", argv[optind]);
                if (short_option.n) printf("%d:", line_number);
              }
              counter++;
              printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
                     ptr + pmatch[0].rm_so);
              ptr += pmatch[0].rm_eo;
              find_match = regexec(&regular, ptr, 1, pmatch, REG_NOTBOL);
            }
            counter = 0;
          }
          if (!short_option.o) printf("%s", str);
          if (str[strlen(str) - 1] != '\n' && new_line_o_flag_counter) {
            printf("\n");
          }
        }
        lines_counter += 1;
      }
      line_number += 1;
    }
  }
  if (short_option.c && !short_option.l) {
    if (*files_counter > 1 && !short_option.h) {
      printf("%s:", argv[optind]);
    }
    if (!(short_option.l && lines_counter)) {
      if (!short_option.v)
        printf("%d\n", lines_counter);
      else
        printf("%d\n", lines_counter);
    } else {
      printf("%d\n", lines_counter);
    }
  }
  if (short_option.l && lines_counter) {
    if (short_option.c) {
      if (sum_counter)
        printf("%s:%d\n", argv[optind],
               1);  // grep системный некорректно работает при флагах lc
      else
        printf("%s:%d\n", argv[optind], 0);
    }
    printf("%s\n", argv[optind]);
  }
  if (short_option.l && !lines_counter && short_option.c) {
    printf("%s:%d\n", argv[optind], 0);
  }
  regfree(&regular);
}
