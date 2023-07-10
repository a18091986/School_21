CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
TEST_LIBS = -lpthread -lcheck -lm
BACK_P = SmartCalcV1/back/
SOURCES = $(wildcard SmartCalcV1/back/*.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))



all: install

qcp:
	git submodule init
	git submodule update

install: qcp build
	cd CalcApp; make

build: s21_smart_calc.a
	rm -rf CalcApp
	mkdir CalcApp
	cd CalcApp; cmake ../SmartCalcV1

uninstall: clean
	rm -rf SmartCalcV1/CMakeLists.txt.user
	rm -rf SmartCalcV1/build
	rm -rf CalcApp

execute:
	cd CalcApp; open ./SmartCalcV1.app

gcov_flag:
	$(eval CFLAGS += --coverage)


debug_flag:
	$(eval CFLAGS += -g)

dist:
	tar --totals -cvf CalcApp.tar CalcApp

dvi:
	rm -rf Documentation
	doxygen
	open Documentation/html/index.html


gcov_report: clean gcov_flag test
	mkdir -p gcov
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov
	rm -rf $(BACK_P)*.gcno $(BACK_P)*.gcda $(BACK_P)*.gcov *.gcno *.gcda *.gcov
	open gcov/index.html

s21_smart_calc.a: clean $(OBJECTS)
	ar -rcs s21_smart_calc.a $(OBJECTS)
	ranlib s21_smart_calc.a
	rm -f $(BACK_P)*.o


test: clean s21_smart_calc.a
	$(CC) $(CFLAGS) Tests/*.c s21_smart_calc.a $(TEST_LIBS) -o test
	./test

debug: debug_flag test

valgrind:
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

clean:
	rm -rf Documentation test gcov $(BACK_P)*.o *.a *.gcda *.gcno *.gch *.pdf *.tar rep.info test.info test.dSYM coverage.info
