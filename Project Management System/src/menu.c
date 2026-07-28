#include "menu.h"

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
    printf("|   [6]   -> Change Project Status                               |\n");
    printf("|   [7]   -> Change Project Priority                             |\n");
    printf("|   [8]   -> Extend Project Deadline                             |\n");
    printf("|  [ESC]  -> Back                                                |\n");
    printf("+---------------------[PRESS YOUR CHOICE]------------------------+\n");
    // Take Input from user and validate that
    char choice;
    do
    {
        choice = get_input;
    } while (choice < '1' || &choice > '8');
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
    case '6':
        change_project_status();
        break;
    case '7':
        change_project_priority();
        break;
    case '8':
        extend_project_deadline();
        break;
    case ESC:
        dashboard();
        break;
    }
    return 0;
}

int task_management_dashboard()
{
    return 0;
}

int project_update_dashboard()
{
    return 0;
}

int task_update_dashboard()
{
    return 0;
}
int report_dashboard()
{
    return 0;
}
int search_dashboard()
{
    return 0;
}