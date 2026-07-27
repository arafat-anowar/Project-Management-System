# ==========================================================
# Makefile for Project Management System
# ==========================================================

CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = main.c \
	src/user.c \
	src/auth.c \
	src/validation.c \
	src/menu.c \
	src/utility.c \
	src/id.c \
	src/project.c \
	src/task.c \
	src/search.c \
	src/report.c \
	src/date.c \
	src/error.c \
	src/sort.c \
	src/ui.c \



OBJ = build/main.o \
	build/user.o \
	build/auth.o \
	build/validation.o \
	build/menu.o \
	build/utility.o \
	build/id.o \
	build/project.o \
	build/task.o \
	build/search.o \
	build/report.o \
	build/date.o \
	build/error.o \
	build/sort.o \
	build/ui.o \

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