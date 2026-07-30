// Header File Guard
#ifndef TASK_H
#define TASK_H

// Global Header Files
#include <stdio.h>
#include <string.h>

// Local Header Files

// Structures
struct task
{
    int unique_id;
    char project_id[20];
    char task_id[20];
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
int change_task_status();
int change_task_priority();
int extend_task_deadline();

#endif