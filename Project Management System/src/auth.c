#include "auth.h"

int generate_user_id(char id[])
{
    // Copy U1001 as Default ID
    strcpy(id, "U1001");

    // Declare a Integer Variable
    int found = 0;

    // Open UserDBS File In Memory
    FILE *userDBS_open = fopen("database\\userDBS.csv", "r");

    // Declare a String Variable For Read Data From File
    char line[210];

    // Declare a Structure Variable
    struct r_account user;

    // Read Data From File With Loop
    while (fgets(line, sizeof(line), userDBS_open) != NULL)
    {   
        // If any data found the found variable is 1
        found = 1;

        // Tokenization The Line and Copy Every Token To Their Variable
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, ",");
        strcpy(user.id, token);
        token = strtok(NULL, ",");
        strcpy(user.name, token);
        token = strtok(NULL, ",");
        strcpy(user.email, token);
        token = strtok(NULL, ",");
        strcpy(user.phone, token);
        token = strtok(NULL, ",");
        strcpy(user.user_name, token);
        token = strtok(NULL, ",");
        strcpy(user.pass, token);
        token = strtok(NULL, ",");
        strcpy(user.security_question, token);
        token = strtok(NULL, ",");
        strcpy(user.role, token);
    }
    
    fclose(userDBS_open);

    if (found == 0)
    {
        return 0;
    }
    else
    {
        strcpy(id, user.id);
        int num_id[20];
        for (int i = 0, j = 1; id[j] != '\0'; i++, j++)
        {
            num_id[i] = (id[j] - '0');
        }

        int usr_id = 0, id_len = strlen(id);
        for (int i = 0; i <= id_len - 2; i++)
        {
            int digit = num_id[i];
            for (int j = i; j <= id_len - 3; j++)
            {
                digit *= 10;
            }
            usr_id += digit;
        }
        usr_id++;
        int tmp = usr_id;
        int j = (strlen(id) - 1);
        while (tmp != 0)
        {
            id[j] = ((tmp % 10) + '0');
            tmp /= 10;
            j--;
        }
        return 0;
    }
}
int create_user()
{
    struct r_account user;

    generate_user_id(user.id);
    printf("\nName : ");
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';

    printf("\nEmail : ");
    fgets(user.email, sizeof(user.email), stdin);
    user.email[strcspn(user.email, "\n")] = '\0';

    printf("\nPhone Number : +880 ");
    fgets(user.phone, sizeof(user.phone), stdin);
    user.phone[strcspn(user.phone, "\n")] = '\0';

    printf("\nUsername : ");
    fgets(user.user_name, sizeof(user.user_name), stdin);
    user.user_name[strcspn(user.user_name, "\n")] = '\0';

    printf("\nPassword : ");
    fgets(user.pass, sizeof(user.pass), stdin);
    user.pass[strcspn(user.pass, "\n")] = '\0';

    printf("\nWhat Is Your Favourite Food : ");
    fgets(user.security_question, sizeof(user.security_question), stdin);
    user.security_question[strcspn(user.security_question, "\n")] = '\0';

    strcpy(user.role, "Individual");

    FILE *file_open_for_write_data;

    file_open_for_write_data = fopen("database\\userDBS.csv", "a");
    fprintf(file_open_for_write_data, "%s,%s,%s,%s,%s,%s,%s,%s\n", user.id, user.name, user.email, user.phone, user.user_name, user.pass, user.security_question, user.role);
    fclose(file_open_for_write_data);

    main_menu();
    return 0;
}
int login()

{
    clear_screen();
    header_screen();
    user_login_screen();
    // Get Details from user
    struct l_account user;
    printf("\nUsername/Email: ");
    fgets(user.user_name_or_email, sizeof(user.user_name_or_email), stdin);
    user.user_name_or_email[strcspn(user.user_name_or_email, "\n")] = '\0';
    printf("\nPassword : ");
    fgets(user.user_pass, sizeof(user.user_pass), stdin);
    user.user_pass[strcspn(user.user_pass, "\n")] = '\0';
    int is_verified = password_verify(user.user_name_or_email, user.user_pass);
    // If verified user redirect to dashboard otherwise redirect to login menu
    if (is_verified == 1)
    {
        dashboard();
    }
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

int logout()
{
    main_menu();
    return 0;
}

int password_verify(char username_or_email[], char password[])
{
    struct r_account user;
    char line[200];
    int found = 0;
    FILE *userDBS_open;
    userDBS_open = fopen("database\\userDBS.csv", "r");
    while (fgets(line, sizeof(line), userDBS_open) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        char *token;

        token = strtok(line, ",");
        strcpy(user.id, token);

        token = strtok(NULL, ",");
        strcpy(user.name, token);

        token = strtok(NULL, ",");
        strcpy(user.email, token);

        token = strtok(NULL, ",");
        strcpy(user.phone, token);

        token = strtok(NULL, ",");
        strcpy(user.user_name, token);

        token = strtok(NULL, ",");
        strcpy(user.pass, token);

        token = strtok(NULL, ",");
        strcpy(user.security_question, token);

        token = strtok(NULL, ",");
        strcpy(user.role, token);

        if ((strcmp(username_or_email, user.email) == 0 && strcmp(password, user.pass) == 0) || (strcmp(username_or_email, user.user_name) == 0 && strcmp(password, user.pass) == 0))
        {
            found = 1;
            break;
        }
    }

    fclose(userDBS_open);

    if (found == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int change_password()
{

    return 0;
}
