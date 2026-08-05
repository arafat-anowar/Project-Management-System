#include "task.h"

int unique_task_id_generator()
{
    struct t_details task;

    int found = 0;

    int id = 10001;

    FILE *taskDBS_open;
    taskDBS_open = fopen("database\\taskDBS.csv", "r");

    char line[3000];

    while (fgets(line, sizeof(line), taskDBS_open) != NULL)
    {
        found = 1;

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
    }
    fclose(taskDBS_open);

    if (found == 0)
    {
        return id;
    }
    else
    {
        return (task.unique_id + 1);
    }
}
int generate_task_id(char id[], char path[])
{
    int found = 0;

    struct t_details task;

    strcpy(id, "T1001");

    FILE *taskDBS_open;
    taskDBS_open = fopen(path, "r");

    char line[3000];

    while (fgets(line, sizeof(line), taskDBS_open) != NULL)
    {
        found = 1;

        line[strcspn(line, "\n")] = '\0';

        char *token;

        token = strtok(line, ",");
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
    }
    fclose(taskDBS_open);

    if (found == 0)
    {
        return 0;
    }
    else
    {
        strcpy(id, task.task_id);
        int num_id[15];
        for (int i = 0, j = 1; id[j] != '\0'; i++, j++)
        {
            num_id[i] = (id[j] - '0');
        }
        int task_id = 0, id_len = strlen(id);
        for (int i = 0; i <= id_len - 2; i++)
        {
            int digit = num_id[i];
            for (int j = i; j <= id_len - 3; j++)
            {
                digit = digit * 10;
            }
            task_id += digit;
        }
        task_id++;
        int tmp = task_id;
        int j = (strlen(id) - 1);
        while (tmp != 0)
        {
            id[j] = ((tmp % 10) + '0');
            tmp /= 10;
            j--;
        }
        return 0;
    }
}

int create_task()
{
    char project_id_or_name[50];
    printf("\nProject ID or Name : ");
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    struct t_details task;
    struct p_details project;

    FILE *projectDBS_open;
    projectDBS_open = fopen("database\\projectDBS.csv", "r");
    char line[3000];
    while (fgets(line, sizeof(line), projectDBS_open) != NULL)
    {
        line[strcspn(line, "\n")] = 0;

        char *token;

        token = strtok(line, ",");
        strcpy(project.id, token);

        token = strtok(NULL, ",");
        strcpy(project.name, token);

        token = strtok(NULL, ",");
        strcpy(project.category, token);

        token = strtok(NULL, ",");
        strcpy(project.description, token);

        token = strtok(NULL, ",");
        strcpy(project.priority, token);

        token = strtok(NULL, ",");
        strcpy(project.status, token);

        token = strtok(NULL, ",");
        strcpy(project.start_date, token);

        token = strtok(NULL, ",");
        strcpy(project.end_date, token);

        token = strtok(NULL, ",");
        strcpy(project.created_by, token);

        if (strcmp(project_id_or_name, project.id) == 0 || strcmp(project_id_or_name, project.name) == 0)
        {
            strcpy(project_id_or_name, project.name);
            break;
        }
    }
    fclose(projectDBS_open);

    char path[100];

    strcpy(path, "database\\Projects\\");
    strcat(path, strlwr(project_id_or_name));
    strcat(path, ".csv");

    task.unique_id = unique_task_id_generator();
    generate_task_id(task.task_id, path);
    strcpy(task.project_id, project.id);

    printf("\nTask Name : ");
    fgets(task.name, sizeof(task.name), stdin);
    task.name[strcspn(task.name, "\n")] = '\0';

    printf("\nTask Description : ");
    fgets(task.description, sizeof(task.description), stdin);
    task.description[strcspn(task.description, "\n")] = '\0';

    printf("\nTask Priority : ");
    fgets(task.priority, sizeof(task.priority), stdin);
    task.priority[strcspn(task.priority, "\n")] = '\0';

    printf("\nTask Status : ");
    fgets(task.status, sizeof(task.status), stdin);
    task.status[strcspn(task.status, "\n")] = '\0';

    printf("\nTask Start Date : ");
    fgets(task.start_date, sizeof(task.start_date), stdin);
    task.start_date[strcspn(task.start_date, "\n")] = '\0';

    printf("\nTask End Date : ");
    fgets(task.end_date, sizeof(task.end_date), stdin);
    task.end_date[strcspn(task.end_date, "\n")] = '\0';

    strcpy(task.created_by, "arafatanowar");

    FILE *file_open_for_write_data;
    file_open_for_write_data = fopen("database\\taskDBS.csv", "a");
    fprintf(file_open_for_write_data, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.unique_id, task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
    fclose(file_open_for_write_data);

    FILE *file_open_for_write_data_in_separate_file;
    file_open_for_write_data_in_separate_file = fopen(path, "a");
    fprintf(file_open_for_write_data_in_separate_file, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
    fclose(file_open_for_write_data_in_separate_file);

    return 0;
}

int view_tasks()
{
    struct t_details task;

    FILE *taskDBS_open = fopen("database\\taskDBS.csv", "r");

    char line[3000];
    task_details_screen();
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

        printf("\n\n");
        printf("Unique Task ID : %d\n", task.unique_id);
        printf("Project ID     : %s\n", task.project_id);
        printf("Task ID        : %s\n", task.task_id);
        printf("Task Name      : %s\n", task.name);
        printf("Description    : %s\n", task.description);
        printf("Priority       : %s\n", task.priority);
        printf("Status         : %s\n", task.status);
        printf("Start Date     : %s\n", task.start_date);
        printf("Deadline       : %s\n", task.end_date);

        Sleep(1000);
    }
    fclose(taskDBS_open);

    return 0;
}

int update_task()
{
    char project_id_or_name[50];
    printf("\nProject ID or Name : ");
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    struct t_details task;
    struct p_details project;

    FILE *projectDBS_open;
    projectDBS_open = fopen("database\\projectDBS.csv", "r");
    char line[3000];
    while (fgets(line, sizeof(line), projectDBS_open) != NULL)
    {
        line[strcspn(line, "\n")] = 0;

        char *token;

        token = strtok(line, ",");
        strcpy(project.id, token);

        token = strtok(NULL, ",");
        strcpy(project.name, token);

        token = strtok(NULL, ",");
        strcpy(project.category, token);

        token = strtok(NULL, ",");
        strcpy(project.description, token);

        token = strtok(NULL, ",");
        strcpy(project.priority, token);

        token = strtok(NULL, ",");
        strcpy(project.status, token);

        token = strtok(NULL, ",");
        strcpy(project.start_date, token);

        token = strtok(NULL, ",");
        strcpy(project.end_date, token);

        token = strtok(NULL, ",");
        strcpy(project.created_by, token);

        if (strcmp(project_id_or_name, project.id) == 0 || strcmp(project_id_or_name, project.name) == 0)
        {
            strcpy(project_id_or_name, project.name);
            break;
        }
    }
    fclose(projectDBS_open);

    char path[100];

    strcpy(path, "database\\Projects\\");
    strcat(path, strlwr(project_id_or_name));
    strcat(path, ".csv");

    char task_id_or_name[50];
    printf("\nTask ID or Name : ");
    fgets(task_id_or_name, sizeof(task_id_or_name), stdin);
    task_id_or_name[strcspn(task_id_or_name, "\n")] = '\0';

    FILE *task_dbs_open, *tmp_task;
    task_dbs_open = fopen("database\\taskDBS.csv", "r");
    tmp_task = fopen("database\\tmp_task.csv", "w");

    while (fgets(line, sizeof(line), task_dbs_open) != NULL)
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

        if (strcmp(task.task_id, task_id_or_name) == 0 || strcmp(task.name, task_id_or_name) == 0)
        {
            task_update_dashboard(&task);
            fprintf(tmp_task, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.unique_id, task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
            continue;
        }
        fprintf(tmp_task, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.unique_id, task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
    }
    fclose(task_dbs_open);
    fclose(tmp_task);
    remove("database\\taskDBS.csv");
    rename("database\\tmp_task.csv", "database\\taskDBS.csv");

    FILE *separate_project_dbs_open, *tmp_for_separate_project_file;
    separate_project_dbs_open = fopen("database\\taskDBS.csv", "r");
    tmp_for_separate_project_file = fopen("database\\Projects\\tmp_task.csv", "w");

    while (fgets(line, sizeof(line), separate_project_dbs_open) != NULL)
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

        fprintf(tmp_for_separate_project_file, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
    }
    fclose(separate_project_dbs_open);
    fclose(tmp_for_separate_project_file);
    remove(path);
    rename("database\\Projects\\tmp_task.csv", path);

    return 0;
}

int delete_task()
{
    char project_id_or_name[50];
    printf("\nProject ID or Name : ");
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    struct t_details task;
    struct p_details project;

    FILE *projectDBS_open;
    projectDBS_open = fopen("database\\projectDBS.csv", "r");
    char line[3000];
    while (fgets(line, sizeof(line), projectDBS_open) != NULL)
    {
        line[strcspn(line, "\n")] = 0;

        char *token;

        token = strtok(line, ",");
        strcpy(project.id, token);

        token = strtok(NULL, ",");
        strcpy(project.name, token);

        token = strtok(NULL, ",");
        strcpy(project.category, token);

        token = strtok(NULL, ",");
        strcpy(project.description, token);

        token = strtok(NULL, ",");
        strcpy(project.priority, token);

        token = strtok(NULL, ",");
        strcpy(project.status, token);

        token = strtok(NULL, ",");
        strcpy(project.start_date, token);

        token = strtok(NULL, ",");
        strcpy(project.end_date, token);

        token = strtok(NULL, ",");
        strcpy(project.created_by, token);

        if (strcmp(project_id_or_name, project.id) == 0 || strcmp(project_id_or_name, project.name) == 0)
        {
            strcpy(project_id_or_name, project.name);
            break;
        }
    }
    fclose(projectDBS_open);

    char path[100];

    strcpy(path, "database\\Projects\\");
    strcat(path, strlwr(project_id_or_name));
    strcat(path, ".csv");

    char task_id_or_name[50];
    printf("\nTask ID or Name : ");
    fgets(task_id_or_name, sizeof(task_id_or_name), stdin);
    task_id_or_name[strcspn(task_id_or_name, "\n")] = '\0';

    FILE *separate_project_dbs_open, *tmp_for_separate_project_file;
    separate_project_dbs_open = fopen(path, "r");
    tmp_for_separate_project_file = fopen("database\\Projects\\tmp_task.csv", "w");

    while (fgets(line, sizeof(line), separate_project_dbs_open) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        char *token;

        token = strtok(line, ",");
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

        if (strcmp(task.task_id, task_id_or_name) == 0 || strcmp(task.name, task_id_or_name) == 0)
        {
            strcpy(task.status, "Deleted");
            fprintf(tmp_for_separate_project_file, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
            continue;
        }
        fprintf(tmp_for_separate_project_file, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
    }
    fclose(separate_project_dbs_open);
    fclose(tmp_for_separate_project_file);
    remove(path);
    rename("database\\Projects\\tmp_task.csv", path);

    FILE *task_dbs_open, *tmp_task;
    task_dbs_open = fopen("database\\taskDBS.csv", "r");
    tmp_task = fopen("database\\tmp_task.csv", "w");

    while (fgets(line, sizeof(line), task_dbs_open) != NULL)
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

        if (strcmp(task.task_id, task_id_or_name) == 0 || strcmp(task.name, task_id_or_name) == 0)
        {
            strcpy(task.status, "Deleted");
            fprintf(tmp_task, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.unique_id, task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
            continue;
        }
        fprintf(tmp_task, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.unique_id, task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
    }
    fclose(task_dbs_open);
    fclose(tmp_task);
    remove("database\\taskDBS.csv");
    rename("database\\tmp_task.csv", "database\\taskDBS.csv");
    return 0;
}

int view_tasks_by_project()
{
    char project_id_or_name[50];
    printf("\nProject ID or Name : ");
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    struct p_details project;

    FILE *projectDBS_open;
    projectDBS_open = fopen("database\\projectDBS.csv", "r");

    char line[3000];
    while (fgets(line, sizeof(line), projectDBS_open) != NULL)
    {
        line[strcspn(line, "\n")] = 0;

        char *token;

        token = strtok(line, ",");
        strcpy(project.id, token);

        token = strtok(NULL, ",");
        strcpy(project.name, token);

        token = strtok(NULL, ",");
        strcpy(project.category, token);

        token = strtok(NULL, ",");
        strcpy(project.description, token);

        token = strtok(NULL, ",");
        strcpy(project.priority, token);

        token = strtok(NULL, ",");
        strcpy(project.status, token);

        token = strtok(NULL, ",");
        strcpy(project.start_date, token);

        token = strtok(NULL, ",");
        strcpy(project.end_date, token);

        token = strtok(NULL, ",");
        strcpy(project.created_by, token);

        if (strcmp(project_id_or_name, project.id) == 0 || strcmp(project_id_or_name, project.name) == 0)
        {
            strcpy(project_id_or_name, project.name);
            break;
        }
    }
    fclose(projectDBS_open);

    char path[100];

    strcpy(path, "database\\Projects\\");
    strcat(path, strlwr(project_id_or_name));
    strcat(path, ".csv");

    struct t_details task;

    FILE *separate_project_dbs_open;
    separate_project_dbs_open = fopen(path, "r");
    task_details_screen();
    while (fgets(line, sizeof(line), separate_project_dbs_open) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        char *token;

        token = strtok(line, ",");
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

        printf("\n\n");
        printf("Task ID     : %s\n", task.task_id);
        printf("Project ID  : %s\n", task.project_id);
        printf("Task Name   : %s\n", task.name);
        printf("Description : %s\n", task.description);
        printf("Priority    : %s\n", task.priority);
        printf("Status      : %s\n", task.status);
        printf("Start Date  : %s\n", task.start_date);
        printf("Deadline    : %s\n", task.end_date);

        Sleep(1000);
    }
    fclose(separate_project_dbs_open);

    return 0;
}
int change_task_name(char name[])
{
    char updated_name[50];
    fgets(updated_name, sizeof(updated_name), stdin);
    updated_name[strcspn(updated_name, "\n")] = '\0';
    strcpy(name, updated_name);
    return 0;
}
int change_task_description(char description[])
{
    char updated_description[50];
    fgets(updated_description, sizeof(updated_description), stdin);
    updated_description[strcspn(updated_description, "\n")] = '\0';
    strcpy(description, updated_description);
    return 0;
}
int change_task_status(char status[])
{
    task_priority_dashboard(status);
    return 0;
}

int change_task_priority(char priority[])
{
    task_priority_dashboard(priority);
    return 0;
}
int change_task_start_date(char start_date[])
{
    char updated_start_date[50];
    fgets(updated_start_date, sizeof(updated_start_date), stdin);
    updated_start_date[strcspn(updated_start_date, "\n")] = '\0';
    strcpy(start_date, updated_start_date);
    return 0;
}
int extend_task_deadline(char deadline[])
{
    char updated_deadline[50];
    fgets(updated_deadline, sizeof(updated_deadline), stdin);
    updated_deadline[strcspn(updated_deadline, "\n")] = '\0';
    strcpy(deadline, updated_deadline);
    return 0;
}
int search_by_task_id_or_name()
{
    char task_id_or_name[50];
    fgets(task_id_or_name, sizeof(task_id_or_name), stdin);
    task_id_or_name[strcspn(task_id_or_name, "\n")] = '\0';

    FILE *taskDBS_open;
    taskDBS_open = fopen("database\\taskDBS.csv", "r");
    struct t_details task;

    char line[3000];
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

        if ((task.unique_id == *(task_id_or_name)) || strcmp(task.name, task_id_or_name) == 0)
        {
            task_details_screen();
            printf("\n\n");
            printf("Unique Task ID : %d\n", task.unique_id);
            printf("Project ID     : %s\n", task.project_id);
            printf("Task ID        : %s\n", task.task_id);
            printf("Task Name      : %s\n", task.name);
            printf("Description    : %s\n", task.description);
            printf("Priority       : %s\n", task.priority);
            printf("Status         : %s\n", task.status);
            printf("Start Date     : %s\n", task.start_date);
            printf("Deadline       : %s\n", task.end_date);
            break;
        }
    }
    return 0;
}
int search_task_by_status()
{
    char status[30];
    task_status_dashboard(status);
    FILE *taskDBS_open;
    taskDBS_open = fopen("database\\taskDBS.csv", "r");
    struct t_details task;
    task_details_screen();
    char line[3000];
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

        if (strcmp(task.status, status) == 0)
        {
            printf("\n\n");
            printf("Task ID        : %s\n", task.task_id);
            printf("Project ID     : %s\n", task.project_id);
            printf("Task Name      : %s\n", task.name);
            printf("Description    : %s\n", task.description);
            printf("Priority       : %s\n", task.priority);
            printf("Status         : %s\n", task.status);
            printf("Start Date     : %s\n", task.start_date);
            printf("Deadline       : %s\n", task.end_date);
        }
    }
    return 0;
}
int search_task_by_priority()
{
    char priority[30];
    task_priority_dashboard(priority);
    FILE *taskDBS_open;
    taskDBS_open = fopen("database\\taskDBS.csv", "r");
    struct t_details task;
    task_details_screen();
    char line[3000];
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

        if (strcmp(task.status, priority) == 0)
        {
            printf("\n\n");
            printf("Task ID        : %s\n", task.task_id);
            printf("Project ID     : %s\n", task.project_id);
            printf("Task Name      : %s\n", task.name);
            printf("Description    : %s\n", task.description);
            printf("Priority       : %s\n", task.priority);
            printf("Status         : %s\n", task.status);
            printf("Start Date     : %s\n", task.start_date);
            printf("Deadline       : %s\n", task.end_date);
        }
    }
    return 0;
}
int sort_tasks()
{
    FILE *taskDBS_open;
    taskDBS_open = fopen("database\\taskDBS.csv", "r");

    struct t_details task[MAX];

    char line[3000];
    int i = 0;
    while (fgets(line, sizeof(line), taskDBS_open) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        char *token;

        token = strtok(line, ",");
        task[i].unique_id = atoi(token);

        token = strtok(NULL, ",");
        strcpy(task[i].task_id, token);

        token = strtok(NULL, ",");
        strcpy(task[i].project_id, token);

        token = strtok(NULL, ",");
        strcpy(task[i].name, token);

        token = strtok(NULL, ",");
        strcpy(task[i].description, token);

        token = strtok(NULL, ",");
        strcpy(task[i].priority, token);

        token = strtok(NULL, ",");
        strcpy(task[i].status, token);

        token = strtok(NULL, ",");
        strcpy(task[i].start_date, token);

        token = strtok(NULL, ",");
        strcpy(task[i].end_date, token);

        token = strtok(NULL, ",");
        strcpy(task[i].created_by, token);

        i++;
    }
    fclose(taskDBS_open);

    qsort(task, i, sizeof(struct t_details), sort_by_priority);

    FILE *sort_task_open;
    sort_task_open = fopen("database\\sort_task.csv", "w");
    for (int j = 0; j < i; j++)
    {
        fprintf(sort_task_open, "%d,%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",(j+1), task[j].unique_id, task[j].task_id, task[j].project_id, task[j].name, task[j].description, task[j].priority, task[j].status, task[j].start_date, task[j].end_date, task[j].created_by);
    }

    fclose(sort_task_open);
    return 0;
}
int sort_by_priority(void *a, void *b)
{
    struct t_details *task_a = (struct t_details *)a;
    struct t_details *task_b = (struct t_details *)b;

    int priority_of_a, priority_of_b;

    if (strcmp(task_a->priority, "High") == 0)
        priority_of_a = 3;
    else if (strcmp(task_a->priority, "Medium") == 0)
        priority_of_a = 2;
    else
        priority_of_a = 1;

    if (strcmp(task_b->priority, "High") == 0)
        priority_of_b = 3;
    else if (strcmp(task_b->priority, "Medium") == 0)
        priority_of_b = 2;
    else
        priority_of_b = 1;

    if (priority_of_b != priority_of_a)
        return priority_of_b - priority_of_a;

    return strcmp(task_a->end_date, task_b->end_date);
}