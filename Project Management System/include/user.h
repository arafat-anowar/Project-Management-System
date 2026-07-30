#ifndef USER_H
#define USER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user
{
    char id[20];
    char name_1st[20];
    char name_last[20];
    char name[30];
    char email[30];
    char phn_num[11];
    char user_name[30];
    char user_pass[20];
    char security_ques[10];
    char user_role[20];
};
// Function Prototypes
int create_user();
#endif