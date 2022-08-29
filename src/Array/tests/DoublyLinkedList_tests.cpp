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