#Project 6 Shell Project , part 2 (with Buddy System Memory Manager)
* Author: YI XIE
* Class: CS453 [Operating Systems] Section 1

##Overview

In this project, we will provide our own memory management

##Manifest

[README.md](./README.md)   **This file**
[buddy.h](./buddy.h)   **header file for buddy memory management**
[buddy.c](./buddy.c)   **buddy memory management implemetation**
[Makefile](./Makefile)   **Makefile**
[buddy-unit-test.c](./buddy-unit-test.c)   **buddy unit test file**
[buddy-test.c](./buddy-test.c)   **buddy test file**
[malloc-test.c](./buddy-test.c)   **buddy malloc test file**
[libbuddy.so](./lib/libbuddy.so)   **shared buddy library**
[libbuddy.a](./lib/libbuddy.so)   **static buddy library **

[mydash](./mydash)   **Under this subdirectory I copied all shell files with make files**


##Building the project

1. There is a Makefile under ./p6  for user to build all test files.
2. The Makefile under ./mydash is for building updated shell files.
3. user needs setup LD_Library_PATH environment varibles so the shell could find shared library.
   This can be down as follows:
   `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../p0/lib`
   `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../lib`
   

##Features and usage

All prototypes for buddy function:

```
void buddy_init(size_t);
void *buddy_calloc(size_t, size_t);
void *buddy_malloc(size_t);
void *buddy_realloc(void *ptr, size_t size);
void buddy_free(void *);

```

There are three provided test files:

```
./buddy-test <num of tests> [random seed] [s|t|v|i]
./buddy-unit-test [s|t|v|i]
./malloc-test <num of tests> [random seed] [s|t|v|i]

```
Shell with replaced memory management cheme based on the buddy system is located under mydash
directory.

## known Bugs
    Too be Done

##Discussion
   The key point of this project is understand how the buddy system works. After read the **Donald
   Knuth. Fundamental Alorithms. The art of Computer programming** related chapter, It gave a big
   picture of buddy system with lots of unclear concepts. I kept searching  binary buddy system.
   After read more articles, I finially understood what struc we need, how freelist[] should be used
   to trace your free block, which made me start write the code.

   Implementation needs a little bit abstract imagination of arranging linkedlist, remove front free
   block, relink the rest of free blocks. I drawed on the paper with fake address and manually to
   track the changes, which is really helpful.

   It took me a while to make the *get_buddy()* function works well with instructor's hint in the
   class.

   Since we are using really big number, instructor's hints in the class is very useful.


## Testing

1. Testing plan for init function:
- check what happens if we init just one byte;
- check what happens if we init less than header size;
- check what happens if we init just one byte plus header size;
- check what happens if we init higher and higher bytes until reach RAM size;
- Check what happens if we init higher than MAX default size;

2. Testing plan for malloc function:
- malloc one byte;
- malloc larger bytes which are a little bit less than pool size ( pool size - header size);
- malloc bytes which are larger than pool size;
- malloc zero byte to see if it result null;
- malloc different sizes and watch printlist function results to see if they match buddy splits;

3.Testing plan for free funtion:
- free one byte ;
- free mallocated bytes;
- free two buddy pointers to see if they could merge; 
- free null pointer;
- free different sized pointer and watch printlist function results to see if they match buddy merges;

4. Testing plan for calloc function:
- check the calloced memory initialized value;
- callloc different size and check memory init values;
- check if nmemb or size is 0, if calloc() returns

5. Testing plan for realloc function:
- check what happens if new size is larger than old size (the content in the memory)
- check what happens if new size is smaller than old size ( the content in the memory);
- check if the size is equal to zero, and ptr is not NULL if it frees ptr;
- check what happens if ptr is NULL;

6. Check if error returns ENOMEM;
- 
    
##Source used

[The Linux Kernel Module Programming Guide](http://www.tldp.org/LDP/lkmpg/2.6/lkmpg.pdf)
[C Book by Kernighan and Ritchie]
[Fundamental Algorithems. The Art of Computer Programming 1 pp. 435-455 by Donald Knuth]




