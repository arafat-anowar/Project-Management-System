#ifndef MENU_H
#define MENU_H
// Global Header Files
#include<stdio.h>
// Local Header Files
#include "user.h"
#include "auth.h"
#include "project.h"
#include "task.h"
#include "utility.h"
// Macros
#define get_input _getch()
#define ESC 27
// Function Prototypes
int main_menu();
int dashboard();
int project_management_dashboard();
int task_management_dashboard();
int project_update_dashboard();
int task_update_dashboard();
int report_dashboard();
int search_dashboard();

#endif