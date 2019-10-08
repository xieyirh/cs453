/**
 * mydash main function.
 * shell project this shell can take limited build-in command and most of system command
 * @author Yi Xie
 * @version 1.0
 */

#include "mydash.h"

int main(int argc, char *argv[]){
    
    if(argc ==2  && strcmp(argv[1], "-v") == 0){
        printf("mydash version: %s\n",git_version());
        return EXIT_SUCCESS;
    }

    run_mydash();

    return EXIT_SUCCESS;
}


