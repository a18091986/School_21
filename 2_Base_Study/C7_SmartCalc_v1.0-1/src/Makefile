TARGET = app
TEST_TARGET = test1
CC = gcc 
# FLAGS = -Wall -Wextra -Werror -std=c11
# FLAGS = -Wextra -Werror -std=c11


VALGRIND_OUTPUT = valgrind.txt
# BUILD_FLAGS = -Wall -Wextra -Werror -std=c11 -pedantic -fanalyzer
GTK_FLAGS = `pkg-config gtk+-3.0 --cflags`
GTK_LIBS = `pkg-config gtk+-3.0 --libs`
VALGRIND_FLAGS = --log-file="$(VALGRIND_OUTPUT)" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med
LIBS_FLAGS = -lcheck
EXECUTABLE = smart_calc

INCLUDES = . 

# SRC_MAIN = $(wildcard *.c) # имена всех исходных файлов
# SRC_LOGIC = $(wildcard logic/*.c) # имена всех исходных файлов
# OBJ_MAIN = $(patsubst %.c, %.o, $(SRC_MAIN)) # имена всех объектных файлов
# OBJ_LOGIC = $(patsubst %.c, %.o, $(SRC_LOGIC)) # имена всех объектных файлов

# $(TARGET) : $(OBJ)
# 	$(CC) $(OBJ) -o $(TARGET) -lm

# %.o : %.c # получение объектных файлов из всех, присутствующих в директории файлов исходных кодов
# 	$(CC) $(FLAGS) -c $< -o $@ 

SRC_MAIN = *.c
SRC_LOGIC = logic/*.c
SRC_TEST = tests/*.c

# build: $(SRC_MAIN) $(SRC_LOGIC)
# 	$(CC) $(FLAGS) 

build: apply_clang  $(SRC_LOGIC)
	$(CC) $(BUILD_FLAGS) $(GTK_FLAGS) $(addprefix -I , $(INCLUDES)) $(SRC_LOGIC) main.c -o $(EXECUTABLE) $(LIBS_FLAGS) $(GTK_LIBS) -lm

run: build
	./$(EXECUTABLE)

test: apply_clang $(SRC_LOGIC) $(SRC_TEST)
	$(CC) $(BUILD_FLAGS) $(addprefix -I , $(INCLUDES)) $(SRC_LOGIC) $(SRC_TEST) -o $(TEST_TARGET) $(LIBS_FLAGS) -lm -lsubunit
	./$(TEST_TARGET)

build_test: apply_clang $(SRC_LOGIC)
	$(CC) $(BUILD_FLAGS) $(addprefix -I , $(INCLUDES)) $(SRC_LOGIC) $(SRC_TEST) -o $(TEST_TARGET) $(LIBS_FLAGS) -lm -lsubunit

apply_clang: 
	cp ../materials/linters/.clang-format .
	clang-format -i *.[ch] || true
	clang-format -i */*.[ch] || true
	rm -f .clang-format

gcov_report: apply_clang
	$(CC) --coverage $(BUILD_FLAGS) $(addprefix -I , $(INCLUDES)) $(SRC_LOGIC) $(SRC_TEST) -o $(TEST_TARGET) $(LIBS_FLAGS) -lm -lsubunit
	./$(TEST_TARGET)
	lcov -t "$(TEST_TARGET)" -o $(TEST_TARGET).info -c -d .
	genhtml -o report $(TEST_TARGET).info
	rm *.gcda *.gcno *.info
	open report/index.html

# test: apply_clang $(SRC_C_FILES)
# 	$(CC) $(BUILD_FLAGS) $(addprefix -I , $(INCLUDES)) $(SRC_LOGIC) $(SRC_TEST) -o $(TEST_TARGET) $(LIBS_FLAGS) -lm -lsubunit
# 	./$(TEST_TARGET)


# test: CFLAGS += -coverage
# test: s21_test.o s21_matrix.o s21_matrix.h
# 	$(CC) $(FLAGS) s21_matrix.o s21_test.o $(TEST_FLAGS) -o test
# 	./test

# test.o: tests.c
# 	$(CC) -c $(FLAGS) s21_test.c


# слева - то, что требуется получить (цель)
# справа - то, что требуется 
# снизу через табуляцию - команды

# gcc main.o mylib.o - o MyProject (получаем бинарный файл)

# .o - объектные файлы
# .c - файлы с исходным кодом

clean : 
	rm *.o
