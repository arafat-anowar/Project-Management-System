#include "task.h"

int create_task()
{
    return 0;
}

int view_tasks()
{
    struct task details;

    FILE *taskDBS_open = fopen("database\\taskDBS.csv", "r");

    char line[3000];
    task_details_screen();
    while (fgets(line, sizeof(line), taskDBS_open) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        char *token;

        token = strtok(line, ",");
        details.unique_id = atoi(token);

        token = strtok(NULL, ",");
        strcpy(details.task_id, token);

        token = strtok(NULL, ",");
        strcpy(details.project_id, token);

        token = strtok(NULL, ",");
        strcpy(details.name, token);

        token = strtok(NULL, ",");
        strcpy(details.description, token);

        token = strtok(NULL, ",");
        strcpy(details.priority, token);

        token = strtok(NULL, ",");
        strcpy(details.status, token);

        token = strtok(NULL, ",");
        strcpy(details.start_date, token);

        token = strtok(NULL, ",");
        strcpy(details.end_date, token);

        token = strtok(NULL, ",");
        strcpy(details.created_by, token);

        printf("\n\n");
        printf("Project ID  : %s\n", details.project_id);
        printf("Task ID     : %s\n", details.task_id);
        printf("Task Name   : %s\n", details.name);
        printf("Description : %s\n", details.description);
        printf("Priority    : %s\n", details.priority);
        printf("Status      : %s\n", details.status);
        printf("Start Date  : %s\n", details.start_date);
        printf("Deadline    : %s\n", details.end_date);
        Sleep(1500);
    }
    fclose(taskDBS_open);

    return 0;
}

int update_task()
{

    return 0;
}

int delete_task()
{
    return 0;
}

int view_tasks_by_project()
{
    return 0;
}
int change_task_name(char name[])
{
    char new_name[50];
    printf("Enter New Task Name : ");
    fgets(new_name,sizeof(new_name),stdin);
    new_name[strcspn(new_name,"\n")]='\0';

    strcpy(name, new_name);

    return 0;
}
int change_task_description(char description[])
{
    char new_description[200];

    printf("Enter New Task Description : ");
    fgets(new_description, sizeof(new_description), stdin);
    new_description[strcspn(new_description, "\n")] = '\0';

    strcpy(description, new_description);

    return 0;
}
int change_task_status(char status[])
{
    char new_status[20];

    printf("Enter New Task Status : ");
    fgets(new_status, sizeof(new_status), stdin);
    new_status[strcspn(new_status, "\n")] = '\0';

    strcpy(status, new_status);

    return 0;
}

int change_task_priority(char priority[])
{
    char new_priority[20];

    printf("Enter New Task Priority : ");
    fgets(new_priority, sizeof(new_priority), stdin);
    new_priority[strcspn(new_priority, "\n")] = '\0';

    strcpy(priority, new_priority);

    return 0;
}
int change_task_start_date(char start_date[])
{
    char new_start_date[15];

    printf("Enter New Task Start Date (YYYY-MM-DD) : ");
    fgets(new_start_date, sizeof(new_start_date), stdin);
    new_start_date[strcspn(new_start_date, "\n")] = '\0';

    strcpy(start_date, new_start_date);

    return 0;
}
int extend_task_deadline(char deadline[])
{
    char new_deadline[15];

    printf("Enter New Task Deadline (YYYY-MM-DD) : ");
    fgets(new_deadline, sizeof(new_deadline), stdin);
    new_deadline[strcspn(new_deadline, "\n")] = '\0';

    strcpy(deadline, new_deadline);

    return 0;
}