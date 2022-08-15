#include <stdlib.h>
#include <stdio.h>
#include <Types/Integer.h>

Integer *int_new(int val) {
    Integer *res = malloc(sizeof(Integer));
    res->val = val;
    return res;
}

void int_destructor(void *obj) {
    free(obj);
}

int int_comparator(void *a, void *b) {
    return ((Integer *) a)->val - ((Integer *) b)->val;
}

void int_print(void *obj) {
    Integer *i = (Integer *) obj;
    printf("%d ", i->val);
}
