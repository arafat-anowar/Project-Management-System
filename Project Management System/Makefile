# ==========================================================
# Makefile for Project Management System
# ==========================================================

CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = main.c \
	src/auth.c \
	src/date.c \
	src/error.c \
	src/id.c \
	src/menu.c \
	src/project.c \
	src/report.c \
	src/search.c \
	src/sort.c \
	src/task.c \
	src/ui.c \
	src/user.c \
	src/utility.c \
	src/validation.c \

OBJ = build/main.o \
	  build/auth.o \
      build/date.o \
	  build/error.o \
	  build/id.o \
	  build/menu.o \
      build/project.o \
	  build/report.o \
	  build/search.o \
	  build/sort.o \
	  build/task.o \
      build/ui.o \
	  build/user.o \
	  build/utility.o \
	  build/validation.o \

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