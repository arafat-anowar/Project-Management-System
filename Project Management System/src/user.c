#include "user.h"

int create_user()
{
    struct details user;

    strcpy(user.id, generate_user_id(user.id));
    printf("\nEnter Your Name : ");
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcps(user.name, "\n")] = "\0";

    printf("\nEnter Your Email : ");
    fgets(user.email, sizeof(user.email), stdin);
    user.email[strcps(user.email, "\n")] = "\0";

    printf("\nEnter Your Phone Number : ");
    fgets(user.phone, sizeof(user.phone), stdin);
    user.phone[strcps(user.phone, "\n")] = "\0";

    printf("\nEnter Your User Name : ");
    fgets(user.user_name, sizeof(user.user_name), stdin);
    user.user_name[strcps(user.user_name, "\n")] = "\0";

    printf("\nEnter Your Password : ");
    fgets(user.pass, sizeof(user.pass), stdin);
    user.pass[strcps(user.pass, "\n")] = "\0";

    printf("\nWhat's Your Favourite Food : ");
    fgets(user.security_ques, sizeof(user.security_ques), stdin);
    user.security_ques[strcps(user.security_ques, "\n")] = "\0";

    printf("\nWhat Is Your Role on the Project");
    fgets(user.role, sizeof(user.role), stdin);
    user.role[strcps(user.role, "\n")] = "\0";

    return 0;
}