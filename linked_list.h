/* See LICENSE file for copyright and license details. */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct node {
	int x;
	int y;
	struct node *next;
};

/* create new node */
struct node *new_node(int x, int y, struct node *next);

/*
 * delete last node from linked list
 * precondition: head != NULL
 */
void delete_last(struct node *head);

/* check if node exists in linked list */
bool node_exists(struct node *head, int x, int y);

/* free each node in linked list */
void free_nodes(struct node *head);

#endif /* LINKED_LIST_H */
