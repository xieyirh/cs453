#Shell Project Part1
* Author: YI XIE
* Class: CS453 [Operating Systems] Section 1

##Overview

In this project, we build our own shell under Linux system. This shell will accept some build in
command as well as system command. We will use provided linked list to save the background
processes. 

##Manifest

README.md   **This file**
makefile    **build file for mydash project1**
Testplan.txt    **test plan**
/mydash-src/mydash_buildingIn.c   **build In functions**
/mydash-src/parsing.c   **parsing command line from mydash stdin**
/mydash-src/mydash.c    **start file**
/mydash-src/run_mydash.c   **implement all functions from here**
/mydash-src/mydash.h    **header file for this project**
/mydash-src/background_job.c    **all functions related to process background jobs**

##Building the project

User could use **make** to build executable file **mydash** to run the program *./mydash*.
User may need set up LD_LIBRARY_PATH enviroment variable so the shell can find the list library when
user runs the shell. This can be done as follows:
'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../p0/lib'

##Features and usage

The mini shell support following functionality:
1. filename completion and command history
2. Normal command execution
3. Handling empty commands
4. Handling EOF.
5. Exit command (build in command 'exit')
6. Change Directory command (build in command 'cd')
7. Prompt
8. Show version
9. Background jobs
10. Job list
11. Simple job control
12. Support 'jobs' command (build in command 'jobs')

## Testing

See TestPlan.txt.

## known Bugs

1. some time there is background job with [defounc] mark when I run ps under my shell
2. There my have some memory leak

##Discussion

This is vey interesting project. It helps me understand how shell works under linux system. I had
difficult time to understand how to put process into background. It takes me a while to make it
work. But I am still not sure if it is the correct way to do this. 
It also take a while to use provided library. The examples under p0 folder helps a lot. 
It take a a while to finaly to make change dirctory work perfectly and prompt with current directory

I am still trying to fully understand to use signal handler if I put it into my job control. 


##Source used
[Turtorial-write a shell in C] (http://brennan.io/2015/01/16/write-a-shell-in-c)
[writing your own shell-Cornell computer science] (https://www.cs.cornell.edu/courses/cs414/2004su/homework/shell/shel.html)




