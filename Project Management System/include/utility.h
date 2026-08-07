#ifndef UTILITY_H
#define UTILITY_H

// Global Header Files
#include <stdio.h>
#include <conio.h>
#include <windows.h>



// Function Prototypes
int user_registration_screen();
int user_login_screen();
int login_invalid_screen();
int project_details_screen();
int task_details_screen();
int pause_screen(int sec);
int clear_screen();
int validate_user_name();
int validate_email();
int validate_phone();
int validate_date();
int current_date();
int compare_date();
int is_overdue();
int move_cursor(int x, int y);
int get_console_width();
<<<<<<< HEAD
int get_console_height();
int init_console();
=======
int clock();
>>>>>>> 63ab50f3491fb11fc2a82d495b2932021d9c406f

#endif