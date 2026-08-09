#include "utility.h"

int validate_date(char date[])
{
    int year, month, day, max_day;

    if (strlen(date) != 10)
    {
        return 0;
    }

    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
        {
            if (date[i] != '-')
            {
                return 0;
            }
        }
        else
        {
            if (date[i] < '0' || date[i] > '9')
            {
                return 0;
            }
        }
    }

    year = (date[0] - '0') * 1000 +
           (date[1] - '0') * 100 +
           (date[2] - '0') * 10 +
           (date[3] - '0');

    month = (date[5] - '0') * 10 +
            (date[6] - '0');

    day = (date[8] - '0') * 10 +
          (date[9] - '0');

    if (month < 1 || month > 12)
    {
        return 0;
    }

    if (month == 2)
    {
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
        {
            max_day = 29;
        }
        else
        {
            max_day = 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        max_day = 30;
    }
    else
    {
        max_day = 31;
    }

    if (day < 1 || day > max_day)
    {
        return 0;
    }

    return 1;
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
    Sleep(sec);
    return 0;
}

int clear_screen()
{
    system("cls");
    return 0;
}

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

// void clock()
// {
//    time_t now;
//     struct tm *current;

//     time(&now);
//     current = localtime(&now);

//     printf("Date : %02d-%02d-%04d\n",
//            current->tm_mday,
//            current->tm_mon + 1,
//            current->tm_year + 1900);

//     printf("Time : %02d:%02d:%02d\n",
//            current->tm_hour,
//            current->tm_min,
//            current->tm_sec);

// }
