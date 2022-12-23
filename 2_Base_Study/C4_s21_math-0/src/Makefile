CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11

all: style power leaks

power: power.o power.h
	$(CC) $(FLAGS) power.o power.h -o power -lm

power.o: power.c
	$(CC) -c $(FLAGS) power.c -o power.o 

style:
	cp ../materials/linters/.clang-format .clang_format
	clang-format -i -style=google power.c power.h

leaks:
	leaks -atExit -- ./power -enbts test.txt

clean:
	rm -rf *.out *.o .clang_format 

rebuild: clean all
