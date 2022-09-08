#include <gtest/gtest.h>

extern "C" {
#include <Types/Integer.h>
#include <Array/LinkedList.h>
}

TEST(LinkedListBasic, TestConstructor) {
    auto ll = LinkedList_new(int_destructor);
    LinkedList_free(&ll);
    EXPECT_EQ(ll, nullptr);
}

TEST(LinkedListBasic, TestDestructor) {
    // Please check mem leak in sanitizer
    auto ll = LinkedList_new(int_destructor);
    for (int i = 0; i < 1e5; i++) {
        LinkedList_add_last(ll, int_new(i));
    }
    LinkedList_free(&ll);
    EXPECT_EQ(ll, nullptr);
}

TEST(LinkedListBasic, TestRemoveLast) {
    // Please check mem leak in sanitizer
    auto ll = LinkedList_new(int_destructor);
    for (int i = 0; i <= 2 << 12; i++) {
        LinkedList_add_last(ll, int_new(i));
    }
    for (int i = 2 << 12; i >= 0; i--) {
        auto num = (Integer*)LinkedList_remove_last(ll);
        EXPECT_EQ(num->val, i);
    }
    LinkedList_free(&ll);
    EXPECT_EQ(ll, nullptr);
}
