CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11

all: s21_grep style leaks

all_and_test: s21_grep test

s21_grep: s21_grep.o s21_grep.h
	$(CC) $(FLAGS) s21_grep.o s21_grep.h -o s21_grep

s21_grep.o: s21_grep.c
	$(CC) -c $(FLAGS) s21_grep.c -o s21_grep.o 

style:
	cp ../../materials/linters/.clang-format .clang_format
	clang-format -i -style=google s21_grep.c s21_grep.h

leaks:
	leaks -atExit -- ./s21_grep -c yet test_1.txt test_2.txt
	leaks -atExit -- ./s21_grep -g yet test_1.txt test_2.txt 

test:
	python3 test.py

clean:
	rm -rf *.out *.o my_grep s21_grep grep_difference system_grep .clang_format

rebuild: clean all
