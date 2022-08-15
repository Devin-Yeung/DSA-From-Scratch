#ifndef ALGO_INTEGER_H
#define ALGO_INTEGER_H


typedef struct Integer {
    int val;
} Integer;


Integer *int_new(int val);

void int_destructor(void *obj);

int int_comparator(void *a, void *b);

void int_print(void *obj);


#endif //ALGO_INTEGER_H
