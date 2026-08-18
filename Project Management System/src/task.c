/*
    ID : 2026-2-60-020
*/
#include "task.h"

int unique_task_id_generator()
{
    // declare all variables
    struct t_details task;
    int found = ZERO, id = INITIAL_UNIQUE_TASK_ID_VALUE;
    char path[TASK_PATH_BUFFER_SIZE], row[TASK_FILE_DATA_SIZE], *field;
    FILE *taskDBS_open;

    // get task database path
    get_path(path);
    strcat(path, TASK_DATABASE_FILE);

    // open taskdbs
    taskDBS_open = fopen(path, FILE_MODE_READ);
    if (taskDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
        return id;
    }

    // read database
    while (fgets(row, sizeof(row), taskDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize data
        field = strtok(row, ",");
        task.unique_id = atoi(field);

        found = 1;
    }

    // close database
    if (fclose(taskDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }
    if (found == ZERO)
    {
        return id;
    }

    return task.unique_id + 1;
}

int generate_task_id(char id[], char path[])
{
    // declare all variables
    struct t_details task;
    int found = ZERO, num_id[15] = {ZERO}, task_id = ZERO, id_len = ZERO, i = ZERO, j = ZERO, digit = ZERO, tmp = ZERO;
    char row[TASK_FILE_DATA_SIZE], *field;
    FILE *taskDBS_open;

    // initialize task id
    strcpy(id, INITIAL_TASK_ID_VALUE);

    // taskdbs open
    taskDBS_open = fopen(path, FILE_MODE_READ);
    if (taskDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
        return 0;
    }

    // read database
    while (fgets(row, sizeof(row), taskDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize data
        field = strtok(row, ",");
        strcpy(task.task_id, field);

        found = 1;
    }

    // close database
    if (fclose(taskDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    if (found == ZERO)
    {
        return 0;
    }

    strcpy(id, task.task_id);
    id_len = strlen(id);

    // convert char array to integer array
    for (i = 0, j = 1; j < id_len; i++, j++)
    {
        num_id[i] = id[j] - '0';
    }

    // convert to number
    for (i = 0; i < id_len - 1; i++)
    {
        digit = num_id[i];
        for (j = i; j < id_len - 2; j++)
        {
            digit *= 10;
        }
        task_id += digit;
    }

    // increment by one
    task_id++;
    tmp = task_id;
    j = id_len - 1;

    // convert to char array
    while (tmp != 0 && j > 0)
    {
        id[j] = (tmp % 10) + '0';
        tmp /= 10;
        j--;
    }

    return 0;
}

int create_task()
{
    // declare all variables
    struct t_details task;
    struct p_details project;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = TASK_BOX_HEIGHT, x = ZERO, y = ZERO, priority_box_width = TASK_PRIORITY_BOX_WIDTH, priority_box_height = TASK_PRIORITY_BOX_HEIGHT, priority_x = ZERO, priority_y = ZERO, is_start_date_valid = ZERO, is_end_date_valid = ZERO, project_found = ZERO;
    char project_id_or_name[PROJECT_SEARCH_SIZE], projectDBS_path[TASK_PATH_BUFFER_SIZE], project_task_path[TASK_PATH_BUFFER_SIZE], taskDBS_path[TASK_PATH_BUFFER_SIZE], row[TASK_FILE_DATA_SIZE], project_file_name[PROJECT_FILE_NAME_SIZE], *field, *username;
    FILE *projectDBS_open, *taskDBS_open, *project_task_open;

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

    // get username
    username = get_user_name();

    // show project id enter screen
    search_project_by_id_or_name_screen(x, y);

    // take project id or name
    move_cursor(x + PROJECT_INPUT_X, y + TASK_CREATE_Y_NAME_OFFSET);
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    // get project database path
    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DATABASE_FILE);

    // projectdbs opne
    projectDBS_open = fopen(projectDBS_path, FILE_MODE_READ);
    if (projectDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
        free(username);
        return 0;
    }

    // read database
    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize data

        field = strtok(row, ",");
        strcpy(project.id, field);

        field = strtok(NULL, ",");
        strcpy(project.name, field);

        if (strcmp(project_id_or_name, project.id) == ZERO || strcmp(project_id_or_name, project.name) == ZERO)
        {
            project_found = 1;
            break;
        }
    }

    // close database
    if (fclose(projectDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    if (project_found == ZERO)
    {
        free(username);
        return 0;
    }

    // get project task database path
    get_path(project_task_path);
    strcat(project_task_path, PROJECTS_FOLDER);
    strcat(project_task_path, "\\");

    strcpy(project_file_name, project.name);
    strlwr(project_file_name);

    strcat(project_task_path, project_file_name);
    strcat(project_task_path, TASK_FILE_EXTENSION);

    // generate unique task id
    task.unique_id = unique_task_id_generator();

    // generate task id
    generate_task_id(task.task_id, project_task_path);

    strcpy(task.project_id, project.id);

    clear_screen();
    header_screen();

    create_task_screen(x, y);

    // take task name
    move_cursor(x + PROJECT_INPUT_X, y + TASK_CREATE_Y_NAME_OFFSET);
    fgets(task.name, sizeof(task.name), stdin);
    task.name[strcspn(task.name, "\n")] = '\0';

    // take task description
    move_cursor(x + PROJECT_INPUT_X, y + TASK_CREATE_Y_DESCRIPTION_OFFSET);
    fgets(task.description, sizeof(task.description), stdin);
    task.description[strcspn(task.description, "\n")] = '\0';

    task_priority_dashboard(task.priority, priority_x, priority_y);

    clear_screen();
    header_screen();

    create_task_screen(x, y);

    move_cursor(x + PROJECT_INPUT_X, y + TASK_CREATE_Y_NAME_OFFSET);
    printf("%s", task.name);

    move_cursor(x + PROJECT_INPUT_X, y + TASK_CREATE_Y_DESCRIPTION_OFFSET);
    printf("%s", task.description);

    move_cursor(x + PROJECT_INPUT_X, y + TASK_CREATE_Y_PRIORITY_OFFSET);
    printf("%s", task.priority);

    strcpy(task.status, DEFAULT_TASK_STATUS);

    // validate date
    do
    {
        move_cursor(x + PROJECT_INPUT_X, y + TASK_CREATE_Y_START_DATE_OFFSET);

        if (is_start_date_valid == ZERO)
        {
            printf("                                                                             ");
            move_cursor(x + PROJECT_INPUT_X, y + TASK_CREATE_Y_START_DATE_OFFSET);
        }

        fgets(task.start_date, sizeof(task.start_date), stdin);
        task.start_date[strcspn(task.start_date, "\n")] = '\0';

        is_start_date_valid = validate_date(task.start_date);
    } while (is_start_date_valid != VALID);

    do
    {
        move_cursor(x + PROJECT_INPUT_X, y + TASK_CREATE_Y_END_DATE_OFFSET);

        if (is_end_date_valid == ZERO)
        {
            printf("                                                                             ");
            move_cursor(x + PROJECT_INPUT_X, y + TASK_CREATE_Y_END_DATE_OFFSET);
        }

        fgets(task.end_date, sizeof(task.end_date), stdin);
        task.end_date[strcspn(task.end_date, "\n")] = '\0';

        is_end_date_valid = validate_date(task.end_date);
    } while (is_end_date_valid != VALID);

    strcpy(task.created_by, username);

    // get task database path
    get_path(taskDBS_path);
    strcat(taskDBS_path, TASK_DATABASE_FILE);

    taskDBS_open = fopen(taskDBS_path, FILE_MODE_APPEND);

    if (taskDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
        free(username);
        return 0;
    }

    // write data to database

    fprintf(taskDBS_open, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.unique_id, task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);

    // close database
    if (fclose(taskDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    project_task_open = fopen(project_task_path, FILE_MODE_APPEND);
    if (project_task_open != NULL)
    {
        // write data to database
        fprintf(project_task_open, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);

        // close database
        if (fclose(project_task_open) == EOF)
        {
            something_went_wrong_screen(FILE_CLOSE_ERROR);
        }
    }

    free(username);

    return 0;
}

int update_task()
{
    // declare all variables
    struct t_details task;
    struct p_details project;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO, project_found = ZERO;
    char project_id_or_name[PROJECT_SEARCH_SIZE], task_id_or_name[TASK_SEARCH_SIZE], projectDBS_path[TASK_PATH_BUFFER_SIZE], taskDBS_path[TASK_PATH_BUFFER_SIZE], tmp_task_path[TASK_PATH_BUFFER_SIZE], project_task_path[TASK_PATH_BUFFER_SIZE], tmp_project_task_path[TASK_PATH_BUFFER_SIZE], project_file_name[PROJECT_FILE_NAME_SIZE], row[TASK_FILE_DATA_SIZE], *field;
    FILE *projectDBS_open, *taskDBS_open, *tmp_task, *tmp_project_task;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // show project id or name enter screen
    search_project_by_id_or_name_screen(x, y);

    // take project id or name
    move_cursor(x + PROJECT_INPUT_X, y + TASK_CREATE_Y_NAME_OFFSET);
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    // get project database path
    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DATABASE_FILE);

    projectDBS_open = fopen(projectDBS_path, FILE_MODE_READ);
    if (projectDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
        return 0;
    }

    // read database
    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize data
        field = strtok(row, ",");
        strcpy(project.id, field);

        field = strtok(NULL, ",");
        strcpy(project.name, field);

        if (strcmp(project_id_or_name, project.id) == ZERO || strcmp(project_id_or_name, project.name) == ZERO)
        {
            project_found = 1;
            break;
        }
    }

    // close database
    if (fclose(projectDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    if (project_found == ZERO)
    {
        return 0;
    }

    search_task_by_id_or_name_screen(x, y);

    // take task id
    move_cursor(x + PROJECT_INPUT_X, y + TASK_SEARCH_INPUT_Y);
    fgets(task_id_or_name, sizeof(task_id_or_name), stdin);
    task_id_or_name[strcspn(task_id_or_name, "\n")] = '\0';

    // get task database path
    get_path(taskDBS_path);
    strcat(taskDBS_path, TASK_DATABASE_FILE);

    // get temporary task database path
    get_path(tmp_task_path);
    strcat(tmp_task_path, TEMP_TASK_DATABASE_FILE);

    // task dbs open
    taskDBS_open = fopen(taskDBS_path, FILE_MODE_READ);
    tmp_task = fopen(tmp_task_path, FILE_MODE_WRITE);

    if (taskDBS_open == NULL || tmp_task == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);

        if (taskDBS_open != NULL)
        {
            // close database
            if (fclose(taskDBS_open) == EOF)
            {
                something_went_wrong_screen(FILE_CLOSE_ERROR);
            }
        }

        if (tmp_task != NULL)
        {
            // close database
            if (fclose(tmp_task) == EOF)
            {
                something_went_wrong_screen(FILE_CLOSE_ERROR);
            }
        }

        return 0;
    }

    // read database
    while (fgets(row, sizeof(row), taskDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize data
        field = strtok(row, ",");
        task.unique_id = atoi(field);

        field = strtok(NULL, ",");
        strcpy(task.task_id, field);

        field = strtok(NULL, ",");
        strcpy(task.project_id, field);

        field = strtok(NULL, ",");
        strcpy(task.name, field);

        field = strtok(NULL, ",");
        strcpy(task.description, field);

        field = strtok(NULL, ",");
        strcpy(task.priority, field);

        field = strtok(NULL, ",");
        strcpy(task.status, field);

        field = strtok(NULL, ",");
        strcpy(task.start_date, field);

        field = strtok(NULL, ",");
        strcpy(task.end_date, field);

        field = strtok(NULL, ",");
        strcpy(task.created_by, field);

        if ((strcmp(task.task_id, task_id_or_name) == ZERO || strcmp(task.name, task_id_or_name) == ZERO) && strcmp(task.project_id, project.id) == ZERO)
        {
            task_update_dashboard(&task, x, y);
        }

        // write data to database
        fprintf(tmp_task, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.unique_id, task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
    }

    // close database
    if (fclose(taskDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }
    // close database
    if (fclose(tmp_task) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    // remove original database
    if (remove(taskDBS_path) != ZERO)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }
    // rename temporary database as original database
    if (rename(tmp_task_path, taskDBS_path) != ZERO)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }

    // get project task database path
    get_path(project_task_path);
    strcat(project_task_path, PROJECTS_FOLDER);
    strcat(project_task_path, "\\");

    strcpy(project_file_name, project.name);
    strlwr(project_file_name);

    strcat(project_task_path, project_file_name);
    strcat(project_task_path, TASK_FILE_EXTENSION);

    // get temporary project task database path
    get_path(tmp_project_task_path);
    strcat(tmp_project_task_path, PROJECTS_FOLDER);
    strcat(tmp_project_task_path, "\\");
    strcat(tmp_project_task_path, TEMP_TASK_DATABASE_FILE);

    taskDBS_open = fopen(taskDBS_path, FILE_MODE_READ);
    tmp_project_task = fopen(tmp_project_task_path, FILE_MODE_WRITE);

    if (taskDBS_open == NULL || tmp_project_task == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);

        if (taskDBS_open != NULL)
        {
            // close database
            if (fclose(taskDBS_open) == EOF)
            {
                something_went_wrong_screen(FILE_CLOSE_ERROR);
            }
        }

        if (tmp_project_task != NULL)
        {
            // close database
            if (fclose(tmp_project_task) == EOF)
            {
                something_went_wrong_screen(FILE_CLOSE_ERROR);
            }
        }

        return 0;
    }

    // read database
    while (fgets(row, sizeof(row), taskDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize data
        field = strtok(row, ",");
        task.unique_id = atoi(field);

        field = strtok(NULL, ",");
        strcpy(task.task_id, field);

        field = strtok(NULL, ",");
        strcpy(task.project_id, field);

        field = strtok(NULL, ",");
        strcpy(task.name, field);

        field = strtok(NULL, ",");
        strcpy(task.description, field);

        field = strtok(NULL, ",");
        strcpy(task.priority, field);

        field = strtok(NULL, ",");
        strcpy(task.status, field);

        field = strtok(NULL, ",");
        strcpy(task.start_date, field);

        field = strtok(NULL, ",");
        strcpy(task.end_date, field);

        field = strtok(NULL, ",");
        strcpy(task.created_by, field);

        if (strcmp(task.project_id, project.id) == ZERO)
        {
            // write data to database
            fprintf(tmp_project_task, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.task_id, project.id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
        }
    }

    // close database
    if (fclose(taskDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }
    // close database
    if (fclose(tmp_project_task) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    // remove original database

    if (remove(project_task_path) != ZERO)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }
    // rename temporary database as original database
    if (rename(tmp_project_task_path, project_task_path) != ZERO)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }

    return 0;
}

int change_task_name(char name[])
{
    // declare all variables
    char new_name[TASK_NAME_SIZE];
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO;

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // show task name enter screen
    change_task_name_screen(x, y);

    // take new task name
    move_cursor(x + PROJECT_INPUT_X, y + TASK_NAME_Y);
    fgets(new_name, sizeof(new_name), stdin);
    new_name[strcspn(new_name, "\n")] = '\0';
    strcpy(name, new_name);

    return 0;
}

int change_task_description(char description[])
{
    // declare all variables
    char new_description[TASK_DESCRIPTION_SIZE];
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO;

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // show task description enter screen
    change_task_description_screen(x, y);

    // take task description
    move_cursor(x + PROJECT_INPUT_X, y + TASK_DESCRIPTION_Y);
    fgets(new_description, sizeof(new_description), stdin);
    new_description[strcspn(new_description, "\n")] = '\0';
    strcpy(description, new_description);

    return 0;
}

int change_task_status(char status[])
{
    // declare all variables
    int terminal_width, terminal_height, x, y;

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - TASK_STATUS_BOX_WIDTH) / TWO;
    y = (terminal_height - TASK_STATUS_BOX_HEIGHT) / TWO;

    // show task status change screen
    task_status_dashboard(status, x, y);

    return 0;
}

int change_task_priority(char priority[])
{
    // declare all variables
    int terminal_width, terminal_height, x, y;

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - TASK_PRIORITY_BOX_WIDTH) / TWO;
    y = (terminal_height - TASK_PRIORITY_BOX_HEIGHT) / TWO;

    // show change task priority screen
    task_priority_dashboard(priority, x, y);

    return 0;
}

int change_task_start_date(char start_date[])
{
    // declare all variables
    char new_start_date[TASK_START_DATE_SIZE];
    int is_valid = INVALID, terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO;

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // validate date
    do
    {
        change_task_start_date_screen(x, y);

        // take date
        move_cursor(x + PROJECT_INPUT_X, y + TASK_START_DATE_Y);
        fgets(new_start_date, sizeof(new_start_date), stdin);
        new_start_date[strcspn(new_start_date, "\n")] = '\0';

        is_valid = validate_date(new_start_date);
    } while (is_valid != VALID);
    strcpy(start_date, new_start_date);

    return 0;
}

int extend_task_deadline(char deadline[])
{
    // declare all variables
    char new_deadline[TASK_END_DATE_SIZE];
    int is_valid = INVALID, terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO;

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // validate date
    do
    {
        extend_task_deadline_screen(x, y);

        // take date
        move_cursor(x + PROJECT_INPUT_X, y + TASK_END_DATE_Y);
        fgets(new_deadline, sizeof(new_deadline), stdin);
        new_deadline[strcspn(new_deadline, "\n")] = '\0';

        is_valid = validate_date(new_deadline);
    } while (is_valid != VALID);

    strcpy(deadline, new_deadline);

    return 0;
}

int delete_task()
{
    // declare all variables
    struct t_details task;
    struct p_details project;
    char project_id_or_name[PROJECT_SEARCH_SIZE], task_id_or_name[TASK_SEARCH_SIZE], projectDBS_path[TASK_PATH_BUFFER_SIZE], taskDBS_path[TASK_PATH_BUFFER_SIZE], tmp_task_path[TASK_PATH_BUFFER_SIZE], project_task_path[TASK_PATH_BUFFER_SIZE], tmp_project_task_path[TASK_PATH_BUFFER_SIZE], project_file_name[PROJECT_FILE_NAME_SIZE], row[TASK_FILE_DATA_SIZE], *field;
    int x = ZERO, y = ZERO, terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, project_found = ZERO;
    FILE *projectDBS_open, *taskDBS_open, *tmp_task, *project_task_open, *tmp_project_task;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // show project id or name enter screen
    search_project_by_id_or_name_screen(x, y);

    // take project id or name
    move_cursor(x + PROJECT_INPUT_X, y + TASK_CREATE_Y_NAME_OFFSET);
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    // get project database path
    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DATABASE_FILE);

    // open project dbs
    projectDBS_open = fopen(projectDBS_path, FILE_MODE_READ);
    if (projectDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
        return 0;
    }

    // read database
    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize data
        field = strtok(row, ",");
        strcpy(project.id, field);

        field = strtok(NULL, ",");
        strcpy(project.name, field);

        if (strcmp(project_id_or_name, project.id) == ZERO || strcmp(project_id_or_name, project.name) == ZERO)
        {
            project_found = 1;
            break;
        }
    }

    // close database
    if (fclose(projectDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    if (project_found == ZERO)
    {
        return 0;
    }

    // get project task database path
    get_path(project_task_path);
    strcat(project_task_path, PROJECTS_FOLDER);
    strcat(project_task_path, "\\");

    strcpy(project_file_name, project.name);
    strlwr(project_file_name);

    strcat(project_task_path, project_file_name);
    strcat(project_task_path, TASK_FILE_EXTENSION);

    // show task id or name enter screen
    search_task_by_id_or_name_screen(x, y);

    // take task id or name
    move_cursor(x + PROJECT_INPUT_X, y + TASK_SEARCH_INPUT_Y);
    fgets(task_id_or_name, sizeof(task_id_or_name), stdin);
    task_id_or_name[strcspn(task_id_or_name, "\n")] = '\0';

    // get temporary project task database path
    get_path(tmp_project_task_path);
    strcat(tmp_project_task_path, PROJECTS_FOLDER);
    strcat(tmp_project_task_path, "\\");
    strcat(tmp_project_task_path, TEMP_TASK_DATABASE_FILE);

    // open database
    project_task_open = fopen(project_task_path, FILE_MODE_READ);
    tmp_project_task = fopen(tmp_project_task_path, FILE_MODE_WRITE);

    if (project_task_open == NULL || tmp_project_task == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);

        if (project_task_open != NULL)
        {
            // close database
            if (fclose(project_task_open) == EOF)
            {
                something_went_wrong_screen(FILE_CLOSE_ERROR);
            }
        }

        if (tmp_project_task != NULL)
        {
            // close database
            if (fclose(tmp_project_task) == EOF)
            {
                something_went_wrong_screen(FILE_CLOSE_ERROR);
            }
        }

        return 0;
    }

    // read database
    while (fgets(row, sizeof(row), project_task_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize data
        field = strtok(row, ",");
        strcpy(task.task_id, field);

        field = strtok(NULL, ",");
        strcpy(task.project_id, field);

        field = strtok(NULL, ",");
        strcpy(task.name, field);

        field = strtok(NULL, ",");
        strcpy(task.description, field);

        field = strtok(NULL, ",");
        strcpy(task.priority, field);

        field = strtok(NULL, ",");
        strcpy(task.status, field);

        field = strtok(NULL, ",");
        strcpy(task.start_date, field);

        field = strtok(NULL, ",");
        strcpy(task.end_date, field);

        field = strtok(NULL, ",");
        strcpy(task.created_by, field);

        if ((strcmp(task.task_id, task_id_or_name) == ZERO || strcmp(task.name, task_id_or_name) == ZERO) && strcmp(task.project_id, project.id) == ZERO)
        {
            continue;
        }

        // write data to database
        fprintf(tmp_project_task, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
    }

    // close database
    if (fclose(project_task_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }
    // close database
    if (fclose(tmp_project_task) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    // remove original database
    if (remove(project_task_path) != ZERO)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }
    // rename temporary database as original database
    if (rename(tmp_project_task_path, project_task_path) != ZERO)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }

    // get task database path
    get_path(taskDBS_path);
    strcat(taskDBS_path, TASK_DATABASE_FILE);

    // get temporary task database path
    get_path(tmp_task_path);
    strcat(tmp_task_path, TEMP_TASK_DATABASE_FILE);

    // open database
    taskDBS_open = fopen(taskDBS_path, FILE_MODE_READ);
    tmp_task = fopen(tmp_task_path, FILE_MODE_WRITE);

    if (taskDBS_open == NULL || tmp_task == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);

        if (taskDBS_open != NULL)
        {
            // close database
            if (fclose(taskDBS_open) == EOF)
            {
                something_went_wrong_screen(FILE_CLOSE_ERROR);
            }
        }

        if (tmp_task != NULL)
        {
            // close database
            if (fclose(tmp_task) == EOF)
            {
                something_went_wrong_screen(FILE_CLOSE_ERROR);
            }
        }

        return 0;
    }

    // read database
    while (fgets(row, sizeof(row), taskDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize data
        field = strtok(row, ",");
        task.unique_id = atoi(field);

        field = strtok(NULL, ",");
        strcpy(task.task_id, field);

        field = strtok(NULL, ",");
        strcpy(task.project_id, field);

        field = strtok(NULL, ",");
        strcpy(task.name, field);

        field = strtok(NULL, ",");
        strcpy(task.description, field);

        field = strtok(NULL, ",");
        strcpy(task.priority, field);

        field = strtok(NULL, ",");
        strcpy(task.status, field);

        field = strtok(NULL, ",");
        strcpy(task.start_date, field);

        field = strtok(NULL, ",");
        strcpy(task.end_date, field);

        field = strtok(NULL, ",");
        strcpy(task.created_by, field);

        if ((strcmp(task.task_id, task_id_or_name) == ZERO || strcmp(task.name, task_id_or_name) == ZERO) && strcmp(task.project_id, project.id) == ZERO)
        {
            continue;
        }

        // write data to database
        fprintf(tmp_task, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.unique_id, task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
    }

    // close database
    if (fclose(taskDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }
    // close database
    if (fclose(tmp_task) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    // remove original database

    if (remove(taskDBS_path) != ZERO)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }
    // rename temporary database as original database
    if (rename(tmp_task_path, taskDBS_path) != ZERO)
    {
        something_went_wrong_screen(SOMETHING_FAILED);
    }

    return 0;
}

int view_tasks()
{
    // declare all variables
    struct t_details task;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO;
    char path[TASK_PATH_BUFFER_SIZE], row[TASK_FILE_DATA_SIZE], *field;
    FILE *taskDBS_open;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // get task database path
    get_path(path);
    strcat(path, TASK_DATABASE_FILE);

    // open database
    taskDBS_open = fopen(path, FILE_MODE_READ);

    if (taskDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
        return 0;
    }

    // read database
    while (fgets(row, sizeof(row), taskDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize data
        field = strtok(row, ",");
        task.unique_id = atoi(field);

        field = strtok(NULL, ",");
        strcpy(task.task_id, field);

        field = strtok(NULL, ",");
        strcpy(task.project_id, field);

        field = strtok(NULL, ",");
        strcpy(task.name, field);

        field = strtok(NULL, ",");
        strcpy(task.description, field);

        field = strtok(NULL, ",");
        strcpy(task.priority, field);

        field = strtok(NULL, ",");
        strcpy(task.status, field);

        field = strtok(NULL, ",");
        strcpy(task.start_date, field);

        field = strtok(NULL, ",");
        strcpy(task.end_date, field);

        field = strtok(NULL, ",");
        strcpy(task.created_by, field);

        clear_screen();
        header_screen();

        task_details_screen(x, y);

        // print task details
        move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_UNIQUE_ID_OFFSET);
        printf("%d ", task.unique_id);

        move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_TASK_ID_OFFSET);
        printf("%s ", task.task_id);

        move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_PROJECT_ID_OFFSET);
        printf("%s ", task.project_id);

        move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_NAME_OFFSET);
        printf("%s ", task.name);

        move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_DESCRIPTION_OFFSET);
        printf("%s ", task.description);

        move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_PRIORITY_OFFSET);
        printf("%s ", task.priority);

        move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_STATUS_OFFSET);
        printf("%s ", task.status);

        move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_START_DATE_OFFSET);
        printf("%s ", task.start_date);

        move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_END_DATE_OFFSET);
        printf("%s ", task.end_date);

        get_input;
    }

    // close database
    if (fclose(taskDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    return 0;
}

int search_by_task_id_or_name()
{
    // declare all variables
    struct t_details task;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO;
    char task_id_or_name[TASK_SEARCH_SIZE], path[TASK_PATH_BUFFER_SIZE], row[TASK_FILE_DATA_SIZE], *field;
    FILE *taskDBS_open;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // show task id or name enter screen
    search_task_by_id_or_name_screen(x, y);

    // take task id or name
    move_cursor(x + PROJECT_INPUT_X, y + TASK_SEARCH_INPUT_Y);
    fgets(task_id_or_name, sizeof(task_id_or_name), stdin);
    task_id_or_name[strcspn(task_id_or_name, "\n")] = '\0';

    // get task database path
    get_path(path);
    strcat(path, TASK_DATABASE_FILE);

    // open database
    taskDBS_open = fopen(path, FILE_MODE_READ);
    if (taskDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
        return 0;
    }

    // read database
    while (fgets(row, sizeof(row), taskDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize data
        field = strtok(row, ",");
        task.unique_id = atoi(field);

        field = strtok(NULL, ",");
        strcpy(task.task_id, field);

        field = strtok(NULL, ",");
        strcpy(task.project_id, field);

        field = strtok(NULL, ",");
        strcpy(task.name, field);

        field = strtok(NULL, ",");
        strcpy(task.description, field);

        field = strtok(NULL, ",");
        strcpy(task.priority, field);

        field = strtok(NULL, ",");
        strcpy(task.status, field);

        field = strtok(NULL, ",");
        strcpy(task.start_date, field);

        field = strtok(NULL, ",");
        strcpy(task.end_date, field);

        field = strtok(NULL, ",");
        strcpy(task.created_by, field);

        if (strcmp(task.task_id, task_id_or_name) == ZERO || strcmp(task.name, task_id_or_name) == ZERO)
        {
            clear_screen();
            header_screen();

            task_details_screen(x, y);

            // print task details
            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_UNIQUE_ID_OFFSET);
            printf("%d", task.unique_id);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_TASK_ID_OFFSET);
            printf("%s", task.task_id);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_PROJECT_ID_OFFSET);
            printf("%s", task.project_id);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_NAME_OFFSET);
            printf("%s", task.name);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_DESCRIPTION_OFFSET);
            printf("%s", task.description);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_PRIORITY_OFFSET);
            printf("%s", task.priority);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_STATUS_OFFSET);
            printf("%s", task.status);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_START_DATE_OFFSET);
            printf("%s", task.start_date);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_END_DATE_OFFSET);
            printf("%s", task.end_date);

            get_input;

            break;
        }
    }

    // close database
    if (fclose(taskDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    return 0;
}

int view_tasks_by_project()
{
    // declare all variables
    struct p_details project;
    struct t_details task;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO, project_found = ZERO;
    char project_id_or_name[PROJECT_SEARCH_SIZE], projectDBS_path[TASK_PATH_BUFFER_SIZE], project_task_path[TASK_PATH_BUFFER_SIZE], project_file_name[PROJECT_FILE_NAME_SIZE], row[TASK_FILE_DATA_SIZE], *field;
    FILE *projectDBS_open, *project_task_open;

    // set terminal for UTF8 and show header screen
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    // show project id or name enter screen
    search_project_by_id_or_name_screen(x, y);

    // take project id or name
    move_cursor(x + PROJECT_INPUT_X, y + TASK_SEARCH_INPUT_Y);
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    // get project database path
    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DATABASE_FILE);

    // open database
    projectDBS_open = fopen(projectDBS_path, FILE_MODE_READ);
    if (projectDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
        return 0;
    }

    // read database
    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize data
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

        if (strcmp(project_id_or_name, project.id) == ZERO || strcmp(project_id_or_name, project.name) == ZERO)
        {
            project_found = 1;
            break;
        }
    }

    // close database
    if (fclose(projectDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    if (project_found == ZERO)
    {
        return 0;
    }

    // get project task database path
    get_path(project_task_path);
    strcat(project_task_path, PROJECTS_FOLDER);
    strcat(project_task_path, "\\");

    strcpy(project_file_name, project.name);
    strlwr(project_file_name);

    strcat(project_task_path, project_file_name);
    strcat(project_task_path, TASK_FILE_EXTENSION);

    // open database
    project_task_open = fopen(project_task_path, FILE_MODE_READ);
    if (project_task_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
        return 0;
    }

    // read database
    while (fgets(row, sizeof(row), project_task_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        // tokenize data
        field = strtok(row, ",");
        strcpy(task.task_id, field);

        field = strtok(NULL, ",");
        strcpy(task.project_id, field);

        field = strtok(NULL, ",");
        strcpy(task.name, field);

        field = strtok(NULL, ",");
        strcpy(task.description, field);

        field = strtok(NULL, ",");
        strcpy(task.priority, field);

        field = strtok(NULL, ",");
        strcpy(task.status, field);

        field = strtok(NULL, ",");
        strcpy(task.start_date, field);

        field = strtok(NULL, ",");
        strcpy(task.end_date, field);

        field = strtok(NULL, ",");
        strcpy(task.created_by, field);

        clear_screen();
        header_screen();

        task_details_screen_for_separate_project(x, y);

        // print task details
        move_cursor(x + PROJECT_INPUT_X, y + TASK_VIEW_PROJECT_Y_TASK_ID_OFFSET);
        printf("%s", task.task_id);

        move_cursor(x + PROJECT_INPUT_X, y + TASK_VIEW_PROJECT_Y_PROJECT_ID_OFFSET);
        printf("%s", task.project_id);

        move_cursor(x + PROJECT_INPUT_X, y + TASK_VIEW_PROJECT_Y_NAME_OFFSET);
        printf("%s", task.name);

        move_cursor(x + PROJECT_INPUT_X, y + TASK_VIEW_PROJECT_Y_DESCRIPTION_OFFSET);
        printf("%s", task.description);

        move_cursor(x + PROJECT_INPUT_X, y + TASK_VIEW_PROJECT_Y_PRIORITY_OFFSET);
        printf("%s", task.priority);

        move_cursor(x + PROJECT_INPUT_X, y + TASK_VIEW_PROJECT_Y_STATUS_OFFSET);
        printf("%s", task.status);

        move_cursor(x + PROJECT_INPUT_X, y + TASK_VIEW_PROJECT_Y_START_DATE_OFFSET);
        printf("%s", task.start_date);

        move_cursor(x + PROJECT_INPUT_X, y + TASK_VIEW_PROJECT_Y_END_DATE_OFFSET);
        printf("%s", task.end_date);

        get_input;
    }

    // close database
    if (fclose(project_task_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    return 0;
}

int search_task_by_status()
{
    struct t_details task;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO, status_box_width = TASK_STATUS_BOX_WIDTH, status_box_height = TASK_STATUS_BOX_HEIGHT, status_x = ZERO, status_y = ZERO;
    char status[TASK_STATUS_SIZE], path[TASK_PATH_BUFFER_SIZE], row[TASK_FILE_DATA_SIZE], *field;
    FILE *taskDBS_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;
    status_x = (terminal_width - status_box_width) / TWO;
    status_y = (terminal_height - status_box_height) / TWO;

    task_status_dashboard(status, status_x, status_y);

    get_path(path);
    strcat(path, TASK_DATABASE_FILE);

    taskDBS_open = fopen(path, FILE_MODE_READ);

    while (fgets(row, sizeof(row), taskDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        field = strtok(row, ",");
        task.unique_id = atoi(field);

        field = strtok(NULL, ",");
        strcpy(task.task_id, field);

        field = strtok(NULL, ",");
        strcpy(task.project_id, field);

        field = strtok(NULL, ",");
        strcpy(task.name, field);

        field = strtok(NULL, ",");
        strcpy(task.description, field);

        field = strtok(NULL, ",");
        strcpy(task.priority, field);

        field = strtok(NULL, ",");
        strcpy(task.status, field);

        field = strtok(NULL, ",");
        strcpy(task.start_date, field);

        field = strtok(NULL, ",");
        strcpy(task.end_date, field);

        field = strtok(NULL, ",");
        strcpy(task.created_by, field);

        if (strcmp(task.status, status) == ZERO)
        {
            clear_screen();
            header_screen();

            task_details_screen(x, y);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_UNIQUE_ID_OFFSET);
            printf("%d", task.unique_id);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_TASK_ID_OFFSET);
            printf("%s", task.task_id);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_PROJECT_ID_OFFSET);
            printf("%s", task.project_id);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_NAME_OFFSET);
            printf("%s", task.name);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_DESCRIPTION_OFFSET);
            printf("%s", task.description);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_PRIORITY_OFFSET);
            printf("%s", task.priority);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_STATUS_OFFSET);
            printf("%s", task.status);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_START_DATE_OFFSET);
            printf("%s", task.start_date);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_END_DATE_OFFSET);
            printf("%s", task.end_date);

            get_input;
        }
    }

    fclose(taskDBS_open);

    return 0;
}

int search_task_by_priority()
{
    struct t_details task;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = CONTAINER_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO, priority_box_width = TASK_PRIORITY_BOX_WIDTH, priority_box_height = TASK_PRIORITY_BOX_HEIGHT, priority_x = ZERO, priority_y = ZERO;
    char priority[TASK_PRIORITY_SIZE], path[TASK_PATH_BUFFER_SIZE], row[TASK_FILE_DATA_SIZE], *field;
    FILE *taskDBS_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;
    priority_x = (terminal_width - priority_box_width) / TWO;
    priority_y = (terminal_height - priority_box_height) / TWO;

    task_priority_dashboard(priority, priority_x, priority_y);

    get_path(path);
    strcat(path, TASK_DATABASE_FILE);

    taskDBS_open = fopen(path, FILE_MODE_READ);

    while (fgets(row, sizeof(row), taskDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        field = strtok(row, ",");
        task.unique_id = atoi(field);

        field = strtok(NULL, ",");
        strcpy(task.task_id, field);

        field = strtok(NULL, ",");
        strcpy(task.project_id, field);

        field = strtok(NULL, ",");
        strcpy(task.name, field);

        field = strtok(NULL, ",");
        strcpy(task.description, field);

        field = strtok(NULL, ",");
        strcpy(task.priority, field);

        field = strtok(NULL, ",");
        strcpy(task.status, field);

        field = strtok(NULL, ",");
        strcpy(task.start_date, field);

        field = strtok(NULL, ",");
        strcpy(task.end_date, field);

        field = strtok(NULL, ",");
        strcpy(task.created_by, field);

        if (strcmp(task.priority, priority) == ZERO)
        {

            clear_screen();
            header_screen();

            task_details_screen(x, y);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_UNIQUE_ID_OFFSET);
            printf("%d ", task.unique_id);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_TASK_ID_OFFSET);
            printf("%s ", task.task_id);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_PROJECT_ID_OFFSET);
            printf("%s ", task.project_id);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_NAME_OFFSET);
            printf("%s ", task.name);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_DESCRIPTION_OFFSET);
            printf("%s ", task.description);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_PRIORITY_OFFSET);
            printf("%s ", task.priority);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_STATUS_OFFSET);
            printf("%s ", task.status);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_START_DATE_OFFSET);
            printf("%s ", task.start_date);

            move_cursor(x + PROJECT_INPUT_X, y + TASK_DETAILS_Y_END_DATE_OFFSET);
            printf("%s ", task.end_date);

            get_input;
        }
    }

    fclose(taskDBS_open);

    return 0;
}

int sort_tasks()
{
    struct t_details task[TASK_ARRAY_SIZE];
    char taskDBS_path[TASK_PATH_BUFFER_SIZE], sort_task_path[TASK_PATH_BUFFER_SIZE], row[TASK_FILE_DATA_SIZE], *field;
    int task_count = ZERO, i;
    FILE *taskDBS_open, *sort_task_open;

    get_path(taskDBS_path);
    strcat(taskDBS_path, TASK_DATABASE_FILE);

    get_path(sort_task_path);
    strcat(sort_task_path, SORTED_TASK_FILE);

    taskDBS_open = fopen(taskDBS_path, FILE_MODE_READ);

    while (fgets(row, sizeof(row), taskDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

        field = strtok(row, ",");
        task[task_count].unique_id = atoi(field);

        field = strtok(NULL, ",");
        strcpy(task[task_count].task_id, field);

        field = strtok(NULL, ",");
        strcpy(task[task_count].project_id, field);

        field = strtok(NULL, ",");
        strcpy(task[task_count].name, field);

        field = strtok(NULL, ",");
        strcpy(task[task_count].description, field);

        field = strtok(NULL, ",");
        strcpy(task[task_count].priority, field);

        field = strtok(NULL, ",");
        strcpy(task[task_count].status, field);

        field = strtok(NULL, ",");
        strcpy(task[task_count].start_date, field);

        field = strtok(NULL, ",");
        strcpy(task[task_count].end_date, field);

        field = strtok(NULL, ",");
        strcpy(task[task_count].created_by, field);

        task_count++;
    }

    fclose(taskDBS_open);

    qsort(task, task_count, sizeof(struct t_details), sort_by_priority);

    sort_task_open = fopen(sort_task_path, FILE_MODE_WRITE);

    for (i = 0; i < task_count; i++)
    {
        fprintf(sort_task_open, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task[i].unique_id, task[i].task_id, task[i].project_id, task[i].name, task[i].description, task[i].priority, task[i].status, task[i].start_date, task[i].end_date, task[i].created_by);
    }

    fclose(sort_task_open);

    return 0;
}

int sort_by_priority(const void *a, const void *b)
{
    struct t_details *task_a = (struct t_details *)a, *task_b = (struct t_details *)b;
    int priority_a = ZERO, priority_b = ZERO;

    if (strcmp(task_a->priority, "High") == ZERO)
    {
        priority_a = 3;
    }
    else if (strcmp(task_a->priority, "Medium") == ZERO)
    {
        priority_a = 2;
    }
    else if (strcmp(task_a->priority, "Low") == ZERO)
    {
        priority_a = 1;
    }

    if (strcmp(task_b->priority, "High") == ZERO)
    {
        priority_b = 3;
    }
    else if (strcmp(task_b->priority, "Medium") == ZERO)
    {
        priority_b = 2;
    }
    else if (strcmp(task_b->priority, "Low") == ZERO)
    {
        priority_b = 1;
    }

    return priority_b - priority_a;
}