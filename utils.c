/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <string.h>

#include "utils.h"


/*
 * Tokenize the string stored in cmd based on DELIMITERS as separators.
 * Return the number of tokens, and store pointers to them in cmd_argv.
 */
int tokenize(char *cmd, char **cmd_argv) {
    int tokenNum = 0;
    int i = 0;
    char *token = strtok(cmd, DELIMITERS);

    while (token != NULL) {
        tokenNum++;
        cmd_argv[i] = token;
        token = strtok(NULL, DELIMITERS);
        i++;
    }
    i = 0;

    return tokenNum;
}
