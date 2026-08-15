#ifndef UTILITY_H
#define UTILITY_H

// Global Header Files
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <dos.h>


#include "auth.h"

#define MAX_LENGTH_OF_DATA_IN_FILE 3000
// Function Prototypes

int pause_screen(int sec);
int clear_screen();

int validate_date(char date[]);
//int current_date(char date[]);
// int current_date();
int compare_date();
int is_overdue();
int move_cursor(int x, int y);
int get_console_width();
// void clock(void);
int get_console_height();
int init_console();
// void clock();
// int validate_input(char field[], int size);





#endif