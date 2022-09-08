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
