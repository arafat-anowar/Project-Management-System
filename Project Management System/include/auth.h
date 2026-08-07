// Header File Guard
#ifndef AUTH_H
#define AUTH_H

// Global Header Files
#include <stdio.h>
#include <string.h>
#include <conio.h>

// Local Header Files
#include "ui.h"
// Macros
#define MAX_LENGTH_OF_DATA_IN_FILE 3000

// Structure for user login information
struct l_account
{
    char user_name_or_email[30];
    char user_pass[30];
};

// Structure for user account information
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
    char login_status[20];
};

// Structure for password recovery information
struct account
{
    char email[30];
    char security_question[15];
    char new_pass[30];
};

// Function Prototypes
int create_user();
int login();
int logout();
int change_password();
int generate_user_id(char id[]);
int change_login_status(char status[]);
int password_verify(char username_or_email[], char password[]);
int input_password(char password[]);
int validate_user_name(char username[]);
int validate_email(char email[]);
int validate_phone(char phone[]);
int get_user_name(char username[]);
int create_directories(char username[]);

#endif