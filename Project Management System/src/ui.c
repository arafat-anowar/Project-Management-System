#include "ui.h"

int main_menu()
{
    header_screen();
    printf("+-------------------------[ MAIN MENU ]--------------------------+\n");
    printf("|   [1]   -> Register                                            |\n");
    printf("|   [2]   -> Login                                               |\n");
    printf("|   [3]   -> Forget Password                                     |\n");
    printf("|  [ESC]  -> Exit                                                |\n");
    printf("+----------------------[PRESS YOUR CHOICE]-----------------------+\n");
    // Take Input from user and validate that
    char choice;
    do
    {
        choice = get_input;
    } while (choice < '1' || choice > '3');
    switch (choice)
    {
    case '1':
        create_user();
        break;
    case '2':
        login();
        break;
    case '3':
        change_password();
        break;
        // case ESC: // Terminate Program
    }
    return 0;
}

int dashboard()
{
    clear_screen();
    header_screen();
    printf("+-------------------------[ DASHBOARD ]--------------------------+\n");
    printf("|   [1]   -> Project Management                                  |\n");
    printf("|   [2]   -> Task Managent                                       |\n");
    printf("|   [3]   -> Reports                                             |\n");
    printf("|   [4]   -> Search                                              |\n");
    printf("|  [ESC]  -> Logout                                              |\n");
    printf("+----------------------[PRESS YOUR CHOICE]-----------------------+\n");
    // Take Input from user and validate that
    char choice;
    do
    {
        choice = get_input;
    } while (choice < '1' || choice > '4');
    switch (choice)
    {
    case '1':
        project_management_dashboard();
        break;
    case '2':
        task_management_dashboard();
        break;
    case '3':
        report_dashboard();
        break;
    case '4':
        search_dashboard();
        break;
    case ESC:
        logout();
        break;
    }
    return 0;
}

int project_management_dashboard()
{
    clear_screen();
    header_screen();
    printf("+--------------------[ PROJECT MANAGEMENT ]----------------------+\n");
    printf("|   [1]   -> Create Project                                      |\n");
    printf("|   [2]   -> Update Project                                      |\n");
    printf("|   [3]   -> Delete Project                                      |\n");
    printf("|   [4]   -> View All Projects                                   |\n");
    printf("|   [5]   -> Search Project                                      |\n");
    printf("|  [ESC]  -> Back                                                |\n");
    printf("+---------------------[PRESS YOUR CHOICE]------------------------+\n");
    // Take Input from user and validate that
    char choice;
    do
    {
        choice = get_input;
    } while (choice < '1' || choice > '5');
    switch (choice)
    {
    case '1':
        create_project();
        break;
    case '2':
        update_project();
        break;
    case '3':
        delete_project();
        break;
    case '4':
        view_projects();
        break;
    case '5':
        search_project();
        break;
    case ESC:
        dashboard();
        break;
    }
    return 0;
}

int task_management_dashboard()
{
    clear_screen();
    header_screen();
    printf("+---------------------[ TASK MANAGEMENT ]------------------------+\n");
    printf("|   [1]   -> Create Task                                         |\n");
    printf("|   [2]   -> Update Task                                         |\n");
    printf("|   [3]   -> Delete Task                                         |\n");
    printf("|   [4]   -> View All Tasks                                      |\n");
    printf("|   [5]   -> View Tasks by Project                               |\n");
    printf("|  [ESC]  -> Back                                                |\n");
    printf("+---------------------[PRESS YOUR CHOICE]------------------------+\n");
    // Take Input from user and validate that
    char choice;
    do
    {
        choice = get_input;
    } while (choice < '1' && choice > '5');
    switch (choice)
    {
    case '1':
        create_task();
        break;
    case '2':
        update_task();
        break;
    case '3':
        delete_task();
        break;
    case '4':
        view_tasks();
        break;
    case '5':
        view_tasks_by_project();
        break;
    case ESC:
        dashboard();
        break;
    }
    return 0;
}

int project_update_dashboard()
{
    clear_screen();
    header_screen();
    printf("+--------------------[ PROJECT UPDATE ]-------------------------+\n");
    printf("|   [1]   -> Update Project Name                                |\n");
    printf("|   [2]   -> Update Category                                    |\n");
    printf("|   [3]   -> Update Description                                 |\n");
    printf("|   [4]   -> Update Priority                                    |\n");
    printf("|   [5]   -> Update Status                                      |\n");
    printf("|   [6]   -> Update Start Date                                  |\n");
    printf("|   [7]   -> Update End Date                                    |\n");
    printf("|  [ESC]  -> Back                                               |\n");
    printf("+--------------------[PRESS YOUR CHOICE]------------------------+\n");
    char choice;
    do
    {
        choice = get_input;
    } while (choice < '1' && choice > '7');
    switch (choice)
    {
    case '1':
        change_project_name();
        break;
    case '2':
        change_project_category();
        break;
    case '3':
        change_project_description();
        break;
    case '4':
        change_project_priority();
        break;
    case '5':
        change_project_status();
        break;
    case '6':
        change_project_start_date();
        break;
    case '7':
        extend_project_deadline();
        break;
    case ESC:
        project_management_dashboard();
        break;
    }
    return 0;
}

int task_update_dashboard()
{
    clear_screen();
    header_screen();
    printf("+---------------------[ TASK UPDATE ]---------------------------+\n");
    printf("|   [1]   -> Update Task Name                                   |\n");
    printf("|   [2]   -> Update Description                                 |\n");
    printf("|   [3]   -> Update Priority                                    |\n");
    printf("|   [4]   -> Update Status                                      |\n");
    printf("|   [5]   -> Update Start Date                                  |\n");
    printf("|   [6]   -> Update End Date                                    |\n");
    printf("|  [ESC]  -> Back                                               |\n");
    printf("+--------------------[PRESS YOUR CHOICE]------------------------+\n");
    char choice;
    do
    {
        choice = get_input;
    } while (choice < '1' && choice > '6');
    // switch (choice)
    // {
    // case '1':
    //     change_task_name();
    //     break;
    // case '2':
    //     change_task_description();
    //     break;
    // case '3':
    //     change_task_priority();
    //     break;
    // case '4':
    //     change_task_status();
    //     break;
    // case '5':
    //     change_task_start_date();
    //     break;
    // case '6':
    //     extend_task_deadline();
    //     break;
    // case ESC:
    //     task_management_dashboard();
    //     break;
    // }
    return 0;
}
int report_dashboard()
{
    clear_screen();
    header_screen();
    printf("+------------------------[ REPORTS ]----------------------------+\n");
    printf("|   [1]   -> Project Summary Report                             |\n");
    printf("|   [2]   -> Task Summary Report                                |\n");
    printf("|   [3]   -> Completed Projects Report                          |\n");
    printf("|   [4]   -> Pending Tasks Report                               |\n");
    printf("|   [5]   -> Overdue Tasks Report                               |\n");
    printf("|   [6]   -> High Priority Tasks Report                         |\n");
    printf("|  [ESC]  -> Back                                               |\n");
    printf("+--------------------[PRESS YOUR CHOICE]------------------------+\n");
    return 0;
}
int search_dashboard()
{
    printf("+-------------------------[ SEARCH ]----------------------------+\n");
    printf("|   [1]   -> Search Project by ID or Name                       |\n");
    printf("|   [2]   -> Search Task by ID or Name                          |\n");
    printf("|   [3]   -> Search by Status                                   |\n");
    printf("|   [4]   -> Search by Priority                                 |\n");
    printf("|  [ESC]  -> Back                                               |\n");
    printf("+--------------------[PRESS YOUR CHOICE]------------------------+\n");
    return 0;
}