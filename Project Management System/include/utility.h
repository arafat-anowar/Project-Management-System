// utility header file start

#ifndef UTILITY_H
#define UTILITY_H

// global header files
#include <stdio.h>
#include <windows.h>
#include <time.h>

// local header files
#include "auth.h"
#include "ui.h"
#include "project.h"

// function prototypes
int pause_screen(int sec);
int clear_screen();
int validate_date(char date[]);
int current_time();
int current_date(char date[]);
int is_overdue(char date[]);
int init_console();
int move_cursor(int x, int y);
int get_console_width();
int get_console_height();
void live_clock(void *arg);
int view_profile();
// int validate_input(char field[], int size);

#endif

// utility header file edn
