#ifndef DSA_FROM_SCRATCH_LINKEDLIST_H
#define DSA_FROM_SCRATCH_LINKEDLIST_H


typedef struct LinkedListNode {
    void *data;
    struct LinkedListNode *next;
} LinkedListNode;

typedef struct LinkedList {
    struct LinkedListNode *dummy_head;
    struct LinkedListNode *tail;
    unsigned size;

    void (*destructor)(void *);
} LinkedList;

LinkedList *LinkedList_new(void(*)(void *));

void LinkedList_free(LinkedList **);

void LinkedList_add_last(LinkedList *, void *);

void *LinkedList_remove_last(LinkedList *);

void *LinkedList_remove(LinkedList *, unsigned);

#endif //DSA_FROM_SCRATCH_LINKEDLIST_H
