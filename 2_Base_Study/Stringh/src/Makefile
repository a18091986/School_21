FLAGS = #-Wall -Werror -Wextra -std=c11

all: main

main: main.o s21_string_first_ten.o s21_string_first_ten.h
	gcc $(FLAGS) main.o s21_string_first_ten.o s21_string_first_ten.h -o main

main.o:
	gcc -c $(FLAGS)  main.c -o main.o

s21_string_first_ten.o:
	gcc -c $(FLAGS)  s21_string_first_ten.c -o s21_string_first_ten.o

# style:
#	cp ../materials/linters/.clang-format .clang_format
#	clang-format -i -style=google arithmetic.c power.c trigonometry.c s21_math.h test/*.c test/*.h
#	rm .clang_format

# leaks:
#	leaks -atExit -- ./s21_math_test

clean:
	rm -rf *.o 

rebuild: clean all
