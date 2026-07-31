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
	build/user.c \
	build/auth.c \
	build/validation.c \
	build/menu.c \
	build/utility.c \
	build/id.c \
	build/project.c \
	build/task.c \
	build/search.c \
	build/report.c \
	build/date.c \
	build/error.c \
	build/sort.c \
	build/ui.c \

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