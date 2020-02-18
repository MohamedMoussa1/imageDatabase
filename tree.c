/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02. 
 * Implemented by Mohamed Moussa on 2020-02
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"


/**
 *  A helper function that allocates a new tree node.
 *
 *  @param value The entry's value. It represents either an attribute or a filename.
 *  @return A pointer to the newly allocated node.
 *  (for now it returns NULL, so the compiler does not complain)
 */
struct TreeNode *allocate_node(const char *value) {
	struct TreeNode *new_node = NULL;
	new_node = malloc(sizeof(struct TreeNode));
	if (new_node == NULL) {
		fprintf(stderr, "Not enough memory to be malloced. Return NULL\n");
		return NULL;
	}

	new_node->child = NULL;
	new_node->sibling = NULL;
	new_node->value = malloc(sizeof(char) * BUFFER_SIZE);
	// check strncpy as well
	strcpy(new_node->value, value);

	return new_node;
}

void tree_insert_helper(struct TreeNode *root, char **values, int level) {
	struct TreeNode *curr = NULL;
	struct TreeNode *p = NULL;
	struct TreeNode *q = NULL;

	curr = root;

	if (level == 0) {
		tree_insert_helper(curr, values, level+1);    // Recursion to check the next level of tree
	} else if (level != 4) {
		if (curr->child == NULL) {    // No values already exist
			p = allocate_node(*values[level-1]);    // Allocate memory for a node with desired value
			curr->child = p;
			tree_insert_helper(p, values, level+1);    // Recursion to check the next level of tree
		} else {    // At least one value exists
			p = curr->child;
			while (p != NULL) {		// Traverse the list of values
				if (strcmp(p->value, *values[level-1])==0) {    // Desired value found
					tree_insert_helper(p, values, level+1);    // Go to the next level
					return;
				}
				q = p;
				p = p->sibling;
			}
			if (p == NULL) {
				q->sibling = allocate_node(*values[level-1]);
				tree_insert_helper(q->sibling, values, level+1);
			}
		}
	} else {    // Level is 4 (Filename level)
		if (curr->child == NULL) {    // No filenames of this type exist
			curr->child = allocate_node(*values[level-1]);
			return;
		}
		p = curr->child;
		while (p != NULL) {		// Traverse the list of filenames
			if (p->sibling == NULL) {
				p->sibling = allocate_node(*values[level-1]);
				return;    // Once filename is added, exit
			}
			p = p->sibling;
		}
	}
}

/**
 *  Insert a new image to a tree
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array, whose first three members are the attribute values for 
 *                the image and the last one is the filename
 */
void tree_insert(struct TreeNode *root, char **values) {
	tree_insert_helper(root, values, 0);
}

/**
 *  Searches a tree to print all files with matching attribute values.
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array of attribute values
 */
void tree_search(const struct TreeNode *root, char **values) {
}

/**
 *  Prints a complete tree to the standard output.
 *
 *  @param tree A pointer to the root of the tree.
 */
void tree_print(const struct TreeNode *tree) {
}
