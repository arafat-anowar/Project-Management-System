#ifndef AUTH_H
#define AUTH_H


#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <errno.h>

#include "ui.h"

// Macros
#define DATABASE_PATH "..\\database\\"

#define USER_DBS DATABASE_PATH "userDBS.csv"
#define CREDENTIAL_DBS DATABASE_PATH "credentialDBS.csv"
#define TMP_CREDENTIAL_DBS DATABASE_PATH "tmp_credentialDBS.csv"
#define LOG_DBS DATABASE_PATH "log.csv"

#define PROJECT_FOLDER "Projects"
#define PROJECT_DBS "projectsDBS.csv"
#define TASK_DBS "taskDBS.csv"
#define SORT_TASK_DBS "sort_task.csv"

#define DEFAULT_ROLE "Individual"

#define LOGIN_STATUS "login"
#define LOGOUT_STATUS "logout"

#define FIRST_USER_ID "U1001"

#define BOX_WIDTH 100
#define REGISTER_BOX_HEIGHT 37
#define LOGIN_BOX_HEIGHT 19
#define CHANGE_PASSWORD_BOX_HEIGHT 19

#define SCREEN_OFFSET_Y 13

#define INPUT_OFFSET_X 10
#define PHONE_INPUT_OFFSET_X 14

#define REGISTER_NAME_Y 6
#define REGISTER_EMAIL_Y 11
#define REGISTER_PHONE_Y 16
#define REGISTER_USERNAME_Y 21
#define REGISTER_PASSWORD_Y 26
#define REGISTER_SECURITY_Y 31

#define LOGIN_USERNAME_Y 6
#define LOGIN_PASSWORD_Y 12

#define CHANGE_PASSWORD_EMAIL_Y 6
#define CHANGE_PASSWORD_SECURITY_Y 11
#define CHANGE_PASSWORD_NEWPASS_Y 16

#define ENTER_KEY 13
#define BACKSPACE_KEY 8

#define VALID 1
#define INVALID 0

#define PHONE_LENGTH 10

#define USERNAME_BUFFER_SIZE 30
#define PATH_BUFFER_SIZE 200

#define READ_MODE "r"
#define WRITE_MODE "w"
#define APPEND_MODE "a"


struct l_account
{
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
    char login_status[20];
};


struct account
{
    char email[30];
    char security_question[15];
    char new_pass[30];
};


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