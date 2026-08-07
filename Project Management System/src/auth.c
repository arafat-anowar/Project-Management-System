#include "auth.h"

int create_user()
{
    struct r_account user;
    int terminal_width = 0, terminal_height = 0, box_width = 0, box_height = 0, x = 0, y = 0, user_name_found = VALID, is_email_valid = VALID, is_phone_valid = VALID;
    FILE *userDBS_open, *credentialDBS_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    box_width = BOX_WIDTH;
    box_height = REGISTER_BOX_HEIGHT;
    x = (terminal_width - box_width) / 2;
    y = ((terminal_height - box_height) / 2) + SCREEN_OFFSET_Y;

    user_registration_screen(x, y);

    generate_user_id(user.id);

    move_cursor(x + INPUT_OFFSET_X, y + REGISTER_NAME_Y);
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';

    do
    {
        move_cursor(x + INPUT_OFFSET_X, y + REGISTER_EMAIL_Y);
        if (is_email_valid == INVALID)
        {
            printf("                                                                             ");
            move_cursor(x + INPUT_OFFSET_X, y + REGISTER_EMAIL_Y);
        }

        fgets(user.email, sizeof(user.email), stdin);
        user.email[strcspn(user.email, "\n")] = '\0';
        is_email_valid = validate_email(user.email);

    } while (is_email_valid != VALID);

    do
    {
        move_cursor(x + PHONE_INPUT_OFFSET_X, y + REGISTER_PHONE_Y);

        if (is_phone_valid == INVALID)
        {
            printf("                                                                             ");
            move_cursor(x + PHONE_INPUT_OFFSET_X, y + REGISTER_PHONE_Y);
        }

        fgets(user.phone, sizeof(user.phone), stdin);
        user.phone[strcspn(user.phone, "\n")] = '\0';
        is_phone_valid = validate_phone(user.phone);

    } while (is_phone_valid != VALID);

    do
    {
        move_cursor(x + INPUT_OFFSET_X, y + REGISTER_USERNAME_Y);

        if (user_name_found == INVALID)
        {
            printf("                                                                             ");
            move_cursor(x + INPUT_OFFSET_X, y + REGISTER_USERNAME_Y);
        }

        fgets(user.user_name, sizeof(user.user_name), stdin);
        user.user_name[strcspn(user.user_name, "\n")] = '\0';

        user_name_found = validate_user_name(user.user_name);

    } while (user_name_found != VALID);

    move_cursor(x + INPUT_OFFSET_X, y + REGISTER_PASSWORD_Y);
    input_password(user.pass);
    user.pass[strcspn(user.pass, "\n")] = '\0';

    move_cursor(x + INPUT_OFFSET_X, y + REGISTER_SECURITY_Y);
    fgets(user.security_question, sizeof(user.security_question), stdin);
    user.security_question[strcspn(user.security_question, "\n")] = '\0';

    strcpy(user.role, DEFAULT_ROLE);

    userDBS_open = fopen(USER_DBS, APPEND_MODE);
    if (userDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }
    credentialDBS_open = fopen(CREDENTIAL_DBS, APPEND_MODE);
    if (credentialDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    fprintf(userDBS_open, "%s,%s,%s,%s,%s\n",
            user.id,
            user.name,
            user.email,
            user.phone,
            user.role);

    fprintf(credentialDBS_open, "%s,%s,%s,%s,%s,%s\n",
            user.id,
            user.user_name,
            user.email,
            user.pass,
            user.security_question,
            LOGOUT_STATUS);

    fclose(userDBS_open);
    fclose(credentialDBS_open);

    create_directories(user.user_name);

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

    box_width = BOX_WIDTH;
    box_height = LOGIN_BOX_HEIGHT;

    x = (terminal_width - box_width) / 2;
    y = ((terminal_height - box_height) / 2) + SCREEN_OFFSET_Y;

    user_login_screen(x, y);

    move_cursor(x + INPUT_OFFSET_X, y + LOGIN_USERNAME_Y);
    fgets(user.user_name_or_email, sizeof(user.user_name_or_email), stdin);
    user.user_name_or_email[strcspn(user.user_name_or_email, "\n")] = '\0';

    move_cursor(x + INPUT_OFFSET_X, y + LOGIN_PASSWORD_Y);
    input_password(user.user_pass);
    user.user_pass[strcspn(user.user_pass, "\n")] = '\0';

    int is_verified = password_verify(user.user_name_or_email, user.user_pass);

    if (is_verified == VALID)
    {
        char login_status[] = LOGIN_STATUS;
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
    char login_status[] = LOGOUT_STATUS;

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

    box_width = BOX_WIDTH;
    box_height = CHANGE_PASSWORD_BOX_HEIGHT;

    x = (terminal_width - box_width) / 2;
    y = ((terminal_height - box_height) / 2) + SCREEN_OFFSET_Y;

    change_password_screen(x, y);

    move_cursor(x + INPUT_OFFSET_X, y + CHANGE_PASSWORD_EMAIL_Y);
    fgets(change_password.email, sizeof(change_password.email), stdin);
    change_password.email[strcspn(change_password.email, "\n")] = '\0';

    move_cursor(x + INPUT_OFFSET_X, y + CHANGE_PASSWORD_SECURITY_Y);
    fgets(change_password.security_question, sizeof(change_password.security_question), stdin);
    change_password.security_question[strcspn(change_password.security_question, "\n")] = '\0';

    move_cursor(x + INPUT_OFFSET_X, y + CHANGE_PASSWORD_NEWPASS_Y);
    input_password(change_password.new_pass);
    change_password.new_pass[strcspn(change_password.new_pass, "\n")] = '\0';

    credentialDBS_open = fopen(CREDENTIAL_DBS, READ_MODE);
    if (credentialDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }
    tmp_credentialDBS_open = fopen(TMP_CREDENTIAL_DBS, WRITE_MODE);
    if (tmp_credentialDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

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

        fprintf(tmp_credentialDBS_open,
                "%s,%s,%s,%s,%s,%s\n",
                user.id,
                user.user_name,
                user.email,
                user.pass,
                user.security_question,
                user.login_status);
    }

    fclose(credentialDBS_open);
    fclose(tmp_credentialDBS_open);

    remove(CREDENTIAL_DBS);
    rename(TMP_CREDENTIAL_DBS, CREDENTIAL_DBS);

    login();

    return 0;
}

int generate_user_id(char id[])
{
    struct r_account user;

    int data_found_in_file = 0, user_id_in_integer = 0, id_length = 0, i = 0, j = 0, tmp_user_id = 0, num_id[20] = {0}, digit = 0;
    char *field, row[MAX_LENGTH_OF_DATA_IN_FILE];
    FILE *userDBS_open;

    strcpy(id, FIRST_USER_ID);

    userDBS_open = fopen(USER_DBS, READ_MODE);
    if (userDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    while (fgets(row, sizeof(row), userDBS_open) != NULL)
    {
        data_found_in_file = 1;

        row[strcspn(row, "\n")] = '\0';

        field = strtok(row, ",");
        strcpy(user.id, field);
    }

    fclose(userDBS_open);

    if (data_found_in_file == INVALID)
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
    j = strlen(id) - 1;

    while (tmp_user_id != 0)
    {
        id[j] = (tmp_user_id % 10) + '0';
        tmp_user_id /= 10;
        j--;
    }

    return 0;
}

int change_login_status(char status[])
{
    struct r_account user;

    FILE *credentialDBS_open, *tmp_credentialDBS_open;

    char username[USERNAME_BUFFER_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;

    get_user_name(username);

    credentialDBS_open = fopen(CREDENTIAL_DBS, READ_MODE);
    if (credentialDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }
    tmp_credentialDBS_open = fopen(TMP_CREDENTIAL_DBS, WRITE_MODE);
    if (tmp_credentialDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

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

        fprintf(tmp_credentialDBS_open,
                "%s,%s,%s,%s,%s,%s\n",
                user.id,
                user.user_name,
                user.email,
                user.pass,
                user.security_question,
                user.login_status);
    }

    fclose(credentialDBS_open);
    fclose(tmp_credentialDBS_open);

    remove(CREDENTIAL_DBS);
    rename(TMP_CREDENTIAL_DBS, CREDENTIAL_DBS);

    return 0;
}

int password_verify(char username_or_email[], char password[])
{
    struct r_account user;

    char row[MAX_LENGTH_OF_DATA_IN_FILE], *field;

    int found = INVALID;

    FILE *credentialDBS_open, *log_open;

    credentialDBS_open = fopen(CREDENTIAL_DBS, READ_MODE);
    if (credentialDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }
    log_open = fopen(LOG_DBS, WRITE_MODE);
    if (log_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

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

        if ((strcmp(username_or_email, user.email) == 0 &&
             strcmp(password, user.pass) == 0) ||
            (strcmp(username_or_email, user.user_name) == 0 &&
             strcmp(password, user.pass) == 0))
        {
            found = VALID;
            fprintf(log_open, "%s\n", user.user_name);
            break;
        }
    }

    fclose(credentialDBS_open);
    fclose(log_open);

    if (found == VALID)
    {
        return VALID;
    }

    return INVALID;
}

int input_password(char password[])
{
    int i = 0;
    char each_character;

    while ((each_character = getch()) != ENTER_KEY)
    {
        if (each_character == BACKSPACE_KEY)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            password[i] = each_character;
            printf("*");
            i++;
        }
    }

    password[i] = '\0';

    return 0;
}

int get_user_name(char username[])
{
    char row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    FILE *log_open;

    log_open = fopen(LOG_DBS, READ_MODE);
    if (log_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    while (fgets(row, sizeof(row), log_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        field = strtok(row, ",");

        strcpy(username, field);
    }

    fclose(log_open);

    return 0;
}

int validate_user_name(char username[])
{
    struct r_account user;

    char row[MAX_LENGTH_OF_DATA_IN_FILE], *field;

    FILE *credentialDBS_open;

    credentialDBS_open = fopen(CREDENTIAL_DBS, READ_MODE);
    if (credentialDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    while (fgets(row, sizeof(row), credentialDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        field = strtok(row, ",");
        strcpy(user.id, field);

        field = strtok(NULL, ",");
        strcpy(user.user_name, field);

        if (strcmp(user.user_name, username) == 0)
        {
            fclose(credentialDBS_open);
            return INVALID;
        }
    }

    fclose(credentialDBS_open);

    return VALID;
}

int validate_email(char email[])
{
    struct r_account user;

    int email_found = INVALID, is_email_valid = VALID;

    char row[MAX_LENGTH_OF_DATA_IN_FILE], *field;

    FILE *credentialDBS_open;

    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            is_email_valid = INVALID;
            break;
        }
    }

    credentialDBS_open = fopen(CREDENTIAL_DBS, READ_MODE);
    if (credentialDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    while (fgets(row, sizeof(row), credentialDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        field = strtok(row, ",");
        strcpy(user.id, field);

        field = strtok(NULL, ",");
        strcpy(user.user_name, field);

        field = strtok(NULL, ",");
        strcpy(user.email, field);

        if (strcmp(user.email, email) == 0)
        {
            email_found = VALID;
            break;
        }
    }

    fclose(credentialDBS_open);

    if (email_found == INVALID && is_email_valid == INVALID)
    {
        return VALID;
    }

    return INVALID;
}

int validate_phone(char phone[])
{
    int phone_length = strlen(phone), count = 0;

    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (phone[i] >= '0' && phone[i] <= '9')
        {
            count++;
        }
    }

    if (count == PHONE_LENGTH && phone_length == PHONE_LENGTH)
    {
        return VALID;
    }

    return INVALID;
}

int create_directories(char username[])
{
    char path[PATH_BUFFER_SIZE];

    FILE *necessary_file_create;

    strcpy(path, DATABASE_PATH);
    strcat(path, username);

    CreateDirectory(path, NULL);

    strcat(path, "\\");
    strcat(path, PROJECT_FOLDER);

    CreateDirectory(path, NULL);

    strcpy(path, DATABASE_PATH);
    strcat(path, username);
    strcat(path, "\\");
    strcat(path, PROJECT_DBS);

    necessary_file_create = fopen(path, WRITE_MODE);
    if (necessary_file_create == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }
    fclose(necessary_file_create);

    strcpy(path, DATABASE_PATH);
    strcat(path, username);
    strcat(path, "\\");
    strcat(path, TASK_DBS);

    necessary_file_create = fopen(path, WRITE_MODE);
    if (necessary_file_create == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }
    fclose(necessary_file_create);

    strcpy(path, DATABASE_PATH);
    strcat(path, username);
    strcat(path, "\\");
    strcat(path, SORT_TASK_DBS);

    necessary_file_create = fopen(path, WRITE_MODE);
    if (necessary_file_create == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }
    fclose(necessary_file_create);

    return 0;
}