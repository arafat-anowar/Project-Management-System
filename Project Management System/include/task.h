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

#define TMP_TASK_DBS "tmp_task.csv"
#define TEMP_TASK_FILE "tmp_task.csv"

#define MAX 100




struct t_details
{
    int unique_id;

    char task_id[15];
    char project_id[15];

    char name[50];
    char description[200];

    char priority[20];
    char status[20];

    char start_date[15];
    char end_date[15];

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