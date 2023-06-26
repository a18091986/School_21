CC = gcc
FLAGS = -Wall -Werror -Wextra

all: main
	./main

main: main.a
	$(CC) $(FLAGS) main.a -lm -o main
	rm -rf *.o *.a


main.a:
	$(CC) $(FLAGS) -c *.c # получаем файлы объектные файлы .o 
	ar rc main.a *.o # создаем статическую библиотеку main.a программой ar  
	ranlib main.a # получаем полноценную библиотеку объектных файлов с индексом символов

clean:
	rm -rf main *.o *.a