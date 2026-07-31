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
