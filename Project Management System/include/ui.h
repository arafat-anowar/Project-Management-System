#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "project.h"
#include "task.h"
#include "auth.h"

#define get_input _getch()

#define ESC 27

struct t_details;
struct p_details;

enum menu_code
{
    MAIN_MENU = 'M',
    DASHBOARD = 'D',
    PROJECT_MENU = 'P',
    TASK_MENU = 'T',
    REPORT_MENU = 'R'
};

/* General */

int header_screen();
int main_menu();
int dashboard();

int project_management_dashboard();
int task_management_dashboard();
int report_dashboard();
int search_dashboard();

/* Project */

int project_status_dashboard(char status[], int x, int y);
int project_priority_dashboard(char priority[], int x, int y);

int search_project_by_priority();

int project_show_screen(int x, int y);

int change_password_screen(int x, int y);

int update_project_dashboard(
    struct p_details *project,
    int x,
    int y,
    int priority_x,
    int priority_y);

int show_project_screen(
    char id[],
    char name[],
    char category[],
    char description[],
    char priority[],
    char status[],
    char start_date[],
    char end_date[],
    char created_by[]);

int search_project_by_id_or_name_screen(int x, int y);

int change_project_name_screen(int x, int y);
int change_project_category_screen(int x, int y);
int change_project_description_screen(int x, int y);

int change_project_start_date_screen(int x, int y);
int extend_project_deadline_screen(int x, int y);
int task_details_screen_for_separate_project(int x, int y);
/* Task */

int create_task_screen(int x, int y);

int task_details_screen(int x, int y);

int task_status_dashboard(char status[], int x, int y);

int task_priority_dashboard(char priority[], int x, int y);

int task_update_screen(int x, int y);

int search_task_by_id_or_name_screen(int x, int y);

/* Authentication */

int user_registration_screen(int x, int y);
int account_create_success_screen(int x, int y);

int user_login_screen(int x, int y);
int login_success_screen(int x, int y);

int redirecting_screen(int x, int y);

int something_wrong_screen(int x, int y);
int invalid_login_screen(int x, int y);

int change_password_successful_screen(int x, int y);
int change_password_failed_screen(int x, int y);
int search_task_by_id_or_name_screen(int x, int y);
int logout_successful_screen(int x, int y);
int change_task_name_screen(int x, int y);

int change_task_description_screen(int x, int y);

int change_task_start_date_screen(int x, int y);

int extend_task_deadline_screen(int x, int y);

int task_update_dashboard(
    struct t_details *task,
    int x,
    int y);

#endif