FLAGS = -pedantic -Wall -Werror -Wextra 
FLAGS_TEST = -lgtest -lgmock -pthread 
# MAIN_COMPILATION = $(FLAGS) calculator/tests.cc calculator/Model/model.cpp calculator/Model/validation.cpp $(FLAGS_TEST)
MAIN_COMPILATION = $(FLAGS) tests.cc Model/model.cpp Model/validation.cpp $(FLAGS_TEST)

# OS = $(shell uname)

# ifeq ($(OS), Linux)
# 	FLAGS_OS = -lcheck -lm -lsubunit 
# 	APP = chmod +x SmartCalc; ./SmartCalc
# else
# 	FLAGS_OS = -lcheck
# 	APP = open SmartCalc.app
# endif

all: test gcov_report install 

install: clean
	mkdir build; cd build; qmake ../s21_calculator_2.0.pro; build/make; ./s21_calculator_2 

uninstall: 
	rm -rf build

dvi: gcov_report
	open report/index.html

dist:
	tar -cf calculator

test: 
	g++ $(MAIN_COMPILATION) -o s21_calculator_test 
	./s21_calculator_test

gcov_report:
	g++ $(MAIN_COMPILATION) --coverage -o gcovreport \
	$(FLAGS_OS)
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info

style:
	clang-format -i -style=google *.c *.h

clean: 
	rm -rf *.o *.gcno *.gcda gcovreport gcovreport.info s21_calculator_test rm report rm s21_calculator.dSYM a.out build 

rebuild: clean all

