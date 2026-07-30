#ifndef USER_H
#define USER_H

struct r_account
{
    char user_id[20];
    char name[30];
    char email[30];
    char phone[11];
    char user_name[20];
    char user_pass[30];
    char security_question[15];
    char user_role[20];
};
// Function Prototypes
int create_user();
#endif