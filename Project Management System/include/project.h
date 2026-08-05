// Header File Guard
#ifndef PROJECT_H
#define PROJECT_H

// Global Header Files
#include <stdio.h>
#include <string.h>

// Local Header Files
#include "ui.h"

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
int change_project_name();
int change_project_category();
int change_project_description();
int change_project_priority();
int change_project_status();
int change_project_start_date();
int extend_project_deadline();
int generate_project_id(char id[]);
int sort_projects();
int search_by_project_id_or_name();
int search_project_by_status();
int search_project_by_priority();

#endif