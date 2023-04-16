TARGET = bin/main
SRC = src/main.c

FLAGS = -Wall -Werror

CC = gcc

all:
	$(CC) $(FLAGS) $(SRC) -o $(TARGET)

run:
	./$(TARGET)
