#include "auth.h"

int login()

{
    clear_screen();
    header_screen();
    user_login_screen();
    // Get Details from user
    struct l_account details;
    printf("\nUsername/Email: ");
    fgets(details.user_name_or_email, sizeof(details.user_name_or_email), stdin);
    details.user_name_or_email[strcspn(details.user_name_or_email, "\n")] = '\0';
    printf("\nPassword : ");
    fgets(details.user_pass, sizeof(details.user_pass), stdin);
    details.user_pass[strcspn(details.user_pass, "\n")] = '\0';
    int is_verified = password_verify(details.user_name_or_email, details.user_pass);
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
    struct details account;
    char line[200];
    int found = 0;
    FILE *userDBS_open;
    userDBS_open = fopen("database\\userDBS.csv", "r");
    while (fgets(line, sizeof(line), userDBS_open) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        char *token;

        token = strtok(line, ",");
        strcpy(account.id, token);

        token = strtok(NULL, ",");
        strcpy(account.name, token);

        token = strtok(NULL, ",");
        strcpy(account.email, token);

        token = strtok(NULL, ",");
        strcpy(account.phone, token);

        token = strtok(NULL, ",");
        strcpy(account.user_name, token);

        token = strtok(NULL, ",");
        strcpy(account.pass, token);

        token = strtok(NULL, ",");
        strcpy(account.security_ques, token);

        token = strtok(NULL, ",");
        strcpy(account.role, token);
        
        if ((strcmp(username_or_email, account.email) == 0 && strcmp(password, account.pass) == 0) ||( strcmp(username_or_email, account.user_name) == 0 && strcmp(password, account.pass) == 0))
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
