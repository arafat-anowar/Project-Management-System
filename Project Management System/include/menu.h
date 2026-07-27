#ifndef MENU_H
#define MENU_H
// Global Header Files
#include<stdio.h>
// Local Header Files
#include "user.h"
// Macros
#define get_input _getch()
// Function Prototypes
int main_menu();
int dashboard();
int project_management_dashboard();
int task_management_dashboard();
int project_update_dashboard();
int task_update_dashboard();
#endif