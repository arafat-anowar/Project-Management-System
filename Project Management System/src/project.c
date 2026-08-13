#include "project.h"

int create_project()
{
    struct p_details project;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = BOX_WIDTH, box_height = PROJECT_BOX_HEIGHT, x = ZERO, y = ZERO, priority_box_width = PRIORITY_BOX_WIDTH, priority_box_height = PRIORITY_BOX_HEIGHT, priority_x = ZERO, priority_y = ZERO, is_start_date_valid = ZERO, is_end_date_valid = ZERO;
    char filepath[PATH_SIZE], *username;
    ;
    FILE *open_projectDBS, *project_file_create;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;
    priority_x = (terminal_width - priority_box_width) / TWO;
    priority_y = (terminal_height - priority_box_height) / TWO;

    create_project_screen(x, y);

    generate_project_id(project.id);

    move_cursor(x + PROJECT_INPUT_X, y + PROJECT_INPUT_Y);
    fgets(project.name, sizeof(project.name), stdin);
    project.name[strcspn(project.name, "\n")] = '\0';

    move_cursor(x + PROJECT_INPUT_X, y + 11);
    fgets(project.category, sizeof(project.category), stdin);
    project.category[strcspn(project.category, "\n")] = '\0';

    move_cursor(x + PROJECT_INPUT_X, y + 16);
    fgets(project.description, sizeof(project.description), stdin);
    project.description[strcspn(project.description, "\n")] = '\0';

    project_priority_dashboard(project.priority, priority_x, priority_y);

    clear_screen();
    header_screen();

    create_project_screen(x, y);

    move_cursor(x + PROJECT_INPUT_X, y + 6);
    printf("%s", project.name);

    move_cursor(x + PROJECT_INPUT_X, y + 11);
    printf("%s", project.category);

    move_cursor(x + PROJECT_INPUT_X, y + 16);
    printf("%s", project.description);

    move_cursor(x + PROJECT_INPUT_X, y + 23);
    printf("%s", project.priority);

    strcpy(project.status, "Created");

    do
    {
        move_cursor(x + PROJECT_INPUT_X, y + 28);
        if (is_start_date_valid == 0)
        {
            printf("                                                                             ");
            move_cursor(x + PROJECT_INPUT_X, y + 28);
        }

        fgets(project.start_date, sizeof(project.start_date), stdin);
        project.start_date[strcspn(project.start_date, "\n")] = '\0';
        is_start_date_valid = validate_date(project.start_date);

    } while (is_start_date_valid != 1);

    do
    {
        move_cursor(x + PROJECT_INPUT_X, y + 33);

        if (is_end_date_valid == 0)
        {
            printf("                                                                             ");
            move_cursor(x + PROJECT_INPUT_X, y + 33);
        }

        fgets(project.end_date, sizeof(project.end_date), stdin);
        project.end_date[strcspn(project.end_date, "\n")] = '\0';
        is_end_date_valid = validate_date(project.end_date);

    } while (is_end_date_valid != 1);

    username = get_user_name();
    strcpy(project.created_by, username);
    free(username);

    get_path(filepath);
    strcat(filepath, PROJECT_DBS_FILE);

    open_projectDBS = fopen(filepath, APPEND_MODE);

    if (open_projectDBS == NULL)
    {
        something_wrong_screen(x, y);
        move_cursor(x + SOMETHING_WENT_WRONG_OFFSET_X, y);
        printf("Error: %s\n", strerror(errno));

        return 0;
    }

    fprintf(open_projectDBS, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", project.id, project.name, project.category, project.description, project.priority, project.status, project.start_date, project.end_date, project.created_by);

    fclose(open_projectDBS);

    get_path(filepath);
    strcat(filepath, PROJECTS_FOLDER);
    strcat(filepath, strlwr(project.name));
    strcat(filepath, PROJECT_FILE_EXTENSION);

    project_file_create = fopen(filepath, WRITE_MODE);

    if (project_file_create == NULL)
    {
        something_wrong_screen(x, y);
        move_cursor(x + SOMETHING_WENT_WRONG_OFFSET_X, y);
        printf("Error: %s\n", strerror(errno));

        return 0;
    }

    fclose(project_file_create);

    project_management_dashboard();

    return 0;
}

int update_project()
{
    struct p_details project;
    char project_id_or_name[PROJECT_ID_OR_NAME_SIZE], path[PATH_SIZE], tmp_path[PATH_SIZE], old_project_file[PROJECT_FILE_PATH_SIZE], new_project_file[PROJECT_FILE_PATH_SIZE], old_project_name[PROJECT_FILE_NAME_SIZE], new_project_name[PROJECT_FILE_NAME_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = BOX_WIDTH, box_height = UPDATE_PROJECT_BOX_HEIGHT, x = ZERO, y = ZERO, priority_box_width = PRIORITY_BOX_WIDTH, priority_box_height = PRIORITY_BOX_HEIGHT, priority_x = ZERO, priority_y = ZERO, found = ZERO;
    FILE *projectDBS_open, *tmp_project;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;
    priority_x = (terminal_width - priority_box_width) / TWO;
    priority_y = (terminal_height - priority_box_height) / TWO;

    search_project_by_id_or_name_screen(x, y);

    move_cursor(x + PROJECT_INPUT_X, y + 5);
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    get_path(path);
    strcat(path, PROJECT_DBS_FILE);

    get_path(tmp_path);
    strcat(tmp_path, TEMP_PROJECT_DBS_FILE);

    projectDBS_open = fopen(path, READ_MODE);

    if (projectDBS_open == NULL)
    {
        something_wrong_screen(x, y);
        move_cursor(x + SOMETHING_WENT_WRONG_OFFSET_X, y);
        printf("Error: %s\n", strerror(errno));

        return 0;
    }

    tmp_project = fopen(tmp_path, WRITE_MODE);

    if (tmp_project == NULL)
    {
        something_wrong_screen(x, y);
        move_cursor(x + SOMETHING_WENT_WRONG_OFFSET_X, y);
        printf("Error: %s\n", strerror(errno));

        return 0;
    }

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
            found = 1;

            update_project_dashboard(&project, x, y, priority_x, priority_y);
        }

        fprintf(tmp_project, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", project.id, project.name, project.category, project.description, project.priority, project.status, project.start_date, project.end_date, project.created_by);
    }

    fclose(projectDBS_open);
    fclose(tmp_project);

    remove(path);
    rename(tmp_path, path);

    project_management_dashboard();

    return 0;
}

int change_project_name(char name[])
{
    char updated_name[50];
    int terminal_width = 0, terminal_height = 0, box_width = BOX_WIDTH, box_height = PROJECT_INPUT_BOX_HEIGHT, x = 0, y = 0;

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

    change_project_name_screen(x, y);

    move_cursor(x + PROJECT_INPUT_X, y + PROJECT_INPUT_Y);
    fgets(updated_name, sizeof(updated_name), stdin);
    updated_name[strcspn(updated_name, "\n")] = '\0';
    strcpy(name, updated_name);

    return 0;
}

int change_project_category(char category[])
{
    char updated_category[50];
    int terminal_width = 0, terminal_height = 0, box_width = BOX_WIDTH, box_height = PROJECT_INPUT_BOX_HEIGHT, x = 0, y = 0;

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

    change_project_category_screen(x, y);

    move_cursor(x + PROJECT_INPUT_X, y + PROJECT_INPUT_Y);
    fgets(updated_category, sizeof(updated_category), stdin);
    updated_category[strcspn(updated_category, "\n")] = '\0';

    strcpy(category, updated_category);

    return 0;
}

int change_project_description(char description[])
{
    char updated_description[200];
    int terminal_width = 0, terminal_height = 0, box_width = BOX_WIDTH, box_height = PROJECT_INPUT_BOX_HEIGHT, x = 0, y = 0;

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

    change_project_description_screen(x, y);

    move_cursor(x + PROJECT_INPUT_X, y + PROJECT_INPUT_Y);
    fgets(updated_description, sizeof(updated_description), stdin);
    updated_description[strcspn(updated_description, "\n")] = '\0';

    strcpy(description, updated_description);

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
    int terminal_width = 0, terminal_height = 0, box_width = BOX_WIDTH, box_height = PROJECT_INPUT_BOX_HEIGHT, x = 0, y = 0, is_start_date_valid = 0;

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

    change_project_start_date_screen(x, y);

    do
    {
        move_cursor(x + PROJECT_INPUT_X, y + PROJECT_INPUT_Y);

        if (is_start_date_valid == 0)
        {
            printf("                                                                             ");
            move_cursor(x + PROJECT_INPUT_X, y + PROJECT_INPUT_Y);
        }

        fgets(updated_start_date, sizeof(updated_start_date), stdin);
        updated_start_date[strcspn(updated_start_date, "\n")] = '\0';
        is_start_date_valid = validate_date(updated_start_date);

    } while (is_start_date_valid != 1);

    strcpy(start_date, updated_start_date);

    return 0;
}

int extend_project_deadline(char deadline[])
{
    char updated_deadline[15];
    int terminal_width = 0, terminal_height = 0, box_width = BOX_WIDTH, box_height = PROJECT_INPUT_BOX_HEIGHT, x = 0, y = 0, is_end_date_valid = 0;

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

    extend_project_deadline_screen(x, y);

    do
    {
        move_cursor(x + PROJECT_INPUT_X, y + PROJECT_INPUT_Y);

        if (is_end_date_valid == 0)
        {
            printf("                                                                             ");
            move_cursor(x + PROJECT_INPUT_X, y + PROJECT_INPUT_Y);
        }

        fgets(updated_deadline, sizeof(updated_deadline), stdin);
        updated_deadline[strcspn(updated_deadline, "\n")] = '\0';
        is_end_date_valid = validate_date(updated_deadline);

    } while (is_end_date_valid != 1);

    strcpy(deadline, updated_deadline);

    return 0;
}

int delete_project()
{
    struct p_details project;
    char project_id_or_name[PROJECT_ID_OR_NAME_SIZE], projectDBS_path[PATH_SIZE], tmp_projectDBS_path[PATH_SIZE], project_file_path[PATH_SIZE], project_file_name[PROJECT_FILE_NAME_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int terminal_width = 0, terminal_height = 0, box_width = BOX_WIDTH, box_height = PROJECT_DELETE_BOX_HEIGHT, x = 0, y = 0;
    FILE *file_for_delete_project, *write_to_new_file;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

    search_project_by_id_or_name_screen(x, y);

    move_cursor(x + PROJECT_INPUT_X, y + 5);
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    get_path(projectDBS_path);
    get_path(tmp_projectDBS_path);

    strcat(projectDBS_path, PROJECT_DBS_FILE);
    strcat(tmp_projectDBS_path, TEMP_PROJECT_DBS_FILE);

    file_for_delete_project = fopen(projectDBS_path, READ_MODE);

    if (file_for_delete_project == NULL)
    {
        something_wrong_screen(x, y);
        move_cursor(x + SOMETHING_WENT_WRONG_OFFSET_X, y);
        printf("Error: %s\n", strerror(errno));

        return 0;
    }

    write_to_new_file = fopen(tmp_projectDBS_path, WRITE_MODE);
    if (write_to_new_file == NULL)
    {
        something_wrong_screen(x, y);
        move_cursor(x + SOMETHING_WENT_WRONG_OFFSET_X, y);
        printf("Error: %s\n", strerror(errno));

        return 0;
    }

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
            strcat(project_file_path, PROJECTS_FOLDER);

            strcpy(project_file_name, project.name);
            strlwr(project_file_name);

            strcat(project_file_path, project_file_name);
            strcat(project_file_path, PROJECT_FILE_EXTENSION);

            remove(project_file_path);
        }

        fprintf(write_to_new_file, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", project.id, project.name, project.category, project.description, project.priority, project.status, project.start_date, project.end_date, project.created_by);
    }

    fclose(file_for_delete_project);
    fclose(write_to_new_file);

    remove(projectDBS_path);
    rename(tmp_projectDBS_path, projectDBS_path);

    project_management_dashboard();

    return 0;
}

int view_projects()
{
    struct p_details project;
    char path[PATH_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int terminal_width = 0, terminal_height = 0, box_width = BOX_WIDTH, box_height = PROJECT_SHOW_BOX_HEIGHT, x = 0, y = 0;
    FILE *projectDBS_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

    get_path(path);
    strcat(path, PROJECT_DBS_FILE);

    projectDBS_open = fopen(path, READ_MODE);

    if (projectDBS_open == NULL)
    {
        init_console();

        terminal_width = get_console_width();
        terminal_height = get_console_height();

        box_width = BOX_WIDTH;
        box_height = REGISTER_BOX_HEIGHT;

        x = (terminal_width - box_width) / TWO;
        y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

        something_wrong_screen(x, y);

        move_cursor(x + SOMETHING_WENT_WRONG_OFFSET_X, y);

        printf("Error: %s\n", strerror(errno));

        return 0;
    }

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

    fclose(projectDBS_open);

    project_management_dashboard();

    return 0;
}

int search_by_project_id_or_name()
{
    struct p_details project;
    char project_id_or_name[PROJECT_ID_OR_NAME_SIZE], projectDBS_path[PATH_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int terminal_width = 0, terminal_height = 0, box_width = BOX_WIDTH, box_height = PROJECT_SHOW_BOX_HEIGHT, x = 0, y = 0;
    FILE *projectDBS_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

    search_project_by_id_or_name_screen(x, y);

    move_cursor(x + PROJECT_INPUT_X, y + 5);

    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);

    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DBS_FILE);

    projectDBS_open = fopen(projectDBS_path, READ_MODE);

    if (projectDBS_open == NULL)
    {
        something_wrong_screen(x, y);
        move_cursor(x + SOMETHING_WENT_WRONG_OFFSET_X, y);
        printf("Error: %s\n", strerror(errno));

        return 0;
    }

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

            break;
        }
    }

    fclose(projectDBS_open);

    project_management_dashboard();

    return 0;
}

int search_project_by_status()
{
    struct p_details project;
    char status[STATUS_SIZE], projectDBS_path[PATH_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int terminal_width = 0, terminal_height = 0, box_width = BOX_WIDTH, box_height = PROJECT_SHOW_BOX_HEIGHT, x = 0, y = 0, status_box_width = STATUS_BOX_WIDTH, status_box_height = STATUS_BOX_HEIGHT, status_x = 0, status_y = 0;
    FILE *projectDBS_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;
    status_x = (terminal_width - status_box_width) / TWO;
    status_y = (terminal_height - status_box_height) / TWO;

    project_status_dashboard(status, status_x, status_y);

    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DBS_FILE);

    projectDBS_open = fopen(projectDBS_path, READ_MODE);

    if (projectDBS_open == NULL)
    {
        something_wrong_screen(x, y);
        move_cursor(x + SOMETHING_WENT_WRONG_OFFSET_X, y);
        printf("Error: %s\n", strerror(errno));

        return 0;
    }

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

int search_project_by_priority()
{
    struct p_details project;
    char priority[50], projectDBS_path[PATH_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int terminal_width = 0, terminal_height = 0, box_width = BOX_WIDTH, box_height = PROJECT_SHOW_BOX_HEIGHT, x = 0, y = 0, priority_box_width = PRIORITY_BOX_WIDTH, priority_box_height = PRIORITY_BOX_HEIGHT, priority_x = 0, priority_y = 0;
    FILE *projectDBS_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;
    priority_x = (terminal_width - priority_box_width) / TWO;
    priority_y = (terminal_height - priority_box_height) / TWO;

    project_priority_dashboard(priority, priority_x, priority_y);

    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DBS_FILE);

    projectDBS_open = fopen(projectDBS_path, READ_MODE);

    if (projectDBS_open == NULL)
    {
        something_wrong_screen(x, y);
        move_cursor(x + SOMETHING_WENT_WRONG_OFFSET_X, y);
        printf("Error: %s\n", strerror(errno));

        return 0;
    }

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

int generate_project_id(char id[])
{
    struct p_details project;
    int found = 0, num_id[20] = {0}, project_id = 0, id_len = 0, tmp = 0, i = 0, j = 0, digit = 0, terminal_width = 0, terminal_height = 0, box_width = BOX_WIDTH, box_height = REGISTER_BOX_HEIGHT, x = 0, y = 0;
    char path[PATH_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    FILE *projectDBS_open;

    strcpy(id, "P1001");

    get_path(path);
    strcat(path, PROJECT_DBS_FILE);

    projectDBS_open = fopen(path, READ_MODE);

    if (projectDBS_open == NULL)
    {
        something_wrong_screen(x, y);
        move_cursor(x + SOMETHING_WENT_WRONG_OFFSET_X, y);
        printf("Error: %s\n", strerror(errno));

        return 0;
    }

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

        for (j = i; j < id_len - TWO; j++)
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

int get_path(char path[])
{
    char *username;
    username = get_user_name();

    strcpy(path, "..\\database\\");
    strcat(path, username);
    strcat(path, "\\");

    free(username);

    return 0;
}

int compare_project_priority(const void *a, const void *b)
{
    struct p_details *project_a = (struct p_details *)a, *project_b = (struct p_details *)b;
    int priority_a = 0, priority_b = 0;

    if (strcmp(project_a->priority, "High") == 0)
    {
        priority_a = 3;
    }
    else if (strcmp(project_a->priority, "Medium") == 0)
    {
        priority_a = 2;
    }
    else if (strcmp(project_a->priority, "Low") == 0)
    {
        priority_a = 1;
    }

    if (strcmp(project_b->priority, "High") == 0)
    {
        priority_b = 3;
    }
    else if (strcmp(project_b->priority, "Medium") == 0)
    {
        priority_b = 2;
    }
    else if (strcmp(project_b->priority, "Low") == 0)
    {
        priority_b = 1;
    }

    return priority_b - priority_a;
}

int sort_projects()
{
    struct p_details projects[PROJECT_ARRAY_SIZE], project;
    char path[PATH_SIZE], sort_path[PATH_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int project_count = 0, terminal_width = 0, terminal_height = 0, box_width = BOX_WIDTH, box_height = REGISTER_BOX_HEIGHT, x = 0, y = 0;
    FILE *projectDBS_open, *sort_project_open;

    get_path(path);
    strcat(path, PROJECT_DBS_FILE);

    get_path(sort_path);
    strcat(sort_path, SORT_PROJECT_FILE);

    projectDBS_open = fopen(path, READ_MODE);

    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        field = strtok(row, ",");
        strcpy(projects[project_count].id, field);

        field = strtok(NULL, ",");
        strcpy(projects[project_count].name, field);

        field = strtok(NULL, ",");
        strcpy(projects[project_count].category, field);

        field = strtok(NULL, ",");
        strcpy(projects[project_count].description, field);

        field = strtok(NULL, ",");
        strcpy(projects[project_count].priority, field);

        field = strtok(NULL, ",");
        strcpy(projects[project_count].status, field);

        field = strtok(NULL, ",");
        strcpy(projects[project_count].start_date, field);

        field = strtok(NULL, ",");
        strcpy(projects[project_count].end_date, field);

        field = strtok(NULL, ",");
        strcpy(projects[project_count].created_by, field);

        project_count++;
    }

    fclose(projectDBS_open);

    qsort(projects, project_count, sizeof(struct p_details), compare_project_priority);

    sort_project_open = fopen(sort_path, WRITE_MODE);

    for (int i = 0; i < project_count; i++)
    {
        fprintf(sort_project_open, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", projects[i].id, projects[i].name, projects[i].category, projects[i].description, projects[i].priority, projects[i].status, projects[i].start_date, projects[i].end_date, projects[i].created_by);
    }

    fclose(sort_project_open);

    return 0;
}
