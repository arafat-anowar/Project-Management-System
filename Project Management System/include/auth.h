// auth header file start

#ifndef AUTH_H
#define AUTH_H

// global header files
#include <stdio.h>
#include <string.h>
#include <conio.h>

// local header files
#include "ui.h"

// macros

#define DATABASE_DIR "..\\database\\"

#define USER_DATABASE_FILE "..\\database\\userDBS.csv"
#define CREDENTIAL_DATABASE_FILE "..\\database\\credentialDBS.csv"
#define TEMP_CREDENTIAL_DATABASE_FILE "..\\database\\tmp_credentialDBS.csv"
#define LOG_FILE "..\\database\\log.csv"

#define PROJECTS_FOLDER "Projects"
#define PROJECT_DATABASE_FILE "projectsDBS.csv"
#define TASK_DATABASE_FILE "taskDBS.csv"
#define SORTED_TASK_FILE "sort_task.csv"
#define SORTED_PROJECT_FILE "sort_project.csv"

#define DEFAULT_ROLE_NAME "Individual"
#define LOGIN_STATUS_VALUE "login"
#define LOGOUT_STATUS_VALUE "logout"
#define FIRST_USER_ID_VALUE "U1001"

#define CONTAINER_WIDTH 100
#define REGISTER_FORM_HEIGHT 37
#define LOGIN_FORM_HEIGHT 19
#define CHANGE_PASSWORD_FORM_HEIGHT 19

#define SCREEN_START_Y 13
#define ERROR_MESSAGE_OFFSET_X 10
#define INPUT_FIELD_OFFSET_X 10
#define PHONE_FIELD_OFFSET_X 14

#define REGISTER_NAME_FIELD_Y 6
#define REGISTER_EMAIL_FIELD_Y 11
#define REGISTER_PHONE_FIELD_Y 16
#define REGISTER_USERNAME_FIELD_Y 21
#define REGISTER_PASSWORD_FIELD_Y 26
#define REGISTER_SECURITY_FIELD_Y 31

#define LOGIN_USERNAME_FIELD_Y 6
#define LOGIN_PASSWORD_FIELD_Y 12

#define CHANGE_PASSWORD_EMAIL_FIELD_Y 6
#define CHANGE_PASSWORD_SECURITY_FIELD_Y 11
#define CHANGE_PASSWORD_NEW_PASSWORD_FIELD_Y 16

#define ENTER 13
#define BACKSPACE 8
#define ESCAPE 27

#define VALID 1
#define INVALID 0
#define ZERO 0
#define TWO 2

#define MAX_PHONE_LENGTH 10
#define MAX_USERNAME_LENGTH 30
#define MAX_PATH_LENGTH 200

#define FILE_MODE_READ "r"
#define FILE_MODE_WRITE "w"
#define FILE_MODE_APPEND "a"

#define MAX_ID_LENGTH 20
#define MAX_NAME_LENGTH 30
#define MAX_EMAIL_LENGTH 30
#define MAX_PHONE_FIELD_LENGTH 13
#define MAX_PASSWORD_LENGTH 30
#define MAX_SECURITY_QUESTION_LENGTH 15
#define MAX_ROLE_LENGTH 20
#define MAX_LOGIN_STATUS_LENGTH 20
#define MAX_USERNAME_OR_EMAIL_LENGTH 30

#define MAX_LENGTH_OF_DATA_IN_FILE 3000

#define FILE_OPEN_ERROR "fop"
#define FILE_CLOSE_ERROR "fcl"
#define SOMETHING_FAILED "mem"
// structure for login 
struct l_account
{
    char user_name_or_email[MAX_USERNAME_OR_EMAIL_LENGTH];
    char user_pass[MAX_PASSWORD_LENGTH];
};

// structure for create account
struct r_account
{
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone[MAX_PHONE_FIELD_LENGTH];
    char user_name[MAX_USERNAME_LENGTH];
    char pass[MAX_PASSWORD_LENGTH];
    char security_question[MAX_SECURITY_QUESTION_LENGTH];
    char role[MAX_ROLE_LENGTH];
    char login_status[MAX_LOGIN_STATUS_LENGTH];
};

// structure for change pass
struct account
{
    char email[MAX_EMAIL_LENGTH];
    char security_question[MAX_SECURITY_QUESTION_LENGTH];
    char new_pass[MAX_PASSWORD_LENGTH];
};


// function prototypes
int create_user();
int login();
int logout();
int change_password();
int generate_user_id(char id[]);
int change_login_status(char status[]);
int password_verify(char username_or_email[], char password[]);
int input_password(char password[]);
char *get_user_name();
int validate_user_name(char username[]);
int validate_email(char email[]);
int validate_phone(char phone[]);
int create_directories(char username[]);

#endif

// auth header file end