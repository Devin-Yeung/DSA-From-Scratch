#include <gtest/gtest.h>

extern "C" {
#include <Types/Integer.h>
#include <Stack/LinkedStack.h>
}

TEST(LinkedStack, TestPopPush) {
    auto st = LinkedStack_new(int_destructor);
    for (int i = 0; i <= 1e5; i++) {
        LinkedStack_push(st, int_new(i));
    }
    for (int i = 1e5; i >= 0; i--) {
        auto num = (Integer *) LinkedStack_pop(st);
        EXPECT_EQ(num->val, i);
        int_destructor(num);
    }
    LinkedList_free(&st);
    EXPECT_EQ(st, nullptr);
}

TEST(LinkedListBasic, TestPeek) {
    auto st = LinkedStack_new(int_destructor);
    for (int i = 0; i <= 1e5; i++) {
        LinkedStack_push(st, int_new(i));
        auto num = (Integer *) LinkedStack_peek(st);
        EXPECT_EQ(num->val, i);
    }
    LinkedList_free(&st);
    EXPECT_EQ(st, nullptr);
}
