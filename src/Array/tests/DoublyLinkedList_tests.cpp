#include <gtest/gtest.h>

extern "C" {
#include <Array/DoublyLinkedList.h>
#include <Types/Integer.h>
}

TEST(DoublyLinkedListBasic, TestConstructor) {
    auto dll = DoublyLinkedList_new(int_destructor);
    DoublyLinkedList_free(&dll);
    EXPECT_EQ(dll, nullptr);
}

TEST(DoublyLinkedListBasic, TestDestructor) {
    // Please check mem leak in sanitizer
    auto dll = DoublyLinkedList_new(int_destructor);
    for (int i = 0; i < 1e5; i++) {
        DoublyLinkedList_add_last(dll, int_new(i));
    }
    DoublyLinkedList_free(&dll);
    EXPECT_EQ(dll, nullptr);
}

TEST(DoublyLinkedListBasic, TestGet) {
    auto dll = DoublyLinkedList_new(int_destructor);

    for (int i = 0; i < 100; i++) {
        DoublyLinkedList_add_last(dll, int_new(i));
    }
    for (int i = 0; i < 100; i++) {
        auto num = (Integer *) DoublyLinkedList_get(dll, i);
        EXPECT_EQ(num->val, i);
    }
    DoublyLinkedList_free(&dll);
    EXPECT_EQ(dll, nullptr);
}

TEST(DoublyLinkedListBasic, TestAddFirst) {
    auto dll = DoublyLinkedList_new(int_destructor);

    for (int i = 0; i <= 100; i++) {
        DoublyLinkedList_add_first(dll, int_new(i));
        auto num = (Integer *) DoublyLinkedList_get(dll, 0);
        EXPECT_EQ(num->val, i);
        EXPECT_EQ(dll->size, i + 1);
    }
    DoublyLinkedList_free(&dll);
    EXPECT_EQ(dll, nullptr);
}


TEST(DoublyLinkedListBasic, TestRemoveLast) {
    auto dll = DoublyLinkedList_new(int_destructor);

    // remove an empty list
    auto res = DoublyLinkedList_remove_last(dll);
    EXPECT_EQ(res, nullptr);

    // simple elems test
    for (int i = 0; i <= 100; i++) {
        DoublyLinkedList_add_last(dll, int_new(i));
    }
    for(int i = 100; i >= 0; i--){
        auto num =(Integer*)DoublyLinkedList_remove_last(dll);
        EXPECT_EQ(num->val, i);
        int_destructor(num);
    }
    EXPECT_EQ(dll->size, 0);
    DoublyLinkedList_free(&dll);
    EXPECT_EQ(dll, nullptr);
}

TEST(DoublyLinkedListBasic, TestRemoveFirst) {
    auto dll = DoublyLinkedList_new(int_destructor);

    // remove an empty list
    auto res = DoublyLinkedList_remove_first(dll);
    EXPECT_EQ(res, nullptr);

    // simple elems test
    for (int i = 0; i <= 100; i++) {
        DoublyLinkedList_add_last(dll, int_new(i));
    }
    for(int i = 0; i <= 100; i++){
        auto num =(Integer*)DoublyLinkedList_remove_first(dll);
        EXPECT_EQ(num->val, i);
        int_destructor(num);
    }
    EXPECT_EQ(dll->size, 0);
    DoublyLinkedList_free(&dll);
    EXPECT_EQ(dll, nullptr);
}

