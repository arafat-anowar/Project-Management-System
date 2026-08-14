#ifndef PROJECT_H
#define PROJECT_H


#include <stdio.h>
#include <string.h>


#include "auth.h"
#include "utility.h"
#include "ui.h"


#define TWO 2

#define READ_MODE "r"
#define WRITE_MODE "w"
#define APPEND_MODE "a"

#define PROJECT_DBS_FILE "projectsDBS.csv"
#define TEMP_PROJECT_DBS_FILE "tmp_projectsDBS.csv"
#define SORT_PROJECT_FILE "sort_project.csv"

#define PROJECTS_FOLDER "Projects\\"
#define PROJECT_FILE_EXTENSION ".csv"

#define PROJECT_BOX_HEIGHT 39
#define UPDATE_PROJECT_BOX_HEIGHT 48
#define PROJECT_INPUT_BOX_HEIGHT 23
#define PROJECT_DELETE_BOX_HEIGHT 13
#define PROJECT_SHOW_BOX_HEIGHT 48

#define PROJECT_SHOW_X 12
#define PROJECT_ID_Y 5
#define PROJECT_NAME_Y 10
#define PROJECT_CATEGORY_Y 15
#define PROJECT_DESCRIPTION_Y 20
#define PROJECT_PRIORITY_Y 27
#define PROJECT_STATUS_Y 32
#define PROJECT_START_DATE_Y 37
#define PROJECT_END_DATE_Y 42

#define PROJECT_INPUT_X 10
#define PROJECT_INPUT_Y 6

#define PROJECT_FILE_PATH_SIZE 200
#define PROJECT_ID_OR_NAME_SIZE 50
#define PROJECT_FILE_NAME_SIZE 100
#define PROJECT_ARRAY_SIZE 1000

#define PROJECT_ID_SIZE 20

#define CATEGORY_SIZE 50
#define DESCRIPTION_SIZE 200
#define STARTDATE_SIZE 12
#define EXTENDDATE_SIZE 12
#define PRIORITY_SIZE 50
#define STATUS_SIZE 20

#define STATUS_BOX_WIDTH 68
#define STATUS_BOX_HEIGHT 13

#define PRIORITY_BOX_WIDTH 68
#define PRIORITY_BOX_HEIGHT 13

#define DEFAULT_STATUS "Created"
#define DELETE_STATUS "Deleted"


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
int compare_project_priority(const void *a, const void *b);


#endif