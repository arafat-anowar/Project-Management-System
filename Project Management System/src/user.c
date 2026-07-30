#include "user.h"

int create_user()
{
    struct user details;
    generate_user_id(details.id);

    printf("Enter your First Name : ");
    fgets(details.name_1st, sizeof(details.name_1st), stdin);
    details.name_1st[strcspn(details.name_1st,"\n")]='\0';
    
    printf("Enter your Last Name : ");
    fgets(details.name_last, sizeof(details.name_last), stdin);
    details.name_last[strcspn(details.name_last,"\n")]='\0';

    printf("Enter your Full Name : ");
    fgets(details.name, sizeof(details.name), stdin);
    details.name[strcspn(details.name,"\n")]='\0';
    
    printf("Enter your Email@ : ");
    fgets(details.email, sizeof(details.email), stdin);
    details.email[strcspn(details.email,"\n")]='\0';

    printf("Enter your Phone Number : ");
    fgets(details.phn_num, sizeof(details.phn_num), stdin);
    details.phn_num[strcspn(details.phn_num,"\n")]='\0';

    printf("Enter your User : ");
    fgets(details.user_name, sizeof(details.user_name), stdin);
    details.user_name[strcspn(details.user_name,"\n")]='\0';

    printf("Enter your Password : ");
    fgets(details.user_pass, sizeof(details.user_pass), stdin);
    details.user_pass[strcspn(details.user_pass,"\n")]='\0';

    printf("Enter your favourite food : ");
    fgets(details.security_ques, sizeof(details.security_ques), stdin);
    details.security_ques[strcspn(details.security_ques,"\n")]='\0';

    strcpy(details.user_role,"Individual");

    FILE *file_open_for_write_data;
    file_open_for_write_data = fopen("database\\userDBS.csv", "a");
    fprintf(file_open_for_write_data,
            "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            details.id,
            details.name_1st,
            details.name_last,
            details.name,
            details.email,
            details.phn_num,
            details.user_name,
            details.user_pass,
            details.security_ques,
            details.user_role);            
    fclose(file_open_for_write_data);

    return 0;
}