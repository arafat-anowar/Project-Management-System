/*
    ID : 2026-2-60-084
*/

#include "project.h"

int create_project()
{
    // declare all variables
    struct p_details project;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = PROJECT_BOX_HEIGHT, x = ZERO, y = ZERO, priority_box_width = PRIORITY_BOX_WIDTH, priority_box_height = PRIORITY_BOX_HEIGHT, priority_x = ZERO, priority_y = ZERO, is_start_date_valid = ZERO, is_end_date_valid = ZERO;
    char filepath[MAX_PATH_LENGTH], *username;
    FILE *open_projectDBS, *project_file_create;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;
    priority_x = (terminal_width - priority_box_width) / TWO;
    priority_y = (terminal_height - priority_box_height) / TWO;

    // show create project screen
    create_project_screen(x, y);

    // generate project id for new project
    generate_project_id(project.id);

    // take project name
    move_cursor(x + PROJECT_INPUT_X, y + PROJECT_INPUT_Y);
    fgets(project.name, sizeof(project.name), stdin);
    project.name[strcspn(project.name, "\n")] = '\0';

    // take project category
    move_cursor(x + PROJECT_INPUT_X, y + 11);
    fgets(project.category, sizeof(project.category), stdin);
    project.category[strcspn(project.category, "\n")] = '\0';

    // take project description
    move_cursor(x + PROJECT_INPUT_X, y + 16);
    fgets(project.description, sizeof(project.description), stdin);
    project.description[strcspn(project.description, "\n")] = '\0';

    // take project priority
    project_priority_dashboard(project.priority, priority_x, priority_y);

    // clear screen and show create project screen
    clear_screen();
    header_screen();

    // show create project form
    create_project_screen(x, y);

    // show entered project name
    move_cursor(x + PROJECT_INPUT_X, y + 6);
    printf("%s", project.name);

    // show entered project category
    move_cursor(x + PROJECT_INPUT_X, y + 11);
    printf("%s", project.category);

    // show entered project description
    move_cursor(x + PROJECT_INPUT_X, y + 16);
    printf("%s", project.description);

    // show selected project priority
    move_cursor(x + PROJECT_INPUT_X, y + 23);
    printf("%s", project.priority);

    // set default project status
    strcpy(project.status, DEFAULT_PROJECT_STATUS);

    // take project start date and validate that
    do
    {
        move_cursor(x + PROJECT_INPUT_X, y + 28);

        if (is_start_date_valid == ZERO)
        {
            printf("                                                                             ");
            move_cursor(x + PROJECT_INPUT_X, y + 28);
        }

        fgets(project.start_date, sizeof(project.start_date), stdin);
        project.start_date[strcspn(project.start_date, "\n")] = '\0';
        is_start_date_valid = validate_date(project.start_date);

    } while (is_start_date_valid != VALID);

    // take project end date and validate that
    do
    {
        move_cursor(x + PROJECT_INPUT_X, y + 33);

        if (is_end_date_valid == ZERO)
        {
            printf("                                                                             ");
            move_cursor(x + PROJECT_INPUT_X, y + 33);
        }

        fgets(project.end_date, sizeof(project.end_date), stdin);
        project.end_date[strcspn(project.end_date, "\n")] = '\0';

        is_end_date_valid = validate_date(project.end_date);

    } while (is_end_date_valid != VALID);

    // get username
    username = get_user_name();

    // set project creator
    strcpy(project.created_by, username);

    // free memory
    free(username);

    // get project database path
    get_path(filepath);
    strcat(filepath, PROJECT_DATABASE_FILE);

    // open project database
    open_projectDBS = fopen(filepath, FILE_MODE_APPEND);
    if (open_projectDBS == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // write project data to database
    fprintf(open_projectDBS, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", project.id, project.name,project.category,project.description,project.priority,project.status,project.start_date,project.end_date,project.created_by);

    // close project database
    if (fclose(open_projectDBS) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    // get project file path
    get_path(filepath);
    strcat(filepath, PROJECTS_FOLDER);
    strcat(filepath, "\\");
    strcat(filepath, strlwr(project.name));
    strcat(filepath, PROJECT_FILE_EXTENSION);

    // create project file
    project_file_create = fopen(filepath, FILE_MODE_WRITE);
    if (project_file_create == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // close project file
    if (fclose(project_file_create) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    return 0;
}

int update_project()
{
    // declare all variables
    struct p_details project;
    char project_id_or_name[PROJECT_ID_OR_NAME_SIZE], path[MAX_PATH_LENGTH], tmp_path[MAX_PATH_LENGTH], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = UPDATE_PROJECT_BOX_HEIGHT, x = ZERO, y = ZERO, priority_box_width = PRIORITY_BOX_WIDTH, priority_box_height = PRIORITY_BOX_HEIGHT, priority_x = ZERO, priority_y = ZERO;
    FILE *projectDBS_open, *tmp_project;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;
    priority_x = (terminal_width - priority_box_width) / TWO;
    priority_y = (terminal_height - priority_box_height) / TWO;

    // show search project screen
    search_project_by_id_or_name_screen(x, y);

    // take project id or name
    move_cursor(x + PROJECT_INPUT_X, y + 5);
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    // get project database path
    get_path(path);
    strcat(path, PROJECT_DATABASE_FILE);

    // get temporary project database path
    get_path(tmp_path);
    strcat(tmp_path, TEMP_PROJECT_DATABASE_FILE);

    // open project database
    projectDBS_open = fopen(path, FILE_MODE_READ);
    if (projectDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // open temporary project database
    tmp_project = fopen(tmp_path, FILE_MODE_WRITE);
    if (tmp_project == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // read project database
    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize them
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

        // check project id or name if found update project
        if (strcmp(project_id_or_name, project.id) == ZERO || strcmp(project_id_or_name, project.name) == ZERO)
        {
            update_project_dashboard(&project, x, y, priority_x, priority_y);
        }

        // write data to temporary database
        fprintf(tmp_project, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", project.id, project.name, project.category, project.description, project.priority,project.status, project.start_date, project.end_date,project.created_by);
    }

    // close databases
    if (fclose(projectDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    if (fclose(tmp_project) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    // remove original database and rename temporary database as original database
    if (remove(path) != ZERO)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }

    if (rename(tmp_path, path) != ZERO)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }

    return 0;
}

int change_project_name(char name[])
{
    // declare all variables
    char updated_name[MAX_USERNAME_LENGTH];
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = PROJECT_INPUT_BOX_HEIGHT, x = ZERO, y = ZERO;

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // show change project name screen
    change_project_name_screen(x, y);

    // take updated project name
    move_cursor(x + PROJECT_INPUT_X, y + PROJECT_INPUT_Y);
    fgets(updated_name, sizeof(updated_name), stdin);
    updated_name[strcspn(updated_name, "\n")] = '\0';

    // update project name
    strcpy(name, updated_name);

    return 0;
}

int change_project_category(char category[])
{
    // declare all variables
    char updated_category[PROJECT_CATEGORY_SIZE];
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = PROJECT_INPUT_BOX_HEIGHT, x = ZERO, y = ZERO;

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // show change project category screen
    change_project_category_screen(x, y);

    // take updated project category
    move_cursor(x + PROJECT_INPUT_X, y + PROJECT_INPUT_Y);
    fgets(updated_category, sizeof(updated_category), stdin);
    updated_category[strcspn(updated_category, "\n")] = '\0';

    // update project category
    strcpy(category, updated_category);

    return 0;
}

int change_project_description(char description[])
{
    // declare all variables
    char updated_description[PROJECT_DESCRIPTION_SIZE];
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = PROJECT_INPUT_BOX_HEIGHT, x = ZERO, y = ZERO;

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // show change project description screen
    change_project_description_screen(x, y);

    // take updated project description
    move_cursor(x + PROJECT_INPUT_X, y + PROJECT_INPUT_Y);
    fgets(updated_description, sizeof(updated_description), stdin);
    updated_description[strcspn(updated_description, "\n")] = '\0';

    // update project description
    strcpy(description, updated_description);

    return 0;
}

int change_project_status(char status[], int x, int y)
{
    // show project status dashboard
    project_status_dashboard(status, x, y);

    return 0;
}

int change_project_priority(char priority[], int x, int y)
{
    // show project priority dashboard
    project_priority_dashboard(priority, x, y);

    return 0;
}

int change_project_start_date(char start_date[])
{
    // declare all variables
    char updated_start_date[PROJECT_START_DATE_SIZE];
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = PROJECT_INPUT_BOX_HEIGHT, x = ZERO, y = ZERO, is_start_date_valid = VALID;

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // show change project start date screen
    change_project_start_date_screen(x, y);

    // take project start date and validate that
    do
    {
        move_cursor(x + PROJECT_INPUT_X, y + PROJECT_INPUT_Y);

        if (is_start_date_valid == INVALID)
        {
            printf("                                                                             ");
            move_cursor(x + PROJECT_INPUT_X, y + PROJECT_INPUT_Y);
        }

        fgets(updated_start_date, sizeof(updated_start_date), stdin);
        updated_start_date[strcspn(updated_start_date, "\n")] = '\0';
        is_start_date_valid = validate_date(updated_start_date);

    } while (is_start_date_valid != VALID);

    // update project start date
    strcpy(start_date, updated_start_date);

    return 0;
}

int extend_project_deadline(char deadline[])
{
    // declare all variables
    char updated_deadline[PROJECT_END_DATE_SIZE];
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = PROJECT_INPUT_BOX_HEIGHT, x = ZERO, y = ZERO, is_end_date_valid = VALID;

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // show extend project deadline screen
    extend_project_deadline_screen(x, y);

    // take project end date and validate that
    do
    {
        move_cursor(x + PROJECT_INPUT_X, y + PROJECT_INPUT_Y);

        if (is_end_date_valid == INVALID)
        {
            printf("                                                                             ");
            move_cursor(x + PROJECT_INPUT_X, y + PROJECT_INPUT_Y);
        }

        fgets(updated_deadline, sizeof(updated_deadline), stdin);
        updated_deadline[strcspn(updated_deadline, "\n")] = '\0';
        is_end_date_valid = validate_date(updated_deadline);

    } while (is_end_date_valid != VALID);

    // update project end date
    strcpy(deadline, updated_deadline);

    return 0;
}

int delete_project()
{
    // declare all variables
    struct p_details project;
    char project_id_or_name[PROJECT_ID_OR_NAME_SIZE], projectDBS_path[MAX_PATH_LENGTH], tmp_projectDBS_path[MAX_PATH_LENGTH], taskDBS_path[MAX_PATH_LENGTH], tmp_taskDBS_path[MAX_PATH_LENGTH], project_file_path[MAX_PATH_LENGTH], project_file_name[PROJECT_FILE_NAME_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = PROJECT_DELETE_BOX_HEIGHT, x = ZERO, y = ZERO;
    FILE *file_for_delete_project, *write_to_new_project_file, *file_for_delete_task, *write_to_new_task_file;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // show search project screen
    search_project_by_id_or_name_screen(x, y);

    // take project id or name
    move_cursor(x + PROJECT_INPUT_X, y + 5);
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    // get project database paths
    get_path(projectDBS_path);
    get_path(tmp_projectDBS_path);
    strcat(projectDBS_path, PROJECT_DATABASE_FILE);
    strcat(tmp_projectDBS_path, TEMP_PROJECT_DATABASE_FILE);

    // open project databases
    file_for_delete_project = fopen(projectDBS_path, FILE_MODE_READ);
    if (file_for_delete_project == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    write_to_new_project_file = fopen(tmp_projectDBS_path, FILE_MODE_WRITE);
    if (write_to_new_project_file == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // read project database
    while (fgets(row, sizeof(row), file_for_delete_project) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize them
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

        // check project id or name if found delete project
        if (strcmp(project.id, project_id_or_name) == ZERO ||strcmp(project.name, project_id_or_name) == ZERO)
        {
            // get project file path
            get_path(project_file_path);
            strcat(project_file_path, PROJECTS_FOLDER);
            strcat(project_file_path, "\\");

            strcpy(project_file_name, project.name);
            strlwr(project_file_name);

            strcat(project_file_path, project_file_name);
            strcat(project_file_path, PROJECT_FILE_EXTENSION);

            // delete project file
            if (remove(project_file_path) != ZERO)
            {
                something_went_wrong_screen(SOMETHING_FAILED);
            }

            continue;
        }

        // write remaining project data to temporary database
        fprintf(write_to_new_project_file, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",project.id,project.name, project.category, project.description, project.priority,project.status,project.start_date,project.end_date,project.created_by);
    }

    // close project databases
    if (fclose(file_for_delete_project) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    if (fclose(write_to_new_project_file) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    // remove original project database and rename temporary database
    if (remove(projectDBS_path) != ZERO)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }

    if (rename(tmp_projectDBS_path, projectDBS_path) != ZERO)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }

    // get task database paths
    get_path(taskDBS_path);
    get_path(tmp_taskDBS_path);

    strcat(taskDBS_path, TASK_DATABASE_FILE);
    strcat(tmp_taskDBS_path, TEMP_TASK_DATABASE_FILE);

    // open task databases
    file_for_delete_task = fopen(taskDBS_path, FILE_MODE_READ);
    if (file_for_delete_task == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    write_to_new_task_file = fopen(tmp_taskDBS_path, FILE_MODE_WRITE);
    if (write_to_new_task_file == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // read task database
    while (fgets(row, sizeof(row), file_for_delete_task) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize them
        field = strtok(row, ",");
        field = strtok(NULL, ",");
        field = strtok(NULL, ",");

        // check project id if task belongs to deleted project
        if (strcmp(field, project.id) == ZERO)
        {
            continue;
        }

        // write remaining task data to temporary database
        fprintf(write_to_new_task_file, "%s\n", row);
    }

    // close task databases
    if (fclose(file_for_delete_task) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    if (fclose(write_to_new_task_file) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    // remove original task database and rename temporary database
    if (remove(taskDBS_path) != ZERO)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }

    if (rename(tmp_taskDBS_path, taskDBS_path) != ZERO)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }

    return 0;
}

int view_projects()
{
    // declare all variables
    struct p_details project;
    char path[MAX_PATH_LENGTH], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = PROJECT_SHOW_BOX_HEIGHT, x = ZERO, y = ZERO;
    FILE *projectDBS_open;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // get project database path
    get_path(path);
    strcat(path, PROJECT_DATABASE_FILE);

    // open project database
    projectDBS_open = fopen(path, FILE_MODE_READ);
    if (projectDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // read project database
    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize them
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

        // clear screen and show project
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

    // close project database
    if (fclose(projectDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    return 0;
}

int search_by_project_id_or_name()
{
    // declare all variables
    struct p_details project;
    char project_id_or_name[PROJECT_ID_OR_NAME_SIZE], projectDBS_path[MAX_PATH_LENGTH], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = PROJECT_SHOW_BOX_HEIGHT, x = ZERO, y = ZERO;
    FILE *projectDBS_open;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // show search project screen
    search_project_by_id_or_name_screen(x, y);

    // take project id or name
    move_cursor(x + PROJECT_INPUT_X, y + 5);
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    // get project database path
    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DATABASE_FILE);

    // open project database
    projectDBS_open = fopen(projectDBS_path, FILE_MODE_READ);
    if (projectDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // read project database
    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize them
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

        // check project id or name if found show project
        if (strcmp(project_id_or_name, project.id) == ZERO ||strcmp(project_id_or_name, project.name) == ZERO)
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

    // close project database
    if (fclose(projectDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    return 0;
}


int search_project_by_status()
{
    // declare all variables
    struct p_details project;
    char status[PROJECT_STATUS_SIZE], projectDBS_path[MAX_PATH_LENGTH], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = PROJECT_SHOW_BOX_HEIGHT, x = ZERO, y = ZERO, status_box_width = STATUS_BOX_WIDTH, status_box_height = STATUS_BOX_HEIGHT, status_x = ZERO, status_y = ZERO;
    FILE *projectDBS_open;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;
    status_x = (terminal_width - status_box_width) / TWO;
    status_y = (terminal_height - status_box_height) / TWO;

    // show project status dashboard
    project_status_dashboard(status, status_x, status_y);

    // get project database path
    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DATABASE_FILE);

    // open project database
    projectDBS_open = fopen(projectDBS_path, FILE_MODE_READ);
    if (projectDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // read project database
    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize them
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

        // check project status if found show project
        if (strcmp(status, project.status) == ZERO)
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

    // close project database
    if (fclose(projectDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    return ZERO;
}

int search_project_by_priority()
{
    // declare all variables
    struct p_details project;
    char priority[PROJECT_PRIORITY_SIZE], projectDBS_path[MAX_PATH_LENGTH], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = PROJECT_SHOW_BOX_HEIGHT, x = ZERO, y = ZERO, priority_box_width = PRIORITY_BOX_WIDTH, priority_box_height = PRIORITY_BOX_HEIGHT, priority_x = ZERO, priority_y = ZERO;
    FILE *projectDBS_open;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;
    priority_x = (terminal_width - priority_box_width) / TWO;
    priority_y = (terminal_height - priority_box_height) / TWO;

    // show project priority dashboard
    project_priority_dashboard(priority, priority_x, priority_y);

    // get project database path
    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DATABASE_FILE);

    // open project database
    projectDBS_open = fopen(projectDBS_path, FILE_MODE_READ);
    if (projectDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
    }

    // read project database
    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize them
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

        // check project priority if found show project
        if (strcmp(priority, project.priority) == ZERO)
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

    // close project database
    if (fclose(projectDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    return 0;
}

int generate_project_id(char id[])
{
    struct p_details project;
    int found = ZERO, num_id[PROJECT_ID_SIZE] = {ZERO}, project_id = ZERO, id_len = ZERO, tmp = ZERO, i = ZERO, j = ZERO, digit = ZERO;
    char path[MAX_PATH_LENGTH], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    FILE *projectDBS_open;

    strcpy(id, "P1001");

    get_path(path);
    strcat(path, PROJECT_DATABASE_FILE);

    projectDBS_open = fopen(path, FILE_MODE_READ);

    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        found = 1;

        row[strcspn(row, "\n")] = '\0';

        field = strtok(row, ",");

        strcpy(project.id, field);
    }

    fclose(projectDBS_open);

    if (found == ZERO)
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

    strcpy(path, DATABASE_DIR);
    strcat(path, username);
    strcat(path, "\\");

    free(username);

    return 0;
}

int compare_project_priority(const void *a, const void *b)
{
    struct p_details *project_a = (struct p_details *)a, *project_b = (struct p_details *)b;
    int priority_a = ZERO, priority_b = ZERO;

    if (strcmp(project_a->priority, "High") == ZERO)
    {
        priority_a = 3;
    }
    else if (strcmp(project_a->priority, "Medium") == ZERO)
    {
        priority_a = 2;
    }
    else if (strcmp(project_a->priority, "Low") == ZERO)
    {
        priority_a = 1;
    }

    if (strcmp(project_b->priority, "High") == ZERO)
    {
        priority_b = 3;
    }
    else if (strcmp(project_b->priority, "Medium") == ZERO)
    {
        priority_b = 2;
    }
    else if (strcmp(project_b->priority, "Low") == ZERO)
    {
        priority_b = 1;
    }

    return priority_b - priority_a;
}

int sort_projects()
{
    struct p_details projects[PROJECT_ARRAY_SIZE];
    char path[MAX_PATH_LENGTH], sort_path[MAX_PATH_LENGTH], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int project_count = ZERO;
    FILE *projectDBS_open, *sort_project_open;

    get_path(path);
    strcat(path, PROJECT_DATABASE_FILE);

    get_path(sort_path);
    strcat(sort_path, SORTED_PROJECT_FILE);

    projectDBS_open = fopen(path, FILE_MODE_READ);

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

    sort_project_open = fopen(sort_path, FILE_MODE_WRITE);

    for (int i = 0; i < project_count; i++)
    {
        fprintf(sort_project_open, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", projects[i].id, projects[i].name, projects[i].category, projects[i].description, projects[i].priority, projects[i].status, projects[i].start_date, projects[i].end_date, projects[i].created_by);
    }

    fclose(sort_project_open);

    return 0;
}