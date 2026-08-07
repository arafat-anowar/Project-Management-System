#include "utility.h"



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




int validate_date()
{
    return 0;
}

//int current_date(char date[])
// int current_date(char date[])
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

//  void clock(void)
// {
//     while (!_kbhit())
//     {
//         time_t now = time(NULL);
//         struct tm *local_time = localtime(&now);

//         move_cursor(0, 0);

//         printf("+------------------------------+\n");
//         printf("|         DIGITAL CLOCK         |\n");
//         printf("+------------------------------+\n");
//         printf("|  Date : %02d/%02d/%04d          |\n",
//                local_time->tm_mday,
//                local_time->tm_mon + 1,
//                local_time->tm_year + 1900);
//         printf("|  Time : %02d:%02d:%02d              |\n",
//                local_time->tm_hour,
//                local_time->tm_min,
//                local_time->tm_sec);
//         printf("+------------------------------+\n");
//         printf("(press any key to exit)         \n");

//         Sleep(1000);
//     }

//     _getch();
// }
int get_console_height()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

int init_console()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    return 0;
}

// int clock()
// {
//     while (1)
//     {
//         time_t now = time(NULL);
//         struct tm *local_time = localtime(&now);

//         system("cls");

//         printf("Date: %02d/%02d/%d\n", local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900);

//         printf("Time: %02d:%02d:%02d\n", local_time->tm_hour, local_time->tm_min, local_time->tm_sec);

//         Sleep(1000);
//     }

//     return 0;

// }

// Auth Header File

