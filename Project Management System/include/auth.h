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

// Function Prototypes
int login();
int logout();
int password_verify();
int change_password();

#endif