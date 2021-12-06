#ifndef NODECALC_H
#define NODECALC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	int data;
	struct node *next;
}node_t;


node_t* insert(node_t* head, int value) {
	node_t* current;
	node_t* previous;
	node_t* new_node;
	
	if (head == NULL) {
		// if first element
		head = (node_t *) malloc(sizeof(node_t));
		head->data = value;
		head->next = NULL;
	}
	else {
		current = head;
		previous = NULL;
		new_node = (node_t *) malloc(sizeof(node_t));
		new_node->data = value;

		while (current != NULL) {
			if (current->data > value) {
				new_node->next = current;
				if (previous == NULL)
					head = new_node;
				else
					previous->next = new_node;
				break;
			}
			if (current->next == NULL) {
				new_node->next = NULL;
				current->next = new_node;
				break;
			}
			previous = current;
			current = current->next;
		}
	}
	return head;
}

node_t* delete(node_t* head, int value) {
	node_t* current;
	node_t* previous; 
	node_t* to_be_deleted;
	if (head->next == NULL) {
		free(head);
		return NULL;
	}
    	else {
        	previous = NULL;
 		current = head;
		while(current != NULL) {
			to_be_deleted = NULL;
			if(current->data == value) {
				if (previous == NULL)
					head = current->next;
				else
					previous->next = current->next;
				to_be_deleted = current;
				current = current->next;
				to_be_deleted->next = NULL;
				free(to_be_deleted);
			}
			else {
				previous = current;
				current = current->next;
			}
		}
        	return head;
	}
}

int sum(node_t *head) {
	node_t* current = head;
	int total = 0;
	
	while (current != NULL) {
		total += current->data;
		current = current->next;
	}
	return total;
}

float average(node_t *head) {
	node_t* current = head;
	int total = 0;
	float avg = 0;
	int count = 0;

	while (current != NULL) {
		total += current->data;
		count += 1;
		current = current->next;
	}
	avg = (float)total / count;

	return avg;	
}

int minimum(node_t *head) {
	node_t* current = head;
	int min = head->data;

	while (current != NULL) {
		if (current->data < min) {
			min = current->data;
		}
		current = current->next;
	}

	return min;
}

int* median(node_t *head) {
	node_t* current = head;
	int count = 0;
	int *mid;
	mid = malloc(2 * sizeof(int));

	while (current != NULL) {
		count += 1;
		current = current->next;
	}
		
	int index = count - 1;
	int i = 0;
	current = head;
	if (index == 0){
		mid[0] = current->data;
		mid[1] = 0;
		return mid;
	}
	while (current != NULL && i < index) {
		if (i == index/2) {
			mid[0] = current->data;
			if ((count%2) == 0) {
				mid[1] = current->next->data;
			}
			else {
				mid[1] = 0;
			}
			break;
		}
		i += 1;
		current = current->next;
	}
	
	return mid;
}


#endif
