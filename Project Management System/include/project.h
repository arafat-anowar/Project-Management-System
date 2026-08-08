// Header File Guard
#ifndef PROJECT_H
#define PROJECT_H

// Global Header Files
#include <stdio.h>
#include <string.h>

// Local Header Files
#include "auth.h"
#include "utility.h"
#include "ui.h"

#define PROJECT_ID_INITIAL "P1001"

#define PROJECT_BOX_WIDTH 100
#define PROJECT_BOX_HEIGHT 48
#define CREATE_PROJECT_BOX_HEIGHT 39

#define PRIORITY_BOX_WIDTH 68
#define PRIORITY_BOX_HEIGHT 13

#define PROJECT_INPUT_X 10
#define PROJECT_SHOW_X 12

#define PROJECT_ID_Y 5
#define PROJECT_NAME_Y 10
#define PROJECT_CATEGORY_Y 15
#define PROJECT_DESCRIPTION_Y 20
#define PROJECT_PRIORITY_Y 27
#define PROJECT_STATUS_Y 32
#define PROJECT_START_DATE_Y 37
#define PROJECT_END_DATE_Y 42

#define PROJECT_DBS_FILE "projectsDBS.csv"
#define TEMP_PROJECT_DBS_FILE "tmp_projectsDBS.csv"
#define PROJECT_FILE_EXTENSION ".csv"

#define STATUS_BUFFER_SIZE 50
#define PATH_BUFFER_SIZE 200

#define PROJECT_SHOW_BOX_HEIGHT 48

#define STATUS_BOX_WIDTH 68
#define STATUS_BOX_HEIGHT 13

// Structures
struct p_details
{
    char id[20];
    char name[50];
    char category[20];
    char description[200];
    char priority[20];
    char status[20];
    char start_date[15];
    char end_date[15];
    char created_by[20];
};

// Function Prototypes
int create_project();
int view_projects();
int update_project();
int delete_project();
int change_project_name(char name[]);
int change_project_category(char category[]);
int change_project_description(char description[]);
int change_project_status(char status[], int x, int y);
int change_project_priority(char priority[], int x, int y);
int change_project_start_date(char start_date[]);
int extend_project_deadline(char deadline[]);
int generate_project_id(char id[]);
int sort_projects();
int search_by_project_id_or_name();
int search_project_by_status();
int search_project_by_priority();
int get_path(char path[]);
int create_project_screen(int x, int y);

#endif