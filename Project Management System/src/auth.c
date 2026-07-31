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

    return 0;
}
int password_verify(char username_or_email[],char password[])
{

    return 0;
}
int change_password()
{

    return 0;
}
