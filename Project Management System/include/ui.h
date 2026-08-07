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

struct t_details;
struct p_details;

// Function Prototypes
int header_screen();
int main_menu();
int dashboard();
int project_management_dashboard();
int task_management_dashboard();
int project_update_dashboard(struct p_details *project);
int task_update_dashboard(struct t_details *task);
int report_dashboard();
int search_dashboard();
int task_status_dashboard(char status[]);
int task_priority_dashboard(char priority[]);
int project_status_dashboard(char status[]);
int project_priority_dashboard(char priority[],char priority_choice);


int user_registration_screen(int x,int y);
int user_login_screen(int x,int y);
int change_password_screen(int x,int y);
#endif