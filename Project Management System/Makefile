# ==========================================================
# Makefile for Project Management System
# ==========================================================

CC = gcc

CFLAGS = -Wall -Wextra -Iincludes

SRC = main.c \
	src/menu.c \
	src/auth.c \
	src/project.c \
	src/task.c \

OBJ = build/main.o \
	  build/menu.o \
      build/auth.o \
	  build/project.o \
	  build/task.o \

TARGET = bin/projectmanagement.exe

# ==========================================================

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p bin
	$(CC) $(OBJ) -o $(TARGET)

build/main.o: main.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build
	rm -rf bin

rebuild: clean all

.PHONY: all run clean rebuild