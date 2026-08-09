#ifndef AUTH_H
#define AUTH_H


#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <errno.h>


#include "ui.h"


#define DATABASE_PATH "..\\database\\"

#define USER_DBS "..\\database\\userDBS.csv"
#define CREDENTIAL_DBS  "..\\database\\credentialDBS.csv"
#define TMP_CREDENTIAL_DBS  "..\\database\\tmp_credentialDBS.csv"
#define LOG_DBS "..\\database\\log.csv"

#define PROJECT_FOLDER "Projects"
#define PROJECT_DBS "projectsDBS.csv"
#define TASK_DBS "taskDBS.csv"
#define SORT_TASK_DBS "sort_task.csv"
#define SORT_PROJECT_DBS "sort_project.csv"

#define DEFAULT_ROLE "Individual"

#define LOGIN_STATUS "login"
#define LOGOUT_STATUS "logout"

#define FIRST_USER_ID "U1001"

#define BOX_WIDTH 100
#define REGISTER_BOX_HEIGHT 37
#define LOGIN_BOX_HEIGHT 19
#define CHANGE_PASSWORD_BOX_HEIGHT 19

#define SCREEN_OFFSET_Y 13
#define SOMETHING_WENT_WRONG_OFFSET_X 10
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
#define ZERO 0
#define TWO 2

#define PHONE_LENGTH 10

#define USERNAME_SIZE 30
#define PATH_SIZE 200

#define READ_MODE "r"
#define WRITE_MODE "w"
#define APPEND_MODE "a"

#define ID_SIZE 20
#define NAME_SIZE 30
#define EMAIL_SIZE 30
#define PHONE_SIZE 13
#define PASSWORD_SIZE 30
#define SECURITY_QUESTION_SIZE 15
#define ROLE_SIZE 20
#define LOGIN_STATUS_SIZE 20
#define USERNAME_OR_EMAIL_SIZE 30


struct l_account
{
    char user_name_or_email[USERNAME_OR_EMAIL_SIZE];
    char user_pass[PASSWORD_SIZE];
};


struct r_account
{
    char id[ID_SIZE];
    char name[NAME_SIZE];
    char email[EMAIL_SIZE];
    char phone[PHONE_SIZE];
    char user_name[USERNAME_SIZE];
    char pass[PASSWORD_SIZE];
    char security_question[SECURITY_QUESTION_SIZE];
    char role[ROLE_SIZE];
    char login_status[LOGIN_STATUS_SIZE];
};


struct account
{
    char email[EMAIL_SIZE];
    char security_question[SECURITY_QUESTION_SIZE];
    char new_pass[PASSWORD_SIZE];
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