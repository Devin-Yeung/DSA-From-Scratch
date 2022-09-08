#include <benchmark/benchmark.h>

extern "C" {
#include <Types/Integer.h>
#include <Array/LinkedList.h>
#include <Array/DoublyLinkedList.h>
}

static void BM_LinkedList_remove_last(benchmark::State &state) {
    auto ll = LinkedList_new(int_destructor);
    // prepare ll
    for (int i = 0; i < state.range(0); i++) {
        LinkedList_add_last(ll, int_new(i));
    }
    for (auto _: state) {
        for (unsigned i = 0; i < ll->size; i++) {
            auto x = (Integer *) LinkedList_remove_last(ll);
            int_destructor(x);
        }
    }
    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(state.range(0)));
    LinkedList_free(&ll);
}


static void BM_DoublyLinkedList_remove_last(benchmark::State &state) {
    auto dll = DoublyLinkedList_new(int_destructor);
    // prepare ll
    for (int i = 0; i < state.range(0); i++) {
        DoublyLinkedList_add_last(dll, int_new(i));
    }
    for (auto _: state) {
        for (unsigned i = 0; i < dll->size; i++) {
            auto x = (Integer *) DoublyLinkedList_remove_last(dll);
            int_destructor(x);
        }
    }
    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(state.range(0)));
    DoublyLinkedList_free(&dll);
}

BENCHMARK(BM_LinkedList_remove_last)->RangeMultiplier(2)->Range(1024, 1024 << 7);
BENCHMARK(BM_DoublyLinkedList_remove_last)->RangeMultiplier(2)->Range(1024, 1024 << 7);
