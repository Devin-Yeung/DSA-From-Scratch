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
        LinkedList_add(ll, int_new(i));
    }
    LinkedList_free(&ll);
    EXPECT_EQ(ll, nullptr);
}
