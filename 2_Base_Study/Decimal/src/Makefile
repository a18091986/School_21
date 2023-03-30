FLAGS = -Wall -Werror -Wextra -std=c11

all: main start

start: clean main
	clear
	./main
		

main: main.o s21_decimal_convert.h
	gcc $(FLAGS) main.o s21_decimal_convert.h -o main

main.o:
	gcc -c $(FLAGS) main.c -o main.o



git:
	git add .
	git commit -am "from make"
	git push

clean:
	rm -rf *.o

rebuild: clean all


