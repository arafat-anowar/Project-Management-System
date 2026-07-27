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
    // case ESC:
    // Terminate Program
    }
    return 0;
}

int dashboard()
{
    return 0;
}

int project_management_dashboard()
{
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