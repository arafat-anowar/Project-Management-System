#include "project.h"

struct project data;
int create_project()
{

    printf("\nProject name : ");
    fgets(data.name, sizeof(data.name), stdin);
    data.name[strcsps(data.name, "\n")] = "\0";

    printf("\nCategory : ");
    fgets(data.category, sizeof(data.category), stdin);
    data.category[strcsps(data.category, "\n")] = "\0";

    printf("\nDescription : ");
    fgets(data.description, sizeof(data.description), stdin);
    data.description[strcsps(data.description, "\n")] = "\0";

    printf("\nPriority : ");
    fgets(data.priority, sizeof(data.priority), stdin);
    data.priority[strcsps(data.priority, "\n")] = "\0";

    printf("\nStatus : ");
    fgets(data.name, sizeof(data.name), stdin);
    data.name[strcsps(data.name, "\n")] = "\0";

    printf("\nProgress : ");
    fgets(data.progress, sizeof(data.progress), stdin);
    data.progress[strcsps(data.progress, "\n")] = "\0";

    printf("\nStart Date : ");
    fgets(data.start_date, sizeof(data.start_date), stdin);
    data.start_date[strcsps(data.start_date, "\n")] = "\0";

    printf("\nEnd data : ");
    fgets(data.end_date, sizeof(data.end_date), stdin);
    data.end_date[strcsps(data.end_date, "\n")] = "\0";

    printf("\nCreated by : ");
    fgets(data.created_by, sizeof(data.created_by), stdin);
    data.created_by[strcsps(data.created_by, "\n")] = "\0";

    return 0;
}

int view_projects()
{
    char id[20], name[30];
    if(search_by_project_id(*id, *name)==0)
    {
        printf("\t\t  ")

    }    





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
