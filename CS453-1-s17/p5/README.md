#Project 5 Linux Device Driver
* Author: YI XIE
* Class: CS453 [Operating Systems] Section 1

##Overview

In this project, I write a simple character driver called **booga**

##Manifest

[README.md](./README.md)   **This file**
[booga.h](./booga.h)   **header file for booga character driver**
[booga.c](./booga.c)   **booga driver**
[Makefile](./Makefile)   **Makefile**
[booga_load](./booga_load)   **shell file to load booga module**
[booga_unload](./booga_unload)   **shell file to unload booga module**
[test_booga.c](./test_booga.c)   **booga driver test file**


##Building the project

There is a Makefile for user to build module file  **booga.ko**
User could open another terminal as root user to watch the output to the system message file with
the command:

`tail -f /var/log/message`

Another methods would be invoke a virtual system console by ctrl-Alt-F2.

##Features and usage

```
./booga_load
./test-booga  <minor number> <buffersize> <read|write>
./booga_unload
```

- minor number **0-3 for booga0 through booga3**
- buffersize **buffer size**
- read|write **read data from device or write data to device**

## known Bugs
    Not found

##Discussion
1. I started this project from given examples and helloworld driver. First issue is on the desktop
   virtual machine which could not build examples and it shows it can not find build file under
   /lib/modules/4.xxxxx/build. I updated my kernel, restarted linux, and still no luck.
   Fortunatelly, my laptop has no this issue, which make me review the behaviors of the examples.

2. The second issue was .ko file could not insert. fortunatelly, some people have same issue and
   post solution on the piazza. I followed the instruction and disabled SElinux, which solved the
   issue. Then I can test and dive into the examples to go through all procdures.

3. Eventhough, we have gone through all these init, cleanup module, read, write functions. It is
   still a little bit difficult to start to understand them. I did research and read five chapters
   of book: **The Linux Kernel Module Programming Guide**. This book explains all related concept
   and gives me a really picture to start the project.

4. The last difficulty I met is send singal from inside kernel to user space. This part spend me
   more than 5 hours to try to find solution. 

5. It seems that the **booga-test1.sh** word count is off by one. I mannully count my output. My
   driver should be correct.

## Testing
1. Load test
    switch to root. type `insmod booga.ko` at command line then use `lsmod`to see if module is
        loaded. Watch system messages file to check assigned major number by the kernel. We also
        could assign a customer major number to see if kernel would clash. I did not try this since
        I don't want to have weired issue happened.
2. Unload test
    type `rmmod booga.ko` at command line then use `lsmod` to see if module is unloaded.
3. data read test
    In this part, we could first diable random pick phrases. Test each minior number from 0 to 3
    with different buffer size to make sure read buffer size is correct. Also different minior
    number besides 0 to 3 would be tried to see if program has boundary check. After nonrandom step
    passed, I enabled random function to see if it could randomly pick any four of phrases.
4. data write test
    No too much I could do in this part since it just return count size and did not really write
    data.
5. Terminate from inside kernel
    I manually load module and in the command line run test file by:
    `./test-booga 3 100 write`
    The test file should give the result like:
   
   ```
       Attempting to write to booga device
       Terminated
    ```
6. booga-test1.sh and booga-test2.sh is used to test booga driver.
7. Run booga-test2.sh serveral times to see if write bytes is less than read bytes when device booga3 is writed.

##Source used

[The Linux Kernel Module Programming Guide](http://www.tldp.org/LDP/lkmpg/2.6/lkmpg.pdf)




