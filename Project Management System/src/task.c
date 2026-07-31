#include "task.h"

int create_task()
{
    header_screen();
    clear_screen();
    struct task details;
    printf("\nEnter Project ID :");
    fgets(details.project_id, sizeof(details.project_id), stdin);
    details.project_id[strcspn(details.project_id, "\n")] = "\0";

    printf("\nTask Name :");
    fgets(details.name, sizeof(details.name), stdin);
    details.name[strcspn(details.name, "\n")] = "\0";

    printf("\nDescription :");
    fgets(details.description, sizeof(details.description), stdin);
    details.description[strcspn(details.description, "\n")] = "\0";

    printf("\nPriority :");
    fgets(details.priority, sizeof(details.priority), stdin);
    details.priority[strcspn(details.priority, "\n")] = "\0";

    printf("\nStatus :");
    fgets(details.status, sizeof(details.status), stdin);
    details.status[strcspn(details.status, "\n")] = "\0";

    printf("\nEnter Start Date :");
    fgets(details.start_date, sizeof(details.start_date), stdin);
    details.start_date[strcspn(details.start_date, "\n")] = "\0";

    printf("\nDeadline :");
    fgets(details.end_date, sizeof(details.end_date), stdin);
    details.end_date[strcspn(details.end_date, "\n")] = "\0";
    
    return 0;
}

int view_tasks()
{
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