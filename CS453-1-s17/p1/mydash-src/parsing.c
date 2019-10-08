#include "mydash.h"

/**parsing the command line
 * @param line command line
 * @param argv parsed command line
 */
void parse(char *line, char **argv)
{
    while (*line != '\0'){
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ ='\0';
        *argv++ =line;
        while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n')
            line++;
    }
    *argv = '\0';
}
