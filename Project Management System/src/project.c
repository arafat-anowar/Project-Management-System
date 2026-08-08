#include "project.h"

int generate_project_id(char id[])
{
    struct p_details project;

    int found = 0, num_id[20] = {0}, project_id = 0, id_len = 0, tmp = 0, i = 0, j = 0, digit = 0;

    char path[200], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;

    FILE *projectDBS_open;

    strcpy(id, "P1001");

    get_path(path);
    strcat(path, "projectsDBS.csv");

    projectDBS_open = fopen(path, "r");

    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        found = 1;

        row[strcspn(row, "\n")] = '\0';

        field = strtok(row, ",");
        strcpy(project.id, field);
    }

    fclose(projectDBS_open);

    if (found == 0)
    {
        return 0;
    }

    strcpy(id, project.id);

    id_len = strlen(id);

    for (i = 0, j = 1; j < id_len; i++, j++)
    {
        num_id[i] = id[j] - '0';
    }

    for (i = 0; i < id_len - 1; i++)
    {
        digit = num_id[i];

        for (j = i; j < id_len - 2; j++)
        {
            digit *= 10;
        }

        project_id += digit;
    }

    project_id++;

    tmp = project_id;
    j = id_len - 1;

    while (tmp != 0 && j > 0)
    {
        id[j] = (tmp % 10) + '0';
        tmp /= 10;
        j--;
    }
    return 0;
}

int create_project()
{
    struct p_details project;

    int terminal_width = 0, terminal_height = 0, box_width = 100, box_height = 39, x = 0, y = 0, priority_box_width = 68, priority_box_height = 13, priority_x = 0, priority_y = 0, is_start_date_valid = 0, is_end_date_valid = 0;

    char filepath[200];

    FILE *open_projectDBS, *project_file_create;

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

    priority_x = (terminal_width - priority_box_width) / 2;
    priority_y = (terminal_height - priority_box_height) / 2;

    project_priority_dashboard(project.priority, priority_x, priority_y);

    clear_screen();
    header_screen();

    create_project_screen(x, y);

    move_cursor(x + 10, y + 6);
    printf("%s", project.name);

    move_cursor(x + 10, y + 11);
    printf("%s", project.category);

    move_cursor(x + 10, y + 16);
    printf("%s", project.description);

    move_cursor(x + 10, y + 23);
    printf("%s", project.priority);

    strcpy(project.status, "Created");

    do
    {
        move_cursor(x + 10, y + 28);

        if (is_start_date_valid == 0)
        {
            printf("                                                                             ");
            move_cursor(x + 10, y + 28);
        }

        fgets(project.start_date, sizeof(project.start_date), stdin);
        project.start_date[strcspn(project.start_date, "\n")] = '\0';

        is_start_date_valid = validate_date(project.start_date);

    } while (is_start_date_valid != 1);

    do
    {
        move_cursor(x + 10, y + 33);

        if (is_end_date_valid == 0)
        {
            printf("                                                                             ");
            move_cursor(x + 10, y + 33);
        }

        fgets(project.end_date, sizeof(project.end_date), stdin);
        project.end_date[strcspn(project.end_date, "\n")] = '\0';

        is_end_date_valid = validate_date(project.end_date);

    } while (is_end_date_valid != 1);

    get_user_name(project.created_by);

    get_path(filepath);
    strcat(filepath, "projectsDBS.csv");

    open_projectDBS = fopen(filepath, "a");

    fprintf(open_projectDBS,"%s,%s,%s,%s,%s,%s,%s,%s,%s\n",project.id,project.name,project.category,project.description, project.priority, project.status, project.start_date, project.end_date, project.created_by);

    fclose(open_projectDBS);

    get_path(filepath);
    strcat(filepath, "Projects\\");
    strcat(filepath, strlwr(project.name));
    strcat(filepath, ".csv");

    project_file_create = fopen(filepath, "w");
    fclose(project_file_create);

    project_management_dashboard();

    return 0;
}

int delete_project()
{
    struct p_details project;

    char project_id_or_name[50], projectDBS_path[200], tmp_projectDBS_path[200], project_file_path[200], project_file_name[100], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;

    int terminal_width = 0, terminal_height = 0, box_width = 100, box_height = 13, x = 0, y = 0;

    FILE *file_for_delete_project, *write_to_new_file;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - box_width) / 2;
    y = ((terminal_height - box_height) / 2) + SCREEN_OFFSET_Y;

    search_project_by_id_or_name_screen(x, y);
    move_cursor(x + 10, y + 5);
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    get_path(projectDBS_path);
    get_path(tmp_projectDBS_path);

    strcat(projectDBS_path, "projectsDBS.csv");
    strcat(tmp_projectDBS_path, "tmp_projectsDBS.csv");

    file_for_delete_project = fopen(projectDBS_path, "r");
    write_to_new_file = fopen(tmp_projectDBS_path, "w");

    while (fgets(row, sizeof(row), file_for_delete_project) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

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

        if (strcmp(project.id, project_id_or_name) == 0 || strcmp(project.name, project_id_or_name) == 0)
        {
            strcpy(project.status, "Deleted");

            get_path(project_file_path);
            strcat(project_file_path, "Projects\\");

            strcpy(project_file_name, project.name);
            strlwr(project_file_name);

            strcat(project_file_path, project_file_name);
            strcat(project_file_path, ".csv");

            remove(project_file_path);
        }

        fprintf(write_to_new_file,"%s,%s,%s,%s,%s,%s,%s,%s,%s\n",project.id,project.name,project.category,project.description,project.priority,project.status,project.start_date,project.end_date,project.created_by);
    }

    fclose(file_for_delete_project);
    fclose(write_to_new_file);

    remove(projectDBS_path);
    rename(tmp_projectDBS_path, projectDBS_path);

    project_management_dashboard();

    return 0;
}

int search_project_by_priority()
{
    struct p_details project;

    char priority[50], projectDBS_path[200], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;

    int terminal_width = 0, terminal_height = 0, box_width = 0, box_height = 48, x = 0, y = 0, priority_box_width = 68, priority_box_height = 13, priority_x = 0, priority_y = 0;

    FILE *projectDBS_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    box_width = BOX_WIDTH;
    box_height = 48;

    x = (terminal_width - box_width) / 2;
    y = ((terminal_height - box_height) / 2) + SCREEN_OFFSET_Y;

    priority_x = (terminal_width - priority_box_width) / 2;
    priority_y = (terminal_height - priority_box_height) / 2;

    project_priority_dashboard(priority, priority_x, priority_y);

    get_path(projectDBS_path);
    strcat(projectDBS_path, "projectsDBS.csv");

    projectDBS_open = fopen(projectDBS_path, "r");

    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

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
            clear_screen();
            header_screen();

            project_show_screen(x, y);

            move_cursor(x + 12, y + 5);
            printf("%s", project.id);

            move_cursor(x + 12, y + 10);
            printf("%s", project.name);

            move_cursor(x + 12, y + 15);
            printf("%s", project.category);

            move_cursor(x + 12, y + 20);
            printf("%s", project.description);

            move_cursor(x + 12, y + 27);
            printf("%s", project.priority);

            move_cursor(x + 12, y + 32);
            printf("%s", project.status);

            move_cursor(x + 12, y + 37);
            printf("%s", project.start_date);

            move_cursor(x + 12, y + 42);
            printf("%s", project.end_date);

            get_input;
        }
    }

    fclose(projectDBS_open);
    project_management_dashboard();

    return 0;
}

int search_by_project_id_or_name()
{
    struct p_details project;

    char project_id_or_name[50], projectDBS_path[200], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;

    int terminal_width = 0, terminal_height = 0, box_width = BOX_WIDTH, box_height = 48, x = 0, y = 0;

    FILE *projectDBS_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - box_width) / 2;
    y = ((terminal_height - box_height) / 2) + SCREEN_OFFSET_Y;

    search_project_by_id_or_name_screen(x, y);

    move_cursor(x + 10, y + 5);

    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    get_path(projectDBS_path);
    strcat(projectDBS_path, "projectsDBS.csv");

    projectDBS_open = fopen(projectDBS_path, "r");

    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

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
            clear_screen();
            header_screen();

            project_show_screen(x, y);

            move_cursor(x + 12, y + 5);
            printf("%s", project.id);

            move_cursor(x + 12, y + 10);
            printf("%s", project.name);

            move_cursor(x + 12, y + 15);
            printf("%s", project.category);

            move_cursor(x + 12, y + 20);
            printf("%s", project.description);

            move_cursor(x + 12, y + 27);
            printf("%s", project.priority);

            move_cursor(x + 12, y + 32);
            printf("%s", project.status);

            move_cursor(x + 12, y + 37);
            printf("%s", project.start_date);

            move_cursor(x + 12, y + 42);
            printf("%s", project.end_date);

            get_input;

            break;
        }
    }

    fclose(projectDBS_open);
    project_management_dashboard();

    return 0;
}

int view_projects()
{
    struct p_details project;

    char path[200];
    char row[MAX_LENGTH_OF_DATA_IN_FILE];
    char *field;

    int terminal_width = 0;
    int terminal_height = 0;
    int box_width = BOX_WIDTH;
    int box_height = 48;
    int x = 0;
    int y = 0;

    FILE *projectDBS_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - box_width) / 2;
    y = ((terminal_height - box_height) / 2) + SCREEN_OFFSET_Y;

    get_path(path);
    strcat(path, "projectsDBS.csv");

    projectDBS_open = fopen(path, "r");

    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

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

        clear_screen();
        header_screen();

        project_show_screen(x, y);

        move_cursor(x + 12, y + 5);
        printf("%s", project.id);

        move_cursor(x + 12, y + 10);
        printf("%s", project.name);

        move_cursor(x + 12, y + 15);
        printf("%s", project.category);

        move_cursor(x + 12, y + 20);
        printf("%s", project.description);

        move_cursor(x + 12, y + 27);
        printf("%s", project.priority);

        move_cursor(x + 12, y + 32);
        printf("%s", project.status);

        move_cursor(x + 12, y + 37);
        printf("%s", project.start_date);

        move_cursor(x + 12, y + 42);
        printf("%s", project.end_date);

        get_input;
    }

    fclose(projectDBS_open);
    project_management_dashboard();

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

int search_project_by_status()
{
    struct p_details project;

    char status[STATUS_SIZE],projectDBS_path[PATH_SIZE],row[MAX_LENGTH_OF_DATA_IN_FILE],*field;

    int terminal_width = 0,terminal_height = 0,box_width = BOX_WIDTH,box_height = PROJECT_SHOW_BOX_HEIGHT,x = 0,y = 0,status_box_width = STATUS_BOX_WIDTH,status_box_height = STATUS_BOX_HEIGHT,status_x = 0,status_y = 0;

    FILE *projectDBS_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - box_width) / 2;
    y = ((terminal_height - box_height) / 2) + SCREEN_OFFSET_Y;

    status_x = (terminal_width - status_box_width) / 2;
    status_y = (terminal_height - status_box_height) / 2;

    project_status_dashboard(status, status_x, status_y);

    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DBS_FILE);

    projectDBS_open = fopen(projectDBS_path, READ_MODE);

    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

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
            clear_screen();
            header_screen();

            project_show_screen(x, y);

            move_cursor(x + PROJECT_SHOW_X, y + PROJECT_ID_Y);
            printf("%s", project.id);

            move_cursor(x + PROJECT_SHOW_X, y + PROJECT_NAME_Y);
            printf("%s", project.name);

            move_cursor(x + PROJECT_SHOW_X, y + PROJECT_CATEGORY_Y);
            printf("%s", project.category);

            move_cursor(x + PROJECT_SHOW_X, y + PROJECT_DESCRIPTION_Y);
            printf("%s", project.description);

            move_cursor(x + PROJECT_SHOW_X, y + PROJECT_PRIORITY_Y);
            printf("%s", project.priority);

            move_cursor(x + PROJECT_SHOW_X, y + PROJECT_STATUS_Y);
            printf("%s", project.status);

            move_cursor(x + PROJECT_SHOW_X, y + PROJECT_START_DATE_Y);
            printf("%s", project.start_date);

            move_cursor(x + PROJECT_SHOW_X, y + PROJECT_END_DATE_Y);
            printf("%s", project.end_date);

            get_input;
        }
    }

    fclose(projectDBS_open);

    project_management_dashboard();

    return 0;
}


// Need to work

int update_project()
{
    struct p_details project;

    char project_id_or_name[50];
    char path[200], tmp_path[200];
    char old_project_file[200], new_project_file[200];
    char old_project_name[100], new_project_name[100];

    char row[MAX_LENGTH_OF_DATA_IN_FILE], *field;

    int terminal_width = 0, terminal_height = 0;
    int box_width = 100, box_height = 48;
    int x = 0, y = 0;
    int priority_box_width = 68, priority_box_height = 13;
    int priority_x = 0, priority_y = 0, found = 0;
    FILE *projectDBS_open, *tmp_project;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - box_width) / 2;
    y = ((terminal_height - box_height) / 2) + 13;

    printf("\nProject ID or Name : ");

    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    get_path(path);
    strcat(path, "projectsDBS.csv");

    get_path(tmp_path);
    strcat(tmp_path, "tmp_projectsDBS.csv");

    projectDBS_open = fopen(path, "r");
    tmp_project = fopen(tmp_path, "w");
    priority_x = (terminal_width - priority_box_width) / 2;
    priority_y = (terminal_height - priority_box_height) / 2;

    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        field = strtok(row, ",");

        if (field == NULL)
        {
            continue;
        }

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

        if (strcmp(project_id_or_name, project.id) == 0 ||
            strcmp(project_id_or_name, project.name) == 0)
        {
            strcpy(old_project_name, project.name);

            clear_screen();
            header_screen();

            project_show_screen(x, y);

            move_cursor(x + 12, y + 5);
            printf("%s", project.id);

            move_cursor(x + 12, y + 10);
            printf("%s", project.name);

            move_cursor(x + 12, y + 15);
            printf("%s", project.category);

            move_cursor(x + 12, y + 20);
            printf("%s", project.description);

            move_cursor(x + 12, y + 27);
            printf("%s", project.priority);

            move_cursor(x + 12, y + 32);
            printf("%s", project.status);

            move_cursor(x + 12, y + 37);
            printf("%s", project.start_date);

            move_cursor(x + 12, y + 42);
            printf("%s", project.end_date);

            move_cursor(x + 12, y + 10);
            change_project_name(project.name);

            move_cursor(x + 12, y + 15);
            change_project_category(project.category);

            move_cursor(x + 12, y + 20);
            change_project_description(project.description);

            project_priority_dashboard(project.priority,
                                       priority_x,
                                       priority_y);

            if (project.priority[0] == '\0')
            {
                fclose(projectDBS_open);
                fclose(tmp_project);
                remove(tmp_path);

                project_management_dashboard();

                return 0;
            }

            project_status_dashboard(project.status,
                                     priority_x,
                                     priority_y);

            if (project.status[0] == '\0')
            {
                fclose(projectDBS_open);
                fclose(tmp_project);
                remove(tmp_path);

                project_management_dashboard();

                return 0;
            }

            clear_screen();
            header_screen();

            project_show_screen(x, y);

            move_cursor(x + 12, y + 5);
            printf("%s", project.id);

            move_cursor(x + 12, y + 10);
            printf("%s", project.name);

            move_cursor(x + 12, y + 15);
            printf("%s", project.category);

            move_cursor(x + 12, y + 20);
            printf("%s", project.description);

            move_cursor(x + 12, y + 27);
            printf("%s", project.priority);

            move_cursor(x + 12, y + 32);
            printf("%s", project.status);

            move_cursor(x + 12, y + 37);
            printf("%s", project.start_date);

            move_cursor(x + 12, y + 42);
            printf("%s", project.end_date);

            move_cursor(x + 12, y + 37);
            change_project_start_date(project.start_date);

            move_cursor(x + 12, y + 42);
            extend_project_deadline(project.end_date);

            if (strcmp(old_project_name, project.name) != 0)
            {
                get_path(old_project_file);
                strcat(old_project_file, "Projects\\");

                strlwr(old_project_name);

                strcat(old_project_file, old_project_name);
                strcat(old_project_file, ".csv");

                get_path(new_project_file);
                strcat(new_project_file, "Projects\\");

                strcpy(new_project_name, project.name);
                strlwr(new_project_name);

                strcat(new_project_file, new_project_name);
                strcat(new_project_file, ".csv");

                rename(old_project_file, new_project_file);
            }
        }

        fprintf(tmp_project,
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
    }

    fclose(projectDBS_open);
    fclose(tmp_project);

    remove(path);
    rename(tmp_path, path);

    if (found == 0)
    {
        printf("\nProject not found.\n");
        get_input;
    }

    project_management_dashboard();

    return 0;
}

int change_project_name(char name[])
{
    char updated_name[50];

    printf("                                                                             ");

    fgets(updated_name, sizeof(updated_name), stdin);
    updated_name[strcspn(updated_name, "\n")] = '\0';

    if (strlen(updated_name) > 0)
    {
        strcpy(name, updated_name);
    }

    return 0;
}

int change_project_category(char category[])
{
    char updated_category[50];

    printf("                                                                             ");

    fgets(updated_category, sizeof(updated_category), stdin);
    updated_category[strcspn(updated_category, "\n")] = '\0';

    if (strlen(updated_category) > 0)
    {
        strcpy(category, updated_category);
    }

    return 0;
}

int change_project_description(char description[])
{
    char updated_description[200];

    printf("                                                                             ");

    fgets(updated_description, sizeof(updated_description), stdin);
    updated_description[strcspn(updated_description, "\n")] = '\0';

    if (strlen(updated_description) > 0)
    {
        strcpy(description, updated_description);
    }

    return 0;
}

int change_project_status(char status[], int x, int y)
{
    project_status_dashboard(status, x, y);

    return 0;
}

int change_project_priority(char priority[], int x, int y)
{
    project_priority_dashboard(priority, x, y);

    return 0;
}

int change_project_start_date(char start_date[])
{
    char updated_start_date[15];

    printf("                                                                             ");

    fgets(updated_start_date, sizeof(updated_start_date), stdin);
    updated_start_date[strcspn(updated_start_date, "\n")] = '\0';

    if (strlen(updated_start_date) > 0)
    {
        if (validate_date(updated_start_date) == 1)
        {
            strcpy(start_date, updated_start_date);
        }
    }

    return 0;
}

int extend_project_deadline(char deadline[])
{
    char updated_deadline[15];

    printf("                                                                             ");

    fgets(updated_deadline, sizeof(updated_deadline), stdin);
    updated_deadline[strcspn(updated_deadline, "\n")] = '\0';

    if (strlen(updated_deadline) > 0)
    {
        if (validate_date(updated_deadline) == 1)
        {
            strcpy(deadline, updated_deadline);
        }
    }

    return 0;
}

int sort_projects()
{
    return 0;
}
