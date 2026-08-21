// ui header file end

#ifndef UI_H
#define UI_H

// Global Header Files
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <process.h>
#include <errno.h>

// Local Header Files
#include "project.h"
#include "task.h"
#include "auth.h"
#include "report.h"
#include "utility.h"

// Macros
#define get_input _getch()
#define ESC 27

// Structures Prototype
struct t_details;
struct p_details;

// enum
enum error_type
{
    FILE_OPEN_ERROR,
    FILE_CLOSE_ERROR,
    SOMETHING_FAILED
};

// function Prototypes

// main menu
int header_screen();
int main_menu();

// dashboard
int dashboard();

// auth
int user_registration_screen(int x, int y);
int account_create_success_screen(int x, int y);
int user_login_screen(int x, int y);
int login_success_screen(int x, int y);
int redirecting_screen(int x, int y);
int invalid_login_screen(int x, int y);
int change_password_successful_screen(int x, int y);
int change_password_failed_screen(int x, int y);
int logout_successful_screen(int x, int y);
int change_password_screen(int x, int y);

// project
int project_management_dashboard();
int create_project_screen(int x, int y);
int search_project_by_id_or_name_screen(int x, int y);
int update_project_dashboard(struct p_details *project, int x, int y, int priority_x, int priority_y);
int change_project_name_screen(int x, int y);
int change_project_category_screen(int x, int y);
int change_project_description_screen(int x, int y);
int change_project_start_date_screen(int x, int y);
int extend_project_deadline_screen(int x, int y);
int project_show_screen(int x, int y);
int project_status_dashboard(char status[], int x, int y);
int project_priority_dashboard(char priority[], int x, int y);
int project_created_successful(int x, int y);
int project_update_successful(int x, int y);
int project_deleted_successful(int x, int y);
int project_not_found(int x, int y);

// task
int task_management_dashboard();
int create_task_screen(int x, int y);
int search_task_by_id_or_name_screen(int x, int y);
int task_update_dashboard(struct t_details *task, int x, int y);
int change_task_name_screen(int x, int y);
int change_task_description_screen(int x, int y);
int change_task_start_date_screen(int x, int y);
int extend_task_deadline_screen(int x, int y);
int task_details_screen(int x, int y);
int task_details_screen_for_separate_project(int x, int y);
int task_status_dashboard(char status[], int x, int y);
int task_priority_dashboard(char priority[], int x, int y);
int task_created_successfully(int x, int y);
int task_not_found(int x, int y);
int task_deleted_successful(int x, int y);
int task_update_successful(int x, int y);

// report
int report_dashboard();
int project_summary_report_screen(int x, int y);
int project_progress_report_screen(int x, int y);
int overdue_projects_report_screen(int x, int y);
int high_priority_projects_report_screen(int x, int y);
int task_summary_report_screen(int x, int y);
int overdue_tasks_report_screen(int x, int y);
int high_priority_tasks_report_screen(int x, int y);
int pending_active_tasks_screen(int x, int y);


// other
int search_dashboard();
int profile_screen(int x, int y);
int something_went_wrong_screen(enum error_type error);
char *get_error_message(enum error_type error);
int date_time_before_login(int x, int y);
int date_time_after_login(int x, int y);


#endif

// ui header file end