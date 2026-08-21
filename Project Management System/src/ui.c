/*
    NAME : SALAMOON HIYA ELINE
    ID : 2026-2-60-537
*/

/*
    unicode use for ui

    ( ╔ ) U+2554  https://www.compart.com/en/unicode/U+2554
    ( ═ ) U+2550  https://www.compart.com/en/unicode/U+2550
    ( ╗ ) U+2557  https://www.compart.com/en/unicode/U+2557
    ( ║ ) U+2551  https://www.compart.com/en/unicode/U+2551
    ( ╠ ) U+2560  https://www.compart.com/en/unicode/U+2560
    ( ╣ ) U+2563  https://www.compart.com/en/unicode/U+2563
    ( ╚ ) U+255A  https://www.compart.com/en/unicode/U+255A
    ( ╝ ) U+255D  https://www.compart.com/en/unicode/U+255D

*/

#include "ui.h"

// main menu UI START
int header_screen()
{
    init_console();
    clear_screen();
    int terminal_width = get_console_width(), terminal_height = get_console_height(), box_width = 100, box_height = 13, x = (terminal_width - box_width) / 2, y = 1, found = 0;
    char row[MAX_LENGTH_OF_DATA_IN_FILE];
    FILE *log_open;

    log_open = fopen("..\\database\\log.csv", "r");

    if (log_open != NULL)
    {
        if (fgets(row, sizeof(row), log_open) != NULL)
        {
            found = 1;
        }

        fclose(log_open);
    }

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 2);
    printf("║                              ██████╗      ███╗   ███╗       ███████╗                             ║");
    move_cursor(x, y + 3);
    printf("║                              ██╔══██╗     ████╗ ████║       ██╔════╝                             ║");
    move_cursor(x, y + 4);
    printf("║                              ██████╔╝     ██╔████╔██║       ███████╗                             ║");
    move_cursor(x, y + 5);
    printf("║                              ██╔═══╝      ██║╚██╔╝██║       ╚════██║                             ║");
    move_cursor(x, y + 6);
    printf("║                              ██║     ██   ██║ ╚═╝ ██║  ██   ███████║                             ║");
    move_cursor(x, y + 7);
    printf("║                              ╚═╝          ╚═╝     ╚═╝      ╚══════╝                              ║");
    move_cursor(x, y + 8);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 9);
    printf("║                                    PROJECT MANAGEMENT SYSTEM                                     ║");
    move_cursor(x, y + 10);
    printf("║                                Plan • Organize • Track • Complete                                ║");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 12);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    date_time_before_login(x, y + 13);

    return 0;
}

int main_menu()
{
    char choice;

    while (1)
    {
        init_console();
        header_screen();

        int terminal_width = get_console_width(), terminal_height = get_console_height(), box_width = 100, box_height = 14,x = (terminal_width - box_width) / 2, y = ((terminal_height - box_height) / 2) + 13;

        move_cursor(x, y + 0);
        printf("╔══════════════════════════════════════════[ MAIN  MENU ]══════════════════════════════════════════╗");
        move_cursor(x, y + 1);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 2);
        printf("║   [1]  Register                                                                                  ║");
        move_cursor(x, y + 3);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 4);
        printf("║   [2]  Login                                                                                     ║");
        move_cursor(x, y + 5);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 6);
        printf("║   [3]  Forgot Password                                                                           ║");
        move_cursor(x, y + 7);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 8);
        printf("║  [ESC] Exit                                                                                      ║");
        move_cursor(x, y + 9);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 10);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 11);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
        move_cursor(x, y + 12);
        printf("║                                        PRESS YOUR CHOICE                                         ║");
        move_cursor(x, y + 13);
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

        do
        {
            choice = get_input;
        } while ((choice < '1' || choice > '3') && choice != ESC);

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
        case ESC:
            exit(1);
        }
    }

    return 0;
}
// main menu UI END

// dashboard UI start
int dashboard()
{
    sort_projects();
    sort_tasks();
    // declare all variables
    char choice;
    int terminal_width, terminal_height, box_width = 100, box_height = 19, x, y;

    while (1)
    {
        clear_screen();
        header_screen();

        // measure terminal height and width also x and y coordinate
        terminal_width = get_console_width();
        terminal_height = get_console_height();

        x = (terminal_width - box_width) / TWO;
        y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

        move_cursor(x, y + 0);
        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
        move_cursor(x, y + 1);
        printf("║                                             DASHBOARD                                            ║");
        move_cursor(x, y + 2);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
        move_cursor(x, y + 3);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 4);
        printf("║    [1]  Project Management                                                                       ║");
        move_cursor(x, y + 5);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 6);
        printf("║    [2]  Task Management                                                                          ║");
        move_cursor(x, y + 7);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 8);
        printf("║    [3]  Reports                                                                                  ║");
        move_cursor(x, y + 9);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 10);
        printf("║    [4]  Search                                                                                   ║");
        move_cursor(x, y + 11);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 12);
        printf("║    [5]  Profile                                                                                  ║");
        move_cursor(x, y + 13);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 14);
        printf("║   [ESC] Logout                                                                                   ║");
        move_cursor(x, y + 15);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 16);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
        move_cursor(x, y + 17);
        printf("║                                         PRESS YOUR CHOICE                                        ║");
        move_cursor(x, y + 18);
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

        // get user choice
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
        case '5':
            view_profile();
            break;
        case ESC:
            logout();
            return 0;
        }
    }

    return 0;
}
// dashboard UI end

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

    redirecting_screen(x, y);
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

    redirecting_screen(x, y);

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

    redirecting_screen(x, y);
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

    redirecting_screen(x, y);
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

    redirecting_screen(x, y);
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

    redirecting_screen(x, y);
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
    // declare all variables
    char choice;
    int terminal_width, terminal_height, box_width = 100, box_height = 23, x, y;

    // set terminal to UTF8
    init_console();

    while (1)
    {
        // sort projects
        sort_projects();

        clear_screen();
        header_screen();

        // measure terminal height and width also x and y coordinate
        terminal_width = get_console_width();
        terminal_height = get_console_height();

        x = (terminal_width - box_width) / TWO;
        y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

        move_cursor(x, y + 0);
        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
        move_cursor(x, y + 1);
        printf("║                                        PROJECT MANAGEMENT                                        ║");
        move_cursor(x, y + 2);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
        move_cursor(x, y + 3);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 4);
        printf("║    [1]  Create Project                                                                           ║");
        move_cursor(x, y + 5);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 6);
        printf("║    [2]  Update Project                                                                           ║");
        move_cursor(x, y + 7);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 8);
        printf("║    [3]  Delete Project                                                                           ║");
        move_cursor(x, y + 9);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 10);
        printf("║    [4]  View All Projects                                                                        ║");
        move_cursor(x, y + 11);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 12);
        printf("║    [5]  Search Project                                                                           ║");
        move_cursor(x, y + 13);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 14);
        printf("║    [6]  View Projects by Status                                                                  ║");
        move_cursor(x, y + 15);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 16);
        printf("║    [7]  View Projects by Priority                                                                ║");
        move_cursor(x, y + 17);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 18);
        printf("║   [ESC] Back                                                                                     ║");
        move_cursor(x, y + 19);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 20);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
        move_cursor(x, y + 21);
        printf("║                                        PRESS YOUR CHOICE                                         ║");
        move_cursor(x, y + 22);
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

        // get user choice
        do
        {
            choice = get_input;

        } while ((choice < '1' || choice > '7') && choice != ESC);

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
        case '6':
            search_project_by_status();
            break;
        case '7':
            search_project_by_priority();
            break;
        case ESC:
            return 0;
        }
    }

    return 0;
}

int create_project_screen(int x, int y)
{
    clear_screen();
    header_screen();

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
    clear_screen();
    header_screen();

    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                          SEARCH PROJECT                                          ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║    Project ID or Name :                                                                          ║");
    move_cursor(x, y + 4);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");
    move_cursor(x, y + 5);
    printf("║    │                                                                                        │    ║");
    move_cursor(x, y + 6);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");
    move_cursor(x, y + 7);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    return 0;
}

int update_project_dashboard(struct p_details *project, int x, int y, int priority_x, int priority_y)
{
    char choice;
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                          UPDATE PROJECT                                          ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("║    Project ID   : %s                                                                          ║", project->id);
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 6);
    printf("║                                   WHAT DO YOU WANT TO UPDATE?                                    ║");
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
    printf("║       [ ESC ]  Back                                                                              ║");
    move_cursor(x, y + 23);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 24);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 25);
    printf("║                                        PRESS YOUR CHOICE                                         ║\n");
    move_cursor(x, y + 26);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    do
    {
        choice = get_input;

    } while ((choice < '1' || choice > '7') && choice != ESC);

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
        project_priority_dashboard(project->priority, priority_x, priority_y);
        break;

    case '5':
        project_status_dashboard(project->status, priority_x, priority_y);
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
    printf("║                                     UPDATE PROJECT NAME                                      ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                              ║");
    move_cursor(x, y + 4);
    printf("║    New Project Name :                                                                        ║");
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

    return 0;
}

int change_project_category_screen(int x, int y)
{
    clear_screen();
    header_screen();
    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                   UPDATE PROJECT CATEGORY                                    ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                              ║");
    move_cursor(x, y + 4);
    printf("║    New Category :                                                                            ║");
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

    return 0;
}

int change_project_description_screen(int x, int y)
{
    clear_screen();
    header_screen();
    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                   UPDATE PROJECT DESCRIPTION                                 ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                              ║");
    move_cursor(x, y + 4);
    printf("║    New Description :                                                                         ║");
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

    return 0;
}

int change_project_start_date_screen(int x, int y)
{
    clear_screen();
    header_screen();
    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                       UPDATE START DATE                                      ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                              ║");
    move_cursor(x, y + 4);
    printf("║    New Start Date (YYYY-MM-DD) :                                                             ║");
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

    return 0;
}

int extend_project_deadline_screen(int x, int y)
{
    clear_screen();
    header_screen();
    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                        UPDATE END DATE                                       ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                              ║");
    move_cursor(x, y + 4);
    printf("║    New End Date (YYYY-MM-DD) :                                                               ║");
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

    return 0;
}

int project_show_screen(int x, int y)
{
    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                          PROJECT DETAILS                                         ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║    Project ID :                                                                                  ║");
    move_cursor(x, y + 4);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");
    move_cursor(x, y + 5);
    printf("║    │                                                                                        │    ║");
    move_cursor(x, y + 6);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");
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
    move_cursor(x, y + 44);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 45);
    printf("║                                      [ ENTER ] Next Project                                      ║");
    move_cursor(x, y + 46);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 47);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    return 0;
}

int project_status_dashboard(char status[], int x, int y)
{
    char choice;

    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                          PROJECT STATUS                                          ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("║    [1]  Created                                                                                  ║");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 6);
    printf("║    [2]  In Progress                                                                              ║");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 8);
    printf("║    [3]  Completed                                                                                ║");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 10);
    printf("║    [4]  Cancelled                                                                                ║");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 12);
    printf("║   [ESC] Back                                                                                     ║");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 14);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 15);
    printf("║                                         PRESS YOUR CHOICE                                        ║");
    move_cursor(x, y + 16);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

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

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                        PROJECT PRIORITY                                          ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("║    [1]  High                                                                                     ║");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 6);
    printf("║    [2]  Medium                                                                                   ║");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 8);
    printf("║    [3]  Low                                                                                      ║");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 10);
    printf("║   [ESC] Back                                                                                     ║");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 12);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 13);
    printf("║                                         PRESS YOUR CHOICE                                        ║");
    move_cursor(x, y + 14);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

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

int project_created_successful(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 2);
    printf("║                                   PROJECT CREATED SUCCESSFULLY                                   ║");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    pause_screen(1000);

    redirecting_screen(x, y);
    return 0;
}

int project_deleted_successful(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 2);
    printf("║                                   PROJECT DELETED SUCCESSFULLY                                   ║");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    pause_screen(1000);

    redirecting_screen(x, y);
    return 0;
}

int project_update_successful(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 2);
    printf("║                                    PROJECT UPDATED SUCCESSFULLY                                  ║");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    pause_screen(1000);

    redirecting_screen(x, y);

    return 0;
}

int project_not_found(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 2);
    printf("║                                         PROJECT NOT FOUND                                        ║");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    pause_screen(1000);

    redirecting_screen(x, y);
    return 0;
}
// project.c UI END

// task.c UI START
int task_management_dashboard()
{
    // declare all variables
    char choice;
    int terminal_width, terminal_height, box_width = 100, box_height = 25, x, y;

    while (1)
    {
        // sort tasks
        sort_tasks();

        clear_screen();
        header_screen();

        // measure terminal height and width also x and y coordinate
        terminal_width = get_console_width();
        terminal_height = get_console_height();

        x = (terminal_width - box_width) / TWO;
        y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

        move_cursor(x, y + 0);
        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
        move_cursor(x, y + 1);
        printf("║                                         TASK MANAGEMENT                                          ║");
        move_cursor(x, y + 2);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
        move_cursor(x, y + 3);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 4);
        printf("║    [1]  Create Task                                                                              ║");
        move_cursor(x, y + 5);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 6);
        printf("║    [2]  Update Task                                                                              ║");
        move_cursor(x, y + 7);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 8);
        printf("║    [3]  Delete Task                                                                              ║");
        move_cursor(x, y + 9);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 10);
        printf("║    [4]  View All Tasks                                                                           ║");
        move_cursor(x, y + 11);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 12);
        printf("║    [5]  View Tasks by Name                                                                       ║");
        move_cursor(x, y + 13);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 14);
        printf("║    [6]  View Tasks by Project                                                                    ║");
        move_cursor(x, y + 15);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 16);
        printf("║    [7]  View Tasks by Status                                                                     ║");
        move_cursor(x, y + 17);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 18);
        printf("║    [8]  View Tasks by Priority                                                                   ║");
        move_cursor(x, y + 19);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 20);
        printf("║   [ESC] Back                                                                                     ║");
        move_cursor(x, y + 21);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 22);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
        move_cursor(x, y + 23);
        printf("║                                        PRESS YOUR CHOICE                                         ║");
        move_cursor(x, y + 24);
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

        // get user choice
        do
        {
            choice = get_input;
        } while ((choice < '1' || choice > '8') && choice != ESC);

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
            return 0;
        }
    }

    return 0;
}

int create_task_screen(int x, int y)
{
    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                           CREATE TASK                                            ║");
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

int task_update_successful(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 2);
    printf("║                                      TASK UPDATED SUCCESSFULLY                                   ║");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    pause_screen(1000);

    redirecting_screen(x, y);

    return 0;
}

int search_task_by_id_or_name_screen(int x, int y)
{
    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                           SEARCH TASK                                            ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║    Task ID or Name :                                                                             ║");
    move_cursor(x, y + 4);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");
    move_cursor(x, y + 5);
    printf("║    │                                                                                        │    ║");
    move_cursor(x, y + 6);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");
    move_cursor(x, y + 7);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    return 0;
}

int task_update_dashboard(struct t_details *task, int x, int y)
{
    char choice;

    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                           UPDATE TASK                                            ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("║    Task ID      : %s                                                                          ║", task->task_id);
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 6);
    printf("║                                    WHAT DO YOU WANT TO UPDATE?                                   ║");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 8);
    printf("║       [ 1 ]  Task Name                                                                           ║");
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
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 22);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 23);
    printf("║                                        PRESS YOUR CHOICE                                         ║\n");
    move_cursor(x, y + 24);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

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

int change_task_name_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                       UPDATE TASK NAME                                       ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                              ║");
    move_cursor(x, y + 4);
    printf("║    New Task Name :                                                                           ║");
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

    return 0;
}

int change_task_description_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                    UPDATE TASK DESCRIPTION                                   ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                              ║");
    move_cursor(x, y + 4);
    printf("║    New Description :                                                                         ║");
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

    return 0;
}

int change_task_start_date_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                       UPDATE START DATE                                      ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                              ║");
    move_cursor(x, y + 4);
    printf("║    New Start Date (YYYY-MM-DD) :                                                             ║");
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

    return 0;
}

int extend_task_deadline_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                       UPDATE END DATE                                        ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                              ║");
    move_cursor(x, y + 4);
    printf("║    New End Date (YYYY-MM-DD) :                                                               ║");
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
    move_cursor(x, y + 3);
    printf("║    Unique Task ID :                                                                              ║");
    move_cursor(x, y + 4);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");
    move_cursor(x, y + 5);
    printf("║    │                                                                                        │    ║");
    move_cursor(x, y + 6);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");
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
    move_cursor(x, y + 49);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 50);
    printf("║                           [ ENTER ] Next Task             [ ESC ] Back                           ║");
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

int task_status_dashboard(char status[], int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                            TASK STATUS                                           ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("║    [1]  Created                                                                                  ║");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 6);
    printf("║    [2]  In Progress                                                                              ║");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 8);
    printf("║    [3]  Completed                                                                                ║");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 10);
    printf("║    [4]  Cancelled                                                                                ║");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 12);
    printf("║   [ESC] Back                                                                                     ║");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 14);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 15);
    printf("║                                        PRESS YOUR CHOICE                                         ║");
    move_cursor(x, y + 16);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

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

int task_priority_dashboard(char priority[], int x, int y)
{
    char choice;

    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                          TASK PRIORITY                                           ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("║    [1]  High                                                                                     ║");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 6);
    printf("║    [2]  Medium                                                                                   ║");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 8);
    printf("║    [3]  Low                                                                                      ║");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 10);
    printf("║   [ESC] Back                                                                                     ║");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 12);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 13);
    printf("║                                         PRESS YOUR CHOICE                                        ║");
    move_cursor(x, y + 14);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

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
    }

    return 0;
}

int task_created_successfully(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 2);
    printf("║                                    TASK CREATED SUCCESSFULLY                                     ║");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    pause_screen(1000);

    redirecting_screen(x, y);

    return 0;
}

int task_not_found(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 2);
    printf("║                                          TASK NOT FOUND                                          ║");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    pause_screen(1000);

    redirecting_screen(x, y);

    return 0;
}

int task_deleted_successful(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 2);
    printf("║                                    TASK DELETED SUCCESSFULLY                                     ║");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    pause_screen(1000);

    redirecting_screen(x, y);
    return 0;
}
// task.c UI END

// report.c UI Start
int report_dashboard()
{
    // declare all variables
    int terminal_width = ZERO, terminal_height = ZERO,box_width = 100, box_height = 27, x = ZERO, y = ZERO;
    char choice;

    while (1)
    {
        clear_screen();
        header_screen();

        // measure terminal height and width also x and y coordinate
        terminal_width = get_console_width();
        terminal_height = get_console_height();
        x = (terminal_width - box_width) / TWO;
        y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

        move_cursor(x, y + 0);
        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
        move_cursor(x, y + 1);
        printf("║                                              REPORTS                                             ║");
        move_cursor(x, y + 2);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
        move_cursor(x, y + 3);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 4);
        printf("║    [1]  Project Summary Report                                                                   ║");
        move_cursor(x, y + 5);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 6);
        printf("║    [2]  Project Progress Report                                                                  ║");
        move_cursor(x, y + 7);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 8);
        printf("║    [3]  Overdue Projects Report                                                                  ║");
        move_cursor(x, y + 9);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 10);
        printf("║    [4]  High Priority Projects Report                                                            ║");
        move_cursor(x, y + 11);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 12);
        printf("║    [5]  Task Summary Report                                                                      ║");
        move_cursor(x, y + 13);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 14);
        printf("║    [6]  Overdue Tasks Report                                                                     ║");
        move_cursor(x, y + 15);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 16);
        printf("║    [7]  High Priority Tasks Report                                                               ║");
        move_cursor(x, y + 17);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 18);
        printf("║    [8]  Pending / Active Tasks Report                                                            ║");
        move_cursor(x, y + 19);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 20);
        printf("║   [ESC] Back                                                                                     ║");
        move_cursor(x, y + 21);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 22);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
        move_cursor(x, y + 23);
        printf("║                                        PRESS YOUR CHOICE                                         ║");
        move_cursor(x, y + 24);
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

        // get user choice
        do
        {
            choice = get_input;

        } while ((choice < '1' || choice > '8') && choice != ESC);

        switch (choice)
        {
        case '1':
            project_summary_report();
            break;
        case '2':
            project_progress_report();
            break;
        case '3':
            overdue_projects_report();
            break;
        case '4':
            high_priority_projects_report();
            break;
        case '5':
            task_summary_report();
            break;
        case '6':
            overdue_tasks_report();
            break;
        case '7':
            high_priority_tasks_report();
            break;
        case '8':
            pending_active_tasks_report();
            break;
        case ESC:
            return 0;
        }
    }

    return 0;
}

int project_summary_report_screen(int x, int y)
{
    init_console();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    move_cursor(x, y + 1);
    printf("║                                         PROJECT SUMMARY                                          ║\n");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 4);
    printf("║    Total Projects       :                                                                        ║\n");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 6);
    printf("║    Created Projects     :                                                                        ║\n");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 8);
    printf("║    In Progress Projects :                                                                        ║\n");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 10);
    printf("║    Completed Projects   :                                                                        ║\n");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 12);
    printf("║    Cancelled Projects   :                                                                        ║\n");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 14);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 15);
    printf("║                                         [ ENTER ]  Next                                          ║\n");
    move_cursor(x, y + 16);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    return 0;
}

int project_progress_report_screen(int x, int y)
{
    init_console();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                         PROJECT PROGRESS                                         ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("║    Project ID          :                                                                         ║");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 6);
    printf("║    Project Name        :                                                                         ║");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 8);
    printf("║    Total Tasks         :                                                                         ║");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 10);
    printf("║    Completed Tasks     :                                                                         ║");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 12);
    printf("║    Progress            :                                                                         ║");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 14);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 15);
    printf("║                                         [ ENTER ]  Next                                          ║");
    move_cursor(x, y + 16);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    return 0;
}

int overdue_projects_report_screen(int x, int y)
{
    init_console();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    move_cursor(x, y + 1);
    printf("║                                        OVERDUE PROJECTS                                          ║\n");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 4);
    printf("║    Project ID   :                                                                                ║\n");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 6);
    printf("║    Project Name :                                                                                ║\n");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 8);
    printf("║    Priority     :                                                                                ║\n");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 10);
    printf("║    Status       :                                                                                ║\n");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 12);
    printf("║    Deadline     :                                                                                ║\n");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 14);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 15);
    printf("║                                         [ ENTER ]  Next                                          ║\n");
    move_cursor(x, y + 16);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    return 0;
}

int high_priority_projects_report_screen(int x, int y)
{
    init_console();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    move_cursor(x, y + 1);
    printf("║                                     HIGH PRIORITY PROJECTS                                       ║\n");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 4);
    printf("║    Project ID   :                                                                                ║\n");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 6);
    printf("║    Project Name :                                                                                ║\n");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 8);
    printf("║    Priority     :                                                                                ║\n");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 10);
    printf("║    Status       :                                                                                ║\n");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 12);
    printf("║    Deadline     :                                                                                ║\n");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 14);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 15);
    printf("║                                         [ ENTER ]  Next                                          ║\n");
    move_cursor(x, y + 16);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    return 0;
}

int task_summary_report_screen(int x, int y)
{
    init_console();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    move_cursor(x, y + 1);
    printf("║                                           TASK SUMMARY                                           ║\n");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 4);
    printf("║    Total Tasks       :                                                                           ║\n");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 6);
    printf("║    Pending Tasks     :                                                                           ║\n");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 8);
    printf("║    Planning Tasks    :                                                                           ║\n");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 10);
    printf("║    In Progress Tasks :                                                                           ║\n");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 12);
    printf("║    Completed Tasks   :                                                                           ║\n");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 14);
    printf("║    Cancelled Tasks   :                                                                           ║\n");
    move_cursor(x, y + 15);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 16);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 17);
    printf("║                                         [ ENTER ]  Next                                          ║\n");
    move_cursor(x, y + 18);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    return 0;
}

int overdue_tasks_report_screen(int x, int y)
{
    init_console();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    move_cursor(x, y + 1);
    printf("║                                          OVERDUE TASKS                                           ║\n");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 4);
    printf("║    Task ID      :                                                                                ║\n");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 6);
    printf("║    Task Name    :                                                                                ║\n");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 8);
    printf("║    Project ID   :                                                                                ║\n");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 10);
    printf("║    Priority     :                                                                                ║\n");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 12);
    printf("║    Status       :                                                                                ║\n");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 14);
    printf("║    Deadline     :                                                                                ║\n");
    move_cursor(x, y + 15);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 16);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 17);
    printf("║                                         [ ENTER ]  Next                                          ║\n");
    move_cursor(x, y + 18);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    return 0;
}

int high_priority_tasks_report_screen(int x, int y)
{
    init_console();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    move_cursor(x, y + 1);
    printf("║                                       HIGH PRIORITY TASKS                                        ║\n");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 4);
    printf("║    Task ID      :                                                                                ║\n");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 6);
    printf("║    Task Name    :                                                                                ║\n");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 8);
    printf("║    Project ID   :                                                                                ║\n");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 10);
    printf("║    Priority     :                                                                                ║\n");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 12);
    printf("║    Status       :                                                                                ║\n");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 14);
    printf("║    Deadline     :                                                                                ║\n");
    move_cursor(x, y + 15);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 16);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 17);
    printf("║                                         [ ENTER ]  Next                                          ║\n");
    move_cursor(x, y + 18);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    return 0;
}

int pending_active_tasks_screen(int x, int y)
{
    init_console();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    move_cursor(x, y + 1);
    printf("║                                      PENDING / ACTIVE TASKS                                      ║\n");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 4);
    printf("║    Task ID      :                                                                                ║\n");
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 6);
    printf("║    Task Name    :                                                                                ║\n");
    move_cursor(x, y + 7);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 8);
    printf("║    Project ID   :                                                                                ║\n");
    move_cursor(x, y + 9);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 10);
    printf("║    Priority     :                                                                                ║\n");
    move_cursor(x, y + 11);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 12);
    printf("║    Status       :                                                                                ║\n");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 14);
    printf("║    Deadline     :                                                                                ║\n");
    move_cursor(x, y + 15);
    printf("║                                                                                                  ║\n");
    move_cursor(x, y + 16);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    move_cursor(x, y + 17);
    printf("║                                         [ ENTER ]  Next                                          ║\n");
    move_cursor(x, y + 18);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    return 0;
}
// report.c UI END

int search_dashboard()
{
    // declare all variables
    char choice;
    int terminal_width, terminal_height, box_width = 100, box_height = 23, x, y;

    // set terminal to UTF8
    init_console();

    while (1)
    {
        header_screen();

        // measure terminal height and width also x and y coordinate
        terminal_width = get_console_width();
        terminal_height = get_console_height();
        x = (terminal_width - box_width) / TWO;
        y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

        move_cursor(x, y + 0);
        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
        move_cursor(x, y + 1);
        printf("║                                           SEARCH                                                 ║");
        move_cursor(x, y + 2);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
        move_cursor(x, y + 3);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 4);
        printf("║    [1]  Search Project by ID or Name                                                             ║");
        move_cursor(x, y + 5);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 6);
        printf("║    [2]  Search Task by Name                                                                      ║");
        move_cursor(x, y + 7);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 8);
        printf("║    [3]                                                                                           ║");
        move_cursor(x, y + 9);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 10);
        printf("║    [4]                                                                                           ║");
        move_cursor(x, y + 11);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 12);
        printf("║   [ESC] Back                                                                                     ║");
        move_cursor(x, y + 13);
        printf("║                                                                                                  ║");
        move_cursor(x, y + 14);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
        move_cursor(x, y + 15);
        printf("║                                         PRESS YOUR CHOICE                                        ║");
        move_cursor(x, y + 16);
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

        // get user choice
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
            return 0;
        }
    }

    return 0;
}

int profile_screen(int x, int y)
{
    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                             PROFILE                                              ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("║    User ID :                                                                                     ║");
    move_cursor(x, y + 5);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");
    move_cursor(x, y + 6);
    printf("║    │                                                                                        │    ║");
    move_cursor(x, y + 7);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");
    move_cursor(x, y + 8);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 9);
    printf("║    Username :                                                                                    ║");
    move_cursor(x, y + 10);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");
    move_cursor(x, y + 11);
    printf("║    │                                                                                        │    ║");
    move_cursor(x, y + 12);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");
    move_cursor(x, y + 13);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 14);
    printf("║    Full Name :                                                                                   ║");
    move_cursor(x, y + 15);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");
    move_cursor(x, y + 16);
    printf("║    │                                                                                        │    ║");
    move_cursor(x, y + 17);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");
    move_cursor(x, y + 18);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 19);
    printf("║    Email Address :                                                                               ║");
    move_cursor(x, y + 20);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");
    move_cursor(x, y + 21);
    printf("║    │                                                                                        │    ║");
    move_cursor(x, y + 22);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");
    move_cursor(x, y + 23);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 24);
    printf("║    Phone Number :                                                                                ║");
    move_cursor(x, y + 25);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");
    move_cursor(x, y + 26);
    printf("║    │                                                                                        │    ║");
    move_cursor(x, y + 27);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");
    move_cursor(x, y + 28);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 29);
    printf("║    Role :                                                                                        ║");
    move_cursor(x, y + 30);
    printf("║    ┌────────────────────────────────────────────────────────────────────────────────────────┐    ║");
    move_cursor(x, y + 31);
    printf("║    │                                                                                        │    ║");
    move_cursor(x, y + 32);
    printf("║    └────────────────────────────────────────────────────────────────────────────────────────┘    ║");
    move_cursor(x, y + 33);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 34);
    printf("║                                           [ ESC ] Back                                           ║");
    move_cursor(x, y + 35);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 36);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    return 0;
}

int something_went_wrong_screen(enum error_type error)
{
    int terminal_width = ZERO, terminal_height = ZERO,box_width = 100,box_height = 27, x = ZERO, y = ZERO;

    init_console();
    header_screen();
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    clear_screen();
    header_screen();

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║                                       SOMETHING WENT WRONG                                       ║");
    move_cursor(x, y + 2);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣");
    move_cursor(x, y + 3);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 4);
    printf("║                                  ERROR : %s ║", get_error_message(error));
    move_cursor(x, y + 5);
    printf("║                                                                                                  ║");
    move_cursor(x, y + 6);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    pause_screen(2000);

    exit(1);

    return 0;
}

char *get_error_message(enum error_type error)
{
    switch (error)
    {
    case FILE_OPEN_ERROR:
        return "FILE OPEN ERROR";

    case FILE_CLOSE_ERROR:
        return "FILE CLOSE ERROR";

    case SOMETHING_FAILED:
        return "SOMETHING FAILED";

    default:
        return "UNKNOWN ERROR";
    }
}

int date_time_before_login(int x, int y)
{
    char date[15];

    current_date(date);

    move_cursor(x, y + 0);
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗");
    move_cursor(x, y + 1);
    printf("║  DATE : %s                                                              TIME :           ║", date);
    move_cursor(x + 89, y + 1);
    current_time();
    move_cursor(x, y + 2);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝");

    static int position[2];

    position[0] = x;
    position[1] = y;

    _beginthread(live_clock, 0, position);

    return 0;
}
