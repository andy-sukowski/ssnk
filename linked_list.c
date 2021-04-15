/* See LICENSE file for copyright and license details. */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

/* create new node */
struct node *new_node(int x, int y, struct node *next)
{
	struct node *new = malloc(sizeof *new);
	if (!new) {
		fputs("Error: memory allocation failed\n", stderr);
		return NULL;
	}
	new->x = x;
	new->y = y;
	new->next = next;
	return new;
}

/*
 * delete last node from linked list
 * precondition: head != NULL
 */
void delete_last(struct node *head)
{
	struct node **cursor = &head;
	while ((*cursor)->next)
		cursor = &(*cursor)->next;
	free(*cursor);
	*cursor = NULL;
}

/* check if node exists in linked list */
bool node_exists(struct node *head, int x, int y)
{
	struct node *cursor = head;
	while (cursor) {
		if (cursor->x == x && cursor->y == y)
			return true;
		cursor = cursor->next;
	}
	return false;
}

/* free each node in linked list */
void free_nodes(struct node *head)
{
	while (head) {
		struct node *tmp = head;
		head = head->next;
		free(tmp);
	}
}
