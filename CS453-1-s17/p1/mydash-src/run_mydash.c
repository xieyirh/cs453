#include "mydash.h"

int job_number = 1;
struct list *background_job_list;

/**
 * shell function to process all system command and built-in command
 */
void run_mydash()
{
    char line[2048];
    char *origin_line;
    int status;
    char *argv[2048];
    int isbg_job = 0;
    pid_t childpid, pid;
    char buff[1024];

   // struct list *background_job_list;

    background_job_list = createList (equals, toString, freeObject);
    
    using_history(); /*enable readline history mechaism*/
    while (1)
    {
       if(signal(SIGCHLD,sig_handler) == SIG_ERR)
           printf("signal error!\n");

        char prompt[100]="";
        if(getenv("DASH_PROMPT") == NULL) {
            prompt[0] = '[';
            strcat(prompt, getcwd(buff,1024));
            strcat(prompt, "] mydash>");
        }
        else
            strcat(prompt, getenv("DASH_PROMPT"));

        pid = waitpid(-1, &status, WNOHANG);
        if(pid>0)
            mydash_job_report(pid, background_job_list);

        origin_line = readline(prompt);
        if (origin_line == NULL)
            exit (1);

        add_history(origin_line);  /*add current line to history list*/
        strcpy(line, origin_line);
       
        if (background_job(line)){
            if(isEmpty(background_job_list)){
                job_number = 1;
            }
            else {
                job_number++;    
            }
            isbg_job = 1;
        }

        parse(line, argv); //token the command line

        if(*line) {
        
            if(isBuildInCommand(argv)){
                runBuildInCommand(argv, pid, background_job_list, origin_line);
            }
            else {
                childpid = fork();
                if (childpid < 0) 
                    perror("fork error!");
                else if (childpid == 0 )
                    execvp(line,argv);
                else {
                    if(isbg_job) {
                        isbg_job = 0;
                        addAtRear(background_job_list, create_Object(job_number, childpid, origin_line));
                        printList(background_job_list);
                        for(int i = 0; i < 1024; i++)
                            if(BPTable[i] == 0 )
                                BPTable[i] = childpid;
                        continue;
                    }
                    else
                        waitpid(childpid, &status, 0);
                }
            }
        }
        
        
        free(origin_line);
    }
    free(background_job_list);
    for (int i = 0; i < 2048; i++){
        free(argv[i]);
    }
    free(argv);
}

