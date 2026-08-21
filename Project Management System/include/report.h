// report header file start

#ifndef REPORT_H
#define REPORT_H

// global header files
#include <stdio.h>
#include <string.h>

// local header files
#include "project.h"
#include "task.h"
#include "ui.h"
#include "utility.h"

// function prototypes
int project_summary_report();
int project_progress_report();
int overdue_projects_report();
int high_priority_projects_report();
int task_summary_report();
int overdue_tasks_report();
int high_priority_tasks_report();
int pending_active_tasks_report();

#endif

// report header file end