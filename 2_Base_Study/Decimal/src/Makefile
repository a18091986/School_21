FLAGS = -Wall -Werror -Wextra -std=c11

all: main
	./main

main: main.o s21_decimal_convert.h
	gcc $(FLAGS) main.o s21_decimal_convert.h -o main -lm

main.o:
	gcc -c $(FLAGS) main.c -o main.o 



git:
	git add .
	git commit -am "from make"
	git push

clean:
	clear & rm -rf *.o

rebuild: clean all


