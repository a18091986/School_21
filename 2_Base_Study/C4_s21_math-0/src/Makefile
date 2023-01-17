FLAGS = -Wall -Werror -Wextra -std=c11

all: s21_math.a test gcov_report 

test: s21_math.a
	 gcc $(FLAGS) test/*.c s21_math.a -o s21_math_test \
	`pkg-config --cflags --libs check`

s21_math.a: 
	gcc $(FLAGS) -c arithmetic.c trigonometry.c power.c
	ar rc s21_math.a *.o
	ranlib s21_math.a
	rm -rf *.o

gcov_report:
	gcc $(FLAGS) --coverage arithmetic.c trigonometry.c power.c test/*.c -o gcovreport \
	`pkg-config --cflags --libs check`
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info

style:
	cp ../materials/linters/.clang-format .clang_format
	clang-format -i -style=google arithmetic.c power.c trigonometry.c s21_math.h test/*.c test/*.h
	rm .clang_format

leaks:
	leaks -atExit -- ./s21_math_test

clean:
	rm -rf *.o s21_math.a s21_math_test *.gcda *.gcno report gcovreport gcovreport.info

rebuild: clean all
