#include "id.h"

int generate_user_id(char id[])
{
    strcpy(id, "U1001");
    int found = 0;
    FILE *userDBS_open = fopen("database\\userDBS.csv", "r");
    char line[210];
    struct details account;
    while (fgets(line, sizeof(line), userDBS_open) != NULL)
    {

        found = 1;
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, ",");
        strcpy(account.id, token);
        token = strtok(NULL, ",");
        strcpy(account.name, token);
        token = strtok(NULL, ",");
        strcpy(account.email, token);
        token = strtok(NULL, ",");
        strcpy(account.phone, token);
        token = strtok(NULL, ",");
        strcpy(account.user_name, token);
        token = strtok(NULL, ",");
        strcpy(account.pass, token);
        token = strtok(NULL, ",");
        strcpy(account.security_ques, token);
        token = strtok(NULL, ",");
        strcpy(account.role, token);
    }
    fclose(userDBS_open);
    if (found == 0)
    {
        return 0;
    }
    else
    {
        strcpy(id, account.id);
        int num_id[20];
        for (int i = 0, j = 1; id[j] != '\0'; i++, j++)
        {
            num_id[i] = (id[j] - '0');
        }

        int usr_id = 0, id_len = strlen(id);
        for (int i = 0; i <= id_len - 2; i++)
        {
            int digit = num_id[i];
            for (int j = i; j <= id_len - 3; j++)
            {
                digit *= 10;
            }
            usr_id += digit;
        }
        usr_id++;
        int tmp = usr_id;
        int j = (strlen(id) - 1);
        while (tmp != 0)
        {
            id[j] = ((tmp % 10)+'0');
            tmp /= 10;
            j--;
        }
        return 0;
    }
}

int generate_project_id(char id[])
{
    strcpy(id, "P1001");
    int found = 0;
    struct project details;
    FILE *projectDBS_open;
    projectDBS_open = fopen("database\\projectDBS.csv", "r");
    char line[1500];
    while (fgets(line, sizeof(line), projectDBS_open) != NULL)
    {
        found = 1;
        line[strcspn(line, "\n")] = '\0';
        char *token;
        token = strtok(line, ",");
        strcpy(details.id, token);
        token = strtok(NULL, ",");
        strcpy(details.category, token);
        token = strtok(NULL, ",");
        strcpy(details.name, token);
        token = strtok(NULL, ",");
        strcpy(details.description, token);
        token = strtok(NULL, ",");
        strcpy(details.priority, token);
        token = strtok(NULL, ",");
        strcpy(details.status, token);
        token = strtok(NULL, ",");
        strcpy(details.progress, token);
        token = strtok(NULL, ",");
        strcpy(details.start_date, token);
        token = strtok(NULL, ",");
        strcpy(details.end_date, token);
        token = strtok(NULL, ",");
        strcpy(details.created_by, token);
    }
    fclose(projectDBS_open);
    if (found == 0)
    {
        return 0;
    }
    else
    {
        strcpy(id, details.id);
        int num_id[20];
        for (int i = 0, j = 1; id[j] != '\0'; i++, j++)
        {
            num_id[i] = (id[j] - '0');
        }

        int project_id = 0, id_len = strlen(id);
        for (int i = 0; i <= id_len - 2; i++)
        {
            int digit = num_id[i];
            for (int j = i; j <= id_len - 3; j++)
            {
                digit *= 10;
            }
            project_id += digit;
        }
        project_id++;
        int tmp = project_id;
        int j = (strlen(id) - 1);
        while (tmp != 0)
        {
            id[j] = tmp % 10;
            tmp /= 10;
            j--;
        }
        return 0;
    }
}

int generate_task_id(char id[], char path[])
{
    int found = 0;
    struct task details;
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
        details.unique_id = atoi(token);
        token = strtok(NULL, ",");
        strcpy(details.project_id, token);
        token = strtok(NULL, ",");
        strcpy(details.task_id, token);
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
    }
    fclose(taskDBS_open);
    if (found == 0)
    {
        return 0;
    }
    else
    {
        strcpy(id, details.task_id);
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
            id[j] = tmp % 10;
            tmp /= 10;
            j--;
        }
        return 0;
    }
}

int unique_task_id_generator(int id)
{
    struct task details;
    int found = 0;
    id = 10001;
    FILE *taskDBS_open;
    taskDBS_open = fopen("database\\taskDBS.csv", "r");
    char line[3000];
    while (fgets(line, sizeof(line), taskDBS_open) != NULL)
    {
        found = 1;
        line[strcspn(line, "\n")] = '\0';
        char *token;
        token = strtok(line, ",");
        details.unique_id = atoi(token);
        token = strtok(NULL, ",");
        strcpy(details.project_id, token);
        token = strtok(NULL, ",");
        strcpy(details.task_id, token);
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
    }
    fclose(taskDBS_open);
    if (found == 0)
    {
        return 0;
    }
    else
    {
        return ++id;
    }
}