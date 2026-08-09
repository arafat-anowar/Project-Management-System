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
int task_update_dashboard(struct t_details *task);
int report_dashboard();
int search_dashboard();

int task_status_dashboard(char status[]);
int task_priority_dashboard(char priority[]);

int project_status_dashboard(char status[],int x,int y);
int project_priority_dashboard(char priority[],int x,int y);

int search_project_by_priority();

int project_show_screen(int x, int y);

int change_password_screen(int x, int y);

// auth.c
int user_registration_screen(int x, int y);
int account_create_success_screen(int x, int y);
int user_login_screen(int x, int y);
int login_success_screen(int x, int y);
int redirecting_screen(int x, int y);
int something_wrong_screen(int x, int y);
int invalid_login_screen(int x, int y);
int change_password_successful_screen(int x, int y);
int change_password_failed_screen(int x, int y);
int logout_successful_screen(int x, int y);


int show_project_screen(
    char id[],
    char name[],
    char category[],
    char description[],
    char priority[],
    char status[],
    char start_date[],
    char end_date[],
    char created_by[]
);

int search_project_by_id_or_name_screen(int x, int y);
int search_project_by_status_screen(int x, int y);
int search_project_by_priority_screen(int x, int y);

#endif