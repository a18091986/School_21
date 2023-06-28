CC=gcc
FLAGS=-Wall -Wextra -Werror

OS = $(shell uname)

ifeq ($(OS), Linux)
	TEST_FLAGS=-lcheck -lgcov -lm -lsubunit
else
	TEST_FLAGS = -lcheck -lgcov
endif

SRC_MATRIX=s21_matrix.c
# OBJ=$(SRC_MATRIX:.c=.o)

# .PHONY: all clean test gcov_report
# all: test s21_decimal.a gcov_report
all: s21_matrix.o s21_matrix.h
	$(CC) $(FLAGS) s21_matrix.o -lm

s21_matrix.o: s21_matrix.c
	$(CC) -c $(FLAGS) s21_matrix.c	

# test:CFLAGS += -coverage
# test: s21_test.o $(OBJ) s21_decimal.h
# 	$(CC) $(FLAGS) $(OBJ) s21_test.o $(TEST_FLAGS) -o test
# 	./test

# s21_test.o: s21_test.c
# 	$(CC) -c $(FLAGS) s21_test.c

# s21_matrix.a: s21_matrix.h $(OBJ)
# 	ar rcs s21_matrix.a $(OBJ)
# 	ranlib s21_matrix.a




# gcov_report: test
# 	./test
# 	lcov -t "gcov_report" -o gcov_report.info -c -d ./
# 	genhtml -o report gcov_report.info;

style:
	clang-format -i -style=google *.c *.h

clean: 
	rm -rf s21_test report test *.o $(OBJ)  *.info s21_decimal.a s21_decimal.gcda s21_decimal.gcno
