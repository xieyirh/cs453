
CC=gcc
CFLAGS=-O -Wall -g -pthread
# Uncomment the line below to enable the use of a debugger
#CPPFLAGS=-g -Wall
# specify libraries to compile below, e.g. -lm (for the math library)
LIBS=

mergesort: mergesortTest.o mergesort.o timing.o 
	$(CC) $(CFLAGS)  mergesortTest.o mergesort.o timing.o $(LIBS) -o mergesort

clean:
	/bin/rm -f *.o mergesort
