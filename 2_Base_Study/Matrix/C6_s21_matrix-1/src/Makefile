CC=gcc
# FLAGS=-Wall -Wextra -Werror -std=c11 -pedantic -g -fsanitize=address
FLAGS=-Wall -Wextra -Werror -std=c11
OS = $(shell uname)

ifeq ($(OS), Linux)
	TEST_FLAGS= -lcheck -lgcov -lm -lsubunit -lrt -pthread
else
	TEST_FLAGS = -lcheck -lgcov
endif

# SRC_MATRIX=s21_matrix.c
# OBJ=$(SRC_MATRIX:.c=.o)

.PHONY: all clean test gcov_report
all: test s21_matrix.a gcov_report

test: CFLAGS += -coverage
test: s21_test.o s21_matrix.o s21_matrix.h
	$(CC) $(FLAGS) s21_matrix.o s21_test.o $(TEST_FLAGS) -o test
	./test

s21_test.o: s21_test.c
	$(CC) -c $(FLAGS) s21_test.c

s21_matrix.a: s21_matrix.h s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o
	ranlib s21_matrix.a

gcov_report: test
	./test
	lcov -t "gcov_report" -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;
	# open ./report/index.html

style:
	clang-format -style=Google -i *.c
	clang-format -style=Google -n *.c


leaks:
	valgrind --tool=memcheck --leak-check=yes  ./test 2>&1 | grep -i 'ERROR'

clean: 
	rm -rf report test *.o *.info *.a s21_matrix.gcda s21_matrix.gcno *.out
