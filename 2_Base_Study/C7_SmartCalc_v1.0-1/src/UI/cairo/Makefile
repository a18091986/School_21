TARGET = main
CC = gcc 
# FLAGS = -Wall -Wextra -Werror -std=c11
# FLAGS = -Wextra -Werror -std=c11

# SRC = $(wildcard *.c) # имена всех исходных файлов
# OBJ = $(patsubst %.c, %.o, $(SRC)) # имена всех объектных файлов

$(TARGET) :
	$(CC) main.c -o app `pkg-config --cflags --libs gtk+-3.0` -Wl,-export-dynamic -lm -ldl

# %.o : %.c # получение объектных файлов из всех, присутствующих в директории файлов исходных кодов
# 	$(CC) $(FLAGS) -c $< -o $@ 

# слева - то, что требуется получить (цель)
# справа - то, что требуется 
# снизу через табуляцию - команды

# gcc main.o mylib.o - o MyProject (получаем бинарный файл)

# .o - объектные файлы
# .c - файлы с исходным кодом

clean : 
	rm *.o
