#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    printf("start buddy malloc\n");
    void *ptr = malloc(10000);
    printf("free pointer\n");
    free(ptr);
    printf("free pointer done \n");
    return 0;
}


