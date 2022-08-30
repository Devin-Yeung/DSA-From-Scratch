#ifndef DSA_FROM_SCRATCH_DOUBLYLINKEDLIST_H
#define DSA_FROM_SCRATCH_DOUBLYLINKEDLIST_H

typedef struct DoublyLinkedListNode {
    void *data;
    struct DoublyLinkedListNode *next;
    struct DoublyLinkedListNode *prev;
} DoublyLinkedListNode;


typedef struct DoublyLinkedList {
    unsigned int size;
    DoublyLinkedListNode *head;
    DoublyLinkedListNode *tail;

    void (*destructor)(void *);
} DoublyLinkedList;

DoublyLinkedList *DoublyLinkedList_new(void(*destructor)(void *));

void DoublyLinkedList_free(DoublyLinkedList **);

void *DoublyLinkedList_get(DoublyLinkedList *, unsigned);

void DoublyLinkedList_add_last(DoublyLinkedList *, void *);

void DoublyLinkedList_add_first(DoublyLinkedList *, void *);

void *DoublyLinkedList_remove_last(DoublyLinkedList *);

void *DoublyLinkedList_remove_first(DoublyLinkedList *);

#endif //DSA_FROM_SCRATCH_DOUBLYLINKEDLIST_H
