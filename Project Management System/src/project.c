#include "project.h"

int generate_project_id(char id[])
{
    strcpy(id, "P1001");

    int found = 0;

    struct p_details project;

    FILE *projectDBS_open;
    projectDBS_open = fopen("database\\projectDBS.csv", "r");

    char line[3000];
    while (fgets(line, sizeof(line), projectDBS_open) != NULL)
    {
        found = 1;
        line[strcspn(line, "\n")] = '\0';
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
    }
    fclose(projectDBS_open);

    if (found == 0)
    {
        return 0;
    }
    else
    {
        strcpy(id, project.id);
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
    struct p_details project;
    generate_project_id(project.id);
    printf("\nProject name : ");
    fgets(project.name, sizeof(project.name), stdin);
    project.name[strcspn(project.name, "\n")] = '\0';

    printf("\nCategory : ");
    fgets(project.category, sizeof(project.category), stdin);
    project.category[strcspn(project.category, "\n")] = '\0';

    printf("\nDescription : ");
    fgets(project.description, sizeof(project.description), stdin);
    project.description[strcspn(project.description, "\n")] = '\0';

    printf("\nPriority : ");
    fgets(project.priority, sizeof(project.priority), stdin);
    project.priority[strcspn(project.priority, "\n")] = '\0';

    strcpy(project.status, "Created");

    printf("\nStart Date : ");
    fgets(project.start_date, sizeof(project.start_date), stdin);
    project.start_date[strcspn(project.start_date, "\n")] = '\0';

    printf("\nDeadline : ");
    fgets(project.end_date, sizeof(project.end_date), stdin);
    project.end_date[strcspn(project.end_date, "\n")] = '\0';

    strcpy(project.created_by, "arafatanowar");

    FILE *open_projectDBS = fopen("database\\projectDBS.csv", "a");

    fprintf(open_projectDBS, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", project.id,
            project.name, project.category, project.description,
            project.priority, project.status,
            project.start_date, project.end_date, project.created_by);

    fclose(open_projectDBS);

    char filepath[100];
    strcpy(filepath, "database\\Projects\\");
    strcat(filepath, strlwr(project.name));
    strcat(filepath, ".csv");

    FILE *project_file_create = fopen(filepath, "w");
    fclose(project_file_create);

    return 0;
}

int view_projects()
{
    struct p_details data;

    printf("\n");
    printf("+----------------------------------------------------------------------+\n");
    printf("|                         PROJECT DETAILS                              |\n");
    printf("+----------------------+-----------------------------------------------+\n");
    printf("| Project ID           | %-s |\n", data.id);
    printf("| Category             | %-s |\n", data.category);
    printf("| Project Name         | %-s |\n", data.name);
    printf("| Description          | %-s |\n", data.description);
    printf("| Priority             | %-s |\n", data.priority);
    printf("| Status               | %-s |\n", data.status);
    printf("| Starting Date        | %-s |\n", data.start_date);
    printf("| Deadline             | %-s |\n", data.end_date);
    printf("+----------------------+-----------------------------------------------+\n");

    return 0;
}

int update_project()
{
    struct p_details data;

    int choice;
    project_update_dashboard();

    return 0;
}

int delete_project()
{
    char project_id_or_name[50];

    printf("Enter Project ID or Project Name : ");
    scanf("%s", project_id_or_name);

    struct p_details project;

    FILE *file_open_for_delete_project, *write_data_to_new_file;

    file_open_for_delete_project = fopen("database\\projectDBS.csv", "r");
    write_data_to_new_file = fopen("database\\tmp.csv", "w");

    while (fscanf(file_open_for_delete_project, "%s,%s,%s,%s,%s,%s,%s,%s,%s",
            project.id, project.category, project.name, project.description, project.priority, 
            project.status, project.start_date, project.end_date, project.created_by) != EOF)
    {

        if (strcmp(project.id, project_id_or_name) == 0 || strcmp(project.name, project_id_or_name) == 0)
        {
            strcpy(project.status, "Deleted");
            fprintf(write_data_to_new_file, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", 
                project.id, project.category, project.name, project.description, project.priority, 
                project.status, project.start_date, project.end_date, project.created_by);
            char path[100];
            strcpy(path, "database\\Projects\\");
            strcat(path, strlwr(project.name));
            strcat(path, ".csv");
            remove(path);
            continue;
        }

        fprintf(write_data_to_new_file, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", project.id, project.category, 
            project.name, project.description, project.priority, project.status, project.start_date, 
            project.end_date, project.created_by);
    }

    fclose(file_open_for_delete_project);
    fclose(write_data_to_new_file);

    remove("database\\projectDBS.csv");
    rename("database\\tmp.csv", "database\\projectDBS.csv");

    project_management_dashboard();

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