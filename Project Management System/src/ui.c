#include "ui.h"

// main menu UI START
int header_screen()
{
    init_console();
    clear_screen();

    int terminal_width = get_console_width();
    int terminal_height = get_console_height();
    int box_width = 100, box_height = 13;
    int x = (terminal_width - box_width) / 2, y = 1;

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 2);
    printf("║                              ██████╗      ███╗   ███╗       ███████╗                             ║\n");
    move_cursor(x, y + 3);
    printf("║                              ██╔══██╗     ████╗ ████║       ██╔════╝                             ║\n");
    move_cursor(x, y + 4);
    printf("║                              ██████╔╝     ██╔████╔██║       ███████╗                             ║\n");
    move_cursor(x, y + 5);
    printf("║                              ██╔═══╝      ██║╚██╔╝██║       ╚════██║                             ║\n");
    move_cursor(x, y + 6);
    printf("║                              ██║     ██   ██║ ╚═╝ ██║  ██   ███████║                             ║\n");
    move_cursor(x, y + 7);
    printf("║                              ╚═╝          ╚═╝     ╚═╝      ╚══════╝                              ║\n");
    move_cursor(x, y + 8);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 9);
    printf("║                                    PROJECT MANAGEMENT SYSTEM                                     ║\n");
    move_cursor(x, y + 10);
    printf("║                                Plan • Organize • Track • Complete                                ║\n");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 12);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    return 0;
}

int main_menu()
{
    init_console();
    header_screen();

    int terminal_width = get_console_width();
    int terminal_height = get_console_height();
    int box_width = 100, box_height = 14;
    int x = (terminal_width - box_width) / 2, y = ((terminal_height - box_height) / 2) + 13;

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════[ MAIN  MENU ]══════════════════════════════════════════╗\n");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 2);
    printf("║   [1]  Register                                                                                  ║\n");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 4);
    printf("║   [2]  Login                                                                                     ║\n");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 6);
    printf("║   [3]  Forgot Password                                                                           ║\n");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 8);
    printf("║  [ESC] Exit                                                                                      ║\n");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 10);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 11);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 12);
    printf("║                                        PRESS YOUR CHOICE                                         ║\n");
    move_cursor(x, y + 13);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    char choice;
    do
    {
        choice = get_input;
    } while ((choice < '1' || choice > '3') && choice != ESC);
    switch (choice)
    {
    case '1':
        create_user();
        login();
        break;
    case '2':
        login();
        main_menu();
        break;
    case '3':
        change_password();
        main_menu();
        break;
        // case ESC: // Terminate Program
    }
    return 0;
}
// main menu UI END

// auth.c UI START
int user_registration_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    move_cursor(x, y + 1);
    printf("║                                          CREATE ACCOUNT                                          ║\n");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 4);
    printf("║    Full Name :                                                                                   ║\n");
    move_cursor(x, y + 5);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║\n");
    move_cursor(x, y + 6);
    printf("║    │                                                                                        │    ║\n");
    move_cursor(x, y + 7);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║\n");
    move_cursor(x, y + 8);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 9);
    printf("║    Email Address :                                                                               ║\n");
    move_cursor(x, y + 10);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║\n");
    move_cursor(x, y + 11);
    printf("║    │                                                                                        │    ║\n");
    move_cursor(x, y + 12);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║\n");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 14);
    printf("║    Phone Number :                                                                                ║\n");
    move_cursor(x, y + 15);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║\n");
    move_cursor(x, y + 16);
    printf("║    │    +880                                                                                │    ║\n");
    move_cursor(x, y + 17);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║\n");
    move_cursor(x, y + 18);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 19);
    printf("║    Username :                                                                                    ║\n");
    move_cursor(x, y + 20);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║\n");
    move_cursor(x, y + 21);
    printf("║    │                                                                                        │    ║\n");
    move_cursor(x, y + 22);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║\n");
    move_cursor(x, y + 23);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 24);
    printf("║    Password :                                                                                    ║\n");
    move_cursor(x, y + 25);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║\n");
    move_cursor(x, y + 26);
    printf("║    │                                                                                        │    ║\n");
    move_cursor(x, y + 27);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║\n");
    move_cursor(x, y + 28);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 29);
    printf("║    What Is Your Favourite Food : :                                                               ║\n");
    move_cursor(x, y + 30);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║\n");
    move_cursor(x, y + 31);
    printf("║    │                                                                                        │    ║\n");
    move_cursor(x, y + 32);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║\n");
    move_cursor(x, y + 33);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 34);
    printf("║                                        [ ENTER ] Register                                        ║\n");
    move_cursor(x, y + 35);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 36);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    return 0;
}

int account_create_success_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 2);
    printf("║                                   ACCOUNT CREATED SUCCESSFULLY                                   ║");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    pause_screen(1000);

    return 0;
}

int user_login_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    move_cursor(x, y + 1);
    printf("║                                              LOGIN                                               ║\n");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 4);
    printf("║    Username / Email :                                                                            ║\n");
    move_cursor(x, y + 5);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║\n");
    move_cursor(x, y + 6);
    printf("║    │                                                                                        │    ║\n");
    move_cursor(x, y + 7);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║\n");
    move_cursor(x, y + 8);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 10);
    printf("║    Password :                                                                                    ║\n");
    move_cursor(x, y + 11);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║\n");
    move_cursor(x, y + 12);
    printf("║    │                                                                                        │    ║\n");
    move_cursor(x, y + 13);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║\n");
    move_cursor(x, y + 14);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 15);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 16);
    printf("║                                         [ ENTER ] Login                                          ║\n");
    move_cursor(x, y + 17);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 18);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    pause_screen(1000);

    return 0;
}

int login_success_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 2);
    printf("║                                         LOGIN SUCCESSFUL                                         ║");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    pause_screen(1000);

    return 0;
}

int redirecting_screen(int x, int y)
{
    clear_screen();
    header_screen();

    int i;

    for (i = 0; i < 4; i++)
    {

        move_cursor(x, y + 0);
        printf("                                            REDIRECTING");

        for (int j = 0; j < i; j++)
        {
            printf(".");
        }

        pause_screen(500);
    }

    return 0;
}

int something_wrong_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 2);
    printf("║                                       SOMETHING WENT WRONG                                       ║");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("║                                            TRY AGAIN                                             ║");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 6);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    pause_screen(1000);

    return 0;
}

int invalid_login_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 2);
    printf("║                                      INVALID LOGIN DETAILS                                       ║");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    pause_screen(1000);

    return 0;
}

int change_password_successful_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 2);
    printf("║                                  PASSWORD CHANGED SUCCESSFULLY                                   ║");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    pause_screen(1000);

    return 0;
}

int change_password_failed_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 2);
    printf("║                                      PASSWORD CHANGE FAILED                                      ║");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    pause_screen(1000);

    return 0;
}

int logout_successful_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 2);
    printf("║                                        LOGOUT SUCCESSFUL                                         ║");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    pause_screen(1000);

    return 0;
}

int change_password_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    move_cursor(x, y + 1);
    printf("║                                         CHANGE PASSWORD                                          ║\n");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 4);
    printf("║    Email Address :                                                                               ║\n");
    move_cursor(x, y + 5);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║\n");
    move_cursor(x, y + 6);
    printf("║    │                                                                                        │    ║\n");
    move_cursor(x, y + 7);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║\n");
    move_cursor(x, y + 8);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 9);
    printf("║    What Is Your Favourite Food :                                                                 ║\n");
    move_cursor(x, y + 10);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║\n");
    move_cursor(x, y + 11);
    printf("║    │                                                                                        │    ║\n");
    move_cursor(x, y + 12);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║\n");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 14);
    printf("║    New Password :                                                                                ║\n");
    move_cursor(x, y + 15);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║\n");
    move_cursor(x, y + 16);
    printf("║    │                                                                                        │    ║\n");
    move_cursor(x, y + 17);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║\n");
    move_cursor(x, y + 18);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 19);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 20);
    printf("║                                    [ ENTER ] Change Password                                     ║\n");
    move_cursor(x, y + 21);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 22);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    return 0;
}

// auth.c UI END

// project.c UI Start
int project_management_dashboard()
{
    sort_projects();

    init_console();
    header_screen();
    int terminal_width = get_console_width();
    int terminal_height = get_console_height();
    int box_width = 100, box_height = 23;
    int x = (terminal_width - box_width) / 2, y = ((terminal_height - box_height) / 2) + 13;
    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    move_cursor(x, y + 1);
    printf("║                                        PROJECT MANAGEMENT                                        ║\n");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 4);
    printf("║    [1]  Create Project                                                                           ║\n");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 6);
    printf("║    [2]  Update Project                                                                           ║\n");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 8);
    printf("║    [3]  Delete Project                                                                           ║\n");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 10);
    printf("║    [4]  View All Projects                                                                        ║\n");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 12);
    printf("║    [5]  Search Project                                                                           ║\n");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 14);
    printf("║    [6]  View Projects by Status                                                                  ║\n");
    move_cursor(x, y + 15);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 16);
    printf("║    [7]  View Projects by Priority                                                                ║\n");
    move_cursor(x, y + 17);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 18);
    printf("║   [ESC] Back                                                                                     ║\n");
    move_cursor(x, y + 19);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 20);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 21);
    printf("║                                        PRESS YOUR CHOICE                                         ║\n");
    move_cursor(x, y + 22);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    char choice;
    do
    {
        choice = get_input;
    } while ((choice < '1' || choice > '7') && choice != ESC);
    switch (choice)
    {
    case '1':
        create_project();
        project_management_dashboard();
        break;
    case '2':
        update_project();
        project_management_dashboard();
        break;
    case '3':
        delete_project();
        project_management_dashboard();
        break;
    case '4':
        view_projects();
        project_management_dashboard();
        break;
    case '5':
        search_by_project_id_or_name();
        project_management_dashboard();
        break;
    case '6':
        search_project_by_status();
        project_management_dashboard();
        break;
    case '7':
        search_project_by_priority();
        project_management_dashboard();
        break;
    case ESC:
        dashboard();
        break;
    }
    return 0;
}

int create_project_screen(int x, int y)
{
    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                      CREATE PROJECT                                              ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("║    Project Name :                                                                                ║");
    move_cursor(x, y + 5);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");
    move_cursor(x, y + 6);
    printf("║    │                                                                                        │    ║");
    move_cursor(x, y + 7);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");
    move_cursor(x, y + 8);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 9);
    printf("║    Category :                                                                                    ║");
    move_cursor(x, y + 10);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");
    move_cursor(x, y + 11);
    printf("║    │                                                                                        │    ║");
    move_cursor(x, y + 12);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 14);
    printf("║    Description :                                                                                 ║");
    move_cursor(x, y + 15);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");
    move_cursor(x, y + 16);
    printf("║    │                                                                                        │    ║");
    move_cursor(x, y + 17);
    printf("║    │                                                                                        │    ║");
    move_cursor(x, y + 18);
    printf("║    │                                                                                        │    ║");
    move_cursor(x, y + 19);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");
    move_cursor(x, y + 20);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 21);
    printf("║    Priority :                                                                                    ║");

    move_cursor(x, y + 22);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 23);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 24);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 25);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 26);
    printf("║    Start Date (YYYY-MM-DD) :                                                                     ║");

    move_cursor(x, y + 27);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 28);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 29);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 30);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 31);
    printf("║    End Date (YYYY-MM-DD) :                                                                       ║");

    move_cursor(x, y + 32);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 33);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 34);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 35);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 36);
    printf("║                                     [ ENTER ] Create Project                                     ║");

    move_cursor(x, y + 37);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 38);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");
    return 0;
}

int search_project_by_id_or_name_screen(int x, int y)
{
    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                              SEARCH PROJECT                                                  ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 3);
    printf("║    Project ID or Name :                                                                      ║");

    move_cursor(x, y + 4);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 5);
    printf("║    │                                                                                    │    ║");

    move_cursor(x, y + 6);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 7);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝");

    move_cursor(x + 24, y + 5);

    return 0;
}

int update_project_dashboard(struct p_details *project,
                             int x,
                             int y,
                             int priority_x,
                             int priority_y)
{
    char choice;
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                                       UPDATE PROJECT                                             ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 4);
    printf("║    Project ID   : %s                                                                          ║", project->id);

    move_cursor(x, y + 5);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 6);
    printf("║                              WHAT DO YOU WANT TO UPDATE?                                         ║");

    move_cursor(x, y + 7);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 8);
    printf("║       [ 1 ]  Project Name                                                                        ║");

    move_cursor(x, y + 9);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 10);
    printf("║       [ 2 ]  Category                                                                            ║");

    move_cursor(x, y + 11);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 12);
    printf("║       [ 3 ]  Description                                                                         ║");

    move_cursor(x, y + 13);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 14);
    printf("║       [ 4 ]  Priority                                                                            ║");

    move_cursor(x, y + 15);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 16);
    printf("║       [ 5 ]  Status                                                                              ║");

    move_cursor(x, y + 17);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 18);
    printf("║       [ 6 ]  Start Date                                                                          ║");

    move_cursor(x, y + 19);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 20);
    printf("║       [ 7 ]  End Date                                                                            ║");

    move_cursor(x, y + 21);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 22);
    printf("║       [ 8 ]  Back                                                                                ║");

    move_cursor(x, y + 23);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 24);
    printf("║                              Select an option :                                                  ║");

    move_cursor(x, y + 25);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 26);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    do
    {
        choice = get_input;

    } while ((choice < '1' || choice > '8') && choice != ESC);

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

        project_priority_dashboard(
            project->priority,
            priority_x,
            priority_y);

        break;

    case '5':

        project_status_dashboard(
            project->status,
            priority_x,
            priority_y);

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

int change_project_name_screen(int x, int y)
{
    clear_screen();
    header_screen();
    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                              UPDATE PROJECT NAME                                             ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 3);
    printf("║                                                                                              ║");

    move_cursor(x, y + 4);
    printf("║    New Project Name :                                                                      ║");

    move_cursor(x, y + 5);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 6);
    printf("║    │                                                                                    │    ║");

    move_cursor(x, y + 7);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 8);
    printf("║                                                                                              ║");

    move_cursor(x, y + 9);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝");

    move_cursor(x + 24, y + 6);

    return 0;
}

int change_project_category_screen(int x, int y)
{
    clear_screen();
    header_screen();
    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                              UPDATE PROJECT CATEGORY                                        ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 3);
    printf("║                                                                                              ║");

    move_cursor(x, y + 4);
    printf("║    New Category :                                                                           ║");

    move_cursor(x, y + 5);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 6);
    printf("║    │                                                                                    │    ║");

    move_cursor(x, y + 7);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 8);
    printf("║                                                                                              ║");

    move_cursor(x, y + 9);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝");

    move_cursor(x + 24, y + 6);

    return 0;
}

int change_project_description_screen(int x, int y)
{
    clear_screen();
    header_screen();
    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                            UPDATE PROJECT DESCRIPTION                                       ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 3);
    printf("║                                                                                              ║");

    move_cursor(x, y + 4);
    printf("║    New Description :                                                                        ║");

    move_cursor(x, y + 5);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 6);
    printf("║    │                                                                                    │    ║");

    move_cursor(x, y + 7);
    printf("║    │                                                                                    │    ║");

    move_cursor(x, y + 8);
    printf("║    │                                                                                    │    ║");

    move_cursor(x, y + 9);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 10);
    printf("║                                                                                              ║");

    move_cursor(x, y + 11);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝");

    move_cursor(x + 8, y + 6);

    return 0;
}

int change_project_start_date_screen(int x, int y)
{
    clear_screen();
    header_screen();
    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                            UPDATE START DATE                                                ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 3);
    printf("║                                                                                              ║");

    move_cursor(x, y + 4);
    printf("║    New Start Date (YYYY-MM-DD) :                                                           ║");

    move_cursor(x, y + 5);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 6);
    printf("║    │                                                                                    │    ║");

    move_cursor(x, y + 7);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 8);
    printf("║                                                                                              ║");

    move_cursor(x, y + 9);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝");

    move_cursor(x + 24, y + 6);

    return 0;
}
int extend_project_deadline_screen(int x, int y)
{
    clear_screen();
    header_screen();
    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                           UPDATE END DATE                                                   ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 3);
    printf("║                                                                                              ║");

    move_cursor(x, y + 4);
    printf("║    New End Date (YYYY-MM-DD) :                                                             ║");

    move_cursor(x, y + 5);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 6);
    printf("║    │                                                                                    │    ║");

    move_cursor(x, y + 7);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 8);
    printf("║                                                                                              ║");

    move_cursor(x, y + 9);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝");

    move_cursor(x + 24, y + 6);

    return 0;
}

// project.c UI END



int dashboard()
{
    init_console();
    header_screen();
    int terminal_width = get_console_width();
    int terminal_height = get_console_height();
    int box_width = 100, box_height = 19;
    int x = (terminal_width - box_width) / 2, y = ((terminal_height - box_height) / 2) + 13;
    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    move_cursor(x, y + 1);
    printf("║                                             DASHBOARD                                            ║\n");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 4);
    printf("║    [1]  Project Management                                                                       ║\n");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 6);
    printf("║    [2]  Task Management                                                                          ║\n");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 8);
    printf("║    [3]  Reports                                                                                  ║\n");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 10);
    printf("║    [4]  Search                                                                                   ║\n");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 12);
    printf("║    [5]  Profile                                                                                  ║\n");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 14);
    printf("║   [ESC] Logout                                                                                   ║\n");
    move_cursor(x, y + 15);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 16);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 17);
    printf("║                                         PRESS YOUR CHOICE                                        ║\n");
    move_cursor(x, y + 18);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    // Take Input from user and validate that
    char choice;
    do
    {
        choice = get_input;
    } while ((choice < '1' || choice > '5') && choice != ESC);
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

int task_management_dashboard()
{
    sort_tasks();
    init_console();
    header_screen();
    int terminal_width = get_console_width();
    int terminal_height = get_console_height();
    int box_width = 100, box_height = 25;
    int x = (terminal_width - box_width) / 2, y = ((terminal_height - box_height) / 2) + 13;
    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    move_cursor(x, y + 1);
    printf("║                                         TASK MANAGEMENT                                          ║\n");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 4);
    printf("║    [1]  Create Task                                                                              ║\n");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 6);
    printf("║    [2]  Update Task                                                                              ║\n");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 8);
    printf("║    [3]  Delete Task                                                                              ║\n");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 10);
    printf("║    [4]  View All Tasks                                                                           ║\n");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 12);
    printf("║    [5]  View Tasks by ID or Name                                                                 ║\n");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 14);
    printf("║    [6]  View Tasks by Project                                                                    ║\n");
    move_cursor(x, y + 15);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 16);
    printf("║    [7]  View Tasks by Status                                                                     ║\n");
    move_cursor(x, y + 17);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 18);
    printf("║    [8]  View Tasks by Priority                                                                   ║\n");
    move_cursor(x, y + 19);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 20);
    printf("║   [ESC] Back                                                                                     ║\n");
    move_cursor(x, y + 21);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 22);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 23);
    printf("║                                        PRESS YOUR CHOICE                                         ║\n");
    move_cursor(x, y + 24);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    // Take Input from user and validate that
    char choice;
    do
    {
        choice = get_input;
    } while ((choice < '1' || choice > '8') && choice != ESC);
    switch (choice)
    {
    case '1':
        create_task();
        task_management_dashboard();
        break;
    case '2':
        update_task();
        task_management_dashboard();
        break;
    case '3':
        delete_task();
        task_management_dashboard();
        break;
    case '4':
        view_tasks();
        task_management_dashboard();
        break;
    case '5':
        search_by_task_id_or_name();
        task_management_dashboard();
        break;
    case '6':
        view_tasks_by_project();
        task_management_dashboard();
        break;
    case '7':
        search_task_by_status();
        task_management_dashboard();
        break;
    case '8':
        search_task_by_priority();
        task_management_dashboard();
        break;
    case ESC:
        dashboard();
        break;
    }
    return 0;
}

int project_show_screen(int x, int y)
{
    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                                         PROJECT DETAILS                                          ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");

    /* Project ID */

    move_cursor(x, y + 3);
    printf("║    Project ID :                                                                                  ║");

    move_cursor(x, y + 4);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 5);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 6);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Project Name */

    move_cursor(x, y + 7);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 8);
    printf("║    Project Name :                                                                                ║");

    move_cursor(x, y + 9);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 10);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 11);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Category */

    move_cursor(x, y + 12);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 13);
    printf("║    Category :                                                                                    ║");

    move_cursor(x, y + 14);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 15);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 16);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Description */

    move_cursor(x, y + 17);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 18);
    printf("║    Description :                                                                                 ║");

    move_cursor(x, y + 19);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 20);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 21);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 22);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 23);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Priority */

    move_cursor(x, y + 24);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 25);
    printf("║    Priority :                                                                                    ║");

    move_cursor(x, y + 26);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 27);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 28);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Status */

    move_cursor(x, y + 29);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 30);
    printf("║    Status :                                                                                      ║");

    move_cursor(x, y + 31);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 32);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 33);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Start Date */

    move_cursor(x, y + 34);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 35);
    printf("║    Start Date (YYYY-MM-DD) :                                                                     ║");

    move_cursor(x, y + 36);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 37);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 38);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* End Date */

    move_cursor(x, y + 39);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 40);
    printf("║    End Date (YYYY-MM-DD) :                                                                       ║");

    move_cursor(x, y + 41);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 42);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 43);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Bottom */

    move_cursor(x, y + 44);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 45);
    printf("║                          [ ENTER ] Next Project        [ ESC ] Back                              ║");

    move_cursor(x, y + 46);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 47);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    return 0;
}

int task_update_dashboard(
    struct t_details *task,
    int x,
    int y)
{
    char choice;

    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                                         UPDATE TASK                                              ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 4);
    printf("║    Task ID      : %s                                                                          ║",
           task->task_id);

    move_cursor(x, y + 5);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 6);
    printf("║                              WHAT DO YOU WANT TO UPDATE?                                         ║");

    move_cursor(x, y + 7);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 8);
    printf("║       [ 1 ]  Task Name                                                                            ║");

    move_cursor(x, y + 9);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 10);
    printf("║       [ 2 ]  Description                                                                         ║");

    move_cursor(x, y + 11);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 12);
    printf("║       [ 3 ]  Priority                                                                            ║");

    move_cursor(x, y + 13);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 14);
    printf("║       [ 4 ]  Status                                                                              ║");

    move_cursor(x, y + 15);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 16);
    printf("║       [ 5 ]  Start Date                                                                          ║");

    move_cursor(x, y + 17);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 18);
    printf("║       [ 6 ]  End Date                                                                            ║");

    move_cursor(x, y + 19);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 20);
    printf("║       [ 7 ]  Back                                                                                ║");

    move_cursor(x, y + 21);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 22);
    printf("║                              Select an option :                                                  ║");

    move_cursor(x, y + 23);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 24);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    do
    {
        choice = get_input;

    } while ((choice < '1' || choice > '7') && choice != ESC);

    switch (choice)
    {
    case '1':

        change_task_name(task->name);

        break;

    case '2':

        change_task_description(task->description);

        break;

    case '3':

        change_task_priority(
            task->priority);

        break;

    case '4':

        change_task_status(
            task->status);

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
int task_status_dashboard(char status[], int x, int y)
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
    } while ((choice < '1' || choice > '4') && choice != ESC);
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
int project_status_dashboard(char status[], int x, int y)
{
    char choice;

    clear_screen();
    header_screen();

    move_cursor(x, y);

    printf("╔══════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                        PROJECT STATUS                            ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 3);
    printf("║                                                                  ║");

    move_cursor(x, y + 4);
    printf("║     [1]   Created                                                ║");

    move_cursor(x, y + 5);
    printf("║     [2]   In Progress                                            ║");

    move_cursor(x, y + 6);
    printf("║     [3]   Completed                                              ║");

    move_cursor(x, y + 7);
    printf("║     [4]   Cancelled                                              ║");

    move_cursor(x, y + 8);
    printf("║                                                                  ║");

    move_cursor(x, y + 9);
    printf("║     [ESC]  Back                                                  ║");

    move_cursor(x, y + 10);
    printf("║                                                                  ║");

    move_cursor(x, y + 11);
    printf("╠══════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 12);
    printf("║                     SELECT YOUR CHOICE                           ║");

    move_cursor(x, y + 13);
    printf("╚══════════════════════════════════════════════════════════════════╝");

    do
    {
        choice = get_input;

    } while ((choice < '1' || choice > '4') && choice != ESC);

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
int project_priority_dashboard(char priority[], int x, int y)
{
    char choice;

    clear_screen();
    header_screen();

    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                       PROJECT PRIORITY                           ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 3);
    printf("║                                                                  ║");

    move_cursor(x, y + 4);
    printf("║     [1]   High                                                   ║");

    move_cursor(x, y + 5);
    printf("║     [2]   Medium                                                 ║");

    move_cursor(x, y + 6);
    printf("║     [3]   Low                                                    ║");

    move_cursor(x, y + 7);
    printf("║                                                                  ║");

    move_cursor(x, y + 8);
    printf("║     [ESC]  Back                                                  ║");

    move_cursor(x, y + 9);
    printf("║                                                                  ║");

    move_cursor(x, y + 10);
    printf("╠══════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 11);
    printf("║                     SELECT YOUR CHOICE                           ║");

    move_cursor(x, y + 12);
    printf("╚══════════════════════════════════════════════════════════════════╝");

    do
    {
        choice = get_input;

    } while ((choice < '1' || choice > '3') && choice != ESC);

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
int task_priority_dashboard(char priority[], int x, int y)
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
    } while ((choice < '1' || choice > '3') && choice != ESC);
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
int report_dashboard()
{
    init_console();
    header_screen();
    int terminal_width = get_console_width();
    int terminal_height = get_console_height();
    int box_width = 100, box_height = 21;
    int x = (terminal_width - box_width) / 2, y = ((terminal_height - box_height) / 2) + 13;
    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    move_cursor(x, y + 1);
    printf("║                                              REPORTS                                             ║\n");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 4);
    printf("║    [1]  Project Summary Report                                                                   ║\n");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 6);
    printf("║    [2]  Task Summary Report                                                                      ║\n");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 8);
    printf("║    [3]  Completed Projects Report                                                                ║\n");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 10);
    printf("║    [4]  Pending Tasks Report                                                                     ║\n");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 12);
    printf("║    [5]  Overdue Tasks Report                                                                     ║\n");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 14);
    printf("║    [6]  High Priority Tasks Report                                                               ║\n");
    move_cursor(x, y + 15);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 16);
    printf("║   [ESC] Back                                                                                     ║\n");
    move_cursor(x, y + 17);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 18);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 19);
    printf("║                                        PRESS YOUR CHOICE                                         ║\n");
    move_cursor(x, y + 20);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    char choice;
    do
    {
        choice = get_input;
    } while ((choice < '1' || choice > '6') && choice != ESC);
    switch (choice)
    {
        // case '1':
        //     create_task();
        //     break;
        // case '2':
        //     update_task();
        //     break;
        // case '3':
        //     delete_task();
        //     break;
        // case '4':
        //     view_tasks();
        //     break;
        // case '5':
        //     search_by_task_id_or_name();
        //     break;
        // case '6':
        //     view_tasks_by_project();
        //     break;

    case ESC:
        dashboard();
        break;
    }
    return 0;
}
int search_dashboard()
{
    char choice;

    clear_screen();
    header_screen();

    printf("+-------------------------[ SEARCH ]----------------------------+\n");
    printf("|   [1]   -> Search Project by ID or Name                       |\n");
    printf("|   [2]   -> Search Task by ID or Name                          |\n");
    printf("|   [3]   -> Search by Status                                   |\n");
    printf("|   [4]   -> Search by Priority                                 |\n");
    printf("|  [ESC]  -> Back                                               |\n");
    printf("+--------------------[PRESS YOUR CHOICE]------------------------+\n");

    do
    {
        choice = get_input;
    } while ((choice < '1' || choice > '4') && choice != ESC);

    switch (choice)
    {
    case '1':
        search_by_project_id_or_name();
        break;

    case '2':
        search_by_task_id_or_name();
        break;

    case '3':
        search_project_by_status();
        break;

    case '4':
        search_project_by_priority();
        break;

    case ESC:
        dashboard();
        break;
    }

    return 0;
}

int show_project_screen(char id[],
                        char name[],
                        char category[],
                        char description[],
                        char priority[],
                        char status[],
                        char start_date[],
                        char end_date[],
                        char created_by[])
{
    clear_screen();
    header_screen();

    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                           PROJECT DETAILS                                   ║\n");
    printf("╠══════════════════════╦═══════════════════════════════════════════════════════╣\n");
    printf("║ Project ID           ║ %-53s ║\n", id);
    printf("║ Project Name         ║ %-53s ║\n", name);
    printf("║ Category             ║ %-53s ║\n", category);
    printf("║ Description          ║ %-53s ║\n", description);
    printf("║ Priority             ║ %-53s ║\n", priority);
    printf("║ Status               ║ %-53s ║\n", status);
    printf("║ Start Date           ║ %-53s ║\n", start_date);
    printf("║ End Date             ║ %-53s ║\n", end_date);
    printf("║ Created By           ║ %-53s ║\n", created_by);
    printf("╚══════════════════════╩═══════════════════════════════════════════════════════╝\n");

    printf("\n");
    printf("                [ ENTER ] Next Project        [ ESC ] Back\n");

    return 0;
}

// int want_to_go_back(int x, int y, char menu_code)
// {
//     char choice;
//     move_cursor(x, y + 0);
//     printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");

//     move_cursor(x, y + 1);
//     printf("║                              ARE YOU WANT TO CONTINUE?                                           ║");

//     move_cursor(x, y + 2);
//     printf("║                                                                                                  ║");

//     move_cursor(x, y + 3);
//     printf("║                               [ 1 ] YES                                            [ 2 ] NO      ║");

//     move_cursor(x, y + 4);
//     printf("║                                                                                                  ║");

//     move_cursor(x, y + 5);
//     printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

//     choice = get_input;

//     if (choice == '1')
//     {

//     }
//     else
//     {
//         switch (menu_code)
//         {
//         case MAIN_MENU:
//             redirecting_screen(x, y);
//             main_menu();
//             break;
//         case DASHBOARD:
//             redirecting_screen(x, y);
//             dashboard();
//             break;
//         case PROJECT_MENU:
//             redirecting_screen(x, y);
//             project_management_dashboard();
//             break;
//         case TASK_MENU:
//             redirecting_screen(x, y);
//             task_management_dashboard();
//             break;
//         case REPORT_MENU:
//             redirecting_screen(x, y);
//             report_dashboard();
//             break;
//         }
//     }
//             return 0;
// }
int create_task_screen(int x, int y)
{
    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                                         CREATE TASK                                             ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 4);
    printf("║    Task Name :                                                                                   ║");

    move_cursor(x, y + 5);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 6);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 7);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 8);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 9);
    printf("║    Description :                                                                                 ║");

    move_cursor(x, y + 10);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 11);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 12);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 13);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 14);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 15);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 16);
    printf("║    Priority :                                                                                    ║");

    move_cursor(x, y + 17);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 18);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 19);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 20);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 21);
    printf("║    Start Date (YYYY-MM-DD) :                                                                     ║");

    move_cursor(x, y + 22);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 23);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 24);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 25);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 26);
    printf("║    End Date (YYYY-MM-DD) :                                                                       ║");

    move_cursor(x, y + 27);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 28);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 29);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 30);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 31);
    printf("║                                       [ ENTER ] Create Task                                      ║");

    move_cursor(x, y + 32);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 33);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    return 0;
}
int task_details_screen(int x, int y)
{
    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                                           TASK DETAILS                                           ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");

    /* Unique Task ID */

    move_cursor(x, y + 3);
    printf("║    Unique Task ID :                                                                              ║");

    move_cursor(x, y + 4);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 5);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 6);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Task ID */

    move_cursor(x, y + 7);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 8);
    printf("║    Task ID :                                                                                     ║");

    move_cursor(x, y + 9);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 10);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 11);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Project ID */

    move_cursor(x, y + 12);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 13);
    printf("║    Project ID :                                                                                  ║");

    move_cursor(x, y + 14);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 15);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 16);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Task Name */

    move_cursor(x, y + 17);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 18);
    printf("║    Task Name :                                                                                   ║");

    move_cursor(x, y + 19);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 20);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 21);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Description */

    move_cursor(x, y + 22);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 23);
    printf("║    Description :                                                                                 ║");

    move_cursor(x, y + 24);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 25);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 26);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 27);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 28);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Priority */

    move_cursor(x, y + 29);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 30);
    printf("║    Priority :                                                                                    ║");

    move_cursor(x, y + 31);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 32);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 33);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Status */

    move_cursor(x, y + 34);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 35);
    printf("║    Status :                                                                                      ║");

    move_cursor(x, y + 36);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 37);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 38);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Start Date */

    move_cursor(x, y + 39);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 40);
    printf("║    Start Date (YYYY-MM-DD) :                                                                     ║");

    move_cursor(x, y + 41);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 42);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 43);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* End Date */

    move_cursor(x, y + 44);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 45);
    printf("║    End Date (YYYY-MM-DD) :                                                                       ║");

    move_cursor(x, y + 46);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 47);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 48);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Bottom */

    move_cursor(x, y + 49);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 50);
    printf("║                          [ ENTER ] Next Task             [ ESC ] Back                            ║");

    move_cursor(x, y + 51);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 52);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    return 0;
}
int task_details_screen_for_separate_project(int x, int y)
{
    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                                           TASK DETAILS                                           ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");

    /* Unique Task ID */

    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 4);
    printf("║    Task ID :                                                                                     ║");

    move_cursor(x, y + 5);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 6);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 7);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Project ID */

    move_cursor(x, y + 8);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 9);
    printf("║    Project ID :                                                                                  ║");

    move_cursor(x, y + 10);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 11);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 12);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Task Name */

    move_cursor(x, y + 13);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 14);
    printf("║    Task Name :                                                                                   ║");

    move_cursor(x, y + 15);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 16);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 17);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Description */

    move_cursor(x, y + 18);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 19);
    printf("║    Description :                                                                                 ║");

    move_cursor(x, y + 20);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 21);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 22);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 23);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 24);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Priority */

    move_cursor(x, y + 25);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 26);
    printf("║    Priority :                                                                                    ║");

    move_cursor(x, y + 27);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 28);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 29);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Status */

    move_cursor(x, y + 30);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 31);
    printf("║    Status :                                                                                      ║");

    move_cursor(x, y + 32);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 33);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 34);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Start Date */

    move_cursor(x, y + 35);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 46);
    printf("║    Start Date (YYYY-MM-DD) :                                                                     ║");

    move_cursor(x, y + 37);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 38);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 39);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* End Date */

    move_cursor(x, y + 40);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 41);
    printf("║    End Date (YYYY-MM-DD) :                                                                       ║");

    move_cursor(x, y + 42);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 43);
    printf("║    │                                                                                        │    ║");

    move_cursor(x, y + 45);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");

    /* Bottom */

    move_cursor(x, y + 46);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 47);
    printf("║                          [ ENTER ] Next Task             [ ESC ] Back                            ║");

    move_cursor(x, y + 48);
    printf("║                                                                                                  ║");

    move_cursor(x, y + 49);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    return 0;
}
int search_task_by_id_or_name_screen(int x, int y)
{
    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                                SEARCH TASK                                                    ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 3);
    printf("║    Task ID or Name :                                                                          ║");

    move_cursor(x, y + 4);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 5);
    printf("║    │                                                                                    │    ║");

    move_cursor(x, y + 6);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 7);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝");

    move_cursor(x + 24, y + 5);

    return 0;
}
int change_task_name_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                               UPDATE TASK NAME                                               ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 3);
    printf("║                                                                                              ║");

    move_cursor(x, y + 4);
    printf("║    New Task Name :                                                                          ║");

    move_cursor(x, y + 5);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 6);
    printf("║    │                                                                                    │    ║");

    move_cursor(x, y + 7);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 8);
    printf("║                                                                                              ║");

    move_cursor(x, y + 9);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝");

    move_cursor(x + 24, y + 6);

    return 0;
}
int change_task_description_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                           UPDATE TASK DESCRIPTION                                            ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 3);
    printf("║                                                                                              ║");

    move_cursor(x, y + 4);
    printf("║    New Description :                                                                        ║");

    move_cursor(x, y + 5);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 6);
    printf("║    │                                                                                    │    ║");

    move_cursor(x, y + 7);
    printf("║    │                                                                                    │    ║");

    move_cursor(x, y + 8);
    printf("║    │                                                                                    │    ║");

    move_cursor(x, y + 9);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 10);
    printf("║                                                                                              ║");

    move_cursor(x, y + 11);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝");

    move_cursor(x + 8, y + 6);

    return 0;
}
int change_task_start_date_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                              UPDATE START DATE                                               ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 3);
    printf("║                                                                                              ║");

    move_cursor(x, y + 4);
    printf("║    New Start Date (YYYY-MM-DD) :                                                           ║");

    move_cursor(x, y + 5);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 6);
    printf("║    │                                                                                    │    ║");

    move_cursor(x, y + 7);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 8);
    printf("║                                                                                              ║");

    move_cursor(x, y + 9);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝");

    move_cursor(x + 24, y + 6);

    return 0;
}
int extend_task_deadline_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");

    move_cursor(x, y + 1);
    printf("║                               UPDATE END DATE                                                ║");

    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");

    move_cursor(x, y + 3);
    printf("║                                                                                              ║");

    move_cursor(x, y + 4);
    printf("║    New End Date (YYYY-MM-DD) :                                                             ║");

    move_cursor(x, y + 5);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────┐    ║");

    move_cursor(x, y + 6);
    printf("║    │                                                                                    │    ║");

    move_cursor(x, y + 7);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────┘    ║");

    move_cursor(x, y + 8);
    printf("║                                                                                              ║");

    move_cursor(x, y + 9);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝");

    move_cursor(x + 24, y + 6);

    return 0;
}
