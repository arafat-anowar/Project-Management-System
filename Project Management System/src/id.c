#include "id.h"

int generate_user_id(char id[])
{
    strcpy(id,"U1001");
    int found = 0;
    FILE *file_open_for_read_details = fopen("database\\userDBS.csv", "r");
    char line[210];
    struct r_account details;
    while (fgets(line, sizeof(line), file_open_for_read_details) != NULL)
    {

        found = 1;
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, ",");
        strcpy(details.user_id,token);
        token = strtok(NULL, ",");
        strcpy(details.name,token);
        token = strtok(NULL, ",");
        strcpy(details.email,token);
        token = strtok(NULL, ",");
        strcpy(details.phone,token);
        token = strtok(NULL, ",");
        strcpy(details.user_name,token);
        token = strtok(NULL, ",");
        strcpy(details.user_pass,token);
        token = strtok(NULL, ",");
        strcpy(details.security_question,token);
        token = strtok(NULL, ",");
        strcpy(details.user_role,token);
    }
    fclose(file_open_for_read_details);
    if (found == 0)
    {
        return 0;
    }
    else
    {
        strcpy(id,details.user_id);
        int num_id[20];
        for (int i = 0, j = 1; id[j] != '\0'; i++, j++)
        {
            num_id[i] = (id[j] - '0');
        }
        
        int usr_id = 0,id_len=strlen(id);
        for (int i = 0; i <= id_len-2; i++)
        {
            int digit = num_id[i];
            for (int j = i; j <= id_len-3; j++)
            {
                digit *= 10;
            }
            usr_id += digit;
        }
        int tmp=++usr_id;
        for (int i = 0,j=id_len-1; tmp!=0; i++,j--)
        {
            id[j]=((tmp%10)+'0');
            tmp=tmp/10;
        }
        return 0;
    }
}
int generate_project_id()
{
    return 0;
}
int generate_task_id()
{
    return 0;
}