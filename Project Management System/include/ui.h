#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "project.h"
#include "task.h"
#include "auth.h"

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
int task_status_dashboard(char status[]);
int task_priority_dashboard(char priority[]);
#endif