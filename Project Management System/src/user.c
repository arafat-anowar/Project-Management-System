#include "user.h"

int create_user()
{
    struct details user;

    strcpy(user.id, generate_user_id(user.id));
    printf("\nEnter Your Name : ");
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcpn(user.name, "\n")] = "\0";

    printf("\nEnter Your Email : ");
    fgets(user.email, sizeof(user.email), stdin);
    user.email[strcpn(user.email, "\n")] = "\0";

    printf("\nEnter Your Phone Number : ");
    fgets(user.phone, sizeof(user.phone), stdin);
    user.phone[strcpn(user.phone, "\n")] = "\0";

    printf("\nEnter Your User Name : ");
    fgets(user.user_name, sizeof(user.user_name), stdin);
    user.user_name[strcpn(user.user_name, "\n")] = "\0";

    printf("\nEnter Your Password : ");
    fgets(user.pass, sizeof(user.pass), stdin);
    user.pass[strcpn(user.pass, "\n")] = "\0";

    printf("\nWhat's Your Favourite Food : ");
    fgets(user.security_ques, sizeof(user.security_ques), stdin);
    user.security_ques[strcpn(user.security_ques, "\n")] = "\0";

    printf("\nWhat Is Your Role on the Project");
    fgets(user.role, sizeof(user.role), stdin);
    user.role[strcpn(user.role, "\n")] = "\0";

    FILE *file_open_for_write_data;
    file_open_for_write_data = fopen("database\\userDBS.csv", "a");
    fprintf(file_open_for_write_data, "ID: %20d, Name: %30s, Email: %30s, Phone Number: %11s, User Name: %20s, Password: %30s, Favourite Food: %15s, Role: %20s\n", user.id, user.name, user.email, user.phone, user.user_name, user.pass, user.security_ques, user.role);
    fclose(file_open_for_write_data);

    return 0;
}
