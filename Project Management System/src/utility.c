#include "utility.h"

// utility source code start

int pause_screen(int sec)
{
    // wait for some seconds
    Sleep(sec);
    return 0;
}

int clear_screen()
{
    // clear terminal screen
    system("cls");
    return 0;
}

int validate_date(char date[])
{
    // declare all variables
    int year, month, day, max_day;

    // check date length
    if (strlen(date) != 10)
    {
        return 0;
    }

    // check date format
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

    // get year, month and day
    year = (date[0] - '0') * 1000 + (date[1] - '0') * 100 + (date[2] - '0') * 10 + (date[3] - '0');
    month = (date[5] - '0') * 10 + (date[6] - '0');
    day = (date[8] - '0') * 10 + (date[9] - '0');

    // check month
    if (month < 1 || month > 12)
    {
        return 0;
    }

    // calculate maximum day of month
    if (month == 2)
    {
        // check leap year
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

    // check day
    if (day < 1 || day > max_day)
    {
        return 0;
    }

    return 1;
}

int current_time()
{
    // declare all variables
    time_t now;
    struct tm *current;

    // get current time
    time(&now);
    current = localtime(&now);

    // show current time
    printf("%2d:%2d:%2d", current->tm_hour, current->tm_min, current->tm_sec);

    return 0;
}

int current_date(char date[])
{
    // declare all variables
    time_t now;
    struct tm *current;

    // get current time
    time(&now);
    current = localtime(&now);

    // get current date
    strftime(date, 15, "%Y-%m-%d", current);

    return 0;
}

int is_overdue(char date[])
{
    // declare variables
    char today[15];

    // get current date
    current_date(today);

    // check overdue date
    if (strcmp(date, today) < 0)
    {
        return 1;
    }

    return 0;
}

int init_console()
{
#ifdef _WIN32
    // set terminal output for UTF8
    SetConsoleOutputCP(CP_UTF8);

    // set terminal input for UTF8
    SetConsoleCP(CP_UTF8);
#endif

    return 0;
}

int move_cursor(int x, int y)
{
    // declare variables
    COORD position;

    // set cursor position
    position.X = x;
    position.Y = y;

    // move cursor
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);

    return 0;
}

int get_console_width()
{
    // declare variables
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // get console information
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    // get console width
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int get_console_height()
{
    // declare variables
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // get console information
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    // get console height
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void live_clock(void *arg)
{
    // get x and y position
    int *position = (int *)arg;

    // get x and y coordinate
    int x = position[0];
    int y = position[1];

    // get console handle
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    // update clock continuously
    while (1)
    {
        // declare all variables
        time_t now;
        struct tm *current;
        char time_string[10];

        // get current time
        time(&now);
        current = localtime(&now);

        // format current time
        sprintf(time_string, "%02d:%02d:%02d", current->tm_hour, current->tm_min, current->tm_sec);

        // set time position
        COORD position;
        position.X = x + 82;
        position.Y = y + 14;

        // declare number of written characters
        DWORD written;

        // write current time to console
        WriteConsoleOutputCharacterA(console, time_string, 8, position, &written);

        // wait for one second
        Sleep(1000);
    }
}

int view_profile()
{
    // declare all variables
    struct r_account account;
    FILE *userDBS_open, *log_open;
    char row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int found = 0, terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // open  database
    userDBS_open = fopen("..\\database\\userDBS.csv", "r");

    // read  database
    while (fgets(row, sizeof(row), userDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize data
        field = strtok(row, ",");
        strcpy(account.id, field);

        field = strtok(NULL, ",");
        strcpy(account.name, field);

        field = strtok(NULL, ",");
        strcpy(account.email, field);

        field = strtok(NULL, ",");
        strcpy(account.phone, field);

        field = strtok(NULL, ",");
        strcpy(account.role, field);
    }

    // close database
    fclose(userDBS_open);

    // open log
    log_open = fopen("..\\database\\log.csv", "r");

    // read log
    while (fgets(row, sizeof(row), log_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // get logged in username
        strcpy(account.user_name, row);
    }

    // close databse
    fclose(log_open);

    // show profile screen
    profile_screen(x, y);

    // show account details
    move_cursor(x + 10, y + 6);
    printf("%s", account.id);

    move_cursor(x + 10, y + 11);
    printf("%s", account.user_name);

    move_cursor(x + 10, y + 16);
    printf("%s", account.name);

    move_cursor(x + 10, y + 21);
    printf("%s", account.email);

    move_cursor(x + 10, y + 26);
    printf("+880 %s", account.phone);

    move_cursor(x + 10, y + 31);
    printf("%s", account.role);

    get_input;

    return 0;
}

// utility source code end

// int validate_input(char field[], int size)
// {
//     int i = ZERO, terminal_width = ZERO, terminal_height = ZERO, box_width = ZERO, box_height = ZERO, x = ZERO, y = ZERO;

//     char ch,row[3000];

//     FILE *log_open=fopen("..\\database\\log.csv","r");
//     terminal_width = get_console_width();
//     terminal_height = get_console_height();

//     box_width = BOX_WIDTH;
//     box_height = CHANGE_PASSWORD_BOX_HEIGHT;

//     x = (terminal_width - box_width) / TWO;
//     y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

//     while (i < size - 1)
//     {
//         ch = getch();

//         if (ch == ESC_KEY)
//         {
//             redirecting_screen(x, y);
//             main_menu();
//             return ESC_KEY;
//         }

//         if (ch == ENTER_KEY)
//         {
//             break;
//         }

//         if (ch == BACKSPACE_KEY)
//         {
//             if (i > ZERO)
//             {
//                 i--;
//                 printf("\b \b");
//             }
//         }
//         else
//         {
//             field[i] = ch;
//             printf("%c", ch);
//             i++;
//         }
//     }

//     field[i] = '\0';

//     return ENTER_KEY;
// }