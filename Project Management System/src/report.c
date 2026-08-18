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