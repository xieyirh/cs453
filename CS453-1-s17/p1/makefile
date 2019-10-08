

CC=gcc
CFLAGS=-g  -Wall

LIBS=-lreadline -lncurses -lmylib -lm 
INCLUDES= -I../p0/include
LFLAGS= -L../p0/lib


PROGS=mydash

SRCS=git_version.c ./mydash-src/mydash.c ./mydash-src/mydash_buildingIn.c ./mydash-src/parsing.c ./mydash-src/run_mydash.c ./mydash-src/background_job.c ./mydash-src/signal_handler.c

OBJS=$(SRCS:.c=.o)


all: $(PROGS)
   # @echo mydash has been compiled

$(PROGS): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(PROGS) $(OBJS) $(LFLAGS) $(LIBS)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

##
## on every build, record the working copy revision string
##
git_version.c: FORCE
		echo -n 'const char* git_version(void) { const char* GIT_Version = "' > git_version.c
		git rev-parse HEAD | cut -c1-6 | tr -d '\n'  >> git_version.c
		echo '"; return GIT_Version; }' >> git_version.c


FORCE:
##
## Then any executable that links in git_version.o will be able
## to call the function git_version() to get a string that
## describes exactly what revision was built.

depend: $(SRCS)
	makedepend $(INCLUDES) $^

clean:
	rm -f ./*.o
	rm -f ./mydash-src/*.o ./mydash-src/*.d
	rm -f ./git_version.c
	rm -f ./$(PROGS)

