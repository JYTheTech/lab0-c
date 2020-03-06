#include "sort.h"
#include <string.h>
#include <strnatcmp.h>
#include "queue.h"

/*
 * Split the linked list into two part:
 * first half and second half.
 */
void split(list_ele_t *list_node,
           list_ele_t **first_half,
           list_ele_t **second_half)
{
    list_ele_t *fast, *slow;
    fast = list_node->next;
    slow = list_node;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
    }
    *first_half = list_node;
    *second_half = slow->next;
    slow->next = NULL;
}

/*
 * Merge the two half of linked list into sorted linked list.
 */
list_ele_t *merge(list_ele_t *first_half, list_ele_t *second_half)
{
    list_ele_t *start, *current;

    if (first_half != NULL && second_half != NULL) {
        if (strnatcasecmp(first_half->value, second_half->value) >= 0) {
            start = second_half;
            second_half = second_half->next;
        } else {
            start = first_half;
            first_half = first_half->next;
        }
    } else if (first_half != NULL) {
        start = first_half;
        first_half = first_half->next;
    } else if (second_half != NULL) {
        start = second_half;
        second_half = second_half->next;
    } else {
        return NULL;
    }
    current = start;

    while (first_half != NULL && second_half != NULL) {
        if (strnatcasecmp(first_half->value, second_half->value) >= 0) {
            current->next = second_half;
            second_half = second_half->next;
        } else {
            current->next = first_half;
            first_half = first_half->next;
        }
        current = current->next;
    }

    if (first_half != NULL) {
        current->next = first_half;
    } else if (second_half != NULL) {
        current->next = second_half;
    }
    return start;
}

/*
 * Merge sort implementation.
 */
void merge_sort(list_ele_t **list_head)
{
    if ((*list_head) == NULL || (*list_head)->next == NULL)
        return;
    list_ele_t *first_half, *second_half;
    split(*list_head, &first_half, &second_half);

    merge_sort(&first_half);
    merge_sort(&second_half);

    *list_head = merge(first_half, second_half);
}