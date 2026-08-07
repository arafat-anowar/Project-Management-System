#include "utility.h"

int user_registration_screen()
{
    return 0;
}

int user_login_screen()
{
    return 0;
}

int login_invalid_screen()
{
    return 0;
}

int project_details_screen()
{
    return 0;
}

int task_details_screen()
{
    return 0;
}

int pause_screen(int sec)
{
    return 0;
}

int clear_screen()
{
    system("cls");
    return 0;
}
int validate_user_name()
{
    return 0;
}

int validate_email()
{
    return 0;
}

int validate_phone()
{
    // int count=0;
    // char character;
    // while ((character=))
    // {
    //     count++;
    // }
    
    
    return 0;
}

int validate_date()
{
    return 0;
}

//int current_date(char date[])
// {
//     return 0;
// }

int compare_date()
{
    return 0;
}
int is_overdue()
{
    return 0;
}
int move_cursor(int x, int y)
{

    COORD position;

    position.X = x;
    position.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    return 0;
}
int get_console_width()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

 void clock(void)
{
    while (!_kbhit())
    {
        time_t now = time(NULL);
        struct tm *local_time = localtime(&now);

        move_cursor(0, 0);

        printf("+------------------------------+\n");
        printf("|         DIGITAL CLOCK         |\n");
        printf("+------------------------------+\n");
        printf("|  Date : %02d/%02d/%04d          |\n",
               local_time->tm_mday,
               local_time->tm_mon + 1,
               local_time->tm_year + 1900);
        printf("|  Time : %02d:%02d:%02d              |\n",
               local_time->tm_hour,
               local_time->tm_min,
               local_time->tm_sec);
        printf("+------------------------------+\n");
        printf("(press any key to exit)         \n");

        Sleep(1000);
    }

    _getch();
}