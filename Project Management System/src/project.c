#include "project.h"

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
            id[j] = ((tmp % 10) + '0');
            tmp /= 10;
            j--;
        }
        return 0;
    }
}

int create_project()
{
    struct project details;
    printf("\nProject name : ");
    fgets(details.name, sizeof(details.name), stdin);
    details.name[strcspn(details.name, "\n")] = '\0';

    printf("\nCategory : ");
    fgets(details.category, sizeof(details.category), stdin);
    details.category[strcspn(details.category, "\n")] = '\0';

    printf("\nDescription : ");
    fgets(details.description, sizeof(details.description), stdin);
    details.description[strcspn(details.description, "\n")] = '\0';

    printf("\nPriority : ");
    fgets(details.priority, sizeof(details.priority), stdin);
    details.priority[strcspn(details.priority, "\n")] = '\0';

    strcpy(details.status,"Created");

    printf("\nStart Date : ");
    fgets(details.start_date, sizeof(details.start_date), stdin);
    details.start_date[strcspn(details.start_date, "\n")] = '\0';

    printf("\nDeadline : ");
    fgets(details.end_date, sizeof(details.end_date), stdin);
    details.end_date[strcspn(details.end_date, "\n")] = '\0';

    strcpy(details.created_by,"arafatanowar");

    FILE *open_projectDBS = fopen("database\\projectDBS.csv", "a");

    fprintf(open_projectDBS, "%s,%s,%s,%s,%s,%s,%s,%s\n",
            details.name, details.category, details.description,
            details.priority, details.status,
            details.start_date, details.end_date, details.created_by);

    fclose(open_projectDBS);

    char filepath[100];
    strcpy(filepath, "database\\Projects\\");
    strcat(filepath, strlwr(details.name));
    strcat(filepath, ".csv");

    FILE *project_file_create = fopen(filepath, "w");
    fclose(project_file_create);

    return 0;
}

int view_projects()
{

    return 0;
}

int update_project()
{

    return 0;
}
int delete_project()
{
    return 0;
}

int search_project()
{
    return 0;
}
int change_project_name()
{
    return 0;
}
int change_project_category()
{
    return 0;
}
int change_project_description()
{
    return 0;
}
int change_project_status()
{
    return 0;
}

int change_project_priority()
{
    return 0;
}
int change_project_start_date()
{
    return 0;
}
int extend_project_deadline()
{
    return 0;
}
int sort_projects()
{
    return 0;
}
int search_by_project_id_or_name()
{
    return 0;
}
int search_project_by_status()
{
    return 0;
}
int search_project_by_priority()
{
    return 0;
}