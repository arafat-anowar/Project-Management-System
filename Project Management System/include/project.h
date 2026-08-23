// project header file start

#ifndef PROJECT_H
#define PROJECT_H

// global header files
#include <stdio.h>
#include <string.h>

// local header files
#include "auth.h"
#include "task.h"
#include "utility.h"
#include "ui.h"

// macros

#define PROJECT_FILE_MODE_READ "r"
#define PROJECT_FILE_MODE_WRITE "w"
#define PROJECT_FILE_MODE_APPEND "a"

#define PROJECT_DATABASE_FILE "projectsDBS.csv"
#define TEMP_PROJECT_DATABASE_FILE "tmp_projectsDBS.csv"
#define SORTED_PROJECT_FILE "sort_project.csv"

#define PROJECT_FOLDER_NAME "Projects\\"
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
#define MAX_LENGTH_OF_DATA_IN_FILE 800
#define PROJECT_ID_OR_NAME_SIZE 50
#define PROJECT_FILE_NAME_SIZE 100
#define PROJECT_ARRAY_SIZE 1000
#define PROJECT_ID_SIZE 20

#define PROJECT_CATEGORY_SIZE 50
#define PROJECT_DESCRIPTION_SIZE 200
#define PROJECT_START_DATE_SIZE 12
#define PROJECT_END_DATE_SIZE 12
#define PROJECT_PRIORITY_SIZE 50
#define PROJECT_STATUS_SIZE 20

#define STATUS_BOX_WIDTH 100
#define STATUS_BOX_HEIGHT 15
#define PRIORITY_BOX_WIDTH 100
#define PRIORITY_BOX_HEIGHT 13

#define DEFAULT_PROJECT_STATUS "Created"
#define DELETED_PROJECT_STATUS "Deleted"
#define CANCELLED_PROJECT_STATUS "Cancelled"
#define COMPLETED_PROJECT_STATUS "Completed"
#define IN_PROGRESS_PROJECT_STATUS "In Progress"

// structure for create project
struct p_details
{
    char id[PROJECT_ID_SIZE];
    char name[PROJECT_ID_OR_NAME_SIZE];
    char category[PROJECT_CATEGORY_SIZE];
    char description[PROJECT_DESCRIPTION_SIZE];
    char priority[PROJECT_PRIORITY_SIZE];
    char status[PROJECT_STATUS_SIZE];
    char start_date[PROJECT_START_DATE_SIZE];
    char end_date[PROJECT_END_DATE_SIZE];
    char created_by[20];
};

// function prototypes

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
int update_cancelled_project_tasks();
int update_created_project_status();
int update_project_status_by_tasks();

#endif

// project header file end