#include <Array/DoublyLinkedList.h>

#ifndef DSA_FROM_SCRATCH_STACK_H
#define DSA_FROM_SCRATCH_STACK_H

typedef struct LinkedStack {
    DoublyLinkedList *stack;
} LinkedStack;

LinkedStack *LinkedStack_new(void (*)(void *));

void LinkedList_free(LinkedStack **);

void *LinkedStack_peek(LinkedStack *);

void LinkedStack_push(LinkedStack *, void *);

void *LinkedStack_pop(LinkedStack *);

#endif //DSA_FROM_SCRATCH_STACK_H
