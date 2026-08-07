#include "auth.h"

int create_user()
{
    struct r_account user;
    int terminal_width = 0, terminal_height = 0, box_width = 0, box_height = 0, x = 0, y = 0;
    FILE *userDBS_open, *credentialDBS_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    box_width = 100;
    box_height = 37;
    x = (terminal_width - box_width) / 2;
    y = ((terminal_height - box_height) / 2) + 13;

    user_registration_screen(x, y);

    generate_user_id(user.id);

    move_cursor((x + 10), y + 6);
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';

    move_cursor((x + 10), y + 11);
    fgets(user.email, sizeof(user.email), stdin);
    user.email[strcspn(user.email, "\n")] = '\0';

    move_cursor((x + 14), y + 16);
    fgets(user.phone, sizeof(user.phone), stdin);
    user.phone[strcspn(user.phone, "\n")] = '\0';

    move_cursor((x + 10), y + 21);
    fgets(user.user_name, sizeof(user.user_name), stdin);
    user.user_name[strcspn(user.user_name, "\n")] = '\0';

    move_cursor((x + 10), y + 26);
    input_password(user.pass);
    user.pass[strcspn(user.pass, "\n")] = '\0';

    move_cursor((x + 10), y + 31);
    fgets(user.security_question, sizeof(user.security_question), stdin);
    user.security_question[strcspn(user.security_question, "\n")] = '\0';

    strcpy(user.role, "Individual");

    userDBS_open = fopen("..\\database\\userDBS.csv", "a");
    credentialDBS_open = fopen("..\\database\\credentialDBS.csv", "a");

    fprintf(userDBS_open, "%s,%s,%s,%s,%s\n", user.id, user.name, user.email, user.phone, user.role);
    fprintf(credentialDBS_open, "%s,%s,%s,%s,%s,logout\n", user.id, user.user_name, user.email, user.pass, user.security_question);

    fclose(userDBS_open);
    fclose(credentialDBS_open);

    login();

    return 0;
}

int login()
{
    struct l_account user;
    int terminal_width = 0, terminal_height = 0, box_width = 0, box_height = 0, x = 0, y = 0;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    box_width = 100;
    box_height = 19;
    x = (terminal_width - box_width) / 2;
    y = ((terminal_height - box_height) / 2) + 13;

    user_login_screen(x, y);

    move_cursor((x + 10), y + 6);
    fgets(user.user_name_or_email, sizeof(user.user_name_or_email), stdin);
    user.user_name_or_email[strcspn(user.user_name_or_email, "\n")] = '\0';

    move_cursor((x + 10), y + 12);
    input_password(user.user_pass);
    user.user_pass[strcspn(user.user_pass, "\n")] = '\0';

    int is_verified = password_verify(user.user_name_or_email, user.user_pass);

    if (is_verified == 1)
    {
        char login_status[] = "login";
        change_login_status(login_status);
        dashboard();
        return 0;
    }
    clear_screen();
    header_screen();
    login_invalid_screen();
    pause_screen(1500);
    login();

    return 0;
}

int logout()
{
    char login_status[] = "logout";
    change_login_status(login_status);
    main_menu();
    return 0;
}

int change_password()
{
    struct r_account user;
    struct account change_password;

    int terminal_width = 0, terminal_height = 0, box_width = 0, box_height = 0, x = 0, y = 0;
    char row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    FILE *credentialDBS_open, *tmp_credentialDBS_open;
    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    box_width = 100;
    box_height = 19;
    x = (terminal_width - box_width) / 2;
    y = ((terminal_height - box_height) / 2) + 13;

    change_password_screen(x, y);

    move_cursor((x + 10), y + 6);
    fgets(change_password.email, sizeof(change_password.email), stdin);
    change_password.email[strcspn(change_password.email, "\n")] = '\0';

    move_cursor((x + 10), y + 11);
    fgets(change_password.security_question, sizeof(change_password.security_question), stdin);
    change_password.security_question[strcspn(change_password.security_question, "\n")] = '\0';

    move_cursor((x + 10), y + 16);
    input_password(change_password.new_pass);
    change_password.new_pass[strcspn(change_password.new_pass, "\n")] = '\0';

    credentialDBS_open = fopen("..\\database\\credentialDBS.csv", "r");
    tmp_credentialDBS_open = fopen("..\\database\\tmp_credentialDBS.csv", "w");

    while (fgets(row, sizeof(row), credentialDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        field = strtok(row, ",");
        strcpy(user.id, field);

        field = strtok(NULL, ",");
        strcpy(user.user_name, field);

        field = strtok(NULL, ",");
        strcpy(user.email, field);

        field = strtok(NULL, ",");
        strcpy(user.pass, field);

        field = strtok(NULL, ",");
        strcpy(user.security_question, field);

        field = strtok(NULL, ",");
        strcpy(user.login_status, field);

        if (strcmp(change_password.email, user.email) == 0 &&
            strcmp(change_password.security_question, user.security_question) == 0)
        {
            strcpy(user.pass, change_password.new_pass);
        }
        fprintf(tmp_credentialDBS_open, "%s,%s,%s,%s,%s,%s\n", user.id, user.user_name, user.email, user.pass, user.security_question, user.login_status);
    }

    fclose(credentialDBS_open);
    fclose(tmp_credentialDBS_open);

    remove("..\\database\\credentialDBS.csv");

    rename("..\\database\\tmp_credentialDBS.csv", "..\\database\\credentialDBS.csv");
    login();
    return 0;
}

int generate_user_id(char id[])
{
    struct r_account user;
    int data_found_in_file = 0, user_id_in_integer = 0, id_length = 0, i = 0, j = 0, tmp_user_id = 0, num_id[20] = {0}, digit = 0;
    char *field, row[MAX_LENGTH_OF_DATA_IN_FILE];
    FILE *userDBS_open;
    strcpy(id, "U1001");

    userDBS_open = fopen("..\\database\\userDBS.csv", "r");

    while (fgets(row, sizeof(row), userDBS_open) != NULL)
    {
        data_found_in_file = 1;

        row[strcspn(row, "\n")] = '\0';

        field = strtok(row, ",");
        strcpy(user.id, field);
    }

    fclose(userDBS_open);

    if (data_found_in_file == 0)
    {
        return 0;
    }
    strcpy(id, user.id);

    for (i = 0, j = 1; id[j] != '\0'; i++, j++)
    {
        num_id[i] = (id[j] - '0');
    }
    id_length = strlen(id);
    for (i = 0; i < id_length - 1; i++)
    {
        digit = num_id[i];
        for (j = i; j < id_length - 2; j++)
        {
            digit *= 10;
        }
        user_id_in_integer += digit;
    }

    user_id_in_integer++;

    tmp_user_id = user_id_in_integer;
    j = (strlen(id) - 1);

    while (tmp_user_id != 0)
    {
        id[j] = ((tmp_user_id % 10) + '0');
        tmp_user_id /= 10;
        j--;
    }

    return 0;
}
int change_login_status(char status[])
{
    struct r_account user;
    FILE *credentialDBS_open, *tmp_credentialDBS_open;
    char username[30], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;

    get_user_name(username);

    credentialDBS_open = fopen("..\\database\\credentialDBS.csv", "r");
    tmp_credentialDBS_open = fopen("..\\database\\tmp_credentialDBS.csv", "w");

    while (fgets(row, sizeof(row), credentialDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';
        field = strtok(row, ",");
        strcpy(user.id, field);

        field = strtok(NULL, ",");
        strcpy(user.user_name, field);

        field = strtok(NULL, ",");
        strcpy(user.email, field);

        field = strtok(NULL, ",");
        strcpy(user.pass, field);

        field = strtok(NULL, ",");
        strcpy(user.security_question, field);

        field = strtok(NULL, ",");
        strcpy(user.login_status, field);

        if (strcmp(user.user_name, username) == 0)
        {
            strcpy(user.login_status, status);
        }
        fprintf(tmp_credentialDBS_open, "%s,%s,%s,%s,%s,%s\n", user.id, user.user_name, user.email, user.pass, user.security_question, user.login_status);
    }

    fclose(credentialDBS_open);
    fclose(tmp_credentialDBS_open);
    remove("..\\database\\credentialDBS.csv");

    rename("..\\database\\tmp_credentialDBS.csv", "..\\database\\credentialDBS.csv");
    return 0;
}
int password_verify(char username_or_email[], char password[])
{
    struct r_account user;

    char row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int found = 0;

    FILE *credentialDBS_open;

    credentialDBS_open = fopen("..\\database\\credentialDBS.csv", "r");

    while (fgets(row, sizeof(row), credentialDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        field = strtok(row, ",");
        strcpy(user.id, field);

        field = strtok(NULL, ",");
        strcpy(user.user_name, field);

        field = strtok(NULL, ",");
        strcpy(user.email, field);

        field = strtok(NULL, ",");
        strcpy(user.pass, field);

        if ((strcmp(username_or_email, user.email) == 0 && strcmp(password, user.pass) == 0) ||
            (strcmp(username_or_email, user.user_name) == 0 && strcmp(password, user.pass) == 0))
        {
            found = 1;
            break;
        }
    }

    fclose(credentialDBS_open);

    if (found == 1)
    {
        return 1;
    }

    return 0;
}

int input_password(char password[])
{
    int i = 0;
    char each_character;
    while ((each_character = getch()) != 13)
    {
        password[i] = each_character;
        printf("*");
        i++;
    }
    password[i] = '\0';
    return 0;
}
