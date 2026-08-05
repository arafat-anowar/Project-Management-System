// Header File Guard
#ifndef TASK_H
#define TASK_H

// Global Header Files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <errno.h>
// Local Header Files
#include "ui.h"
#include "utility.h"
#include "project.h"

#define MAX 10000

// Structures
struct t_details
{
    int unique_id;
    char task_id[20];
    char project_id[20];
    char name[50];
    char description[200];
    char priority[20];
    char status[20];
    char start_date[15];
    char end_date[15];
    char created_by[20];
};

// Function Prototypes
int create_task();
int view_tasks();
int update_task();
int delete_task();
int view_tasks_by_project();
int change_task_name(char name[]);
int change_task_description(char description[]);
int change_task_priority(char priority[]);
int change_task_status(char status[]);
int change_task_start_date(char start_date[]);
int extend_task_deadline(char deadline[]);
int generate_task_id(char id[],char path[]);
int unique_task_id_generator();
int sort_tasks();
int search_by_task_id_or_name();
int search_task_by_status();
int search_task_by_priority();
int sort_by_priority(void *a, void *b);

#endif