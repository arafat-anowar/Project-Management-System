#include "report.h"
#include "task.h"
#include "project.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>

int deadline_has_passed(char end_date[])
{
    time_t now = time(NULL);
    struct tm *today_tm = localtime(&now);

    char today[15];
    sprintf(today, "%04d-%02d-%02d", today_tm->tm_year + 1900, today_tm->tm_mon + 1, today_tm->tm_mday);

    return strcmp(end_date, today) < 0;
}

int completes_tasks()
{
    struct t_details task;

    FILE *taskDBS_open = fopen("..\\database\\taskDBS.csv", "r");
    if (taskDBS_open == NULL)
    {
        printf("\nNo tasks found.\n");
        return 0;
    }

    char line[MAX_LENGTH_OF_DATA_IN_FILE];
    int count = 0;

    task_details_screen();
    printf("\n--- Completed Tasks ---\n");

    while (fgets(line, sizeof(line), taskDBS_open) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        char *token;

        token = strtok(line, ",");
        task.unique_id = atoi(token);

        token = strtok(NULL, ",");
        strcpy(task.task_id, token);

        token = strtok(NULL, ",");
        strcpy(task.project_id, token);

        token = strtok(NULL, ",");
        strcpy(task.name, token);

        token = strtok(NULL, ",");
        strcpy(task.description, token);

        token = strtok(NULL, ",");
        strcpy(task.priority, token);

        token = strtok(NULL, ",");
        strcpy(task.status, token);

        token = strtok(NULL, ",");
        strcpy(task.start_date, token);

        token = strtok(NULL, ",");
        strcpy(task.end_date, token);

        token = strtok(NULL, ",");
        strcpy(task.created_by, token);

        if (strcmp(task.status, "Completed") == 0)
        {
            printf("\nTask ID     : %s\n", task.task_id);
            printf("Project ID  : %s\n", task.project_id);
            printf("Name        : %s\n", task.name);
            printf("Deadline    : %s\n", task.end_date);
            count++;
        }
    }
    fclose(taskDBS_open);

    printf("\nTotal Completed Tasks : %d\n", count);
    return 0;
}

int pending_tasks()
{
    struct t_details task;

    FILE *taskDBS_open = fopen("..\\database\\taskDBS.csv", "r");
    if (taskDBS_open == NULL)
    {
        printf("\nNo tasks found.\n");
        return 0;
    }

    char line[MAX_LENGTH_OF_DATA_IN_FILE];
    int count = 0;

    task_details_screen();
    printf("\n--- Pending Tasks ---\n");

    while (fgets(line, sizeof(line), taskDBS_open) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        char *token;

        token = strtok(line, ",");
        task.unique_id = atoi(token);

        token = strtok(NULL, ",");
        strcpy(task.task_id, token);

        token = strtok(NULL, ",");
        strcpy(task.project_id, token);

        token = strtok(NULL, ",");
        strcpy(task.name, token);

        token = strtok(NULL, ",");
        strcpy(task.description, token);

        token = strtok(NULL, ",");
        strcpy(task.priority, token);

        token = strtok(NULL, ",");
        strcpy(task.status, token);

        token = strtok(NULL, ",");
        strcpy(task.start_date, token);

        token = strtok(NULL, ",");
        strcpy(task.end_date, token);

        token = strtok(NULL, ",");
        strcpy(task.created_by, token);

        if (strcmp(task.status, "Completed") != 0)
        {
            printf("\nTask ID     : %s\n", task.task_id);
            printf("Project ID  : %s\n", task.project_id);
            printf("Name        : %s\n", task.name);
            printf("Status      : %s\n", task.status);
            printf("Deadline    : %s\n", task.end_date);
            count++;
        }
    }
    fclose(taskDBS_open);

    printf("\nTotal Pending Tasks : %d\n", count);
    return 0;
}

int overdue_tasks()
{
    struct t_details task;

    FILE *taskDBS_open = fopen("..\\database\\taskDBS.csv", "r");
    if (taskDBS_open == NULL)
    {
        printf("\nNo tasks found.\n");
        return 0;
    }

    char line[MAX_LENGTH_OF_DATA_IN_FILE];
    int count = 0;

    task_details_screen();
    printf("\n--- Overdue Tasks ---\n");

    while (fgets(line, sizeof(line), taskDBS_open) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        char *token;

        token = strtok(line, ",");
        task.unique_id = atoi(token);

        token = strtok(NULL, ",");
        strcpy(task.task_id, token);

        token = strtok(NULL, ",");
        strcpy(task.project_id, token);

        token = strtok(NULL, ",");
        strcpy(task.name, token);

        token = strtok(NULL, ",");
        strcpy(task.description, token);

        token = strtok(NULL, ",");
        strcpy(task.priority, token);

        token = strtok(NULL, ",");
        strcpy(task.status, token);

        token = strtok(NULL, ",");
        strcpy(task.start_date, token);

        token = strtok(NULL, ",");
        strcpy(task.end_date, token);

        token = strtok(NULL, ",");
        strcpy(task.created_by, token);

        if (strcmp(task.status, "Completed") != 0 && deadline_has_passed(task.end_date))
        {
            printf("\nTask ID     : %s\n", task.task_id);
            printf("Project ID  : %s\n", task.project_id);
            printf("Name        : %s\n", task.name);
            printf("Status      : %s\n", task.status);
            printf("Deadline    : %s\n", task.end_date);
            count++;
        }
    }
    fclose(taskDBS_open);

    printf("\nTotal Overdue Tasks : %d\n", count);
    return 0;
}

