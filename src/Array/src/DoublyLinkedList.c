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

/**
 * SAFETY: the caller SHOULD NOT free the resource
 * that callee returns, the doubly-linked-list still
 * take its ownership
 * @param dll the doubly-linked-list
 * @param index the index of element you want to get
 * @return
 */
void *DoublyLinkedList_get(DoublyLinkedList *dll, unsigned index) {
    unsigned i = 0;
    if (index <= (dll->size / 2)) {
        DoublyLinkedListNode *cur = dll->head->next;
        while (i < index) {
            cur = cur->next;
            i += 1;
        }
        return cur->data;
    } else {
        DoublyLinkedListNode *cur = dll->tail->prev;
        index = (dll->size - index - 1);
        while (i < index) {
            cur = cur->prev;
            i += 1;
        }
        return cur->data;
    }
}

void DoublyLinkedList_add_last(DoublyLinkedList *dll, void *elem) {
    DoublyLinkedListNode *new_node = malloc(sizeof(DoublyLinkedListNode));
    // move the ownership of elem
    new_node->data = elem;

    DoublyLinkedListNode *front = dll->tail->prev;
    DoublyLinkedListNode *back = dll->tail;

    // front -> new_node
    front->next = new_node;
    // front <- new_node
    new_node->prev = front;
    // new_node <- back
    back->prev = new_node;
    // new_node -> back
    new_node->next = back;
    // front <-> new_node <-> back
    dll->size += 1;
}

void DoublyLinkedList_add_first(DoublyLinkedList *dll, void *elem) {
    DoublyLinkedListNode *new_node = malloc(sizeof(DoublyLinkedListNode));
    // move the ownership of elem
    new_node->data = elem;

    DoublyLinkedListNode *front = dll->head;
    DoublyLinkedListNode *back = dll->head->next;

    // front -> new_node
    front->next = new_node;
    // front <- new_node
    new_node->prev = front;
    // new_node <- back
    back->prev = new_node;
    // new_node -> back
    new_node->next = back;
    // front <-> new_node <-> back
    dll->size += 1;
}

/**
 * SAFETY: the caller is responsible to free the data
 * that callee returns
 * @param dll the doubly-linked-list
 * @return
 */
void *DoublyLinkedList_remove_last(DoublyLinkedList *dll) {
    if (dll == NULL || dll->size == 0) {
        // TODO: error handling
        return NULL;
    }

    // Our Target:
    // front <-> x <-> dummy_tail
    // front <-> dummy_tail
    DoublyLinkedListNode *to_be_removed = dll->tail->prev;
    DoublyLinkedListNode *front = front = to_be_removed->prev;

    // front <- dummy_tail
    dll->tail->prev = front;
    // front -> dummy_tail
    front->next = dll->tail;
    // take the data and free the node
    void *data = to_be_removed->data;
    free(to_be_removed);
    dll->size -= 1;
    return data;
}

void *DoublyLinkedList_remove_first(DoublyLinkedList *dll) {
    if (dll == NULL || dll->size == 0) {
        // TODO: error handling
        return NULL;
    }

    // Our Target:
    // dummy_head <-> to_be_removed <-> back
    // dummy_head <-> back
    DoublyLinkedListNode *to_be_removed = dll->head->next;
    DoublyLinkedListNode *back = to_be_removed->next;

    // dummy_head -> back
    dll->head->next = back;
    // dummy_head <- back
    back->prev = dll->head;
    // take the data and free the node
    void *data = to_be_removed->data;
    free(to_be_removed);
    dll->size -= 1;
    return data;
}