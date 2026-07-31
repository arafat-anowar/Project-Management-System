#include "auth.h"

int login()

{
    clear_screen();
    header_screen();
   user_login_screen();
    // Get Details from user
    struct l_account details;
    printf("\nUsername/Email: ");
    fgets( details.user_name_or_email,sizeof( details.user_name_or_email),stdin);
    details.user_name_or_email[strcspn(details.user_name_or_email,”\n”)]=’\0’;
    printf("\nPassword : ");
    fgets( details.user_password,sizeof( details.user_password),stdin);
   details.user_password[strcspn(details.user_password,”\n”)]=’\0’;
    int is_verified = login_verify(details.user_name_or_email, details.user_pass);
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
        delay_screen;
        login();
    }

    return 0;
}
int logout()
{

    return 0;
}
int password_verify()
{

    return 0;
}
int change_password()
{

    return 0;
}