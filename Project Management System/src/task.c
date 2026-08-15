#include "task.h"

int unique_task_id_generator()
{
    struct t_details task;
    int found = ZERO, id = UNIQUE_TASK_ID_INITIAL;
    char path[PATH_BUFFER_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    FILE *taskDBS_open;

    get_path(path);
    strcat(path, TASK_DBS);

    taskDBS_open = fopen(path, READ_MODE);

    while (fgets(row, sizeof(row), taskDBS_open) != NULL)
    {
        found = 1;

        row[strcspn(row, "\n")] = '\0';

        field = strtok(row, ",");
        task.unique_id = atoi(field);
    }

    fclose(taskDBS_open);

    if (found == ZERO)
    {
        return id;
    }

    return task.unique_id + 1;
}

int generate_task_id(char id[], char path[])
{
    struct t_details task;
    int found = ZERO, num_id[15] = {ZERO}, task_id = ZERO, id_len = ZERO, i = ZERO, j = ZERO, digit = ZERO, tmp = ZERO;
    char row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    FILE *taskDBS_open;

    strcpy(id, TASK_ID_INITIAL);

    taskDBS_open = fopen(path, READ_MODE);

    while (fgets(row, sizeof(row), taskDBS_open) != NULL)
    {
        found = 1;

        row[strcspn(row, "\n")] = '\0';

        field = strtok(row, ",");
        strcpy(task.task_id, field);
    }

    fclose(taskDBS_open);

    if (found == ZERO)
    {
        return 0;
    }

    strcpy(id, task.task_id);

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

        task_id += digit;
    }

    task_id++;

    tmp = task_id;
    j = id_len - 1;

    while (tmp != 0)
    {
        id[j] = (tmp % 10) + '0';

        tmp /= 10;
        j--;
    }

    return 0;
}

int create_task()
{
    struct t_details task;
    struct p_details project;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = BOX_WIDTH, box_height = TASK_BOX_HEIGHT, x = ZERO, y = ZERO, priority_box_width = PRIORITY_BOX_WIDTH, priority_box_height = PRIORITY_BOX_HEIGHT, priority_x = ZERO, priority_y = ZERO, status_box_width = STATUS_BOX_WIDTH, status_box_height = STATUS_BOX_HEIGHT, status_x = ZERO, status_y = ZERO, project_found = ZERO, is_start_date_valid = ZERO, is_end_date_valid = ZERO;
    char project_id_or_name[PROJECT_ID_OR_NAME_SIZE], projectDBS_path[PATH_BUFFER_SIZE], project_task_path[PATH_BUFFER_SIZE], taskDBS_path[PATH_BUFFER_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field, *username;
    FILE *projectDBS_open, *taskDBS_open, *project_task_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

    priority_x = (terminal_width - priority_box_width) / TWO;
    priority_y = (terminal_height - priority_box_height) / TWO;

    status_x = (terminal_width - status_box_width) / TWO;
    status_y = (terminal_height - status_box_height) / TWO;

    username = get_user_name();

    search_project_by_id_or_name_screen(x, y);

    move_cursor(x + PROJECT_INPUT_X, y + 5);
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DBS);

    projectDBS_open = fopen(projectDBS_path, READ_MODE);

    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

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

    fclose(projectDBS_open);

    get_path(project_task_path);
    strcat(project_task_path, PROJECT_FOLDER);
    strcat(project_task_path, "\\");
    strcat(project_task_path, strlwr(project.name));
    strcat(project_task_path, PROJECT_FILE_EXTENSION);

    task.unique_id = unique_task_id_generator();

    generate_task_id(task.task_id, project_task_path);

    strcpy(task.project_id, project.id);

    clear_screen();
    header_screen();

    create_task_screen(x, y);

    move_cursor(x + TASK_INPUT_X, y + 6);
    fgets(task.name, sizeof(task.name), stdin);
    task.name[strcspn(task.name, "\n")] = '\0';

    move_cursor(x + TASK_INPUT_X, y + 11);
    fgets(task.description, sizeof(task.description), stdin);
    task.description[strcspn(task.description, "\n")] = '\0';

    task_priority_dashboard(task.priority, priority_x, priority_y);

    clear_screen();
    header_screen();

    create_task_screen(x, y);

    move_cursor(x + TASK_INPUT_X, y + 6);
    printf("%s", task.name);

    move_cursor(x + TASK_INPUT_X, y + 11);
    printf("%s", task.description);

    move_cursor(x + TASK_INPUT_X, y + 18);
    printf("%s", task.priority);

    strcpy(task.status, DEFAULT_STATUS);

    do
    {
        move_cursor(x + TASK_INPUT_X, y + 23);
        if (is_start_date_valid == ZERO)
        {
            printf("                                                                             ");
            move_cursor(x + TASK_INPUT_X, y + 23);
        }

        fgets(task.start_date, sizeof(task.start_date), stdin);
        task.start_date[strcspn(task.start_date, "\n")] = '\0';
        is_start_date_valid = validate_date(task.start_date);

    } while (is_start_date_valid != VALID);

    do
    {
        move_cursor(x + TASK_INPUT_X, y + 28);
        if (is_end_date_valid == ZERO)
        {
            printf("                                                                             ");
            move_cursor(x + TASK_INPUT_X, y + 28);
        }

        fgets(task.end_date, sizeof(task.end_date), stdin);
        task.end_date[strcspn(task.end_date, "\n")] = '\0';
        is_end_date_valid = validate_date(task.end_date);

    } while (is_end_date_valid != VALID);

    strcpy(task.created_by, username);

    get_path(taskDBS_path);

    strcat(taskDBS_path, TASK_DBS);

    taskDBS_open = fopen(taskDBS_path, APPEND_MODE);

    fprintf(taskDBS_open, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.unique_id, task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);

    fclose(taskDBS_open);

    project_task_open = fopen(project_task_path, APPEND_MODE);

    fprintf(project_task_open, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);

    fclose(project_task_open);

    free(username);

    return 0;
}

int view_tasks()
{
    struct t_details task;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = BOX_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO;
    char path[PATH_BUFFER_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    FILE *taskDBS_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

    get_path(path);
    strcat(path, TASK_DBS);

    taskDBS_open = fopen(path, READ_MODE);

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

        clear_screen();
        header_screen();

        task_details_screen(x, y);

        move_cursor(x + 10, y + 5);
        printf("%d", task.unique_id);

        move_cursor(x + 10, y + 10);
        printf("%s", task.task_id);

        move_cursor(x + 10, y + 15);
        printf("%s", task.project_id);

        move_cursor(x + 10, y + 20);
        printf("%s", task.name);

        move_cursor(x + 10, y + 25);
        printf("%s", task.description);

        move_cursor(x + 10, y + 32);
        printf("%s", task.priority);

        move_cursor(x + 10, y + 37);
        printf("%s", task.status);

        move_cursor(x + 10, y + 42);
        printf("%s", task.start_date);

        move_cursor(x + 10, y + 47);
        printf("%s", task.end_date);

        get_input;
    }

    fclose(taskDBS_open);

    return 0;
}

int update_task()
{
    struct t_details task;
    struct p_details project;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = BOX_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO, project_found = ZERO, task_found = ZERO;
    char project_id_or_name[PROJECT_ID_OR_NAME_SIZE], task_id_or_name[TASK_ID_OR_NAME_SIZE], projectDBS_path[PATH_BUFFER_SIZE], taskDBS_path[PATH_BUFFER_SIZE], tmp_task_path[PATH_BUFFER_SIZE], project_task_path[PATH_BUFFER_SIZE], tmp_project_task_path[PATH_BUFFER_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    FILE *projectDBS_open, *taskDBS_open, *tmp_task, *project_task_open, *tmp_project_task;

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
    strcat(projectDBS_path, PROJECT_DBS);

    projectDBS_open = fopen(projectDBS_path, READ_MODE);

    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

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

    fclose(projectDBS_open);

    search_task_by_id_or_name_screen(x, y);

    move_cursor(x + TASK_INPUT_X, y + TASK_SEARCH_INPUT_Y);
    fgets(task_id_or_name, sizeof(task_id_or_name), stdin);
    task_id_or_name[strcspn(task_id_or_name, "\n")] = '\0';

    get_path(taskDBS_path);
    strcat(taskDBS_path, TASK_DBS);

    get_path(tmp_task_path);
    strcat(tmp_task_path, TMP_TASK_DBS);

    taskDBS_open = fopen(taskDBS_path, READ_MODE);
    tmp_task = fopen(tmp_task_path, WRITE_MODE);

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

        if ((strcmp(task.task_id, task_id_or_name) == ZERO || strcmp(task.name, task_id_or_name) == ZERO) && strcmp(task.project_id, project.id) == ZERO)
        {
            task_found = 1;
            task_update_dashboard(&task, x, y);
        }
        fprintf(tmp_task, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.unique_id, task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
    }

    fclose(taskDBS_open);
    fclose(tmp_task);

    remove(taskDBS_path);

    rename(tmp_task_path, taskDBS_path);

    get_path(project_task_path);
    strcat(project_task_path, PROJECT_FOLDER);
    strcat(project_task_path, "\\");
    strcat(project_task_path, strlwr(project.name));
    strcat(project_task_path, PROJECT_FILE_EXTENSION);

    get_path(tmp_project_task_path);
    strcat(tmp_project_task_path, PROJECT_FOLDER);
    strcat(tmp_project_task_path, "\\");
    strcat(tmp_project_task_path, TEMP_TASK_FILE);

    taskDBS_open = fopen(taskDBS_path, READ_MODE);

    tmp_project_task = fopen(tmp_project_task_path, WRITE_MODE);

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

        if (strcmp(task.project_id, project.id) == ZERO)
        {
            fprintf(tmp_project_task, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.task_id, project.id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
        }
    }

    fclose(project_task_open);
    fclose(tmp_project_task);

    remove(project_task_path);

    rename(tmp_project_task_path, project_task_path);

    return 0;
}

int delete_task()
{
    struct t_details task;
    struct p_details project;
    char project_id_or_name[PROJECT_ID_OR_NAME_SIZE], task_id_or_name[TASK_ID_OR_NAME_SIZE], projectDBS_path[PATH_BUFFER_SIZE], taskDBS_path[PATH_BUFFER_SIZE], tmp_task_path[PATH_BUFFER_SIZE], project_task_path[PATH_BUFFER_SIZE], tmp_project_task_path[PATH_BUFFER_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int project_found = ZERO, task_found = ZERO, x = ZERO, y = ZERO, terminal_width = ZERO, terminal_height = ZERO, box_width = ZERO, box_height = ZERO;
    FILE *projectDBS_open, *taskDBS_open, *tmp_task, *project_task_open, *tmp_project_task;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

    search_project_by_id_or_name_screen(x, y);
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DBS);

    projectDBS_open = fopen(projectDBS_path, READ_MODE);

    while (fgets(row, sizeof(row), projectDBS_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

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

    fclose(projectDBS_open);

    get_path(project_task_path);
    strcat(project_task_path, PROJECT_FOLDER);
    strcat(project_task_path, "\\");
    strcat(project_task_path, strlwr(project.name));
    strcat(project_task_path, PROJECT_FILE_EXTENSION);

    search_task_by_id_or_name_screen(x, y);

    move_cursor(x + TASK_INPUT_X, y + TASK_SEARCH_INPUT_Y);
    fgets(task_id_or_name, sizeof(task_id_or_name), stdin);
    task_id_or_name[strcspn(task_id_or_name, "\n")] = '\0';

    get_path(tmp_project_task_path);
    strcat(tmp_project_task_path, PROJECT_FOLDER);
    strcat(tmp_project_task_path, "\\");
    strcat(tmp_project_task_path, TEMP_TASK_FILE);

    project_task_open = fopen(project_task_path, READ_MODE);

    tmp_project_task = fopen(tmp_project_task_path, WRITE_MODE);

    while (fgets(row, sizeof(row), project_task_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

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

        if (strcmp(task.task_id, task_id_or_name) == ZERO || strcmp(task.name, task_id_or_name) == ZERO)
        {
            strcpy(task.status, DELETE_STATUS);
            task_found = 1;
        }

        fprintf(tmp_project_task, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
    }

    fclose(project_task_open);
    fclose(tmp_project_task);

    remove(project_task_path);
    rename(tmp_project_task_path, project_task_path);

    get_path(taskDBS_path);
    strcat(taskDBS_path, TASK_DBS);

    get_path(tmp_task_path);
    strcat(tmp_task_path, TMP_TASK_DBS);

    taskDBS_open = fopen(taskDBS_path, READ_MODE);

    tmp_task = fopen(tmp_task_path, WRITE_MODE);

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

        if ((strcmp(task.task_id, task_id_or_name) == ZERO || strcmp(task.name, task_id_or_name) == ZERO))
        {
            strcpy(task.status, DELETE_STATUS);
        }

        fprintf(tmp_task, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", task.unique_id, task.task_id, task.project_id, task.name, task.description, task.priority, task.status, task.start_date, task.end_date, task.created_by);
    }

    fclose(taskDBS_open);
    fclose(tmp_task);

    remove(taskDBS_path);
    rename(tmp_task_path, taskDBS_path);

    return 0;
}

int view_tasks_by_project()
{
    struct p_details project;
    struct t_details task;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = BOX_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO, project_found = ZERO;
    char project_id_or_name[PROJECT_ID_OR_NAME_SIZE], projectDBS_path[PATH_BUFFER_SIZE], project_task_path[PATH_BUFFER_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    FILE *projectDBS_open, *project_task_open;

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
    strcat(projectDBS_path, PROJECT_DBS);

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

        if (strcmp(project_id_or_name, project.id) == ZERO || strcmp(project_id_or_name, project.name) == ZERO)
        {
            project_found = 1;
            break;
        }
    }

    fclose(projectDBS_open);

    get_path(project_task_path);
    strcat(project_task_path, PROJECT_FOLDER);
    strcat(project_task_path, "\\");
    strcat(project_task_path, strlwr(project.name));
    strcat(project_task_path, PROJECT_FILE_EXTENSION);

    project_task_open = fopen(project_task_path, READ_MODE);

    while (fgets(row, sizeof(row), project_task_open) != NULL)
    {
        row[strcspn(row, "\n")] = '\0';

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

        move_cursor(x + 10, y + 6);
        printf("%s", task.task_id);

        move_cursor(x + 10, y + 11);
        printf("%s", task.project_id);

        move_cursor(x + 10, y + 16);
        printf("%s", task.name);

        move_cursor(x + 10, y + 21);
        printf("%s", task.description);

        move_cursor(x + 10, y + 28);
        printf("%s", task.priority);

        move_cursor(x + 10, y + 33);
        printf("%s", task.status);

        move_cursor(x + 10, y + 38);
        printf("%s", task.start_date);

        move_cursor(x + 10, y + 43);
        printf("%s", task.end_date);

        get_input;
    }

    fclose(project_task_open);

    return 0;
}

int change_task_name(char name[])
{
    char updated_name[TASK_NAME_SIZE];
    int terminal_width = ZERO, terminal_height = ZERO, box_width = BOX_WIDTH, box_height = PROJECT_INPUT_BOX_HEIGHT, x = ZERO, y = ZERO;

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

    change_task_name_screen(x, y);

    move_cursor(x + 10, y + 6);
    fgets(updated_name, sizeof(updated_name), stdin);
    updated_name[strcspn(updated_name, "\n")] = '\0';
    strcpy(name, updated_name);

    return 0;
}

int change_task_description(char description[])
{
    char updated_description[DESCRIPTION_SIZE];
    int terminal_width = ZERO, terminal_height = ZERO, box_width = BOX_WIDTH, box_height = PROJECT_INPUT_BOX_HEIGHT, x = ZERO, y = ZERO;

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

    change_task_description_screen(x, y);

    move_cursor(x + 10, y + 6);
    fgets(updated_description, sizeof(updated_description), stdin);
    updated_description[strcspn(updated_description, "\n")] = '\0';
    strcpy(description, updated_description);

    return 0;
}

int change_task_status(char status[])
{
    int terminal_width, terminal_height, x, y;

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - TASK_STATUS_BOX_WIDTH) / TWO;
    y = (terminal_height - TASK_STATUS_BOX_HEIGHT) / TWO;

    task_status_dashboard(status, x, y);

    return 0;
}

int change_task_priority(char priority[])
{
    int terminal_width, terminal_height, x, y;

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - TASK_PRIORITY_BOX_WIDTH) / TWO;
    y = (terminal_height - TASK_PRIORITY_BOX_HEIGHT) / TWO;

    task_priority_dashboard(priority, x, y);

    return 0;
}

int change_task_start_date(char start_date[])
{
    char updated_start_date[STARTDATE_SIZE];
    int is_valid = INVALID, terminal_width = ZERO, terminal_height = ZERO, box_width = BOX_WIDTH, box_height = PROJECT_INPUT_BOX_HEIGHT, x = ZERO, y = ZERO;

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

    do
    {
        change_task_start_date_screen(x, y);

        move_cursor(x + 10, y + 6);
        fgets(updated_start_date, sizeof(updated_start_date), stdin);
        updated_start_date[strcspn(updated_start_date, "\n")] = '\0';
        is_valid = validate_date(updated_start_date);

    } while (is_valid != VALID);

    strcpy(start_date, updated_start_date);

    return 0;
}

int extend_task_deadline(char deadline[])
{
    char updated_deadline[EXTENDDATE_SIZE];
    int is_valid = INVALID, terminal_width = ZERO, terminal_height = ZERO, box_width = BOX_WIDTH, box_height = PROJECT_INPUT_BOX_HEIGHT, x = ZERO, y = ZERO;

    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

    do
    {
        extend_task_deadline_screen(x, y);

        move_cursor(x + 10, y + 6);
        fgets(updated_deadline, sizeof(updated_deadline), stdin);
        updated_deadline[strcspn(updated_deadline, "\n")] = '\0';
        is_valid = validate_date(updated_deadline);

    } while (is_valid != VALID);

    strcpy(deadline, updated_deadline);

    return 0;
}

int search_by_task_id_or_name()
{
    struct t_details task;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = BOX_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO;
    char task_id_or_name[TASK_ID_OR_NAME_SIZE], path[PATH_BUFFER_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    FILE *taskDBS_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;

    search_task_by_id_or_name_screen(x, y);

    move_cursor(x + TASK_INPUT_X, y + TASK_SEARCH_INPUT_Y);
    fgets(task_id_or_name, sizeof(task_id_or_name), stdin);
    task_id_or_name[strcspn(task_id_or_name, "\n")] = '\0';

    get_path(path);
    strcat(path, TASK_DBS);

    taskDBS_open = fopen(path, READ_MODE);

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

        if (strcmp(task.task_id, task_id_or_name) == ZERO || strcmp(task.name, task_id_or_name) == ZERO)
        {
            clear_screen();
            header_screen();

            task_details_screen(x, y);

            move_cursor(x + 10, y + 5);
            printf("%d", task.unique_id);

            move_cursor(x + 10, y + 10);
            printf("%s", task.task_id);

            move_cursor(x + 10, y + 15);
            printf("%s", task.project_id);

            move_cursor(x + 10, y + 28);
            printf("%s", task.name);

            move_cursor(x + 10, y + 25);
            printf("%s", task.description);

            move_cursor(x + 10, y + 32);
            printf("%s", task.priority);

            move_cursor(x + 10, y + 37);
            printf("%s", task.status);

            move_cursor(x + 10, y + 42);
            printf("%s", task.start_date);

            move_cursor(x + 10, y + 47);
            printf("%s", task.end_date);

            get_input;

            break;
        }
    }

    fclose(taskDBS_open);

    return 0;
}

int search_task_by_status()
{
    struct t_details task;
    int terminal_width = ZERO, terminal_height = ZERO, box_width = BOX_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO, status_box_width = STATUS_BOX_WIDTH, status_box_height = STATUS_BOX_HEIGHT, status_x = ZERO, status_y = ZERO;
    char status[STATUS_SIZE], path[PATH_BUFFER_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    FILE *taskDBS_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;
    status_x = (terminal_width - status_box_width) / TWO;
    status_y = (terminal_height - status_box_height) / TWO;

    task_status_dashboard(status, status_x, status_y);

    get_path(path);
    strcat(path, TASK_DBS);

    taskDBS_open = fopen(path, READ_MODE);

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

            move_cursor(x + 10, y + 5);
            printf("%d", task.unique_id);

            move_cursor(x + 10, y + 10);
            printf("%s", task.task_id);

            move_cursor(x + 10, y + 15);
            printf("%s", task.project_id);

            move_cursor(x + 10, y + 20);
            printf("%s", task.name);

            move_cursor(x + 10, y + 25);
            printf("%s", task.description);

            move_cursor(x + 10, y + 32);
            printf("%s", task.priority);

            move_cursor(x + 10, y + 37);
            printf("%s", task.status);

            move_cursor(x + 10, y + 42);
            printf("%s", task.start_date);

            move_cursor(x + 10, y + 47);
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
    int terminal_width = ZERO, terminal_height = ZERO, box_width = BOX_WIDTH, box_height = TASK_DETAILS_BOX_HEIGHT, x = ZERO, y = ZERO, priority_box_width = PRIORITY_BOX_WIDTH, priority_box_height = PRIORITY_BOX_HEIGHT, priority_x = ZERO, priority_y = ZERO;
    char priority[PRIORITY_SIZE], path[PATH_BUFFER_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    FILE *taskDBS_open;

    init_console();
    header_screen();

    terminal_width = get_console_width();
    terminal_height = get_console_height();

    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_OFFSET_Y;
    priority_x = (terminal_width - priority_box_width) / TWO;
    priority_y = (terminal_height - priority_box_height) / TWO;

    task_priority_dashboard(priority, priority_x, priority_y);

    get_path(path);
    strcat(path, TASK_DBS);

    taskDBS_open = fopen(path, READ_MODE);

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

            move_cursor(x + 10, y + 5);
            printf("%d", task.unique_id);

            move_cursor(x + 10, y + 10);
            printf("%s", task.task_id);

            move_cursor(x + 10, y + 15);
            printf("%s", task.project_id);

            move_cursor(x + 10, y + 20);
            printf("%s", task.name);

            move_cursor(x + 10, y + 25);
            printf("%s", task.description);

            move_cursor(x + 10, y + 32);
            printf("%s", task.priority);

            move_cursor(x + 10, y + 37);
            printf("%s", task.status);

            move_cursor(x + 10, y + 42);
            printf("%s", task.start_date);

            move_cursor(x + 10, y + 47);
            printf("%s", task.end_date);

            get_input;
        }
    }

    fclose(taskDBS_open);

    return 0;
}

int sort_tasks()
{
    struct t_details task[TASK_ARRAY_SIZE];
    char taskDBS_path[PATH_BUFFER_SIZE], sort_task_path[PATH_BUFFER_SIZE], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int task_count = ZERO, i;
    FILE *taskDBS_open, *sort_task_open;

    get_path(taskDBS_path);
    strcat(taskDBS_path, TASK_DBS);

    get_path(sort_task_path);
    strcat(sort_task_path, SORT_TASK_DBS);

    taskDBS_open = fopen(taskDBS_path, READ_MODE);

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

    sort_task_open = fopen(sort_task_path, WRITE_MODE);

    for (i = ZERO; i < task_count; i++)
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