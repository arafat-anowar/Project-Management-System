#ifndef TASK_H
#define TASK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "ui.h"
#include "project.h"

#define TASK_PATH_BUFFER_SIZE 200
#define TASK_FILE_DATA_SIZE 3000

#define INITIAL_TASK_ID_VALUE "T1001"
#define INITIAL_UNIQUE_TASK_ID_VALUE 10001

#define TEMP_TASK_DATABASE_FILE "tmp_task.csv"
#define TASK_FILE_EXTENSION ".csv"
#define TASK_ARRAY_SIZE 1000

#define TASK_ID_SIZE 15
#define TASK_PROJECT_ID_SIZE 15
#define TASK_NAME_SIZE 50
#define TASK_DESCRIPTION_SIZE 200
#define TASK_START_DATE_SIZE 15
#define TASK_END_DATE_SIZE 15
#define TASK_STATUS_SIZE 30
#define TASK_PRIORITY_SIZE 30
#define TASK_SEARCH_SIZE 100
#define PROJECT_SEARCH_SIZE 100

#define TASK_BOX_HEIGHT 33
#define TASK_DETAILS_BOX_HEIGHT 53
#define TASK_STATUS_BOX_WIDTH 66
#define TASK_STATUS_BOX_HEIGHT 13
#define TASK_PRIORITY_BOX_WIDTH 66
#define TASK_PRIORITY_BOX_HEIGHT 13

#define TASK_CREATE_NAME_OFFSET_Y 6
#define TASK_CREATE_DESCRIPTION_OFFSET_Y 11
#define TASK_CREATE_PRIORITY_OFFSET_Y 18
#define TASK_CREATE_START_DATE_OFFSET_Y 23
#define TASK_CREATE_END_DATE_OFFSET_Y 28

#define TASK_DETAILS_UNIQUE_ID_OFFSET_Y 5
#define TASK_DETAILS_TASK_ID_OFFSET_Y 10
#define TASK_DETAILS_PROJECT_ID_OFFSET_Y 15
#define TASK_DETAILS_NAME_OFFSET_Y 20
#define TASK_DETAILS_DESCRIPTION_OFFSET_Y 25
#define TASK_DETAILS_PRIORITY_OFFSET_Y 32
#define TASK_DETAILS_STATUS_OFFSET_Y 37
#define TASK_DETAILS_START_DATE_OFFSET_Y 42
#define TASK_DETAILS_END_DATE_OFFSET_Y 47

#define TASK_VIEW_PROJECT_TASK_ID_Y_OFFSET 6
#define TASK_VIEW_PROJECT_PROJECT_ID_Y_OFFSET 11
#define TASK_VIEW_PROJECT_NAME_Y_OFFSET 16
#define TASK_VIEW_PROJECT_DESCRIPTION_Y_OFFSET 21
#define TASK_VIEW_PROJECT_PRIORITY_Y_OFFSET 28
#define TASK_VIEW_PROJECT_STATUS_Y_OFFSET 33
#define TASK_VIEW_PROJECT_START_DATE_Y_OFFSET 38
#define TASK_VIEW_PROJECT_END_DATE_Y_OFFSET 43

#define TASK_INPUT_X 10
#define TASK_NAME_Y 6
#define TASK_DESCRIPTION_Y 11
#define TASK_PRIORITY_Y 18
#define TASK_START_DATE_Y 23
#define TASK_END_DATE_Y 28

#define TASK_DETAILS_INPUT_X 10
#define TASK_UNIQUE_ID_Y 5
#define TASK_ID_Y 10
#define TASK_PROJECT_ID_Y 15
#define TASK_NAME_DETAILS_Y 20
#define TASK_DESCRIPTION_DETAILS_Y 25
#define TASK_PRIORITY_DETAILS_Y 32
#define TASK_STATUS_DETAILS_Y 37
#define TASK_START_DATE_DETAILS_Y 42
#define TASK_END_DATE_DETAILS_Y 47

#define TASK_SEARCH_INPUT_Y 5
#define SCREEN_START_Y 13

#define DEFAULT_TASK_STATUS "Created"
#define DELETED_TASK_STATUS "Deleted"

struct t_details
{
    int unique_id;
    char task_id[TASK_ID_SIZE];
    char project_id[TASK_PROJECT_ID_SIZE];
    char name[TASK_NAME_SIZE];
    char description[TASK_DESCRIPTION_SIZE];
    char priority[TASK_PRIORITY_SIZE];
    char status[TASK_STATUS_SIZE];
    char start_date[TASK_START_DATE_SIZE];
    char end_date[TASK_END_DATE_SIZE];
    char created_by[20];
};

int unique_task_id_generator();
int generate_task_id(char id[], char path[]);
int create_task();
int view_tasks();
int update_task();
int delete_task();
int view_tasks_by_project();
int change_task_name(char name[]);
int change_task_description(char description[]);
int change_task_status(char status[]);
int change_task_priority(char priority[]);
int change_task_start_date(char start_date[]);
int extend_task_deadline(char deadline[]);
int search_by_task_id_or_name();
int search_task_by_status();
int search_task_by_priority();
int sort_tasks();
int sort_by_priority(const void *a, const void *b);


#endif