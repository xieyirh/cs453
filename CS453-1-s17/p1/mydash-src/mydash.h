/**
 * mydash header file
 * author Yi Xie
 * version 1.0
**/

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <List.h>
#include <Node.h>
#include <signal.h>
/**
 * define a struct to store my job information
**/

struct job_info_object{
    int job_number;
    pid_t pid;
    char *command;
} ;

/**
 * global variable to update job number
**/

extern int job_number;
/**
 * all functions for mydash project
**/
extern pid_t BPTable[1024];
extern struct list *background_job_list;

void parse(char *, char **);
void run_mydash();
const char *git_version(void);
int mydash_cd(char **);
int background_job(char *);
int equals(const void *, const void *);
char *toString(const void *obj);
void freeObject(void *);
struct node *create_Object(int, pid_t, char *);
struct job_info_object *create_job(int, pid_t, char *);

void mydash_jobs(pid_t, struct list*);
void mydash_job_report(pid_t, struct list*);

int isBuildInCommand(char **);
void runBuildInCommand(char **, pid_t, struct list *, char *);
void sig_handler(int);

