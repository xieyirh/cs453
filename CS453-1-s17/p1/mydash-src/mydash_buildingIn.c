#include "mydash.h"
#include <pwd.h>

/**
 * return 1 if the command is a build-in command
 * @param argv  parsed command line
 * @return 1 if the command is a build-in command
 */
int isBuildInCommand(char **argv)
{
    if (strcmp (argv[0], "exit") == 0)
        return 1;
    else if(strcmp(argv[0], "mydash") == 0)
        return 1;
    else if(strcmp(argv[0], "cd") == 0)
        return 1;
    else if(strcmp(argv[0], "jobs") == 0)
        return 1;
    else 
        return 0;
}

/**
 * run building command
 * @param argv parsed command line
 * @param pid process id
 * @param background_job_lis background job list
 */
void runBuildInCommand(char **argv, pid_t pid, struct list *background_job_list, char *line)
{
    if (strcmp (argv[0], "exit") == 0) {
        free(line);
        exit(EXIT_SUCCESS);
    }
    if(strcmp(argv[0], "mydash") == 0)
       if (strcmp(argv[1], "-v") == 0)
           printf(" mydash_version %s\n",git_version());
    if (strcmp(argv[0],"cd") == 0 && argv[1] == NULL) 
        if(chdir(getpwuid(getuid())->pw_dir) == -1)
            printf("No such file or directory!\n");
    if (strcmp(argv[0],"cd") == 0 && argv[1] != NULL) 
        if(chdir(argv[1]) == -1)
            printf("No such file or directory!\n");
    if (strcmp(argv[0], "jobs")==0)
        mydash_jobs(pid, background_job_list);
}    

/**
 * process jobs command and list all running process and done process in the screen
 * @param pid process id
 * @param background_job_list background job list
 */
void mydash_jobs(pid_t pid, struct list *background_job_list)
{   
    struct node *tempNode;
    int node_size;
    
    node_size = getSize(background_job_list);

    for(int i = 0; i < node_size; i++){
        tempNode = removeFront(background_job_list);
        if(((struct job_info_object *)tempNode->obj)->pid == pid){
            printf("[%d] Done %s\n",((struct job_info_object *)tempNode->obj)->job_number,((struct job_info_object *)tempNode->obj)->command);
            freeNode(tempNode, freeObject);
        }
        else {
            printf("[%d] Running %s\n",((struct job_info_object *)tempNode->obj)->job_number,((struct job_info_object *)tempNode->obj)->command);
            addAtRear(background_job_list, tempNode);
        }
    }
    tempNode = NULL;

}

/**
 * report finished job by displaying job number and command
 * @param pid process id
 * @background_job_list background job list
 */
void mydash_job_report(pid_t pid, struct list *background_job_list)
{
    struct job_info_object *searchjob;
    struct node *foundjob, *rmjob;
    char *fakejob = "fakejob";

    searchjob = create_job(-1, pid, fakejob);
    foundjob = search(background_job_list, searchjob);
    rmjob = removeNode(background_job_list, foundjob);

    if (rmjob!= NULL) {
        printf("[%d] Done %s\n",((struct job_info_object *)rmjob->obj)->job_number,((struct job_info_object *)rmjob->obj)->command);
        freeObject(searchjob);                        
        freeNode(rmjob, freeObject);
    }
}
