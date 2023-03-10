FLAGS = -Wall -Werror -Wextra -std=c11

all: main start_program

start_program: main
		./main

main: main.o
		gcc $(FLAGS) main.o -o main

main.o:
		gcc -c $(FLAGS) main.c -o main.o

git:
	git add .
	git commit -am "from make"
	git push

clean-win: 
		del *.o

clean-lin:
		rm -rf *.o

rebuild-win: clean-win all

rebuild-lin: clean-lin all


