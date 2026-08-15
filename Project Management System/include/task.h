#ifndef TASK_H
#define TASK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "ui.h"

#define PATH_BUFFER_SIZE 200
#define MAX_LENGTH_OF_DATA_IN_FILE 3000

#define TASK_ID_INITIAL "T1001"
#define UNIQUE_TASK_ID_INITIAL 10001
#define TMP_TASK_DBS "tmp_task.csv"
#define TEMP_TASK_FILE "tmp_task.csv"

#define TASK_ARRAY_SIZE 1000

#define TASK_ID_SIZE 15
#define TASK_PROJECT_ID_SIZE 15

#define TASK_NAME_SIZE 50
#define TASK_DESCRIPTION_SIZE 200

#define TASK_STARTDATE_SIZE 15
#define TASK_EXTENDDATE_SIZE 15

#define TASK_STATUS_SIZE 30
#define TASK_PRIORITY_SIZE 30

#define TASK_ID_OR_NAME_SIZE 100
#define TASK_PROJECT_ID_OR_NAME_SIZE 100

#define TASK_BOX_HEIGHT 33

#define TASK_DETAILS_BOX_HEIGHT 53

#define TASK_STATUS_BOX_WIDTH 66
#define TASK_STATUS_BOX_HEIGHT 13

#define TASK_PRIORITY_BOX_WIDTH 66
#define TASK_PRIORITY_BOX_HEIGHT 13

#define TASK_INPUT_X 10

#define TASK_NAME_Y 6
#define TASK_DESCRIPTION_Y 11
#define TASK_PRIORITY_Y 18
#define TASK_START_DATE_Y 23
#define TASK_END_DATE_Y 28

#define TASK_DETAILS_INPUT_X 10

#define TASK_UNIQUE_ID_Y 5
#define TASK_DETAILS_TASK_ID_Y 10
#define TASK_DETAILS_PROJECT_ID_Y 15
#define TASK_DETAILS_NAME_Y 20
#define TASK_DETAILS_DESCRIPTION_Y 25
#define TASK_DETAILS_PRIORITY_Y 32
#define TASK_DETAILS_STATUS_Y 37
#define TASK_DETAILS_START_DATE_Y 42
#define TASK_DETAILS_END_DATE_Y 47
#define TASK_ID_Y TASK_DETAILS_TASK_ID_Y
#define TASK_PROJECT_ID_Y TASK_DETAILS_PROJECT_ID_Y

#define TASK_SEARCH_INPUT_Y 5

struct t_details
{
   int unique_id;

   char task_id[TASK_ID_SIZE];
   char project_id[TASK_PROJECT_ID_SIZE];

   char name[TASK_NAME_SIZE];
   char description[TASK_DESCRIPTION_SIZE];

   char priority[TASK_PRIORITY_SIZE];
   char status[TASK_STATUS_SIZE];

   char start_date[TASK_STARTDATE_SIZE];
   char end_date[TASK_EXTENDDATE_SIZE];

   char created_by[20];
};

int unique_task_id_generator();

int generate_task_id(char id[],char path[]);

int create_task();

int view_tasks();

int update_task();

int delete_task();

int view_tasks_by_project();

int change_task_name(char name[]);

int change_task_description( char description[]);

int change_task_status(char status[]);

int change_task_priority(char priority[]);

int change_task_start_date(char start_date[]);

int extend_task_deadline(char deadline[]);

int search_by_task_id_or_name();

int search_task_by_status();

int search_task_by_priority();

int sort_tasks();

int sort_by_priority(const void *a,const void *b);

#endif