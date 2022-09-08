#include <Array/LinkedList.h>
#include <stdlib.h>


LinkedList *LinkedList_new(void(*destructor)(void *)) {
    LinkedList *ll = malloc(sizeof(LinkedList));

    LinkedListNode *dummy_head = malloc(sizeof(LinkedListNode));
    dummy_head->data = NULL;
    dummy_head->next = NULL;

    ll->dummy_head = dummy_head;
    ll->tail = dummy_head;
    ll->size = 0;
    ll->destructor = destructor;

    return ll;
}

void LinkedList_free(LinkedList **ll) {
    void (*destructor)(void *) = (*ll)->destructor;
    LinkedListNode *cur = (*ll)->dummy_head;
    while (cur != NULL) {
        // free the data
        free(cur->data);
        LinkedListNode *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(*ll);
    (*ll) = NULL;
}

void LinkedList_add_last(LinkedList *ll, void *data) {
    LinkedListNode *node = malloc(sizeof(LinkedListNode));
    node->data = data;
    node->next = NULL;

    ll->tail->next = node;
    ll->tail = node;
    ll->size += 1;
}

/**
 * SAFETY: the caller is responsible to free
 * the object that callee returns
 * @param ll the linked-list
 * @param index the index of elem to be removed
 * @return the been removed
 */
void *LinkedList_remove(LinkedList *ll, unsigned index) {
    if (index >= ll->size) {
        // TODO: Error Handling
        return NULL;
    }
    // prev -> to_be_removed -> next
    LinkedListNode *prev = ll->dummy_head;
    for (unsigned i = 0; i < index; i++) {
        prev = prev->next;
    }
    LinkedListNode *to_be_removed = prev->next;
    prev->next = to_be_removed->next;
    void *data = to_be_removed->data;
    free(to_be_removed);
    ll->size -= 1;
    return data;
}

/**
 * SAFETY: the caller is responsible to free
 * the object that callee returns
 * @param ll the linked-list
 * @return the data been removed
 */
void *LinkedList_remove_last(LinkedList *ll) {
    return LinkedList_remove(ll, ll->size - 1);
}
