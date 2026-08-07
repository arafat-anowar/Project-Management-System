#include "project.h"

int generate_project_id(char id[])
{
    strcpy(id, "P1001");

    int found = 0;
    char path[100];
    get_path(path);
    strcat(path, "projectsDBS.csv");
    struct p_details project;

    FILE *projectDBS_open;
    projectDBS_open = fopen(path, "r");

    char row[3000];
    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        found = 1;
        row[strcspn(row, "\n")] = '\0';
        char *field;
        field = strtok(row, ",");
        strcpy(project.id, field);
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

    int terminal_width = 0;
    int terminal_height = 0;
    int box_width = 100;
    int box_height = 39;
    int x = 0;
    int y = 0;
    char priority_choice;
    FILE *open_projectDBS;
    FILE *project_file_create;

    char filepath[200];

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - box_width) / 2;
    y = ((terminal_height - box_height) / 2) + 13;

    create_project_screen(x, y);

    generate_project_id(project.id);

    move_cursor(x + 10, y + 6);
    fgets(project.name, sizeof(project.name), stdin);
    project.name[strcspn(project.name, "\n")] = '\0';

    move_cursor(x + 10, y + 11);
    fgets(project.category, sizeof(project.category), stdin);
    project.category[strcspn(project.category, "\n")] = '\0';

    move_cursor(x + 10, y + 16);
    fgets(project.description, sizeof(project.description), stdin);
    project.description[strcspn(project.description, "\n")] = '\0';

    move_cursor(x + 10, y + 21);
    priority_choice=get_input;
    project_priority_dashboard(project.priority,priority_choice);

    move_cursor(x + 10, y + 21);
    printf("%s", project.priority);

    strcpy(project.status, "Created");

    move_cursor(x + 10, y + 26);
    fgets(project.start_date, sizeof(project.start_date), stdin);
    project.start_date[strcspn(project.start_date, "\n")] = '\0';

    move_cursor(x + 10, y + 31);
    fgets(project.end_date, sizeof(project.end_date), stdin);
    project.end_date[strcspn(project.end_date, "\n")] = '\0';

    get_user_name(project.created_by);

    get_path(filepath);
    strcat(filepath, "projectsDBS.csv");

    open_projectDBS = fopen(filepath, "a");

    fprintf(open_projectDBS,
            "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            project.id,
            project.name,
            project.category,
            project.description,
            project.priority,
            project.status,
            project.start_date,
            project.end_date,
            project.created_by);

    fclose(open_projectDBS);

    get_path(filepath);
    strcat(filepath, "Projects\\");
    strcat(filepath, strlwr(project.name));
    strcat(filepath, ".csv");

    project_file_create = fopen(filepath, "w");
    fclose(project_file_create);

    return 0;
}

int view_projects()
{
    struct p_details project;

    FILE *projectDBS_open;
    projectDBS_open = fopen("..\\database\\projectDBS.csv", "r");

    char row[3000];
    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = 0;

        char *field;

        field = strtok(row, ",");
        strcpy(project.id, field);

        field = strtok(NULL, ",");
        strcpy(project.name, field);

        field = strtok(NULL, ",");
        strcpy(project.category, field);

        field = strtok(NULL, ",");
        strcpy(project.description, field);

        field = strtok(NULL, ",");
        strcpy(project.priority, field);

        field = strtok(NULL, ",");
        strcpy(project.status, field);

        field = strtok(NULL, ",");
        strcpy(project.start_date, field);

        field = strtok(NULL, ",");
        strcpy(project.end_date, field);

        field = strtok(NULL, ",");
        strcpy(project.created_by, field);

        printf("+----------------------------------------------------------------------+\n");
        printf("|                         PROJECT DETAILS                              |\n");
        printf("+----------------------+-----------------------------------------------+\n");
        printf("| Project ID           | %-s |\n", project.id);
        printf("| Category             | %-s |\n", project.category);
        printf("| Project Name         | %-s |\n", project.name);
        printf("| Description          | %-s |\n", project.description);
        printf("| Priority             | %-s |\n", project.priority);
        printf("| Status               | %-s |\n", project.status);
        printf("| Starting Date        | %-s |\n", project.start_date);
        printf("| Deadrow             | %-s |\n", project.end_date);
        printf("+----------------------+-----------------------------------------------+\n");
    }
    fclose(projectDBS_open);

    return 0;
}

int update_project()
{
    char project_id_or_name[50];

    printf("\nProject ID or Name : ");
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    struct p_details project;

    FILE *projectDBS_open = fopen("..\\database\\projectDBS.csv", "r");
    FILE *tmp_project = fopen("..\\database\\tmp.csv", "w");

    char row[3000];
    int found = 0;

    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';
        char *field;
        field = strtok(row, ",");
        strcpy(project.id, field);
        field = strtok(NULL, ",");
        strcpy(project.name, field);
        field = strtok(NULL, ",");
        strcpy(project.category, field);
        field = strtok(NULL, ",");
        strcpy(project.description, field);
        field = strtok(NULL, ",");
        strcpy(project.priority, field);
        field = strtok(NULL, ",");
        strcpy(project.status, field);
        field = strtok(NULL, ",");
        strcpy(project.start_date, field);
        field = strtok(NULL, ",");
        strcpy(project.end_date, field);
        field = strtok(NULL, ",");
        strcpy(project.created_by, field);

        if (strcmp(project_id_or_name, project.id) == 0 || strcmp(project_id_or_name, project.name) == 0)
        {
            project_update_dashboard(&project);
            break;
        }
        fprintf(tmp_project, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", project.id, project.name, project.category, project.description, project.priority, project.status, project.start_date, project.end_date, project.created_by);
    }

    fclose(projectDBS_open);
    fclose(tmp_project);

    remove("..\\database\\projectDBS.csv");
    rename("..\\database\\tmp.csv", "..\\database\\projectDBS.csv");

    return 0;
}

int delete_project()
{
    struct p_details project;
    char project_id_or_name[50];

    printf("\nEnter Project ID or Project Name : ");
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    FILE *file_for_delete_project = fopen("..\\database\\projectDBS.csv", "r");
    FILE *write_to_new_file = fopen("..\\database\\tmp.csv", "w");

    char row[3000];

    while (fgets(row, sizeof(row), file_for_delete_project) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        char *field;

        field = strtok(row, ",");
        strcpy(project.id, field);

        field = strtok(NULL, ",");
        strcpy(project.name, field);

        field = strtok(NULL, ",");
        strcpy(project.category, field);

        field = strtok(NULL, ",");
        strcpy(project.description, field);

        field = strtok(NULL, ",");
        strcpy(project.priority, field);

        field = strtok(NULL, ",");
        strcpy(project.status, field);

        field = strtok(NULL, ",");
        strcpy(project.start_date, field);

        field = strtok(NULL, ",");
        strcpy(project.end_date, field);

        field = strtok(NULL, ",");
        strcpy(project.created_by, field);

        if (strcmp(project.id, project_id_or_name) == 0 ||
            strcmp(project.name, project_id_or_name) == 0)
        {

            strcpy(project.status, "Deleted");

            fprintf(write_to_new_file, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", project.id, project.name, project.category, project.description, project.priority, project.status, project.start_date, project.end_date, project.created_by);

            char path[100];

            strcpy(path, "..\\database\\Projects\\");
            strcat(path, strlwr(project.name));
            strcat(path, ".csv");

            remove(path);

            continue;
        }

        fprintf(write_to_new_file, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", project.id, project.name, project.category, project.description, project.priority, project.status, project.start_date, project.end_date, project.created_by);
    }

    fclose(file_for_delete_project);
    fclose(write_to_new_file);

    remove("..\\database\\projectDBS.csv");
    rename("..\\database\\tmp.csv", "..\\database\\projectDBS.csv");

    project_management_dashboard();

    return 0;
}
int change_project_name(char name[])
{
    char updated_name[50];
    fgets(updated_name, sizeof(updated_name), stdin);
    updated_name[strcspn(updated_name, "\n")] = '\0';
    strcpy(name, updated_name);
    return 0;
}
int change_project_category(char category[])
{
    char updated_category[50];
    fgets(updated_category, sizeof(updated_category), stdin);
    updated_category[strcspn(updated_category, "\n")] = '\0';
    strcpy(category, updated_category);
    return 0;
}
int change_project_description(char description[])
{
    char updated_description[50];
    fgets(updated_description, sizeof(updated_description), stdin);
    updated_description[strcspn(updated_description, "\n")] = '\0';
    strcpy(description, updated_description);
    return 0;
}
int change_project_status(char status[])
{
    project_status_dashboard(status);
    return 0;
}

int change_project_priority(char priority[])
{
    // project_priority_dashboard(priority);
    return 0;
}
int change_project_start_date(char start_date[])
{
    char updated_start_date[50];
    fgets(updated_start_date, sizeof(updated_start_date), stdin);
    updated_start_date[strcspn(updated_start_date, "\n")] = '\0';
    strcpy(start_date, updated_start_date);
    return 0;
}
int extend_project_deadline(char deadline[])
{
    char updated_deadrow[50];
    fgets(updated_deadrow, sizeof(updated_deadrow), stdin);
    updated_deadrow[strcspn(updated_deadrow, "\n")] = '\0';
    strcpy(deadline, updated_deadrow);
    return 0;
}
int sort_projects()
{

    return 0;
}
int search_by_project_id_or_name()
{
    char project_id_or_name[50];
    printf("\nProject ID or Name : ");
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    struct p_details project;

    FILE *projectDBS_open;
    projectDBS_open = fopen("..\\database\\projectDBS.csv", "r");

    char row[3000];
    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = 0;

        char *field;

        field = strtok(row, ",");
        strcpy(project.id, field);

        field = strtok(NULL, ",");
        strcpy(project.name, field);

        field = strtok(NULL, ",");
        strcpy(project.category, field);

        field = strtok(NULL, ",");
        strcpy(project.description, field);

        field = strtok(NULL, ",");
        strcpy(project.priority, field);

        field = strtok(NULL, ",");
        strcpy(project.status, field);

        field = strtok(NULL, ",");
        strcpy(project.start_date, field);

        field = strtok(NULL, ",");
        strcpy(project.end_date, field);

        field = strtok(NULL, ",");
        strcpy(project.created_by, field);

        if (strcmp(project_id_or_name, project.id) == 0 || strcmp(project_id_or_name, project.name) == 0)
        {
            printf("Project ID  : %s\n", project.id);
            printf("Project name: %s\n", project.name);
            printf("Category    : %s\n", project.category);
            printf("Description : %s\n", project.description);
            printf("Priority    : %s\n", project.priority);
            printf("Status      : %s\n", project.status);
            printf("Start Date  : %s\n", project.start_date);
            printf("Deadrow    : %s\n", project.end_date);
            break;
        }
    }
    fclose(projectDBS_open);
    return 0;
}
int search_project_by_status()
{
    struct p_details project;

    char status[50];

    printf("\nEnter your status : ");
    fgets(status, sizeof(status), stdin);
    status[strcspn(status, "\n")] = '\0';

    FILE *projectDBS_open;
    projectDBS_open = fopen("..\\database\\projectDBS.csv", "r");

    char row[3000];
    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = 0;

        char *field;

        field = strtok(row, ",");
        strcpy(project.id, field);

        field = strtok(NULL, ",");
        strcpy(project.name, field);

        field = strtok(NULL, ",");
        strcpy(project.category, field);

        field = strtok(NULL, ",");
        strcpy(project.description, field);

        field = strtok(NULL, ",");
        strcpy(project.priority, field);

        field = strtok(NULL, ",");
        strcpy(project.status, field);

        field = strtok(NULL, ",");
        strcpy(project.start_date, field);

        field = strtok(NULL, ",");
        strcpy(project.end_date, field);

        field = strtok(NULL, ",");
        strcpy(project.created_by, field);

        if (strcmp(status, project.status) == 0)
        {
            printf("Project ID  : %s\n", project.id);
            printf("Project name: %s\n", project.name);
            printf("Category    : %s\n", project.category);
            printf("Description : %s\n", project.description);
            printf("Priority    : %s\n", project.priority);
            printf("Status      : %s\n", project.status);
            printf("Start Date  : %s\n", project.start_date);
            printf("Deadrow    : %s\n", project.end_date);
            break;
        }
    }
    fclose(projectDBS_open);

    return 0;
}
int search_project_by_priority()
{
    struct p_details project;

    char priority[50];

    printf("\nEnter your Priority : ");
    fgets(priority, sizeof(priority), stdin);
    priority[strcspn(priority, "\n")] = '\0';

    FILE *projectDBS_open;
    projectDBS_open = fopen("..\\database\\projectDBS.csv", "r");

    char row[3000];
    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = 0;

        char *field;

        field = strtok(row, ",");
        strcpy(project.id, field);

        field = strtok(NULL, ",");
        strcpy(project.name, field);

        field = strtok(NULL, ",");
        strcpy(project.category, field);

        field = strtok(NULL, ",");
        strcpy(project.description, field);

        field = strtok(NULL, ",");
        strcpy(project.priority, field);

        field = strtok(NULL, ",");
        strcpy(project.status, field);

        field = strtok(NULL, ",");
        strcpy(project.start_date, field);

        field = strtok(NULL, ",");
        strcpy(project.end_date, field);

        field = strtok(NULL, ",");
        strcpy(project.created_by, field);

        if (strcmp(priority, project.priority) == 0)
        {
            printf("Project ID  : %s\n", project.id);
            printf("Project name: %s\n", project.name);
            printf("Category    : %s\n", project.category);
            printf("Description : %s\n", project.description);
            printf("Priority    : %s\n", project.priority);
            printf("Status      : %s\n", project.status);
            printf("Start Date  : %s\n", project.start_date);
            printf("Deadrow    : %s\n", project.end_date);
            break;
        }
    }
    fclose(projectDBS_open);

    return 0;
}

int get_path(char path[])
{
    char username[30];
    get_user_name(username);

    strcpy(path, "..\\database\\");
    strcat(path, username);
    strcat(path, "\\");

    return 0;
}