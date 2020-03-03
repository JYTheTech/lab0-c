#ifndef LAB0_SORT_H
#define LAB0_SORT_H

#include <string.h>
#include "queue.h"

/*
 * Split the linked list into two part:
 * first half and second half.
 */
void split(list_ele_t *q, list_ele_t **first_half, list_ele_t **second_half);

/*
 * Merge the two half of linked list into sorted linked list.
 */
list_ele_t *merge(list_ele_t *first_half, list_ele_t *second_half);

/*
 * Merge sort implementation.
 */
void merge_sort(list_ele_t **list_head);

#endif /* LAB0_SORT_H */