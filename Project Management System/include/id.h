// Header File Guard
#ifndef ID_H
#define ID_H

// Global Header Files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Local Header Files
#include "user.h"
#include "project.h"
#include "task.h"

// Function Prototypes
int generate_user_id(char id[]);
int generate_project_id(char id[]);
int generate_task_id(char id[],char path[]);

#endif