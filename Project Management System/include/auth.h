// Header File Guard
#ifndef AUTH_H
#define AUTH_H

// Global Header Files
#include<stdio.h>
#include<string.h>
#include<conio.h>

// Local Header Files
#include "utility.h"
#include "ui.h"

// Structures
struct l_account{
    char user_name_or_email[30];
    char user_pass[30];
};
struct r_account
{
    char id[20];
    char name[30];
    char email[30];
    char phone[13];
    char user_name[20];
    char pass[30];
    char security_question[15];
    char role[20];
};

// Function Prototypes
int login();
int logout();
int password_verify(char username_or_email[],char password[]);
int change_password();
int create_user();
int generate_user_id(char id[]);

#endif