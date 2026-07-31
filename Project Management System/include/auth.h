// Header File Guard
#ifndef AUTH_H
#define AUTH_H

// Global Header Files
#include<stdio.h>
#include<string.h>
#include<conio.h>

// Local Header Files
#include "user.h"
#include "menu.h"
struct l_account{
    char user_name_or_email[30];
    char user_pass[30];
};
 
// Function Prototypes
int login();
int logout();
int password_verify();
int change_password();

#endif