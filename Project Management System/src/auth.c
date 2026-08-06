#include "auth.h"

// Main Source Code Start From Here

/*
    Goal : This function generates a unique user id for every new user.
*/
int generate_user_id(char id[])
{
    // Firstly assign U1001 to id.
    strcpy(id, "U1001");

    // Declare a variable which is confirm that database isn't empty.
    int data_found = 0;

    // Open userDBS
    FILE *userDBS_open = fopen("..\\database\\userDBS.csv", "r");
    // If file not open show a error to user.
    if (userDBS_open == NULL)
    {
        perror("userDBS.csv");
        return 0;
    }

    // Declare structure variable.
    struct r_account user;

    // Store every rows data.
    char row[MAX_LENGTH];
    // Read data with loop
    while (fgets(row, sizeof(row), userDBS_open) != NULL)
    {
        // Assign 1 to data_found variable.
        data_found = 1;

        // Handle enter character
        row[strcspn(row, "\n")] = '\0';

        // Divide rows data into pieces
        char *field = strtok(row, ",");
        strcpy(user.id, field);

        field = strtok(NULL, ",");
        strcpy(user.name, field);

        field = strtok(NULL, ",");
        strcpy(user.email, field);

        field = strtok(NULL, ",");
        strcpy(user.phone, field);

        field = strtok(NULL, ",");
        strcpy(user.user_name, field);

        field = strtok(NULL, ",");
        strcpy(user.pass, field);

        field = strtok(NULL, ",");
        strcpy(user.security_question, field);

        field = strtok(NULL, ",");
        strcpy(user.role, field);
    }

    // Close userDBS
    fclose(userDBS_open);

    // If file empty return default ID.
    if (data_found == 0)
    {
        return 0;
    }
    // Else generate a new ID.
    else
    {
        // Copy the last user id of file.
        strcpy(id, user.id);

        // Declare a integer array
        int num_id[20];

        // Convert ASCII value to decimal value
        for (int i = 0, j = 1; id[j] != '\0'; i++, j++)
        {
            num_id[i] = (id[j] - '0');
        }

        // Declare two integer variable.usr_id store a decimal number and id_len store id length.
        int usr_id = 0, id_len = strlen(id);

        // Convert to a decimal number.
        for (int i = 0; i <= id_len - 2; i++)
        {
            int digit = num_id[i];
            for (int j = i; j <= id_len - 3; j++)
            {
                digit *= 10;
            }

            usr_id += digit;
        }

        // Increase id by 1
        usr_id++;

        // Convert Decimal number to ASCII and store that into ID.
        int tmp = usr_id;
        int j = (strlen(id) - 1);

        while (tmp != 0)
        {
            id[j] = ((tmp % 10) + '0');
            tmp /= 10;
            j--;
        }
        // Return ID.
        return 0;
    }
}

/*
    Goal : This function create a new user and store that into userDBS.
*/
int create_user()
{
    // Structure variable for store user information.
    struct r_account user;

    // Generate a new user id.
    generate_user_id(user.id);

    // Take user name.
    printf("\nName : ");
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';

    // Take user email.
    printf("\nEmail : ");
    fgets(user.email, sizeof(user.email), stdin);
    user.email[strcspn(user.email, "\n")] = '\0';

    // Take user phone number.
    printf("\nPhone Number : +880 ");
    fgets(user.phone, sizeof(user.phone), stdin);
    user.phone[strcspn(user.phone, "\n")] = '\0';

    // Take username.
    printf("\nUsername : ");
    fgets(user.user_name, sizeof(user.user_name), stdin);
    user.user_name[strcspn(user.user_name, "\n")] = '\0';

    // Take password.
    input_password_two(&user);
    user.pass[strcspn(user.pass, "\n")] = '\0';

    // Take answer of security question.
    printf("\nWhat Is Your Favourite Food : ");
    fgets(user.security_question, sizeof(user.security_question), stdin);
    user.security_question[strcspn(user.security_question, "\n")] = '\0';

    // Set default role.
    strcpy(user.role, "Individual");

    // Open user database file.
    FILE *userDBS_open = fopen("..\\database\\userDBS.csv", "a");

    // If file can not open show the error.
    if (userDBS_open == NULL)
    {
        perror("userDBS.csv");
        return 0;
    }

    // Save all user data into database.
    fprintf(userDBS_open, "%s,%s,%s,%s,%s,%s,%s,%s\n",
            user.id, user.name, user.email, user.phone,
            user.user_name, user.pass,
            user.security_question, user.role);

    // Close the file.
    fclose(userDBS_open);

    // Go to login page.
    login();

    return 0;
}

// This function login a user.
int login()

{
    // Show the login screen.
    clear_screen();
    header_screen();
    user_login_screen();

    // Structure variable for store login data.
    struct l_account user;

    // Take username or email.
    printf("\nUsername/Email: ");
    fgets(user.user_name_or_email, sizeof(user.user_name_or_email), stdin);
    user.user_name_or_email[strcspn(user.user_name_or_email, "\n")] = '\0';

    // Take user password.
    input_password(&user);
    user.user_pass[strcspn(user.user_pass, "\n")] = '\0';
    // Check username/email and password is correct or not.
    int is_verified = password_verify(user.user_name_or_email, user.user_pass);

    // If login is successful go to dashboard.
    if (is_verified == 1)
    {
        dashboard();
    }

    // Otherwise show invalid message and ask for login again.
    else
    {
        clear_screen();
        header_screen();
        login_invalid_screen();
        pause_screen(1500);
        login();
    }

    return 0;
}

// This function logout the current user.
int logout()
{
    // Go back to main menu.
    main_menu();

    return 0;
}

// This function check user login information.
int password_verify(char username_or_email[], char password[])
{
    // Structure variable for store user data.
    struct r_account user;

    // Variables needed for file reading.
    char row[MAX_LENGTH];
    int found = 0;

    // Open user database file.
    FILE *userDBS_open;
    userDBS_open = fopen("..\\database\\userDBS.csv", "r");

    // If file can not open show the error.
    if (userDBS_open == NULL)
    {
        perror("userDBS.csv");
        return 0;
    }

    // Read all user data from file.
    while (fgets(row, sizeof(row), userDBS_open) != NULL)
    {
        // Remove new row character.
        row[strcspn(row, "\n")] = '\0';

        // Split the row into different parts.
        char *field;

        // Store every value into structure.
        field = strtok(row, ",");
        strcpy(user.id, field);

        field = strtok(NULL, ",");
        strcpy(user.name, field);

        field = strtok(NULL, ",");
        strcpy(user.email, field);

        field = strtok(NULL, ",");
        strcpy(user.phone, field);

        field = strtok(NULL, ",");
        strcpy(user.user_name, field);

        field = strtok(NULL, ",");
        strcpy(user.pass, field);

        field = strtok(NULL, ",");
        strcpy(user.security_question, field);

        field = strtok(NULL, ",");
        strcpy(user.role, field);

        // Check if username/email and password matched.
        if ((strcmp(username_or_email, user.email) == 0 && strcmp(password, user.pass) == 0) ||
            (strcmp(username_or_email, user.user_name) == 0 && strcmp(password, user.pass) == 0))
        {
            found = 1;
            break;
        }
    }

    // Close the file.
    fclose(userDBS_open);

    // If user found return 1.
    if (found == 1)
    {
        return 1;
    }

    // Otherwise return 0.
    return 0;
}

// This function change user password.
int change_password()
{
    // Structure variables for store user data.
    struct r_account user;
    struct account change_password;

    // Take user email.
    printf("\nEmail : ");
    fgets(change_password.email, sizeof(change_password.email), stdin);
    change_password.email[strcspn(change_password.email, "\n")] = '\0';

    // Take answer of security question.
    printf("\nWhat Is Your Favourite Food : ");
    fgets(change_password.security_question, sizeof(change_password.security_question), stdin);
    change_password.security_question[strcspn(change_password.security_question, "\n")] = '\0';

    // Store each row from file.
    char row[MAX_LENGTH];

    // Open user database and temporary file.
    FILE *userDBS_open, *tmp_userDBS_open;
    userDBS_open = fopen("..\\database\\userDBS.csv", "r");

    // If file can not open show the error.
    if (userDBS_open == NULL)
    {
        perror("userDBS.csv");
        return 0;
    }

    tmp_userDBS_open = fopen("..\\database\\tmp_userDBS.csv", "w");

    // If file can not open show the error.
    if (tmp_userDBS_open == NULL)
    {
        perror("userDBS.csv");
        return 0;
    }

    // Read all user data from file.
    while (fgets(row, sizeof(row), userDBS_open) != NULL)
    {
        // Remove new row character.
        row[strcspn(row, "\n")] = '\0';

        // Split the row into different parts.
        char *field;

        // Store every value into structure.
        field = strtok(row, ",");
        strcpy(user.id, field);

        field = strtok(NULL, ",");
        strcpy(user.name, field);

        field = strtok(NULL, ",");
        strcpy(user.email, field);

        field = strtok(NULL, ",");
        strcpy(user.phone, field);

        field = strtok(NULL, ",");
        strcpy(user.user_name, field);

        field = strtok(NULL, ",");
        strcpy(user.pass, field);

        field = strtok(NULL, ",");
        strcpy(user.security_question, field);

        field = strtok(NULL, ",");
        strcpy(user.role, field);

        // Check email and security answer.
        if (strcmp(change_password.email, user.email) == 0 &&
            strcmp(change_password.security_question, user.security_question) == 0)
        {
            // Take new password.
            printf("Enter New Password : ");
            fgets(user.pass, sizeof(user.pass), stdin);
            user.pass[strcspn(user.pass, "\n")] = '\0';
        }

        // Write user data into temporary file.
        fprintf(tmp_userDBS_open, "%s,%s,%s,%s,%s,%s,%s,%s\n",
                user.id, user.name, user.email, user.phone,
                user.user_name, user.pass,
                user.security_question, user.role);
    }

    // Close both files.
    fclose(userDBS_open);
    fclose(tmp_userDBS_open);

    // Delete old database.
    remove("..\\database\\userDBS.csv");

    // If delete failed show the error.
    if (remove("..\\database\\userDBS.csv") != 0)
    {
        perror("remove");
    }

    // Rename temporary file.
    rename("..\\database\\tmp_userDBS.csv", "..\\database\\userDBS.csv");

    // If rename failed show the error.
    if (rename("..\\database\\tmp_userDBS.csv", "..\\database\\userDBS.csv") != 0)
    {
        perror("rename");
    }

    return 0;
}
int input_password(struct l_account *user)
{
    char password[30];
    int i = 0;
    char each_character;
    printf("\nPassword : ");
    while ((each_character = getch()) != 13)
    {
        password[i] = each_character;
        printf("*");
        i++;
    }
    printf("\n");
    strcpy(user->user_pass,password);
    return 0;
}
int input_password_two(struct r_account *user)
{
    char password[30];
    int i = 0;
    char each_character;
    printf("\nPassword : ");
    while ((each_character = getch()) != 13)
    {
        password[i] = each_character;
        printf("*");
        i++;
    }
    printf("\n");
    strcpy(user->pass,password);
    return 0;
}