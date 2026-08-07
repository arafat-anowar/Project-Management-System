#ifndef UTILITY_H
#define UTILITY_H

// Global Header Files
#include <stdio.h>
#include <conio.h>
#include <windows.h>
<<<<<<< HEAD
#include <time.h>
#include <dos.h>

=======

#include "auth.h"

#define MAX_LENGTH_OF_DATA_IN_FILE 3000
>>>>>>> 8064a04718014d1d73c921108a7ae4d884a2558d
// Function Prototypes

int login_invalid_screen();
int project_details_screen();
int task_details_screen();
int pause_screen(int sec);
int clear_screen();

int validate_date();
<<<<<<< HEAD
//int current_date(char date[]);
=======
// int current_date();
>>>>>>> 8064a04718014d1d73c921108a7ae4d884a2558d
int compare_date();
int is_overdue();
int move_cursor(int x, int y);
int get_console_width();
<<<<<<< HEAD
// void clock(void);
=======
int get_console_height();
int init_console();
// int clock();




>>>>>>> 8064a04718014d1d73c921108a7ae4d884a2558d

#endif