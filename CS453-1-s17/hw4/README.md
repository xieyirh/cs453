#Homework 4 Monitor
* Author: YI XIE
* Class: CS453 [Operating Systems] Section 1

##Overview

In this homework, we write a solution out in C using PTthreads and monitor based
on conditional variables and mutexes, and in Java using monitor based approach to demonstrate the
use of the monitor.

##Manifest

README.md   **This file**
1. C version

[FileAccess.h](./c_version/FileAccess.h)   **header file**
[FileAccess.c](./c_version/FileAccess.c)   **file access**
[TestFileAccess.c](./c_version/TestFileAccess.c)   **file access test driver**

2. Java version

[FileAccess.java](./java_version/FileAccess.java)   **FileAccess object**
[FileAccessMonitor.java](./java_version/FileAccessMonitor.javac)   **FileAccessMonitor object**
[TestFileAccess.java](./java_version/TestFileAccess.java)   **file access test driver **

##Building the project

In each directory, this is related Makefile for user to build executable file **TestFileAccess**

##Features and usage

1. C version usage:
    `./TestFileAccess <numThreads> <max Sum> <iterations>`
2. Java version usage:
    `java TestFileAccess <numThreads> <max Sum> <iterations>`
3. Usage:
    <numThreads> total spawned threads.
    <max sum> The sum of threads id to decide file access.
    <iterations> the file access times for each thread id.

## known Bugs
    Not found
##Discussion

1. Monitor pseudo-code to coordinate access to the file.

```
    monitor FileAccess{
        ...
        public:

        //constructor
        FileAccess(int max){

        }

        public synchronized void StartAccess(int id){
            sum = sum + id;
            while(sum > max){
                this.wait();
            }
            this.notify;
        }

        public synchronized void EndAccess(int id){
            sum = sum -id;
            this.notify();
        }
```
2. There are two versions to simulate monitor by using C and Java. It seems the Java version
   is much easier to implement than the C version since Java has buildIn Synchronized feature which
   makes the programming much easier. I also spend some time to understand how timer works under this
   version.


##Source used

[Concurrency Concepts in Java](https://www.youtube.com/watch?v=RHoP92anvxY)
[What is Timer and TimerTask in Java-Turorial
Example](http://javarevisited.blogspot.com/2013/02/what-is-timer-and-timertask-in-java-example-tutorial.html)





