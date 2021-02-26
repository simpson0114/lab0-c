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
    /* TODO: What if malloc returned NULL? */
    if (q == NULL)
        return NULL;
    q->head = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    if (q) {
        while (q->head != NULL) {
            list_ele_t *tmp = q->head;
            q->head = q->head->next;
            free(tmp->value);
            free(tmp);
        }
        /* Free queue structure */
        free(q);
    }
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
    /* TODO: What should you do if the q is NULL? */
    if (q == NULL)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    newh->value = malloc(strlen(s) + 1);
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    strncpy(newh->value, s, strlen(s) + 1);
    if (q->head == NULL)
        q->tail = newh;
    newh->next = q->head;
    q->head = newh;
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
    if (newt == NULL)
        return false;
    newt->value = malloc(strlen(s) + 1);
    newt->next = NULL;
    strncpy(newt->value, s, strlen(s) + 1);
    if (q->head == NULL) {
        q->head = q->tail = newt;
        q->size++;
        return true;
    }
    q->tail->next = newt;
    q->tail = newt;
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
    list_ele_t *tmp = q->head;
    if (q->head == NULL)
        return false;
    strncpy(sp, q->head->value, bufsize);
    q->head = q->head->next;
    q->size--;
    free(tmp->value);
    free(tmp);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
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
    if (q != NULL) {
        list_ele_t *tmp;
        list_ele_t *next_list;
        tmp = q->tail;
        while (q->head != tmp) {
            next_list = q->head;
            while (next_list->next->next == NULL)
                next_list = next_list->next;
            tmp->next = next_list;
            tmp = next_list;
            tmp->next = NULL;
        }
        tmp->next = NULL;
        q->head = q->tail;
        q->tail = tmp;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q != NULL) {
    }
}
