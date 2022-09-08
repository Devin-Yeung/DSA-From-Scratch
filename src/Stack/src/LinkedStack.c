#include <Stack/LinkedStack.h>
#include <stdlib.h>

LinkedStack *LinkedStack_new(void (*destructor)(void *)){
    LinkedStack *st = malloc(sizeof(LinkedStack));
    st->stack = DoublyLinkedList_new(destructor);
    return st;
}

void LinkedList_free(LinkedStack **st){
    DoublyLinkedList_free(&(*st)->stack);
    free(*st);
    *st = NULL;
}

/**
 * SAFETY: the caller does not have the ownership
 * of data, which means the caller should not free the data;
 *
 * @param st stack
 * @return the data on the top of stack
 */
void *LinkedStack_peek(LinkedStack *st) {
    return st->stack->dummy_tail->prev->data;
}

/**
 * push data to the stack
 * @param st stack
 * @param data the data to be pushed
 */
void LinkedStack_push(LinkedStack *st, void *data) {
    DoublyLinkedList_add_last(st->stack, data);
}


/**
 * SAFETY: the caller is responsible to free the data
 * that callee returns
 * @param st stack
 * @return the data been pop
 */
void *LinkedStack_pop(LinkedStack *st) {
    return DoublyLinkedList_remove_last(st->stack);
}