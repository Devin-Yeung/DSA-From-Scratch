#ifndef ALGO_ARRAY_LIST_H
#define ALGO_ARRAY_LIST_H

// the default capacity of the initial arraylist
#define DEFAULT_CAPACITY 10

typedef struct ArrayList {
    unsigned int capacity;
    unsigned int size;
    void **elem_data;

    void (*destructor)(void *);
} ArrayList;

ArrayList *ArrayList_new(void(*)(void *));

void ArrayList_free(ArrayList **);

void ArrayList_add(ArrayList *, unsigned, void *);

void ArrayList_add_last(ArrayList *, void *);

void *ArrayList_get(ArrayList *, unsigned);

void *ArrayList_remove(ArrayList *, unsigned);

void *ArrayList_remove_last(ArrayList *);

void *ArrayList_set(ArrayList *, unsigned, void *);

unsigned ArrayList_new_capacity(ArrayList *arr, unsigned min_capacity);

void ArrayList_grow(ArrayList *arr, unsigned min_capacity);

#endif
