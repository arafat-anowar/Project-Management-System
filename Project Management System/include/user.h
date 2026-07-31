#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <string.h>

#include "id.h"

struct details
{
    char id[20];
    char name[30];
    char email[30];
    char phone[13];
    char user_name[20];
    char pass[30];
    char security_ques[15];
    char role[20];
};

// Function Prototypes
int create_user();
#endif