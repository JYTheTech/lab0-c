#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));

    if (q == NULL)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL)
        return;
    /* Free elements of the queue */
    while (q->head != NULL) {
        list_ele_t *tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
    }
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;

    if (q == NULL)
        return false;
    newh = malloc(sizeof(list_ele_t));

    if (newh == NULL) {
        return false;
    } else {
        newh->value = malloc(sizeof(char) * strlen(s) + 1);
    }

    if (newh->value == NULL) {
        free(newh);
        return false;
    } else {
        memset(newh->value, 0, sizeof(char) * strlen(s) + 1);
        strncpy(newh->value, s, sizeof(char) * strlen(s) + 1);
    }

    if (q->head == NULL) {
        newh->next = NULL;
        q->head = newh;
        q->tail = newh;
    } else {
        newh->next = q->head;
        q->head = newh;
    }
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newt;

    if (q == NULL)
        return false;
    newt = malloc(sizeof(list_ele_t));

    if (newt == NULL) {
        return false;
    } else {
        newt->value = malloc(sizeof(char) * strlen(s) + 1);
    }

    if (newt->value == NULL) {
        free(newt);
        return false;
    } else {
        memset(newt->value, 0, sizeof(char) * strlen(s) + 1);
        strncpy(newt->value, s, sizeof(char) * strlen(s) + 1);
    }

    newt->next = NULL;

    if (q->tail == NULL) {
        q->tail = newt;
        q->head = newt;
    } else {
        q->tail->next = newt;
        q->tail = newt;
    }
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->head == NULL)
        return false;

    if (bufsize != 0 && q->head->value != NULL && sp != NULL) {
        if (strlen(q->head->value) + 1 > bufsize) {
            strncpy(sp, q->head->value, bufsize);
            sp[bufsize - 1] = '\0';
        } else {
            strncpy(sp, q->head->value,
                    sizeof(char) * strlen(q->head->value) + 1);
        }
    }
    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL || q->head == NULL)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->head == NULL)
        return;

    q->tail = q->head;
    list_ele_t *prev, *cur, *next;
    prev = NULL;
    cur = q->head;
    next = q->head->next;
    while (next != NULL) {
        cur->next = prev;
        prev = cur;
        cur = next;
        next = next->next;
    }
    cur->next = prev;
    q->head = cur;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q) {}