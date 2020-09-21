#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"
#include "strnatcmp.h"

list_ele_t *merge(list_ele_t *l1, list_ele_t *l2)
{
    // merge with pseudo node

    if (!l2)
        return l1;
    if (!l1)
        return l2;

    list_ele_t *head, *temp;

    if (strnatcmp(l1->value, l2->value) < 0) {
        head = l1;
        temp = l1;
        l1 = l1->next;
    } else {
        head = l2;
        temp = l2;
        l2 = l2->next;
    }

    while (l1 && l2) {
        if (strnatcmp(l1->value, l2->value) < 0) {
            temp->next = l1;
            temp = temp->next;
            l1 = l1->next;
        } else {
            temp->next = l2;
            temp = temp->next;
            l2 = l2->next;
        }
    }

    if (l1)
        temp->next = l1;
    if (l2)
        temp->next = l2;

    return head;
}

list_ele_t *mergeSortList(list_ele_t *head)
{
    // merge sort
    if (!head || !head->next)
        return head;

    list_ele_t *fast = head->next;
    list_ele_t *slow = head;

    // split list
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    slow->next = NULL;

    // sort each list
    list_ele_t *l1 = mergeSortList(head);
    list_ele_t *l2 = mergeSortList(fast);

    // merge sorted l1 and sorted l2
    return merge(l1, l2);
}

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
    if (!q)
        return;
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
    /* TODO: What should you do if the q is NULL? */
    if (q == NULL)
        return false;
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (newh == NULL)
        return false;
    newh->value = malloc(strlen(s) + 1);
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    strncpy(newh->value, s, strlen(s));
    newh->value[strlen(s)] = '\0';
    newh->next = q->head;
    q->head = newh;
    if (q->head->next == NULL)
        q->tail = newh;
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
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *newh;
    if (q == NULL)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;
    newh->value = malloc(strlen(s) + 1);
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    strncpy(newh->value, s, strlen(s));
    newh->value[strlen(s)] = '\0';
    newh->next = NULL;
    if (q->head != NULL) {
        q->tail->next = newh;
        q->tail = newh;
    } else {
        q->head = newh;
        q->tail = newh;
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
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL || q->head == NULL)
        return false;
    list_ele_t *tmp;
    tmp = q->head;
    q->head = q->head->next;
    if (sp != NULL) {
        strncpy(sp, tmp->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
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
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL)
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
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q != NULL && q->head != NULL) {
        list_ele_t *cur, *tmp;
        cur = q->head;
        while (cur != q->tail) {
            tmp = q->tail->next;
            q->tail->next = cur;
            cur = cur->next;
            q->tail->next->next = tmp;
        }
        q->tail = q->head;
        q->head = cur;
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
    if (!q || q->head == NULL || q->size == 1)
        return;

    q->head = mergeSortList(q->head);

    list_ele_t *tmp = q->head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    q->tail = tmp;
}
