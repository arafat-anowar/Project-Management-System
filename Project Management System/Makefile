# ==========================================================
# Makefile for Project Management System
# ==========================================================

CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = main.c \
	src/auth.c \
	src/project.c \
	src/report.c \
	src/task.c \
	src/ui.c \
	src/utility.c \

OBJ = build/main.o \
	  build/auth.o \
      build/project.o \
	  build/report.o \
	  build/task.o \
      build/ui.o \
	  build/utility.o \

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