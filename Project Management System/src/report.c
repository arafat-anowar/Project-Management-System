// #include "report.h"

// #include <string.h>
// #include <stdlib.h>
// #include <time.h>

// int completes_tasks()
// {
//     struct task_details task;

//     FILE *taskDBS_open = fopen("..\\database\\taskDBS.csv", "r");
//     if (taskDBS_open == NULL)
//     {
//         printf("\nNo tasks found.\n");
//         return 0;
//     }

//     char line[MAX_LENGTH_OF_DATA_IN_FILE];
//     int count = 0;

//     task_details_screen();
//     printf("\n--- Completed Tasks ---\n");

//     while (fgets(line, sizeof(line), taskDBS_open) != NULL)
//     {
//         line[strcspn(line, "\n")] = '\0';

//         char *token;

//         token = strtok(line, ",");
//         task.unique_id = atoi(token);

//         token = strtok(NULL, ",");
//         strcpy(task.task_id, token);

//         token = strtok(NULL, ",");
//         strcpy(task.project_id, token);

//         token = strtok(NULL, ",");
//         strcpy(task.name, token);

//         token = strtok(NULL, ",");
//         strcpy(task.description, token);

//         token = strtok(NULL, ",");
//         strcpy(task.priority, token);

//         token = strtok(NULL, ",");
//         strcpy(task.status, token);

//         token = strtok(NULL, ",");
//         strcpy(task.start_date, token);

//         token = strtok(NULL, ",");
//         strcpy(task.end_date, token);

//         token = strtok(NULL, ",");
//         strcpy(task.created_by, token);

//         if (strcmp(task.status, "Completed") == 0)
//         {
//             printf("\nTask ID     : %s\n", task.task_id);
//             printf("Project ID  : %s\n", task.project_id);
//             printf("Name        : %s\n", task.name);
//             printf("Deadline    : %s\n", task.end_date);
//             count++;
//         }
//     }
//     fclose(taskDBS_open);

//     printf("\nTotal Completed Tasks : %d\n", count);
//     return 0;
// }

