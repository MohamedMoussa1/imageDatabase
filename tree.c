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
struct TreeNode *allocate_node(const char *value)
{
	struct TreeNode *new_node = NULL;
	new_node = malloc(sizeof(struct TreeNode));
	if (new_node == NULL)
	{
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

void tree_insert_helper(struct TreeNode *root, char **values, int level)
{
	struct TreeNode *curr = NULL;
	struct TreeNode *p = NULL;
	struct TreeNode *t = NULL;

	curr = root;

	if (level == 0)
	{
		tree_insert_helper(curr, values, level + 1); // Recursion to check the next level of tree
	}
	else if (level != 4)
	{
		if (curr->child == NULL)
		{ // No values already exist
			//printf("%s, %d, BEFORE\n", curr->value, level);
			p = allocate_node(&*values[level - 1]); // Allocate memory for a node with desired value
			curr->child = p;
			//printf("%s, %d\n", curr->child->value, level);
			tree_insert_helper(p, values, level + 1); // Recursion to check the next level of tree
		}
		else
		{ // At least one value exists
			p = curr->child;
			while (p != NULL)
			{ // Traverse the list of values
				if (strcmp(p->value, &*values[level - 1]) == 0)
				{											  // Desired value found
					tree_insert_helper(p, values, level + 1); // Go to the next level
					return;
				}
				p = p->sibling;
			}
			if (p == NULL) // Did NOT find the value
			{
				// q->sibling = allocate_node(&*values[level - 1]);
				// //printf("HERE\n");
				// tree_insert_helper(q->sibling, values, level + 1);

				p = curr->child;
				if (strcmp(&*values[level - 1], p->value) < 0) { // If our value is < the old value at the head
					// Insert at head
					t = p;
					p = allocate_node(&*values[level - 1]);   // Allocate memory for a node with desired value
					p->sibling = t;							  // Set our sibling
					curr->child = p;						  // Update curr(parent) child
					tree_insert_helper(p, values, level + 1); // Recursion to check the next level of tree
				} else {
					t = p->sibling;    // Keep trace if p->sibling
					while (p != NULL) {
						if (strcmp(&*values[level - 1], p->value) > 0) {    // If our value is > p->value
							if (t == NULL) {
								// Insert at tail
								p->sibling = allocate_node(&*values[level - 1]);   // Allocate memory for a node with desired value
								tree_insert_helper(p->sibling, values, level + 1);  // Recursion to check the next level of tree
								break;
							} else if (strcmp(&*values[level - 1], t->value) < 0) {    // If our value is < p->value
								// Insert at middle
								p->sibling = allocate_node(&*values[level - 1]);   // Allocate memory for a node with desired value
								p->sibling->sibling = t;
								tree_insert_helper(p->sibling, values, level + 1);  // Recursion to check the next level of tree
								break;
							}
						}
						t = t->sibling;
						p = p->sibling;
					}
				}
			}
		}
	}
	else
	{ // Level is 4 (Filename level)
		if (curr->child == NULL)
		{ // No filenames of this type exist
			curr->child = allocate_node(&*values[level - 1]);
			//printf("%s, %d\n", curr->child->value, level);
			return;
		}
		p = curr->child;
    	if (strcmp(&*values[level - 1], p->value) < 0) { // If our value is < the old value at the head
			// Insert at head
			t = p;
			p = allocate_node(&*values[level - 1]);   // Allocate memory for a node with desired value
			p->sibling = t;							  // Set our sibling
			curr->child = p;						  // Update curr(parent) child
			return;		
		} else {
			t = p->sibling;    // Keep trace of p->sibling
			printf("HERERERE\n");
			while (p != NULL) {
				printf("Also HERERERE\n");
				if (strcmp(&*values[level - 1], p->value) > 0) {    // If our value is > p->value
					if (t == NULL) {
						// Insert at tail
						p->sibling = allocate_node(&*values[level - 1]);   // Allocate memory for a node with desired value
						return;
					} else if (strcmp(&*values[level - 1], t->value) < 0) {    // If our value is < p->value
						// Insert at middle
						p->sibling = allocate_node(&*values[level - 1]);   // Allocate memory for a node with desired value
						p->sibling->sibling = t;
						return;
					}
				}
				t = t->sibling;
				p = p->sibling;
			}
		}
		// while (p != NULL)
		// { // Traverse the list of filenames
		// 	if (p->sibling == NULL)
		// 	{
		// 		p->sibling = allocate_node(&*values[level - 1]);
		// 		return; // Once filename is added, exit
		// 	}
		// 	p = p->sibling;
		// }
	}
}

/**
 *  Insert a new image to a tree
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array, whose first three members are the attribute values for 
 *                the image and the last one is the filename
 */
void tree_insert(struct TreeNode *root, char **values)
{
	tree_insert_helper(root, values, 0);
}

/**
 *  Searches a tree to print all files with matching attribute values.
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array of attribute values
 */
void tree_search(const struct TreeNode *root, char **values)
{
	struct TreeNode *p = NULL;
	if (root->child == NULL)
	{
		printf("(NULL)\n");
		return;
	}

	p = root->child; // Level 1 Color

	while (p != NULL)
	{
		if (strcmp(p->value, values[0]) == 0)
		{
			p = p->child; // Level 2 Shape
			while (p != NULL)
			{
				if (strcmp(p->value, values[1]) == 0)
				{
					p = p->child; // Level 3 Texture
					while (p != NULL)
					{
						if (strcmp(p->value, values[2]) == 0)
						{
							p = p->child; //Level 4 Filename
							while (p != NULL)
							{
								printf("%s ", p->value);
								p = p->sibling;
							}
							return;
						}
						if (p == NULL)
							break;
						p = p->sibling;
					}
				}
				if (p == NULL)
					break;
				p = p->sibling;
			}
		}
		if (p == NULL)
			break;
		p = p->sibling;
	}
	printf("(NULL)\n");
}

/**
 *  Prints a complete tree to the standard output.
 *
 *  @param tree A pointer to the root of the tree.
 */
void tree_print(const struct TreeNode *tree)
{
	struct TreeNode *p1 = NULL;
	struct TreeNode *p2 = NULL;
	struct TreeNode *p3 = NULL;
	struct TreeNode *p4 = NULL;

	if (tree->child != NULL)
	{ // Tree contains files
		p1 = tree->child;

		while (p1 != NULL)
		{ // Level 1 Color
			//printf("%s ", p1->value);
			p2 = p1->child;

			while (p2 != NULL)
			{ // Level 2 Shape
				//printf("%s ", p2->value);
				p3 = p2->child;

				while (p3 != NULL)
				{ // Level 3 Texture
					//printf("%s ", p3->value);
					p4 = p3->child;

					while (p4 != NULL)
					{ // Level 4 Filename
						printf("%s %s %s %s\n", p1->value, p2->value, p3->value, p4->value);
						p4 = p4->sibling;
					}
					p3 = p3->sibling;
				}
				p2 = p2->sibling;
			}
			p1 = p1->sibling;
		}
	}
	else
	{
		printf("(NULL)\n");
	}
}
