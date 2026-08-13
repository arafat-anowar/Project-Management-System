#include "task.h"

int unique_task_id_generator()
{
    struct t_details task;
    int found = 0, id = 10001;
    char path[PATH_BUFFER_SIZE], line[MAX_LENGTH_OF_DATA_IN_FILE], *token;
    FILE *taskDBS_open;

    get_path(path);
    strcat(path, TASK_DBS);
    taskDBS_open = fopen(path, READ_MODE);

    if (taskDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    while (fgets(line, sizeof(line), taskDBS_open) != NULL)
    {
        found = 1;
        line[strcspn(line, "\n")] = '\0';

        token = strtok(line, ",");
        task.unique_id = atoi(token);
        token = strtok(NULL, ","); strcpy(task.task_id, token);
        token = strtok(NULL, ","); strcpy(task.project_id, token);
        token = strtok(NULL, ","); strcpy(task.name, token);
        token = strtok(NULL, ","); strcpy(task.description, token);
        token = strtok(NULL, ","); strcpy(task.priority, token);
        token = strtok(NULL, ","); strcpy(task.status, token);
        token = strtok(NULL, ","); strcpy(task.start_date, token);
        token = strtok(NULL, ","); strcpy(task.end_date, token);
        token = strtok(NULL, ","); strcpy(task.created_by, token);
    }

    fclose(taskDBS_open);

    if (found == 0)
        return id;

    return task.unique_id + 1;
}

int generate_task_id(char id[], char path[])
{
    int found = 0;
    struct t_details task;
    char line[MAX_LENGTH_OF_DATA_IN_FILE], *token;

    strcpy(id, TASK_ID_INITIAL);

    FILE *taskDBS_open = fopen(path, READ_MODE);

    if (taskDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    while (fgets(line, sizeof(line), taskDBS_open) != NULL)
    {
        found = 1;
        line[strcspn(line, "\n")] = '\0';

        token = strtok(line, ",");
        strcpy(task.task_id, token);
        token = strtok(NULL, ","); strcpy(task.project_id, token);
        token = strtok(NULL, ","); strcpy(task.name, token);
        token = strtok(NULL, ","); strcpy(task.description, token);
        token = strtok(NULL, ","); strcpy(task.priority, token);
        token = strtok(NULL, ","); strcpy(task.status, token);
        token = strtok(NULL, ","); strcpy(task.start_date, token);
        token = strtok(NULL, ","); strcpy(task.end_date, token);
        token = strtok(NULL, ","); strcpy(task.created_by, token);
    }

    fclose(taskDBS_open);

    if (found == 0)
        return 0;

    strcpy(id, task.task_id);

    {
        int num_id[15];
        int task_id = 0;
        int id_len = strlen(id);
        int i, j;

        for (i = 0, j = 1; j < id_len; i++, j++)
            num_id[i] = id[j] - '0';

        for (i = 0; i <= id_len - 2; i++)
        {
            int digit = num_id[i];

            for (j = i; j <= id_len - 3; j++)
                digit *= 10;

            task_id += digit;
        }

        task_id++;

        {
            int tmp = task_id;
            j = id_len - 1;

            while (tmp != 0)
            {
                id[j] = (tmp % 10) + '0';
                tmp /= 10;
                j--;
            }
        }
    }

    return 0;
}

int create_task()
{
    char project_id_or_name[50];
    char projectDBS_path[PATH_BUFFER_SIZE];
    char path[PATH_BUFFER_SIZE];
    char taskDBS_path[PATH_BUFFER_SIZE];
    struct t_details task;
    struct p_details project;

    printf("\nProject ID or Name : ");
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DBS);

    FILE *projectDBS_open = fopen(projectDBS_path, READ_MODE);

    if (projectDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    {
        char line[MAX_LENGTH_OF_DATA_IN_FILE];

        while (fgets(line, sizeof(line), projectDBS_open) != NULL)
        {
            char *token;
            line[strcspn(line, "\n")] = '\0';

            token = strtok(line, ",");
            strcpy(project.id, token);
            token = strtok(NULL, ","); strcpy(project.name, token);
            token = strtok(NULL, ","); strcpy(project.category, token);
            token = strtok(NULL, ","); strcpy(project.description, token);
            token = strtok(NULL, ","); strcpy(project.priority, token);
            token = strtok(NULL, ","); strcpy(project.status, token);
            token = strtok(NULL, ","); strcpy(project.start_date, token);
            token = strtok(NULL, ","); strcpy(project.end_date, token);
            token = strtok(NULL, ","); strcpy(project.created_by, token);

            if (strcmp(project_id_or_name, project.id) == 0 ||
                strcmp(project_id_or_name, project.name) == 0)
            {
                strcpy(project_id_or_name, project.name);
                break;
            }
        }
    }

    fclose(projectDBS_open);

    get_path(path);
    strcat(path, PROJECT_FOLDER);
    strcat(path, strlwr(project_id_or_name));
    strcat(path, PROJECT_FILE_EXTENSION);

    task.unique_id = unique_task_id_generator();
    generate_task_id(task.task_id, path);
    strcpy(task.project_id, project.id);

    printf("\nTask Name : ");
    fgets(task.name, sizeof(task.name), stdin);
    task.name[strcspn(task.name, "\n")] = '\0';

    printf("\nTask Description : ");
    fgets(task.description, sizeof(task.description), stdin);
    task.description[strcspn(task.description, "\n")] = '\0';

    printf("\nTask Priority : ");
    fgets(task.priority, sizeof(task.priority), stdin);
    task.priority[strcspn(task.priority, "\n")] = '\0';

    printf("\nTask Status : ");
    fgets(task.status, sizeof(task.status), stdin);
    task.status[strcspn(task.status, "\n")] = '\0';

    printf("\nTask Start Date : ");
    fgets(task.start_date, sizeof(task.start_date), stdin);
    task.start_date[strcspn(task.start_date, "\n")] = '\0';

    printf("\nTask End Date : ");
    fgets(task.end_date, sizeof(task.end_date), stdin);
    task.end_date[strcspn(task.end_date, "\n")] = '\0';

    // get_user_name(task.created_by);

    get_path(taskDBS_path);
    strcat(taskDBS_path, TASK_DBS);

    FILE *file_open_for_write_data = fopen(taskDBS_path, APPEND_MODE);

    if (file_open_for_write_data == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    fprintf(file_open_for_write_data, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            task.unique_id, task.task_id, task.project_id, task.name,
            task.description, task.priority, task.status, task.start_date,
            task.end_date, task.created_by);
    fclose(file_open_for_write_data);

    FILE *file_open_for_write_data_in_separate_file = fopen(path, APPEND_MODE);

    if (file_open_for_write_data_in_separate_file == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    fprintf(file_open_for_write_data_in_separate_file, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            task.task_id, task.project_id, task.name, task.description,
            task.priority, task.status, task.start_date, task.end_date,
            task.created_by);
    fclose(file_open_for_write_data_in_separate_file);

    return 0;
}

int view_tasks()
{
    struct t_details task;
    char path[PATH_BUFFER_SIZE], line[MAX_LENGTH_OF_DATA_IN_FILE];

    get_path(path);
    strcat(path, TASK_DBS);

    FILE *taskDBS_open = fopen(path, READ_MODE);

    if (taskDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    task_details_screen();

    while (fgets(line, sizeof(line), taskDBS_open) != NULL)
    {
        char *token;
        line[strcspn(line, "\n")] = '\0';

        token = strtok(line, ",");
        task.unique_id = atoi(token);
        token = strtok(NULL, ","); strcpy(task.task_id, token);
        token = strtok(NULL, ","); strcpy(task.project_id, token);
        token = strtok(NULL, ","); strcpy(task.name, token);
        token = strtok(NULL, ","); strcpy(task.description, token);
        token = strtok(NULL, ","); strcpy(task.priority, token);
        token = strtok(NULL, ","); strcpy(task.status, token);
        token = strtok(NULL, ","); strcpy(task.start_date, token);
        token = strtok(NULL, ","); strcpy(task.end_date, token);
        token = strtok(NULL, ","); strcpy(task.created_by, token);

        printf("\n\n");
        printf("Unique Task ID : %d\n", task.unique_id);
        printf("Project ID     : %s\n", task.project_id);
        printf("Task ID        : %s\n", task.task_id);
        printf("Task Name      : %s\n", task.name);
        printf("Description    : %s\n", task.description);
        printf("Priority       : %s\n", task.priority);
        printf("Status         : %s\n", task.status);
        printf("Start Date     : %s\n", task.start_date);
        printf("Deadline       : %s\n", task.end_date);

        Sleep(1000);
    }

    fclose(taskDBS_open);
    return 0;
}

int update_task()
{
    char project_id_or_name[50];
    char projectDBS_path[PATH_BUFFER_SIZE];
    char path[PATH_BUFFER_SIZE];
    char taskDBS_path[PATH_BUFFER_SIZE];
    char tmp_task_path[PATH_BUFFER_SIZE];

    printf("\nProject ID or Name : ");
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    struct t_details task;
    struct p_details project;

    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DBS);

    FILE *projectDBS_open = fopen(projectDBS_path, READ_MODE);

    if (projectDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    {
        char line[MAX_LENGTH_OF_DATA_IN_FILE];

        while (fgets(line, sizeof(line), projectDBS_open) != NULL)
        {
            char *token;
            line[strcspn(line, "\n")] = '\0';

            token = strtok(line, ",");
            strcpy(project.id, token);
            token = strtok(NULL, ","); strcpy(project.name, token);
            token = strtok(NULL, ","); strcpy(project.category, token);
            token = strtok(NULL, ","); strcpy(project.description, token);
            token = strtok(NULL, ","); strcpy(project.priority, token);
            token = strtok(NULL, ","); strcpy(project.status, token);
            token = strtok(NULL, ","); strcpy(project.start_date, token);
            token = strtok(NULL, ","); strcpy(project.end_date, token);
            token = strtok(NULL, ","); strcpy(project.created_by, token);

            if (strcmp(project_id_or_name, project.id) == 0 ||
                strcmp(project_id_or_name, project.name) == 0)
            {
                strcpy(project_id_or_name, project.name);
                break;
            }
        }
    }

    fclose(projectDBS_open);

    get_path(path);
    strcat(path, PROJECT_FOLDER);
    strcat(path, strlwr(project_id_or_name));
    strcat(path, PROJECT_FILE_EXTENSION);

    char task_id_or_name[50];

    printf("\nTask ID or Name : ");
    fgets(task_id_or_name, sizeof(task_id_or_name), stdin);
    task_id_or_name[strcspn(task_id_or_name, "\n")] = '\0';

    get_path(taskDBS_path);
    get_path(tmp_task_path);
    strcat(taskDBS_path, TASK_DBS);
    strcat(tmp_task_path, TMP_TASK_DBS);

    FILE *task_dbs_open = fopen(taskDBS_path, READ_MODE);
    FILE *tmp_task = fopen(tmp_task_path, WRITE_MODE);

    if (task_dbs_open == NULL || tmp_task == NULL)
    {
        if (task_dbs_open != NULL) fclose(task_dbs_open);
        if (tmp_task != NULL) fclose(tmp_task);
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    {
        char line[MAX_LENGTH_OF_DATA_IN_FILE];

        while (fgets(line, sizeof(line), task_dbs_open) != NULL)
        {
            char *token;
            line[strcspn(line, "\n")] = '\0';

            token = strtok(line, ",");
            task.unique_id = atoi(token);
            token = strtok(NULL, ","); strcpy(task.task_id, token);
            token = strtok(NULL, ","); strcpy(task.project_id, token);
            token = strtok(NULL, ","); strcpy(task.name, token);
            token = strtok(NULL, ","); strcpy(task.description, token);
            token = strtok(NULL, ","); strcpy(task.priority, token);
            token = strtok(NULL, ","); strcpy(task.status, token);
            token = strtok(NULL, ","); strcpy(task.start_date, token);
            token = strtok(NULL, ","); strcpy(task.end_date, token);
            token = strtok(NULL, ","); strcpy(task.created_by, token);

            if (strcmp(task.task_id, task_id_or_name) == 0 ||
                strcmp(task.name, task_id_or_name) == 0)
                task_update_dashboard(&task);

            fprintf(tmp_task, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
                    task.unique_id, task.task_id, task.project_id, task.name,
                    task.description, task.priority, task.status,
                    task.start_date, task.end_date, task.created_by);
        }
    }

    fclose(task_dbs_open);
    fclose(tmp_task);

    remove(taskDBS_path);
    rename(tmp_task_path, taskDBS_path);

    {
        char tmp_project_task_path[PATH_BUFFER_SIZE];

        get_path(tmp_project_task_path);
        strcat(tmp_project_task_path, PROJECT_FOLDER);
        strcat(tmp_project_task_path, TEMP_TASK_FILE);

        FILE *separate_project_dbs_open = fopen(taskDBS_path, READ_MODE);
        FILE *tmp_for_separate_project_file =
            fopen(tmp_project_task_path, WRITE_MODE);

        if (separate_project_dbs_open == NULL ||
            tmp_for_separate_project_file == NULL)
        {
            if (separate_project_dbs_open != NULL)
                fclose(separate_project_dbs_open);
            if (tmp_for_separate_project_file != NULL)
                fclose(tmp_for_separate_project_file);

            printf("Error: %s\n", strerror(errno));
            return 0;
        }

        {
            char line[MAX_LENGTH_OF_DATA_IN_FILE];

            while (fgets(line, sizeof(line), separate_project_dbs_open) != NULL)
            {
                char *token;
                line[strcspn(line, "\n")] = '\0';

                token = strtok(line, ",");
                task.unique_id = atoi(token);
                token = strtok(NULL, ","); strcpy(task.task_id, token);
                token = strtok(NULL, ","); strcpy(task.project_id, token);
                token = strtok(NULL, ","); strcpy(task.name, token);
                token = strtok(NULL, ","); strcpy(task.description, token);
                token = strtok(NULL, ","); strcpy(task.priority, token);
                token = strtok(NULL, ","); strcpy(task.status, token);
                token = strtok(NULL, ","); strcpy(task.start_date, token);
                token = strtok(NULL, ","); strcpy(task.end_date, token);
                token = strtok(NULL, ","); strcpy(task.created_by, token);

                fprintf(tmp_for_separate_project_file,
                        "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
                        task.task_id, task.project_id, task.name,
                        task.description, task.priority, task.status,
                        task.start_date, task.end_date, task.created_by);
            }
        }

        fclose(separate_project_dbs_open);
        fclose(tmp_for_separate_project_file);

        remove(path);
        rename(tmp_project_task_path, path);
    }

    return 0;
}

int delete_task()
{
    char project_id_or_name[50];
    char projectDBS_path[PATH_BUFFER_SIZE];
    char path[PATH_BUFFER_SIZE];
    char taskDBS_path[PATH_BUFFER_SIZE];
    char tmp_task_path[PATH_BUFFER_SIZE];

    printf("\nProject ID or Name : ");
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    struct t_details task;
    struct p_details project;

    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DBS);

    FILE *projectDBS_open = fopen(projectDBS_path, READ_MODE);

    if (projectDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    {
        char line[MAX_LENGTH_OF_DATA_IN_FILE];

        while (fgets(line, sizeof(line), projectDBS_open) != NULL)
        {
            char *token;
            line[strcspn(line, "\n")] = '\0';

            token = strtok(line, ",");
            strcpy(project.id, token);
            token = strtok(NULL, ","); strcpy(project.name, token);
            token = strtok(NULL, ","); strcpy(project.category, token);
            token = strtok(NULL, ","); strcpy(project.description, token);
            token = strtok(NULL, ","); strcpy(project.priority, token);
            token = strtok(NULL, ","); strcpy(project.status, token);
            token = strtok(NULL, ","); strcpy(project.start_date, token);
            token = strtok(NULL, ","); strcpy(project.end_date, token);
            token = strtok(NULL, ","); strcpy(project.created_by, token);

            if (strcmp(project_id_or_name, project.id) == 0 ||
                strcmp(project_id_or_name, project.name) == 0)
            {
                strcpy(project_id_or_name, project.name);
                break;
            }
        }
    }

    fclose(projectDBS_open);

    get_path(path);
    strcat(path, PROJECT_FOLDER);
    strcat(path, strlwr(project_id_or_name));
    strcat(path, PROJECT_FILE_EXTENSION);

    char task_id_or_name[50];

    printf("\nTask ID or Name : ");
    fgets(task_id_or_name, sizeof(task_id_or_name), stdin);
    task_id_or_name[strcspn(task_id_or_name, "\n")] = '\0';

    {
        char tmp_project_task_path[PATH_BUFFER_SIZE];

        get_path(tmp_project_task_path);
        strcat(tmp_project_task_path, PROJECT_FOLDER);
        strcat(tmp_project_task_path, TEMP_TASK_FILE);

        FILE *separate_project_dbs_open = fopen(path, READ_MODE);
        FILE *tmp_for_separate_project_file =
            fopen(tmp_project_task_path, WRITE_MODE);

        if (separate_project_dbs_open == NULL ||
            tmp_for_separate_project_file == NULL)
        {
            if (separate_project_dbs_open != NULL)
                fclose(separate_project_dbs_open);
            if (tmp_for_separate_project_file != NULL)
                fclose(tmp_for_separate_project_file);

            printf("Error: %s\n", strerror(errno));
            return 0;
        }

        {
            char line[MAX_LENGTH_OF_DATA_IN_FILE];

            while (fgets(line, sizeof(line), separate_project_dbs_open) != NULL)
            {
                char *token;
                line[strcspn(line, "\n")] = '\0';

                token = strtok(line, ",");
                strcpy(task.task_id, token);
                token = strtok(NULL, ","); strcpy(task.project_id, token);
                token = strtok(NULL, ","); strcpy(task.name, token);
                token = strtok(NULL, ","); strcpy(task.description, token);
                token = strtok(NULL, ","); strcpy(task.priority, token);
                token = strtok(NULL, ","); strcpy(task.status, token);
                token = strtok(NULL, ","); strcpy(task.start_date, token);
                token = strtok(NULL, ","); strcpy(task.end_date, token);
                token = strtok(NULL, ","); strcpy(task.created_by, token);

                if (strcmp(task.task_id, task_id_or_name) == 0 ||
                    strcmp(task.name, task_id_or_name) == 0)
                    strcpy(task.status, "Deleted");

                fprintf(tmp_for_separate_project_file,
                        "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
                        task.task_id, task.project_id, task.name,
                        task.description, task.priority, task.status,
                        task.start_date, task.end_date, task.created_by);
            }
        }

        fclose(separate_project_dbs_open);
        fclose(tmp_for_separate_project_file);

        remove(path);
        rename(tmp_project_task_path, path);
    }

    get_path(taskDBS_path);
    get_path(tmp_task_path);
    strcat(taskDBS_path, TASK_DBS);
    strcat(tmp_task_path, TMP_TASK_DBS);

    {
        FILE *task_dbs_open = fopen(taskDBS_path, READ_MODE);
        FILE *tmp_task = fopen(tmp_task_path, WRITE_MODE);

        if (task_dbs_open == NULL || tmp_task == NULL)
        {
            if (task_dbs_open != NULL) fclose(task_dbs_open);
            if (tmp_task != NULL) fclose(tmp_task);

            printf("Error: %s\n", strerror(errno));
            return 0;
        }

        {
            char line[MAX_LENGTH_OF_DATA_IN_FILE];

            while (fgets(line, sizeof(line), task_dbs_open) != NULL)
            {
                char *token;
                line[strcspn(line, "\n")] = '\0';

                token = strtok(line, ",");
                task.unique_id = atoi(token);
                token = strtok(NULL, ","); strcpy(task.task_id, token);
                token = strtok(NULL, ","); strcpy(task.project_id, token);
                token = strtok(NULL, ","); strcpy(task.name, token);
                token = strtok(NULL, ","); strcpy(task.description, token);
                token = strtok(NULL, ","); strcpy(task.priority, token);
                token = strtok(NULL, ","); strcpy(task.status, token);
                token = strtok(NULL, ","); strcpy(task.start_date, token);
                token = strtok(NULL, ","); strcpy(task.end_date, token);
                token = strtok(NULL, ","); strcpy(task.created_by, token);

                if (strcmp(task.task_id, task_id_or_name) == 0 ||
                    strcmp(task.name, task_id_or_name) == 0)
                    strcpy(task.status, "Deleted");

                fprintf(tmp_task, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
                        task.unique_id, task.task_id, task.project_id,
                        task.name, task.description, task.priority,
                        task.status, task.start_date, task.end_date,
                        task.created_by);
            }
        }

        fclose(task_dbs_open);
        fclose(tmp_task);

        remove(taskDBS_path);
        rename(tmp_task_path, taskDBS_path);
    }

    return 0;
}

int view_tasks_by_project()
{
    char project_id_or_name[50];
    char projectDBS_path[PATH_BUFFER_SIZE];
    char path[PATH_BUFFER_SIZE];

    printf("\nProject ID or Name : ");
    fgets(project_id_or_name, sizeof(project_id_or_name), stdin);
    project_id_or_name[strcspn(project_id_or_name, "\n")] = '\0';

    struct p_details project;

    get_path(projectDBS_path);
    strcat(projectDBS_path, PROJECT_DBS);

    FILE *projectDBS_open = fopen(projectDBS_path, READ_MODE);

    if (projectDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    {
        char line[MAX_LENGTH_OF_DATA_IN_FILE];

        while (fgets(line, sizeof(line), projectDBS_open) != NULL)
        {
            char *token;
            line[strcspn(line, "\n")] = '\0';

            token = strtok(line, ",");
            strcpy(project.id, token);
            token = strtok(NULL, ","); strcpy(project.name, token);
            token = strtok(NULL, ","); strcpy(project.category, token);
            token = strtok(NULL, ","); strcpy(project.description, token);
            token = strtok(NULL, ","); strcpy(project.priority, token);
            token = strtok(NULL, ","); strcpy(project.status, token);
            token = strtok(NULL, ","); strcpy(project.start_date, token);
            token = strtok(NULL, ","); strcpy(project.end_date, token);
            token = strtok(NULL, ","); strcpy(project.created_by, token);

            if (strcmp(project_id_or_name, project.id) == 0 ||
                strcmp(project_id_or_name, project.name) == 0)
            {
                strcpy(project_id_or_name, project.name);
                break;
            }
        }
    }

    fclose(projectDBS_open);

    get_path(path);
    strcat(path, PROJECT_FOLDER);
    strcat(path, strlwr(project_id_or_name));
    strcat(path, PROJECT_FILE_EXTENSION);

    struct t_details task;
    FILE *separate_project_dbs_open = fopen(path, READ_MODE);

    if (separate_project_dbs_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    task_details_screen();

    {
        char line[MAX_LENGTH_OF_DATA_IN_FILE];

        while (fgets(line, sizeof(line), separate_project_dbs_open) != NULL)
        {
            char *token;
            line[strcspn(line, "\n")] = '\0';

            token = strtok(line, ",");
            strcpy(task.task_id, token);
            token = strtok(NULL, ","); strcpy(task.project_id, token);
            token = strtok(NULL, ","); strcpy(task.name, token);
            token = strtok(NULL, ","); strcpy(task.description, token);
            token = strtok(NULL, ","); strcpy(task.priority, token);
            token = strtok(NULL, ","); strcpy(task.status, token);
            token = strtok(NULL, ","); strcpy(task.start_date, token);
            token = strtok(NULL, ","); strcpy(task.end_date, token);
            token = strtok(NULL, ","); strcpy(task.created_by, token);

            printf("\n\n");
            printf("Task ID     : %s\n", task.task_id);
            printf("Project ID  : %s\n", task.project_id);
            printf("Task Name   : %s\n", task.name);
            printf("Description : %s\n", task.description);
            printf("Priority    : %s\n", task.priority);
            printf("Status      : %s\n", task.status);
            printf("Start Date  : %s\n", task.start_date);
            printf("Deadline    : %s\n", task.end_date);

            Sleep(1000);
        }
    }

    fclose(separate_project_dbs_open);
    return 0;
}

int change_task_name(char name[])
{
    char updated_name[50];

    fgets(updated_name, sizeof(updated_name), stdin);
    updated_name[strcspn(updated_name, "\n")] = '\0';
    strcpy(name, updated_name);

    return 0;
}

int change_task_description(char description[])
{
    char updated_description[50];

    fgets(updated_description, sizeof(updated_description), stdin);
    updated_description[strcspn(updated_description, "\n")] = '\0';
    strcpy(description, updated_description);

    return 0;
}

int change_task_status(char status[])
{
    task_status_dashboard(status);
    return 0;
}

int change_task_priority(char priority[])
{
    task_priority_dashboard(priority);
    return 0;
}

int change_task_start_date(char start_date[])
{
    char updated_start_date[50];

    fgets(updated_start_date, sizeof(updated_start_date), stdin);
    updated_start_date[strcspn(updated_start_date, "\n")] = '\0';
    strcpy(start_date, updated_start_date);

    return 0;
}

int extend_task_deadline(char deadline[])
{
    char updated_deadline[50];

    fgets(updated_deadline, sizeof(updated_deadline), stdin);
    updated_deadline[strcspn(updated_deadline, "\n")] = '\0';
    strcpy(deadline, updated_deadline);

    return 0;
}

int search_by_task_id_or_name()
{
    char task_id_or_name[50];
    char path[PATH_BUFFER_SIZE];

    fgets(task_id_or_name, sizeof(task_id_or_name), stdin);
    task_id_or_name[strcspn(task_id_or_name, "\n")] = '\0';

    get_path(path);
    strcat(path, TASK_DBS);

    FILE *taskDBS_open = fopen(path, READ_MODE);
    struct t_details task;

    if (taskDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    {
        char line[MAX_LENGTH_OF_DATA_IN_FILE];

        while (fgets(line, sizeof(line), taskDBS_open) != NULL)
        {
            char *token;
            line[strcspn(line, "\n")] = '\0';

            token = strtok(line, ",");
            task.unique_id = atoi(token);
            token = strtok(NULL, ","); strcpy(task.task_id, token);
            token = strtok(NULL, ","); strcpy(task.project_id, token);
            token = strtok(NULL, ","); strcpy(task.name, token);
            token = strtok(NULL, ","); strcpy(task.description, token);
            token = strtok(NULL, ","); strcpy(task.priority, token);
            token = strtok(NULL, ","); strcpy(task.status, token);
            token = strtok(NULL, ","); strcpy(task.start_date, token);
            token = strtok(NULL, ","); strcpy(task.end_date, token);
            token = strtok(NULL, ","); strcpy(task.created_by, token);

            if ((task.unique_id == *(task_id_or_name)) ||
                strcmp(task.name, task_id_or_name) == 0)
            {
                task_details_screen();

                printf("\n\n");
                printf("Unique Task ID : %d\n", task.unique_id);
                printf("Project ID     : %s\n", task.project_id);
                printf("Task ID        : %s\n", task.task_id);
                printf("Task Name      : %s\n", task.name);
                printf("Description    : %s\n", task.description);
                printf("Priority       : %s\n", task.priority);
                printf("Status         : %s\n", task.status);
                printf("Start Date     : %s\n", task.start_date);
                printf("Deadline       : %s\n", task.end_date);
                break;
            }
        }
    }

    fclose(taskDBS_open);
    return 0;
}

int search_task_by_status()
{
    char status[30];
    char path[PATH_BUFFER_SIZE];

    task_status_dashboard(status);

    get_path(path);
    strcat(path, TASK_DBS);

    FILE *taskDBS_open = fopen(path, READ_MODE);
    struct t_details task;

    if (taskDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    task_details_screen();

    {
        char line[MAX_LENGTH_OF_DATA_IN_FILE];

        while (fgets(line, sizeof(line), taskDBS_open) != NULL)
        {
            char *token;
            line[strcspn(line, "\n")] = '\0';

            token = strtok(line, ",");
            task.unique_id = atoi(token);
            token = strtok(NULL, ","); strcpy(task.task_id, token);
            token = strtok(NULL, ","); strcpy(task.project_id, token);
            token = strtok(NULL, ","); strcpy(task.name, token);
            token = strtok(NULL, ","); strcpy(task.description, token);
            token = strtok(NULL, ","); strcpy(task.priority, token);
            token = strtok(NULL, ","); strcpy(task.status, token);
            token = strtok(NULL, ","); strcpy(task.start_date, token);
            token = strtok(NULL, ","); strcpy(task.end_date, token);
            token = strtok(NULL, ","); strcpy(task.created_by, token);

            if (strcmp(task.status, status) == 0)
            {
                printf("\n\n");
                printf("Task ID        : %s\n", task.task_id);
                printf("Project ID     : %s\n", task.project_id);
                printf("Task Name      : %s\n", task.name);
                printf("Description    : %s\n", task.description);
                printf("Priority       : %s\n", task.priority);
                printf("Status         : %s\n", task.status);
                printf("Start Date     : %s\n", task.start_date);
                printf("Deadline       : %s\n", task.end_date);
            }
        }
    }

    fclose(taskDBS_open);
    return 0;
}

int search_task_by_priority()
{
    char priority[30];
    char path[PATH_BUFFER_SIZE];

    task_priority_dashboard(priority);

    get_path(path);
    strcat(path, TASK_DBS);

    FILE *taskDBS_open = fopen(path, READ_MODE);
    struct t_details task;

    if (taskDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    task_details_screen();

    {
        char line[MAX_LENGTH_OF_DATA_IN_FILE];

        while (fgets(line, sizeof(line), taskDBS_open) != NULL)
        {
            char *token;
            line[strcspn(line, "\n")] = '\0';

            token = strtok(line, ",");
            task.unique_id = atoi(token);
            token = strtok(NULL, ","); strcpy(task.task_id, token);
            token = strtok(NULL, ","); strcpy(task.project_id, token);
            token = strtok(NULL, ","); strcpy(task.name, token);
            token = strtok(NULL, ","); strcpy(task.description, token);
            token = strtok(NULL, ","); strcpy(task.priority, token);
            token = strtok(NULL, ","); strcpy(task.status, token);
            token = strtok(NULL, ","); strcpy(task.start_date, token);
            token = strtok(NULL, ","); strcpy(task.end_date, token);
            token = strtok(NULL, ","); strcpy(task.created_by, token);

            if (strcmp(task.status, priority) == 0)
            {
                printf("\n\n");
                printf("Task ID        : %s\n", task.task_id);
                printf("Project ID     : %s\n", task.project_id);
                printf("Task Name      : %s\n", task.name);
                printf("Description    : %s\n", task.description);
                printf("Priority       : %s\n", task.priority);
                printf("Status         : %s\n", task.status);
                printf("Start Date     : %s\n", task.start_date);
                printf("Deadline       : %s\n", task.end_date);
            }
        }
    }

    fclose(taskDBS_open);
    return 0;
}

int sort_tasks()
{
    char taskDBS_path[PATH_BUFFER_SIZE];
    char sort_task_path[PATH_BUFFER_SIZE];

    get_path(taskDBS_path);
    get_path(sort_task_path);

    strcat(taskDBS_path, TASK_DBS);
    strcat(sort_task_path, SORT_TASK_DBS);

    FILE *taskDBS_open = fopen(taskDBS_path, READ_MODE);

    if (taskDBS_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    struct t_details task[MAX];
    char line[MAX_LENGTH_OF_DATA_IN_FILE];
    int i = 0;

    while (fgets(line, sizeof(line), taskDBS_open) != NULL)
    {
        char *token;
        line[strcspn(line, "\n")] = '\0';

        token = strtok(line, ",");
        task[i].unique_id = atoi(token);
        token = strtok(NULL, ","); strcpy(task[i].task_id, token);
        token = strtok(NULL, ","); strcpy(task[i].project_id, token);
        token = strtok(NULL, ","); strcpy(task[i].name, token);
        token = strtok(NULL, ","); strcpy(task[i].description, token);
        token = strtok(NULL, ","); strcpy(task[i].priority, token);
        token = strtok(NULL, ","); strcpy(task[i].status, token);
        token = strtok(NULL, ","); strcpy(task[i].start_date, token);
        token = strtok(NULL, ","); strcpy(task[i].end_date, token);
        token = strtok(NULL, ","); strcpy(task[i].created_by, token);

        i++;
    }

    fclose(taskDBS_open);

    qsort(task, i, sizeof(struct t_details), sort_by_priority);

    FILE *sort_task_open = fopen(sort_task_path, WRITE_MODE);

    if (sort_task_open == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }

    for (int j = 0; j < i; j++)
    {
        fprintf(sort_task_open,
                "%d,%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
                j + 1, task[j].unique_id, task[j].task_id,
                task[j].project_id, task[j].name, task[j].description,
                task[j].priority, task[j].status, task[j].start_date,
                task[j].end_date, task[j].created_by);
    }

    fclose(sort_task_open);
    return 0;
}

int sort_by_priority(const void *a, const void *b)
{
    struct t_details *task_a = (struct t_details *)a;
    struct t_details *task_b = (struct t_details *)b;

    int priority_of_a;
    int priority_of_b;

    if (strcmp(task_a->priority, "High") == 0)
        priority_of_a = 3;
    else if (strcmp(task_a->priority, "Medium") == 0)
        priority_of_a = 2;
    else
        priority_of_a = 1;

    if (strcmp(task_b->priority, "High") == 0)
        priority_of_b = 3;
    else if (strcmp(task_b->priority, "Medium") == 0)
        priority_of_b = 2;
    else
        priority_of_b = 1;

    if (priority_of_b != priority_of_a)
        return priority_of_b - priority_of_a;

    return strcmp(task_a->end_date, task_b->end_date);
}
