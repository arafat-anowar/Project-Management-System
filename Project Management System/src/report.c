#include "report.h"
#include "task.h"
#include "project.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>

int project_summary_report()
{
    // declare all variables
    struct p_details project;
    char path[MAX_PATH_LENGTH], row[MAX_LENGTH_OF_DATA_IN_FILE], *field;
    int total_projects = ZERO, created_projects = ZERO, in_progress_projects = ZERO, completed_projects = ZERO,cancelled_projects = ZERO, terminal_width, terminal_height, box_width = CONTAINER_WIDTH, box_height = 19,x,y;
    FILE *projectDBS_open;

    // get project database path
    get_path(path);
    strcat(path, PROJECT_DATABASE_FILE);

    // open database
    projectDBS_open = fopen(path, FILE_MODE_READ);
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

        total_projects++;

        if (strcmp(project.status, DEFAULT_PROJECT_STATUS) == ZERO)
        {
            created_projects++;
        }
        else if (strcmp(project.status, IN_PROGRESS_PROJECT_STATUS) == ZERO)
        {
            in_progress_projects++;
        }
        else if (strcmp(project.status, COMPLETED_PROJECT_STATUS) == ZERO)
        {
            completed_projects++;
        }
        else if (strcmp(project.status, CANCELLED_PROJECT_STATUS) == ZERO)
        {
            cancelled_projects++;
        }
    }

    // close database
    if (fclose(projectDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);

    }

    // set terminal to UTF8
    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    project_summary_report_screen(x, y);

    // print task details
    move_cursor(x + 30, y + 4);
    printf("%d", total_projects);

    move_cursor(x + 30, y + 6);
    printf("%d", created_projects);

    move_cursor(x + 30, y + 8);
    printf("%d", in_progress_projects);

    move_cursor(x + 30, y + 10);
    printf("%d", completed_projects);

    move_cursor(x + 30, y + 12);
    printf("%d", cancelled_projects);

    move_cursor(x + 45, y + 15);
    get_input;

    return 0;
}

int project_progress_report()
{
    // declare all variables
    struct p_details project;
    struct t_details task;
    char project_path[MAX_PATH_LENGTH],task_path[TASK_PATH_BUFFER_SIZE],project_row[MAX_LENGTH_OF_DATA_IN_FILE],task_row[TASK_FILE_DATA_SIZE],*field;
    int project_found = ZERO,total_tasks = ZERO, completed_tasks = ZERO, progress = ZERO, terminal_width, terminal_height, box_width = CONTAINER_WIDTH, box_height = 16, x, y;
    FILE *projectDBS_open,*taskDBS_open;

    // get project database path
    get_path(project_path);
    strcat(project_path, PROJECT_DATABASE_FILE);

    // open database
    projectDBS_open = fopen(project_path, FILE_MODE_READ);
    if (projectDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
        return 0;
    }

    // read database
    while (fgets(project_row, sizeof(project_row), projectDBS_open) != NULL)
    {
        project_row[strcspn(project_row, "\n")] = '\0';

        // tokenize data
        field = strtok(project_row, ",");
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

        project_found = 1;
        break;
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

    // get task database path
    get_path(task_path);
    strcat(task_path, PROJECT_FOLDER_NAME);
    strcat(task_path, "\\");
    strcat(task_path, strlwr(project.name));
    strcat(task_path, TASK_FILE_EXTENSION);

    // open database
    taskDBS_open = fopen(task_path, FILE_MODE_READ);
    if (taskDBS_open == NULL)
    {
        something_went_wrong_screen(FILE_OPEN_ERROR);
        return 0;
    }

    // read database
    while (fgets(task_row, sizeof(task_row), taskDBS_open) != NULL)
    {
        task_row[strcspn(task_row, "\n")] = '\0';

        // tokenize data
        field = strtok(task_row, ",");
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
            total_tasks++;

            if (strcmp(task.status, COMPLETED_TASK_STATUS) == ZERO)
            {
                completed_tasks++;
            }
        }
    }

    // close database
    if (fclose(taskDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);
    }

    if (total_tasks != ZERO)
    {
        progress = (completed_tasks * 100) / total_tasks;
    }

    init_console();
    header_screen();

    // measure terminal height and width also x and y coordinate
    terminal_width = get_console_width();
    terminal_height = get_console_height();
    x = (terminal_width - box_width) / TWO;
    y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

    project_progress_report_screen(x, y);

    // print task details
    move_cursor(x + 24, y + 4);
    printf("%s", project.id);

    move_cursor(x + 24, y + 6);
    printf("%s", project.name);

    move_cursor(x + 24, y + 8);
    printf("%d", total_tasks);

    move_cursor(x + 24, y + 10);
    printf("%d", completed_tasks);

    move_cursor(x + 24, y + 12);
    printf("%d%%", progress);

    move_cursor(x + 45, y + 13);
    get_input;

    return 0;
}

int overdue_projects_report()
{
    // declare all variables
    struct p_details project;
    char path[MAX_PATH_LENGTH], row[MAX_LENGTH_OF_DATA_IN_FILE], *field,today[PROJECT_END_DATE_SIZE];
    int terminal_width,terminal_height,box_width = CONTAINER_WIDTH,box_height = 17,x,y;
    FILE *projectDBS_open;

    // get current date
    current_date(today);

    // get project database path
    get_path(path);
    strcat(path, PROJECT_DATABASE_FILE);

    // open database
    projectDBS_open = fopen(path, FILE_MODE_READ);
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

        if (strcmp(project.end_date, today) < ZERO &&strcmp(project.status, COMPLETED_PROJECT_STATUS) != ZERO &&strcmp(project.status, CANCELLED_PROJECT_STATUS) != ZERO)
        {
            // set terminal utf8
            init_console();
            header_screen();

            // measure terminal height and width also x and y coordinate
            terminal_width = get_console_width();
            terminal_height = get_console_height();
            x = (terminal_width - box_width) / TWO;
            y = ((terminal_height - box_height) / TWO) + SCREEN_START_Y;

            overdue_projects_report_screen(x, y);

            // print task details
            move_cursor(x + 24, y + 4);
            printf("%s", project.id);

            move_cursor(x + 24, y + 6);
            printf("%s", project.name);

            move_cursor(x + 24, y + 8);
            printf("%s", project.priority);

            move_cursor(x + 24, y + 10);
            printf("%s", project.status);

            move_cursor(x + 24, y + 12);
            printf("%s", project.end_date);

            move_cursor(x + 45, y + 13);
            get_input;
        }
    }

    // close database
    if (fclose(projectDBS_open) == EOF)
    {
        something_went_wrong_screen(FILE_CLOSE_ERROR);

    }

    return 0;
}