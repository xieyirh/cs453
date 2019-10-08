# Homework-2 Prepping for your Driver project

* author: Yi Xie
* Class: CS453 [Operating Systems] Section 1

## Overview

In this homework, we are preparing our Linux VM to be ready for developing a small kernel driver. We
will:

1. Downloading the Linux Kernel sources.
2. making a small change to the maximum number of threads that can be created and then
   rebuild/reinstalling the kernel.

## Manifest

README.md   ** README file for homework report **

## preparations (problems part 1)

* Linux Kernel 4.9.9 from [The linux Kernel Archives](http://www.kernel.org)
* Developer tools based on [Building teh Linux
  Kernel](http://cs.boisestate.edu/~cs453/handouts/Linux-Kernel-Building-Guide.html)
* Oringial notes
> * threads-max = 63544
> * max user processes = 31772

## Kernel modification (problem part 2)

In this part, we need modify the linux kernel so it allows a user to run up to 95% of the maximum
processes(instead of the default 50%). 

Since instruction give us the hint, I opened the *kernel/fork.c* to check the resource file, which I
downloaded from The linux Kernel Archives. At the very beginning (line 100), I found: `#define MAX_THREADS FUTEX_TID_MASK`. 
Then I searched the whole source file with keywords `max_threads`. Under the line 403, the code
block defined the set_max_threads function:

```
403 static void set_max_threads(unsigned int max_threads_suggested)
404 {
405         u64 threads;
406
407         /*
408          * The number of threads shall be limited such that the thread
409          * structures may only consume a small part of the available memory.
410          */
411         if (fls64(totalram_pages) + fls64(PAGE_SIZE) > 64)
412                 threads = MAX_THREADS;
413         else
414                 threads = div64_u64((u64) totalram_pages * (u64) PAGE_SIZE,
415                                     (u64) THREAD_SIZE * 8UL);
416
417         if (threads > max_threads_suggested)
418                 threads = max_threads_suggested;
419
420         max_threads = clamp_t(u64, threads, MIN_THREADS, MAX_THREADS);
421 }

```
Based on the set_max_threads function, I understood that Linux calculates the threads 
max_threads = mempages / (8 * THREAD_SIZE / PAGE_SIZE); After keep looking the following code block,
I found that the function ` void __init_fork_init(void) `:

```
void __init fork_init(void)
429 {
430         int i;
431 #ifndef CONFIG_ARCH_TASK_STRUCT_ALLOCATOR
432 #ifndef ARCH_MIN_TASKALIGN
433 #define ARCH_MIN_TASKALIGN      L1_CACHE_BYTES
434 #endif
435         /* create a slab on which task_structs can be allocated */
436         task_struct_cachep = kmem_cache_create("task_struct",
437                         arch_task_struct_size, ARCH_MIN_TASKALIGN,
438                         SLAB_PANIC|SLAB_NOTRACK|SLAB_ACCOUNT, NULL);
439 #endif
440 
441         /* do the arch specific task caches init */
442         arch_task_cache_init();
443 
444         set_max_threads(MAX_THREADS);
445 
446         init_task.signal->rlim[RLIMIT_NPROC].rlim_cur = max_threads/2;
447         init_task.signal->rlim[RLIMIT_NPROC].rlim_max = max_threads/2;
448         init_task.signal->rlim[RLIMIT_SIGPENDING] =
449                 init_task.signal->rlim[RLIMIT_NPROC];
450 
451         for (i = 0; i < UCOUNT_COUNTS; i++) {
452                 init_user_ns.ucount_max[i] = max_threads/2;
453         }
454 }

```
The line 446, 447 and 452 divided the max_threads by 2 which match the 50% of the maximum processes.
This are some defined variables I have no ideas what are they. I then went to google found very
convienient website: [Linux Cross Reference](lxr.free-electrons.com), which supports jump between
differet files. I found some uses definition:

```
> # define RLIMIT_NPROC           6       /* max number of processes */
> int max_threads;                /* tunable limit on nr_threads */

```
According to the problem requirments, I did some modification to verify my thoughts:

```
--- origin_fork.c	2017-02-13 00:14:19.636334660 -0700
+++ fork.c	2017-02-13 00:18:11.119028002 -0700
@@ -443,13 +443,13 @@
 
 	set_max_threads(MAX_THREADS);
 
-	init_task.signal->rlim[RLIMIT_NPROC].rlim_cur = max_threads/2;
-	init_task.signal->rlim[RLIMIT_NPROC].rlim_max = max_threads/2;
+	init_task.signal->rlim[RLIMIT_NPROC].rlim_cur = max_threads * 95/100;
+	init_task.signal->rlim[RLIMIT_NPROC].rlim_max = max_threads * 95 /100;
 	init_task.signal->rlim[RLIMIT_SIGPENDING] =
 		init_task.signal->rlim[RLIMIT_NPROC];
 
 	for (i = 0; i < UCOUNT_COUNTS; i++) {
-		init_user_ns.ucount_max[i] = max_threads/2;
+		init_user_ns.ucount_max[i] = max_threads * 95/100;
 	}
 }

```
## Building my Kernel

By following the Building the Linux Kernel instruction, I rebuilt my own version of Linux Kernel. It
took me about one and half hour to make. 

**Here is the results after the new Kernel**

```
cat /proc/sys/kernel/threads-max
63367

ulimit -Ha

core file size          (blocks, -c) unlimited
data seg size           (kbytes, -d) unlimited
scheduling priority             (-e) 0
file size               (blocks, -f) unlimited
pending signals                 (-i) 60198
max locked memory       (kbytes, -l) 64
max memory size         (kbytes, -m) unlimited
open files                      (-n) 4096
pipe size            (512 bytes, -p) 8
POSIX message queues     (bytes, -q) 819200
real-time priority              (-r) 0
stack size              (kbytes, -s) unlimited
cpu time               (seconds, -t) unlimited
max user processes              (-u) 60198
virtual memory          (kbytes, -v) unlimited
file locks                      (-x) unlimited

```
Now the max user processes are 60198, and the threads-max is 63367 which is slightly different from
my original records - 63544. I guess this change may comes from ram size calculation. 

60198/63367 = 0.95!!!

## Sources used

[Linux Cross reference](lxr.free-electrons.com/source/kernel/fork.c



