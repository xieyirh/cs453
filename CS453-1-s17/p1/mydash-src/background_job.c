#include "mydash.h"

/**
 * if the command has a & , It is a background job. also it removes the & a and extra space. 
 * @param line user input command line through stdin
 * @return 1 if it is background job, otherwise return 0;
 */
int background_job(char *line)
{
    if (line != NULL){
        for (int i = strlen(line) -1; i >= 0; i--){
            if (line[i] == '&'){
                line[i] = '\0';
                i--;
                while(line[i] ==' '){
                    line[i] ='\0';
                    i--;
                }
                return 1;
            }
        }
    }
        return 0;
    }

/**
 * linked list supply function return 0 if pid is not equal
 * @param obj pass the first job object
 * @param other pass the second job object
 * @return 1 if two object's pid number is same, otherwise return 0
 */
int equals(const void *obj, const void *other)
{
    struct job_info_object *o1 = (struct job_info_object *) obj;
    struct job_info_object *o2 = (struct job_info_object *) other;
    return o1->pid == o2->pid;
}

/**linked list supply function return a string with job number, process-id, and user input command
 * @param obj job_info_object defined in mydash.h
 * return string
 */
char *toString(const void *obj)
{
    struct job_info_object *object = (struct job_info_object *)obj;
    const int MAX_DIGITS = 2048;
    char *buf;
    buf =(char*) malloc(sizeof(char) * MAX_DIGITS);
    snprintf(buf,MAX_DIGITS, "[%d] %d %s",object->job_number,object->pid, object->command );
    return buf;
}

/**
 * free objects
 * @param obj generic object
 */
void freeObject(void *obj)
{
    struct job_info_object *jobobj = (struct job_info_object*) obj;
    if (jobobj == NULL) 
        return;
    free(jobobj);
}

/**
 * create node 
 * @param job_number job number
 * @param pid process id
 * @param line command line
 * @return job node
 */
struct node *create_Object(int job_number, pid_t pid, char* line)
{
    struct job_info_object *job_object;
    struct node *job_node;

    job_object = create_job(job_number, pid, line);

    job_node = createNode(job_object);
    return job_node;
}

/**
 * create job object
 * @param job_number job number
 * @param pid process id
 * @param line command line
 * @return job object
 */
struct job_info_object *create_job(int job_number, pid_t pid, char *line)
{
    struct job_info_object *job_object;

    job_object = (struct job_info_object *)malloc(sizeof(struct job_info_object));
    job_object->job_number = job_number;
    job_object->pid = pid; 
    job_object->command = line;
    return job_object;
}


