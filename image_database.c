/*
 * Created by Mohamed Moussa
 */

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "utils.h"

int main(void) {

        // char array to hold a line of input
	char buf[BUFFER_SIZE] = {'\0'};

        // char* array to hold the pointers to tokens
	char *args[INPUT_ARG_MAX_NUM];


        // the root of the tree
        struct TreeNode root;
        root.value = "";
        root.child = NULL;
        root.sibling = NULL;

	struct TreeNode *root_ptr = &root;

        // Add your code below:
        int num;

        args[0] = malloc(sizeof(char)*BUFFER_SIZE);
        args[1] = malloc(sizeof(char)*BUFFER_SIZE);
        args[2] = malloc(sizeof(char)*BUFFER_SIZE);
        args[3] = malloc(sizeof(char)*BUFFER_SIZE);
        args[4] = malloc(sizeof(char)*BUFFER_SIZE);

        while (fgets(buf, BUFFER_SIZE, stdin) != NULL) {
                num = tokenize(buf, args);

                if (args[0][0] == 'i' && args[0][1] == '\0' && num == 5) {
                        printf("Insert cmd\n");
                } else if (args[0][0] == 'q' && args[0][1] == '\0' && num == 4) {
                        printf("Query cmd\n");
                } else if (args[0][0] == 'p' && args[0][1] == '\0' && num == 1) {
                        printf("Print all cmd\n");
                } else {
                        fprintf(stderr, "Invalid command.\n");
                }
        }

        return 0;
}
