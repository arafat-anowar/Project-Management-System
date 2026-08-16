#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <windows.h>
#include <time.h>

#include "auth.h"

int pause_screen(int sec);
int clear_screen();
int validate_date(char date[]);
int current_time();
int current_date();
int is_overdue(char date[]);
int init_console();
int move_cursor(int x, int y);
int get_console_width();
int get_console_height();
// int validate_input(char field[], int size);

#endif