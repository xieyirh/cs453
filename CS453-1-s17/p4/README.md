#Project 4 Thread-safe monitor library
* Author: YI XIE
* Class: CS453 [Operating Systems] Section 1

##Overview

In this project, we create a thread-safe bounded version of the linked-list library. Then we test it
using a provided producer-consumer program. 

##Manifest

[README.md](./README.md)   **This file**
[ThreadsafeBoundedList.h](./wrapper-library/ThreadsafeBoundedList.h)   **header file API for library**
[ThreadsafeBoundedList.c](./wrapper-library/ThreadsafeBoundedList.c)   **function implementation of the header file**
[Makefile](./wrapper-library/Makefile)   **Makefile**
[Item.h](./Item.h)   **header file for object**
[Item.c](./Item.c)   **function implementation of the header file for object**
[pc.c](./Item.c)   **producer-consumer test file**
[test-pc](./test-pc.sh) **test shell file**


##Building the project

In each directory, this is related Makefile for user to build executable file **pc**

##Features and usage

`./pc  <poolsize> <#items/producer> <#producer> <#consumer> <sleep interval(microsecs)>`

- poolsize **linked-list size**
- #items/producer **items each producer produce**
- #producer **total producer amount**
- #consumer **total consumer amount**
- sleep interval(microsecs) **sleep intervals between producers and consumers**


## known Bugs
    Not found
##Discussion

    The ThreadsafeBoundedList.h header file is intuitive and the instruction is pretty easy to follow. The biggest problem I met in this project is kind of lock. In the function `tsb_addAtFront` and similar add/remove nodes funtion, there are while loop. In the while condition, I reused tsb_isFull and tsb_isEmpty function. Since there are mutex in the tsb_isFull/tsb_isEmpty function, which cause the **pc** program locked forever. This problem took me serveral hours to solve. In my solution, I could either remove mutex in my tsb_isEmpty/tsb_isFull funtion or implement the tsb_isEmpty/tsb_isFull in the while loop. I used the first method.


##Source used

Instructor's notes and sample programs.




