#include <Array/DoublyLinkedList.h>
#include <stdlib.h>

DoublyLinkedList *DoublyLinkedList_new(void(*destructor)(void *)) {
    DoublyLinkedList *dll = malloc(sizeof(DoublyLinkedList));

    DoublyLinkedListNode *dummy_head = malloc(sizeof(DoublyLinkedListNode));
    DoublyLinkedListNode *dummy_tail = malloc(sizeof(DoublyLinkedListNode));

    dummy_head->data = NULL;
    dummy_head->next = dummy_tail;
    dummy_head->prev = NULL;

    dummy_tail->data = NULL;
    dummy_tail->next = NULL;
    dummy_tail->prev = dummy_head;

    dll->size = 0;
    dll->head = dummy_head;
    dll->tail = dummy_tail;
    dll->destructor = destructor;

    return dll;
}

void DoublyLinkedList_free(DoublyLinkedList **dll) {
    DoublyLinkedListNode *cur = (*dll)->head;
    do {
        DoublyLinkedListNode *next = cur->next;
        // destruct the data
        (*dll)->destructor(cur->data);
        free(cur);
        // advance the ptr
        cur = next;
    } while (cur != NULL);
    free(*dll);
    // reset dll
    *dll = NULL;
}
