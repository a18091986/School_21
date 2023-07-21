CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11

all: style s21_cat leaks

all_and_test: all test

s21_cat: s21_cat.o s21_cat.h
	$(CC) $(FLAGS) s21_cat.o s21_cat.h -o s21_cat

s21_cat.o: s21_cat.c
	$(CC) -c $(FLAGS) s21_cat.c -o s21_cat.o 

style:
	cp ../../materials/linters/.clang-format .clang_format
	clang-format -i -style=google s21_cat.c s21_cat.h

leaks:
	leaks -atExit -- ./s21_cat -enbts test.txt

test:
	python3 test.py

clean:
	rm -rf *.out *.o my_cat s21_cat cat_difference system_cat .clang_format

rebuild: clean all
