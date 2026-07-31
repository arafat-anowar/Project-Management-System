#include "project.h"

struct project data;
int create_project()
{

    printf("\nProject name : ");
    fgets(data.name, sizeof(data.name), stdin);
    data.name[strcspn(data.name, "\n")] = '\0';

    printf("\nCategory : ");
    fgets(data.category, sizeof(data.category), stdin);
    data.category[strcspn(data.category, "\n")] = '\0';

    printf("\nDescription : ");
    fgets(data.description, sizeof(data.description), stdin);
    data.description[strcspn(data.description, "\n")] = '\0';

    printf("\nPriority : ");
    fgets(data.priority, sizeof(data.priority), stdin);
    data.priority[strcspn(data.priority, "\n")] = '\0';

    printf("\nStatus : ");
    fgets(data.name, sizeof(data.name), stdin);
    data.name[strcspn(data.name, "\n")] = '\0';

    printf("\nProgress : ");
    fgets(data.progress, sizeof(data.progress), stdin);
    data.progress[strcspn(data.progress, "\n")] = '\0';

    printf("\nStart Date : ");
    fgets(data.start_date, sizeof(data.start_date), stdin);
    data.start_date[strcspn(data.start_date, "\n")] = '\0';

    printf("\nEnd data : ");
    fgets(data.end_date, sizeof(data.end_date), stdin);
    data.end_date[strcspn(data.end_date, "\n")] = '\0';

    printf("\nCreated by : ");
    fgets(data.created_by, sizeof(data.created_by), stdin);
    data.created_by[strcspn(data.created_by, "\n")] = '\0';

    return 0;
}

int view_projects()
{
        
    printf("\n");
    printf("+----------------------------------------------------------------------+\n");
    printf("|                         PROJECT DETAILS                              |\n");
    printf("+----------------------+-----------------------------------------------+\n");
    printf("| Project ID           | %-45s |\n", data.id);
    printf("| Category             | %-45s |\n", data.category);
    printf("| Project Name         | %-45s |\n", data.name);
    printf("| Description          | %-45s |\n", data.description);
    printf("| Priority             | %-45s |\n", data.priority);
    printf("| Status               | %-45s |\n", data.status);
    printf("| Progress             | %-45s |\n", data.progress);
    printf("| Start Date           | %-45s |\n", data.start_date);
    printf("| End Date             | %-45s |\n", data.end_date);
    printf("| Created By           | %-45s |\n", data.created_by);
    printf("+----------------------+-----------------------------------------------+\n");
    

    return 0;
}

int update_project()
{
    char project_id_or_name[50];
    char updated_details[200];
    char line[500];
    char choice;

    printf("Enter Project ID or Project Name: ");
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    FILE *file_open_for_update = fopen("database\\projectDBS.csv", "r");
    FILE *temp_file = fopen("database\\tmp.csv", "w");

    if (file_open_for_update == NULL || temp_file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    int found = 0;

    while (fgets(line, sizeof(line), file_open_for_update) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        char *token;

        token = strtok(line, ",");
        strcpy(data.id, token);

        token = strtok(NULL, ",");
        strcpy(data.category, token);

        token = strtok(NULL, ",");
        strcpy(data.name, token);

        token = strtok(NULL, ",");
        strcpy(data.description, token);

        token = strtok(NULL, ",");
        strcpy(data.priority, token);

        token = strtok(NULL, ",");
        strcpy(data.status, token);

        token = strtok(NULL, ",");
        strcpy(data.progress, token);

        token = strtok(NULL, ",");
        strcpy(data.start_date, token);

        token = strtok(NULL, ",");
        strcpy(data.end_date, token);

        token = strtok(NULL, ",");
        strcpy(data.created_by, token);

        if (strcmp(data.id, project_id_or_name) == 0 ||
            strcmp(data.name, project_id_or_name) == 0)
        {
            found = 1;

            printf("\n========== CURRENT PROJECT DETAILS ==========\n");
            printf("Project ID    : %s\n", data.id);
            printf("Category      : %s\n", data.category);
            printf("Project Name  : %s\n", data.name);
            printf("Description   : %s\n", data.description);
            printf("Priority      : %s\n", data.priority);
            printf("Status        : %s\n", data.status);
            printf("Progress      : %s\n", data.progress);
            printf("Start Date    : %s\n", data.start_date);
            printf("End Date      : %s\n", data.end_date);
            printf("Created By    : %s\n", data.created_by);

            printf("\n1. Category\n");
            printf("2. Project Name\n");
            printf("3. Description\n");
            printf("4. Priority\n");
            printf("5. Status\n");
            printf("6. Progress\n");
            printf("7. Start Date\n");
            printf("8. End Date\n");

            printf("\nEnter your choice: ");
            scanf(" %c", &choice);
            getchar();

            switch (choice)
            {
            case '1':
                printf("New Category: ");
                fgets(data.category, sizeof(data.category), stdin);
                data.category[strcspn(data.category, "\n")] = '\0';
                break;

            case '2':
                printf("New Project Name: ");
                fgets(data.name, sizeof(data.name), stdin);
                data.name[strcspn(data.name, "\n")] = '\0';
                break;

            case '3':
                printf("New Description: ");
                fgets(data.description, sizeof(data.description), stdin);
                data.description[strcspn(data.description, "\n")] = '\0';
                break;

            case '4':
                printf("New Priority: ");
                fgets(data.priority, sizeof(data.priority), stdin);
                data.priority[strcspn(data.priority, "\n")] = '\0';
                break;

            case '5':
                printf("New Status: ");
                fgets(data.status, sizeof(data.status), stdin);
                data.status[strcspn(data.status, "\n")] = '\0';
                break;

            case '6':
                printf("New Progress: ");
                fgets(data.progress, sizeof(data.progress), stdin);
                data.progress[strcspn(data.progress, "\n")] = '\0';
                break;

            case '7':
                printf("New Start Date: ");
                fgets(data.start_date, sizeof(data.start_date), stdin);
                data.start_date[strcspn(data.start_date, "\n")] = '\0';
                break;

            case '8':
                printf("New End Date: ");
                fgets(data.end_date, sizeof(data.end_date), stdin);
                data.end_date[strcspn(data.end_date, "\n")] = '\0';
                break;

            default:
                printf("Invalid choice!\n");
            }
        }

        fprintf(temp_file,
                "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
                data.id,
                data.category,
                data.name,
                data.description,
                data.priority,
                data.status,
                data.progress,
                data.start_date,
                data.end_date,
                data.created_by);
    }

    fclose(file_open_for_update);
    fclose(temp_file);

    remove("database\\projectDBS.csv");
    rename("database\\tmp.csv", "database\\projectDBS.csv");

    if (found)
        printf("\nProject updated successfully!\n");
    else
        printf("\nProject not found!\n");

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
