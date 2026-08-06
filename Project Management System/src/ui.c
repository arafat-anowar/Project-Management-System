#include "ui.h"

int header_screen()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    clear_screen();
    int terminal_width = get_console_width();
    int box_width = 100;
    int x = (terminal_width - box_width) / 2;
    move_cursor(x, 1);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    move_cursor(x, 2);
    printf("║                                                                                                  ║\n");
    move_cursor(x, 3);
    printf("║                              ██████╗      ███╗   ███╗       ███████╗                             ║\n");
    move_cursor(x, 4);
    printf("║                              ██╔══██╗     ████╗ ████║       ██╔════╝                             ║\n");
    move_cursor(x, 5);
    printf("║                              ██████╔╝     ██╔████╔██║       ███████╗                             ║\n");
    move_cursor(x, 6);
    printf("║                              ██╔═══╝      ██║╚██╔╝██║       ╚════██║                             ║\n");
    move_cursor(x, 7);
    printf("║                              ██║     ██   ██║ ╚═╝ ██║  ██   ███████║                             ║\n");
    move_cursor(x, 8);
    printf("║                              ╚═╝          ╚═╝     ╚═╝      ╚══════╝                              ║\n");
    move_cursor(x, 9);
    printf("║                                                                                                  ║\n");
    move_cursor(x, 10);
    printf("║                                    PROJECT MANAGEMENT SYSTEM                                     ║\n");
    move_cursor(x, 11);
    printf("║                                Plan • Organize • Track • Complete                                ║\n");
    move_cursor(x, 12);
    printf("║                                                                                                  ║\n");
    move_cursor(x, 13);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    return 0;
}

int main_menu()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    header_screen();
    int terminal_width = get_console_width();
    int box_width = 100;
    int x = (terminal_width - box_width) / 2;
    move_cursor(x,20 );
    printf("╔══════════════════════════════════════════[ MAIN  MENU ]══════════════════════════════════════════╗\n");

    move_cursor(x, 21);
    printf("║                                                                                                  ║\n");

    move_cursor(x, 22);
    printf("║   [1]  Register                                                                                  ║\n");

    move_cursor(x, 23);
    printf("║   [2]  Login                                                                                     ║\n");

    move_cursor(x, 24);
    printf("║   [3]  Forgot Password                                                                           ║\n");

    move_cursor(x, 25);
    printf("║  [ESC] Exit                                                                                      ║\n");

    move_cursor(x, 26); 
    printf("║                                                                                                  ║\n");

    move_cursor(x, 27);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    move_cursor(x, 28);
    printf("║                                        PRESS YOUR CHOICE                                         ║\n");

    move_cursor(x, 29);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
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
    // clear_screen();
    // header_screen();
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
        search_by_project_id_or_name();
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
    printf("|   [5]   -> View Tasks by ID or Name                            |\n");
    printf("|   [6]   -> View Tasks by Project                               |\n");
    printf("|   [7]   -> View Tasks by Status                                |\n");
    printf("|   [8]   -> View Tasks by Priority                              |\n");
    printf("|  [ESC]  -> Back                                                |\n");
    printf("+---------------------[PRESS YOUR CHOICE]------------------------+\n");
    // Take Input from user and validate that
    char choice;
    do
    {
        choice = get_input;
    } while (choice < '1' && choice > '8');
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
        search_by_task_id_or_name();
        break;
    case '6':
        view_tasks_by_project();
        break;
    case '7':
        search_task_by_status();
        break;
    case '8':
        search_task_by_priority();
        break;

    case ESC:
        dashboard();
        break;
    }
    return 0;
}

int project_update_dashboard(struct p_details *project)
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
        change_project_name(project->name);
        break;
    case '2':
        change_project_category(project->category);
        break;
    case '3':
        change_project_description(project->description);
        break;
    case '4':
        change_project_priority(project->priority);
        break;
    case '5':
        change_project_status(project->status);
        break;
    case '6':
        change_project_start_date(project->start_date);
        break;
    case '7':
        extend_project_deadline(project->end_date);
        break;
    case ESC:
        project_management_dashboard();
        break;
    }
    return 0;
}

int task_update_dashboard(struct t_details *task)
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
    switch (choice)
    {
    case '1':
        change_task_name(task->name);
        break;
    case '2':
        change_task_description(task->description);
        break;
    case '3':
        change_task_priority(task->priority);
        break;
    case '4':
        change_task_status(task->status);
        break;
    case '5':
        change_task_start_date(task->start_date);
        break;
    case '6':
        extend_task_deadline(task->end_date);
        break;
    case ESC:
        task_management_dashboard();
        break;
    }
    return 0;
}
int task_status_dashboard(char status[])
{
    clear_screen();
    header_screen();
    printf("+---------------------[ TASK STATUS ]---------------------------+\n");
    printf("|   [1]   -> Created                                            |\n");
    printf("|   [2]   -> In Progress                                        |\n");
    printf("|   [3]   -> Completed                                          |\n");
    printf("|   [4]   -> Cancelled                                          |\n");
    printf("|  [ESC]  -> Back                                               |\n");
    printf("+--------------------[PRESS YOUR CHOICE]------------------------+\n");
    char choice;
    do
    {
        choice = get_input;
    } while (choice < '1' && choice > '4');
    switch (choice)
    {
    case '1':
        strcpy(status, "Created");
        break;
    case '2':
        strcpy(status, "In Progress");
        break;
    case '3':
        strcpy(status, "Completed");
        break;
    case '4':
        strcpy(status, "Cancelled");
        break;
    case ESC:
        task_management_dashboard();
        break;
    }
    return 0;
}
int project_status_dashboard(char status[])
{
    clear_screen();
    header_screen();
    printf("+---------------------[ PROJECT STATUS ]---------------------------+\n");
    printf("|   [1]   -> Created                                            |\n");
    printf("|   [2]   -> In Progress                                        |\n");
    printf("|   [3]   -> Completed                                          |\n");
    printf("|   [4]   -> Cancelled                                          |\n");
    printf("|  [ESC]  -> Back                                               |\n");
    printf("+--------------------[PRESS YOUR CHOICE]------------------------+\n");
    char choice;
    do
    {
        choice = get_input;
    } while (choice < '1' && choice > '4');
    switch (choice)
    {
    case '1':
        strcpy(status, "Created");
        break;
    case '2':
        strcpy(status, "In Progress");
        break;
    case '3':
        strcpy(status, "Completed");
        break;
    case '4':
        strcpy(status, "Cancelled");
        break;
    case ESC:
        project_management_dashboard();
        break;
    }
    return 0;
}
int task_priority_dashboard(char priority[])
{
    clear_screen();
    header_screen();
    printf("+--------------------[ TASK PRIORITY ]--------------------------+\n");
    printf("|   [1]   -> High                                               |\n");
    printf("|   [2]   -> Medium                                             |\n");
    printf("|   [3]   -> Low                                                |\n");
    printf("|  [ESC]  -> Back                                               |\n");
    printf("+--------------------[PRESS YOUR CHOICE]------------------------+\n");
    char choice;
    do
    {
        choice = get_input;
    } while (choice < '1' || choice > '3');
    switch (choice)
    {
    case '1':
        strcpy(priority, "High");
        break;

    case '2':
        strcpy(priority, "Medium");
        break;

    case '3':
        strcpy(priority, "Low");
        break;

    case ESC:
        task_management_dashboard();
        break;
        ;
    }
    return 0;
}
int project_priority_dashboard(char priority[])
{
    clear_screen();
    header_screen();
    printf("+--------------------[ PROJECT PRIORITY ]--------------------------+\n");
    printf("|   [1]   -> High                                               |\n");
    printf("|   [2]   -> Medium                                             |\n");
    printf("|   [3]   -> Low                                                |\n");
    printf("|  [ESC]  -> Back                                               |\n");
    printf("+--------------------[PRESS YOUR CHOICE]------------------------+\n");
    char choice;
    do
    {
        choice = get_input;
    } while (choice < '1' || choice > '3');
    switch (choice)
    {
    case '1':
        strcpy(priority, "High");
        break;

    case '2':
        strcpy(priority, "Medium");
        break;

    case '3':
        strcpy(priority, "Low");
        break;

    case ESC:
        project_management_dashboard();
        break;
    }
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