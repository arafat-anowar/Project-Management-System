#include "task.h"

int create_task()
{
    struct task details;

    unique_task_id_generator(details.unique_id);

    printf("\nProject ID : ");
    fgets(details.project_id, sizeof(details.project_id), stdin);
    details.project_id[strcspn(details.project_id, "\n")] = '\0';

    struct project info;
    char line[3000];
    char path[100] = "";

    FILE *projectDBS_open = fopen("database\\projectDBS.csv", "r");

    fgets(line, sizeof(line), projectDBS_open);

    while (fgets(line, sizeof(line), projectDBS_open) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        char *token;

        token = strtok(line, ",");
        strcpy(info.id, token);

        token = strtok(NULL, ",");
        strcpy(info.category, token);

        token = strtok(NULL, ",");
        strcpy(info.name, token);

        token = strtok(NULL, ",");
        strcpy(info.description, token);

        token = strtok(NULL, ",");
        strcpy(info.priority, token);

        token = strtok(NULL, ",");
        strcpy(info.status, token);

        token = strtok(NULL, ",");
        strcpy(info.progress, token);

        token = strtok(NULL, ",");
        strcpy(info.start_date, token);

        token = strtok(NULL, ",");
        strcpy(info.end_date, token);

        token = strtok(NULL, ",");
        strcpy(info.created_by, token);

        if (strcmp(details.project_id, info.id) == 0)
        {
            strcpy(path, "database\\Projects\\");
            strcat(path, strlwr(info.name));
            strcat(path, ".csv");
            break;
        }
    }
    fclose(projectDBS_open);

    generate_task_id(details.task_id, path);

    printf("\nTask Name : ");
    fgets(details.name, sizeof(details.name), stdin);
    details.name[strcspn(details.name, "\n")] = '\0';

    printf("\nDescription : ");
    fgets(details.description, sizeof(details.description), stdin);
    details.description[strcspn(details.description, "\n")] = '\0';

    printf("\nPriority : ");
    fgets(details.priority, sizeof(details.priority), stdin);
    details.priority[strcspn(details.priority, "\n")] = '\0';

    printf("\nStatus : ");
    fgets(details.status, sizeof(details.status), stdin);
    details.status[strcspn(details.status, "\n")] = '\0';

    printf("\nStart Date : ");
    fgets(details.start_date, sizeof(details.start_date), stdin);
    details.start_date[strcspn(details.start_date, "\n")] = '\0';

    printf("\nDeadline : ");
    fgets(details.end_date, sizeof(details.end_date), stdin);
    details.end_date[strcspn(details.end_date, "\n")] = '\0';

    strcpy(details.created_by, "mdarafatanowar");

    FILE *taskDBS_open = fopen("database\\taskDBS.csv", "a");

    fprintf(taskDBS_open, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", details.unique_id, details.task_id, details.project_id, details.name, details.description, details.priority, details.status, details.start_date, details.end_date, details.created_by);

    fclose(taskDBS_open);

    FILE *dedicated_project_file_open = fopen(path, "a");

    fprintf(dedicated_project_file_open, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", details.task_id, details.project_id, details.name, details.description, details.priority, details.status, details.start_date, details.end_date, details.created_by);

    fclose(dedicated_project_file_open);

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
        strcpy(details.unique_id, token);

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
int change_task_name()
{
    return 0;
}
int change_task_description()
{
    return 0;
}
int change_task_status()
{
    return 0;
}

int change_task_priority()
{
    return 0;
}
int change_task_start_date()
{
    return 0;
}
int extend_task_deadline()
{
    return 0;
}