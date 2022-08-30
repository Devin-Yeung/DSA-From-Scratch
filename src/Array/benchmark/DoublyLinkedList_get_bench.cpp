#include <benchmark/benchmark.h>


extern "C" {
#include <Array/DoublyLinkedList.h>
#include <Types/Integer.h>
}

static void BM_DoublyLinkedList_get(benchmark::State &state) {
    auto dll = DoublyLinkedList_new(int_destructor);
    // prepare dll
    for (int i = 0; i < state.range(0); i++) {
        DoublyLinkedList_add_last(dll, int_new(i));
    }
    int end = state.range(0);
    for (auto _: state) {
        for (int i = 0; i < end; i += 2) {
            DoublyLinkedList_get(dll, i);
        }
    }
    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(state.range(0)));
    DoublyLinkedList_free(&dll);
}

BENCHMARK(BM_DoublyLinkedList_get)->RangeMultiplier(2)->Range(8, 8 << 10);


static void BM_DoublyLinkedList_get_first_half_only(benchmark::State &state) {
    auto dll = DoublyLinkedList_new(int_destructor);
    // prepare dll
    for (int i = 0; i < state.range(0); i++) {
        DoublyLinkedList_add_last(dll, int_new(i));
    }
    int half = state.range(0) / 2;
    for (auto _: state) {
        for (int i = 0; i < half; i++) {
            DoublyLinkedList_get(dll, i);
        }
    }
    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(state.range(0)));
    DoublyLinkedList_free(&dll);
}

BENCHMARK(BM_DoublyLinkedList_get_first_half_only)->RangeMultiplier(2)->Range(8, 8 << 10);


static void BM_DoublyLinkedList_get_second_half_only(benchmark::State &state) {
    auto dll = DoublyLinkedList_new(int_destructor);
    // prepare dll
    for (int i = 0; i < state.range(0); i++) {
        DoublyLinkedList_add_last(dll, int_new(i));
    }
    int half = state.range(0) / 2;
    int end = state.range(0);
    for (auto _: state) {
        for (int i = half; i < end; i++) {
            DoublyLinkedList_get(dll, i);
        }
    }
    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(state.range(0)));
    DoublyLinkedList_free(&dll);
}

BENCHMARK(BM_DoublyLinkedList_get_second_half_only)->RangeMultiplier(2)->Range(8, 8 << 10);

BENCHMARK_MAIN();