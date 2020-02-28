/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 * Implemented by Mohamed Moussa on 2020-02
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

        char *args2[INPUT_ARG_MAX_NUM - 1];
        char *args3[INPUT_ARG_MAX_NUM - 2];

        args[0] = malloc(sizeof(char)*BUFFER_SIZE);
        args[1] = malloc(sizeof(char)*BUFFER_SIZE);
        args[2] = malloc(sizeof(char)*BUFFER_SIZE);
        args[3] = malloc(sizeof(char)*BUFFER_SIZE);
        args[4] = malloc(sizeof(char)*BUFFER_SIZE);

        args2[0] = malloc(sizeof(char)*BUFFER_SIZE);
        args2[1] = malloc(sizeof(char)*BUFFER_SIZE);
        args2[2] = malloc(sizeof(char)*BUFFER_SIZE);
        args2[3] = malloc(sizeof(char)*BUFFER_SIZE);

        args3[0] = malloc(sizeof(char)*BUFFER_SIZE);
        args3[1] = malloc(sizeof(char)*BUFFER_SIZE);
        args3[2] = malloc(sizeof(char)*BUFFER_SIZE);

        while (fgets(buf, BUFFER_SIZE, stdin) != NULL) {
                num = tokenize(buf, args);

                for (int i = 0; i < INPUT_ARG_MAX_NUM - 1; i++) {
                        args2[i] = args[i+1];
                }

                for (int i = 0; i < INPUT_ARG_MAX_NUM - 2; i++) {
                        args3[i] = args[i+1];
                }

                if (args[0][0] == 'i' && args[0][1] == '\0' && num == 5) {
                        //printf("Insert cmd\n");
                        tree_insert(root_ptr, args2);
                } else if (args[0][0] == 'q' && args[0][1] == '\0' && num == 4) {
                        //printf("Query cmd\n");
                        tree_search(root_ptr, args3);
                } else if (args[0][0] == 'p' && args[0][1] == '\0' && num == 1) {
                        //printf("Print all cmd\n");
                        tree_print(root_ptr);
                } else {
                        fprintf(stderr, "Invalid command.\n");
                }

                for (int i = 0; i < INPUT_ARG_MAX_NUM - 1; i++) {
                        args2[i] = NULL;
                }

                for (int i = 0; i < INPUT_ARG_MAX_NUM - 2; i++) {
                        args3[i] = NULL;
                }
        }

        return 0;
}
