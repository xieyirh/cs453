
DEBUG=
CC=gcc
CFLAGS=-g  -Wall  $(DEBUG)
LFLAGS=-lpthread

OBJS=FileAccess.o TestFileAccess.o

all: TestFileAccess

TestFileAccess: FileAccess.h $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $(OBJS) 
	

clean:
	/bin/rm -f *.o  $(OBJS) TestFileAccess
