#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Array/ArrayList.h>


/**
 * Returns a capacity at least as large as the given minimum capacity.
 * Returns the current capacity increased by 50% if that suffices.
 * Will not return a capacity greater than MAX_ARRAY_SIZE unless
 * the given minimum capacity is greater than MAX_ARRAY_SIZE.
 *
 * @param min_capacity the desired minimum capacity
 */

unsigned ArrayList_new_capacity(ArrayList *arr, unsigned min_capacity) {
    int old_capacity = arr->capacity;
    // new capacity = 1.5 old capacity
    int new_capacity = old_capacity + (old_capacity >> 1);
    // when the old capacity is 0,
    // the new capacity will always be 0
    if (arr->capacity == 0) {
        return min_capacity > DEFAULT_CAPACITY ? min_capacity : DEFAULT_CAPACITY;
    }
    return new_capacity > min_capacity ? new_capacity : min_capacity;
}


/**
 * Increases the capacity to ensure that it can hold at least the
 * number of elements specified by the minimum capacity argument.
 *
 * @param min_capacity the desired minimum capacity
 */
void ArrayList_grow(ArrayList *arr, unsigned min_capacity) {
    int new_capacity = ArrayList_new_capacity(arr, min_capacity);
    void **old_elem_data = arr->elem_data;
    arr->elem_data = malloc(new_capacity * sizeof(void *));
    // memory set & copy
    // memset(arr->elem_data, 0, new_capacity * sizeof(void *));
    memcpy(arr->elem_data, old_elem_data, arr->capacity * sizeof(void *));
    free(old_elem_data);
    // reset the new capacity
    arr->capacity = new_capacity;
}


ArrayList *ArrayList_new(void(*destructor)(void *)) {
    if (destructor == NULL) {
        // TODO: error handling
        return NULL;
    }
    ArrayList *al = malloc(sizeof(ArrayList));
    al->capacity = DEFAULT_CAPACITY;
    al->size = 0;
    al->elem_data = malloc(DEFAULT_CAPACITY * sizeof(void *));
    al->destructor = destructor;
    return al;
}

/**
 * Inserts the specified element at the specified position in this
 * list. Shifts the element currently at that position (if any) and
 * any subsequent elements to the right (adds one to their indices).
 *
 * @param index index at which the specified element is to be inserted
 * @param element element to be inserted
 */
void ArrayList_add(ArrayList *arr, unsigned int index, void *element) {
    unsigned size = arr->size;
    // boundary check
    if (index > size) {
        // TODO error handling
        fprintf(stderr, "Index out of bound!");
    }
    // Array Expansion
    if (arr->capacity < size + 1) {
        ArrayList_grow(arr, size + 1);
    }

    memcpy(&arr->elem_data[index + 1], &arr->elem_data[index], (size - index) * sizeof(void *));
    arr->elem_data[index] = element;

    // increment the size
    arr->size += 1;
}


void ArrayList_add_last(ArrayList *arr, void *elem) {
    ArrayList_add(arr, arr->size, elem);
}


/**
 * SAFETY:
 * the caller does not have the ownership of the object
 * that the function returns, which means the caller
 * should NOT free that object
 *
 * @param arr
 * @param index
 * @return
 */
void *ArrayList_get(ArrayList *arr, unsigned index) {
    if (index > arr->size) {
        // TODO error handling
        fprintf(stderr, "Index out of bound!\n");
    }
    return arr->elem_data[index];
}


/**
 * SAFETY:
 * this function transfer the ownership of resource
 * to the caller, which means caller is responsible
 * to free the object
 * @param arr
 * @param index
 * @return
 */
void *ArrayList_remove(ArrayList *arr, unsigned index) {
    unsigned size = arr->size;
    // boundary check
    if (index > size) {
        // TODO error handling
        fprintf(stderr, "Index out of bound!\n");
    }
    // TODO: Shrink Array

    // special case: remove the last elem
    if (index != arr->size - 1) {
        memcpy(&arr->elem_data[index], &arr->elem_data[index + 1], (size - index) * sizeof(void *));
    }

    // decrement the size
    arr->size -= 1;
    return arr->elem_data[arr->size - 1];
}

/**
 * SAFETY:
 * this function transfer the ownership of resource
 * to the caller, which means caller is responsible
 * to free the object
 * @param arr
 * @return
 */
void *ArrayList_remove_last(ArrayList *arr) {
    if (arr->size == 0) {
        // TODO: error handling
        fprintf(stderr, "No elements in the ArrayList\n");
        return NULL;
    }
    // decrement the size
    arr->size -= 1;
    return arr->elem_data[arr->size - 1];
}

/**
 * SAFETY:
 * the caller does not have the ownership of the elem
 * that the function returns, which means the caller
 * should NOT free that object
 *
 * @param arr
 * @param index
 * @param elem
 * @return
 */
void *ArrayList_set(ArrayList *arr, unsigned index, void *elem) {
    ArrayList *cur = ArrayList_get(arr, index);
    if (elem != cur) {
        arr->destructor(cur);
        arr->elem_data[index] = elem;
    }
    return elem;
}

void ArrayList_free(ArrayList **arr) {
    for (int i = 0; i < (*arr)->size; i++) {
        void **elem_data = (*arr)->elem_data;
        (*arr)->destructor(elem_data[i]);
    }
    free((*arr)->elem_data);
    free(*arr);
    *arr = NULL;
}
