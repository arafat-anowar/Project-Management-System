/*
    Name : KAMRUL HASAN RIFAT
    ID : 2026-2-60-022
*/

#include "auth.h"

// auth main source code start

int create_user()
{
    // Declare all variables
    struct r_account user;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = ZERO, box_height = ZERO, x = ZERO, y = ZERO, user_name_found = VALID, is_email_valid = VALID, is_phone_valid = VALID;
    FILE *userDBS_open, *credentialDBS_open;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    box_width = CONTAINER_WIDTH;
    box_height = REGISTER_FORM_HEIGHT;
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // show user create form
    user_registration_screen(x, y);

    // generate a user id for new user
    generate_user_id(user.id);

    // take user full name
    move_cursor(x + INPUT_FIELD_OFFSET_X, y + REGISTER_NAME_FIELD_Y);
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';

    // take user email and validate that
    do
    {
        move_cursor(x + INPUT_FIELD_OFFSET_X, y + REGISTER_EMAIL_FIELD_Y);
        if (is_email_valid == INVALID)
        {
            printf("                                                                             ");
            move_cursor(x + INPUT_FIELD_OFFSET_X, y + REGISTER_EMAIL_FIELD_Y);
        }

        fgets(user.email, sizeof(user.email), stdin);
        user.email[strcspn(user.email, "\n")] = '\0';
        is_email_valid = validate_email(user.email);

    } while (is_email_valid != VALID);

    // take user phone number and validate that
    do
    {
        move_cursor(x + PHONE_FIELD_OFFSET_X, y + REGISTER_PHONE_FIELD_Y);
        if (is_phone_valid == INVALID)
        {
            printf("                                                                             ");
            move_cursor(x + PHONE_FIELD_OFFSET_X, y + REGISTER_PHONE_FIELD_Y);
        }

        fgets(user.phone, sizeof(user.phone), stdin);
        user.phone[strcspn(user.phone, "\n")] = '\0';
        is_phone_valid = validate_phone(user.phone);

    } while (is_phone_valid != VALID);

    // take user name and check is username already exist
    do
    {
        move_cursor(x + INPUT_FIELD_OFFSET_X, y + REGISTER_USERNAME_FIELD_Y);
        if (user_name_found == INVALID)
        {
            printf("                                                                             ");
            move_cursor(x + INPUT_FIELD_OFFSET_X, y + REGISTER_USERNAME_FIELD_Y);
        }

        fgets(user.user_name, sizeof(user.user_name), stdin);
        user.user_name[strcspn(user.user_name, "\n")] = '\0';
        user_name_found = validate_user_name(user.user_name);

    } while (user_name_found != VALID);

    // take user pass
    move_cursor(x + INPUT_FIELD_OFFSET_X, y + REGISTER_PASSWORD_FIELD_Y);
    input_password(user.pass);
    user.pass[strcspn(user.pass, "\n")] = '\0';

    // take input  security question's answer
    move_cursor(x + INPUT_FIELD_OFFSET_X, y + REGISTER_SECURITY_FIELD_Y);
    fgets(user.security_question, sizeof(user.security_question), stdin);
    user.security_question[strcspn(user.security_question, "\n")] = '\0';

    // set a default role for user
    strcpy(user.role, DEFAULT_ROLE_NAME);

    // open databases for write data
    userDBS_open = fopen(USER_DATABASE_FILE, FILE_MODE_APPEND);
    if (userDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    credentialDBS_open = fopen(CREDENTIAL_DATABASE_FILE, FILE_MODE_APPEND);
    if (credentialDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // write data to files
    fprintf(userDBS_open, "%s,%s,%s,%s,%s\n", user.id, user.name, user.email, user.phone, user.role);
    fprintf(credentialDBS_open, "%s,%s,%s,%s,%s,%s\n", user.id, user.user_name, user.email, user.pass, user.security_question, LOGOUT_STATUS_VALUE);

    // close databases
    if (fclose(userDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    if (fclose(credentialDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    // create necessary folder and files for user
    create_directories(user.user_name);

    // show account create successful screen
    account_create_success_screen(x, y);

    return 0;
}

int login()
{
    // Declare all variables
    struct l_account user;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = ZERO, box_height = ZERO, x = ZERO, y = ZERO;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    box_width = CONTAINER_WIDTH;
    box_height = LOGIN_FORM_HEIGHT;
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // show user login form
    user_login_screen(x, y);

    // take user email or username
    move_cursor(x + INPUT_FIELD_OFFSET_X, y + LOGIN_USERNAME_FIELD_Y);
    fgets(user.user_name_or_email, sizeof(user.user_name_or_email), stdin);
    user.user_name_or_email[strcspn(user.user_name_or_email, "\n")] = '\0';

    // take input user pass
    move_cursor(x + INPUT_FIELD_OFFSET_X, y + LOGIN_PASSWORD_FIELD_Y);
    input_password(user.user_pass);
    user.user_pass[strcspn(user.user_pass, "\n")] = '\0';

    // check userdetails
    int is_verified = password_verify(user.user_name_or_email, user.user_pass);

    // if user details correct redirect to dashboard
    if (is_verified == VALID)
    {
        char login_status[] = LOGIN_STATUS_VALUE;
        change_login_status(login_status);
        login_success_screen(x, y);
        dashboard();
        return 0;
    }

    // if user details wrong show error
    invalid_login_screen(x, y);
    
    return 0;
}

int logout()
{
    // declare all variables
    int terminal_width = ZERO, terminal_height = ZERO, box_width = ZERO, box_height = ZERO, x = ZERO, y = ZERO;
    FILE *log_open;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    box_width = CONTAINER_WIDTH;
    box_height = CHANGE_PASSWORD_FORM_HEIGHT;
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // change user login status to logout
    char login_status[] = LOGOUT_STATUS_VALUE;
    change_login_status(login_status);

    // clear log file
    log_open = fopen(LOG_FILE, FILE_MODE_WRITE);
    if (log_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // close log file
    if (log_open != NULL)
    {
        if (fclose(log_open) == EOF)
        {
            something_went_wrong_screen(FILE_CLOSE_ERROR);
        }
    }

    // show successful screen
    logout_successful_screen(x, y);

    return 0;
}

int change_password()
{
    // declare all variables
    struct r_account user;
    struct account change_password;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = ZERO, box_height = ZERO, x = ZERO, y = ZERO, found = ZERO;
    char row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    FILE *credentialDBS_open, *tmp_credentialDBS_open;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    box_width = CONTAINER_WIDTH;
    box_height = CHANGE_PASSWORD_FORM_HEIGHT;
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // show change password form
    change_password_screen(x, y);

    // take input user email
    move_cursor(x + INPUT_FIELD_OFFSET_X, y + CHANGE_PASSWORD_EMAIL_FIELD_Y);
    fgets(change_password.email, sizeof(change_password.email), stdin);
    change_password.email[strcspn(change_password.email, "\n")] = '\0';

    // take input security answer
    move_cursor(x + INPUT_FIELD_OFFSET_X, y + CHANGE_PASSWORD_SECURITY_FIELD_Y);
    fgets(change_password.security_question, sizeof(change_password.security_question), stdin);
    change_password.security_question[strcspn(change_password.security_question, "\n")] = '\0';

    // take input new password
    move_cursor(x + INPUT_FIELD_OFFSET_X, y + CHANGE_PASSWORD_NEW_PASSWORD_FIELD_Y);
    input_password(change_password.new_pass);
    change_password.new_pass[strcspn(change_password.new_pass, "\n")] = '\0';

    // open databases
    credentialDBS_open = fopen(CREDENTIAL_DATABASE_FILE, FILE_MODE_READ);
    if (credentialDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    tmp_credentialDBS_open = fopen(TEMP_CREDENTIAL_DATABASE_FILE, FILE_MODE_WRITE);
    if (tmp_credentialDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // read database
    while (fgets(row, sizeof(row), credentialDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize them
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

        // check email and security question if found update password
        if (strcmp(change_password.email, user.email) == 0 && strcmp(change_password.security_question, user.security_question) == 0)
        {
            found = 1;
            strcpy(user.pass, change_password.new_pass);
        }

        // write data to databases
        fprintf(tmp_credentialDBS_open, "%s,%s,%s,%s,%s,%s\n", user.id, user.user_name, user.email, user.pass, user.security_question, user.login_status);
    }

    // close databases
    if (fclose(credentialDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    if (fclose(tmp_credentialDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    // remove original database and rename tmp database as original database
    if (remove(CREDENTIAL_DATABASE_FILE) != 0)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }

    if (rename(TEMP_CREDENTIAL_DATABASE_FILE, CREDENTIAL_DATABASE_FILE) != 0)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }

    // if pass change successful show successful screen
    if (found == 0)
    {
        change_password_failed_screen(x, y);
        main_menu();
        return 0;
    }

    // if failed to change pass show error
    change_password_successful_screen(x, y);

    return 0;
}

int generate_user_id(char id[])
{
    // declare all variables
    struct r_account user;
    int data_found_in_file = ZERO, user_id_in_integer = ZERO, id_length = ZERO, i = ZERO, j = ZERO, tmp_user_id = ZERO, num_id[20] = {ZERO}, digit = ZERO;
    char *field, row[MAX_LENGTH_OF_DATA_IN_FILE];
    FILE *userDBS_open;

    // initialize id
    strcpy(id, FIRST_USER_ID_VALUE);

    // database open
    userDBS_open = fopen(USER_DATABASE_FILE, FILE_MODE_READ);
    if (userDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // read database
    while (fgets(row, sizeof(row), userDBS_open) != NULL)
    {
        data_found_in_file = 1;

        row[strcspn(row, "\n")] = '\0';

        // tokenize them
        field = strtok(row, ",");
        strcpy(user.id, field);
    }

    // close database
    if (fclose(userDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    // if no data found in file return default id
    if (data_found_in_file == 0)
    {
        return 0;
    }

    strcpy(id, user.id);

    // copy id's char array to integer array
    for (i = 0, j = 1; id[j] != '\0'; i++, j++)
    {
        num_id[i] = (id[j] - '0');
    }

    // get length of id
    id_length = strlen(id);

    // convert id's array to a number
    for (i = 0; i < id_length - 1; i++)
    {
        digit = num_id[i];

        for (j = i; j < id_length - 2; j++)
        {
            digit *= 10;
        }

        user_id_in_integer += digit;
    }

    // increment id by 1
    user_id_in_integer++;

    tmp_user_id = user_id_in_integer;
    j = strlen(id) - 1;

    // convert number to char array
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
    // declare all variables
    struct r_account user;
    FILE *credentialDBS_open, *tmp_credentialDBS_open;
    char *username, row[MAX_LENGTH_OF_DATA_IN_FILE], *field;

    // get user name
    username = get_user_name();

    // open databases
    credentialDBS_open = fopen(CREDENTIAL_DATABASE_FILE, FILE_MODE_READ);
    if (credentialDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    tmp_credentialDBS_open = fopen(TEMP_CREDENTIAL_DATABASE_FILE, FILE_MODE_WRITE);
    if (tmp_credentialDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // read data from file
    while (fgets(row, sizeof(row), credentialDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize them
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

        // if username found change status
        if (strcmp(user.user_name, username) == 0)
        {
            strcpy(user.login_status, status);
        }

        // write data to database
        fprintf(tmp_credentialDBS_open, "%s,%s,%s,%s,%s,%s\n", user.id, user.user_name, user.email, user.pass, user.security_question, user.login_status);
    }

    // free memory
    free(username);

    // close databases
    if (fclose(credentialDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    if (fclose(tmp_credentialDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    // delete main database and rename tmp database
    if (remove(CREDENTIAL_DATABASE_FILE) != 0)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }

    if (rename(TEMP_CREDENTIAL_DATABASE_FILE, CREDENTIAL_DATABASE_FILE) != 0)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }

    return 0;
}

int password_verify(char username_or_email[], char password[])
{
    // declare all variables
    struct r_account user;
    char row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int found = INVALID;
    FILE *credentialDBS_open, *log_open;

    // open databases
    credentialDBS_open = fopen(CREDENTIAL_DATABASE_FILE, FILE_MODE_READ);
    if (credentialDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    log_open = fopen(LOG_FILE, FILE_MODE_WRITE);
    if (log_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // read data from databases
    while (fgets(row, sizeof(row), credentialDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize them
        field = strtok(row, ",");
        strcpy(user.id, field);

        field = strtok(NULL, ",");
        strcpy(user.user_name, field);

        field = strtok(NULL, ",");
        strcpy(user.email, field);

        field = strtok(NULL, ",");
        strcpy(user.pass, field);

        // verify details if details are correct write username to log file
        if ((strcmp(username_or_email, user.email) == 0 && strcmp(password, user.pass) == 0) || (strcmp(username_or_email, user.user_name) == 0 && strcmp(password, user.pass) == 0))
        {
            found = 1;
            fprintf(log_open, "%s\n", user.user_name);
            break;
        }
    }

    // close database
    if (fclose(credentialDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    if (fclose(log_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    // if details are correct return valid
    if (found == 1)
    {
        return VALID;
    }

    // if details are wrong return invalid
    return INVALID;
}

int input_password(char password[])
{
    // declare variables
    int i = 0;
    char each_character;

    // run a loop until user enter enter char
    while ((each_character = getch()) != ENTER)
    {
        // if user enter backspace key clear last char
        if (each_character == BACKSPACE)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        // otherwise store pass in string and print * 
        else
        {
            password[i] = each_character;
            printf("*");
            i++;
        }
    }

    // add null char 
    password[i] = '\0';

    return 0;
}

char *get_user_name()
{
    // declare variables
    char *username, row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    FILE *log_open;

    // open log file
    log_open = fopen(LOG_FILE, FILE_MODE_READ);
    if (log_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // read data
    while (fgets(row, sizeof(row), log_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // define dynamic memory
        username = malloc(strlen(row) + 1);
        if (username == NULL)
        {
            something_went_wrong_screen(SOMETHING_FAILED);
        }

        // tokenize them
        field = strtok(row, ",");
        strcpy(username, field);
    }

    // close log file
    if (fclose(log_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    // return username
    return username;
}

int validate_user_name(char username[])
{
    // declare all variables
    struct r_account user;
    char row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    FILE *credentialDBS_open;

    // open database
    credentialDBS_open = fopen(CREDENTIAL_DATABASE_FILE, FILE_MODE_READ);
    if (credentialDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // read data
    while (fgets(row, sizeof(row), credentialDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize them
        field = strtok(row, ",");
        strcpy(user.id, field);

        field = strtok(NULL, ",");
        strcpy(user.user_name, field);

        // if username already exist return invalid
        if (strcmp(user.user_name, username) == 0)
        {
            if (fclose(credentialDBS_open) == EOF)
            {
                something_went_wrong_screen(FILE_CLOSE_ERROR);
            }

            return INVALID;
        }
    }

    // close database
    if (fclose(credentialDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    return VALID;
}

int validate_email(char email[])
{
    // declare all variables
    struct r_account user;
    int is_email_valid = INVALID;
    char row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    FILE *credentialDBS_open;

    // check @ char is available i users input
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            is_email_valid = VALID;
            break;
        }
    }

    // check is email address already exist
    credentialDBS_open = fopen(CREDENTIAL_DATABASE_FILE, FILE_MODE_READ);
    if (credentialDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
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
            is_email_valid = INVALID;
            break;
        }
    }

    if (fclose(credentialDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    // if all things are right return valid
    if (is_email_valid == VALID)
    {
        return VALID;
    }

    // if any condition wrong return invalid
    return INVALID;
}

int validate_phone(char phone[])
{
    // declare all variables
    int phone_length = strlen(phone), count = 0;

    // check phone number length
    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (phone[i] >= '0' && phone[i] <= '9')
        {
            count++;
        }
    }

    // if all condition are true return valid
    if (count == MAX_PHONE_LENGTH && phone_length == MAX_PHONE_LENGTH)
    {
        return VALID;
    }

    // if any condition is wrong return invalid
    return INVALID;
}

int create_directories(char username[])
{
    // declare variables
    char path[MAX_PATH_LENGTH];
    FILE *necessary_file_create;

    // create a folder in database with username
    strcpy(path, DATABASE_DIR);
    strcat(path, username);

    if (CreateDirectory(path, NULL) == 0)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }

    // create projects folder inside user's folder
    strcat(path, "\\");
    strcat(path, PROJECTS_FOLDER);

    if (CreateDirectory(path, NULL) == 0)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }

    // create projectdbs file
    strcpy(path, DATABASE_DIR);
    strcat(path, username);
    strcat(path, "\\");
    strcat(path, PROJECT_DATABASE_FILE);
    necessary_file_create = fopen(path, FILE_MODE_WRITE);

    if (necessary_file_create == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }
    else
    {
        if (fclose(necessary_file_create) == EOF)
        {
            something_went_wrong_screen(FILE_CLOSE_ERROR);
        }
    }

    // create taskdbs file
    strcpy(path, DATABASE_DIR);
    strcat(path, username);
    strcat(path, "\\");
    strcat(path, TASK_DATABASE_FILE);
    necessary_file_create = fopen(path, FILE_MODE_WRITE);

    if (necessary_file_create == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }
    else
    {
        if (fclose(necessary_file_create) == EOF)
        {
            something_went_wrong_screen(FILE_CLOSE_ERROR);
        }
    }

    // create sorttask file
    strcpy(path, DATABASE_DIR);
    strcat(path, username);
    strcat(path, "\\");
    strcat(path, SORTED_TASK_FILE);
    necessary_file_create = fopen(path, FILE_MODE_WRITE);

    if (necessary_file_create == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }
    else
    {
        if (fclose(necessary_file_create) == EOF)
        {
            something_went_wrong_screen(FILE_CLOSE_ERROR);
        }
    }

    // create sortproject file
    strcpy(path, DATABASE_DIR);
    strcat(path, username);
    strcat(path, "\\");
    strcat(path, SORTED_PROJECT_FILE);
    necessary_file_create = fopen(path, FILE_MODE_WRITE);

    if (necessary_file_create == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }
    else
    {
        if (fclose(necessary_file_create) == EOF)
        {
            something_went_wrong_screen(FILE_CLOSE_ERROR);
        }
    }

    return 0;
}

// auth main source code end