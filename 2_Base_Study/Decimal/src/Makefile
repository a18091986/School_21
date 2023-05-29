FLAGS = -Wall -Werror -Wextra -std=c11

all: main


main: main.o usefull_for_convert
	gcc $(FLAGS) main.a -o main

main.a:
	gcc -c $(FLAGS) *.c
	rm -rf *.o

git:
	git add .
	git commit -am "from make"
	git push

clean:
	clear & rm -rf *.o

rebuild: clean all


