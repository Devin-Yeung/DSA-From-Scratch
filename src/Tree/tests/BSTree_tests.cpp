#include <gtest/gtest.h>

extern "C" {
#include <Types/Integer.h>
#include <Tree/BinaryTree.h>
}

TEST(BSTBasic, TestConstructor) {
    BSTree *bst = BSTree_new(int_destructor, int_comparator);
    EXPECT_EQ(0, bst->size);
    BSTree_free(&bst);
}

TEST(BSTBasic, TestDestructor) {
    BSTree *bst = BSTree_new(int_destructor, int_comparator);
    BSTree_free(&bst);
    EXPECT_EQ(bst, nullptr);
}

TEST(BSTBasic, TestAdd) {
    BSTree *bst = BSTree_new(int_destructor, int_comparator);
    for(int i = 0; i < 1e4; i++) {
        Integer* integer = int_new(i);
        BSTree_add(bst,integer);
    }
    EXPECT_EQ(bst->size, 1e4);
    BSTree_free(&bst);
}
