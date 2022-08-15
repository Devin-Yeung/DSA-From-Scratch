#include <gtest/gtest.h>

extern "C" {
#include <Types/Integer.h>
#include <Array/ArrayList.h>
}

TEST(ArrayListBasic, TestConstructor) {
    ArrayList *arr = ArrayList_new(int_destructor);
    EXPECT_EQ(arr->size, 0);
    EXPECT_EQ(arr->capacity, 10);
    ArrayList_add_last(arr, int_new(1));
    EXPECT_EQ(arr->size, 1);
    EXPECT_EQ(arr->capacity, 10);
    ArrayList_free(&arr);
}

TEST(ArrayListBasic, TestDestructor) {
    ArrayList *arr = ArrayList_new(int_destructor);
    for (int i = 0; i < 100; i++) {
        ArrayList_add_last(arr, int_new(i));
    }
    ArrayList_free(&arr);
    EXPECT_EQ(arr, nullptr);
}

TEST(ArrayListBasic, TestNewCapacity) {
    ArrayList *arr = ArrayList_new(int_destructor);
    EXPECT_EQ(ArrayList_new_capacity(arr, 11), 15);
    // reset size to 10
    arr->capacity = 10;
    EXPECT_EQ(ArrayList_new_capacity(arr, 16), 16);
    arr->capacity = 15;
    EXPECT_EQ(ArrayList_new_capacity(arr, 16), 22);
    ArrayList_free(&arr);
}

TEST(ArrayListBasic, TestGrow) {
    ArrayList *arr = ArrayList_new(int_destructor);
    for (int i = 0; i < 1e5; i++) {
        ArrayList_add_last(arr, int_new(i));
    }
    for (int i = 0; i < 1e5; i++) {
        Integer *a = (Integer *) ArrayList_get(arr, i);
        EXPECT_EQ(a->val, i);
    }
    ArrayList_free(&arr);
}

TEST(ArrayListBasic, TestAddAndGet) {
    ArrayList *arr = ArrayList_new(int_destructor);
    // Do not trigger grow in this case
    for (int i = 0; i < 9; i++) {
        ArrayList_add_last(arr, int_new(i));
    }
    for (int i = 0; i < 9; i++) {
        Integer val = *(Integer *) ArrayList_get(arr, i);
        EXPECT_EQ(val.val, i);
    }
    // Trigger the grow method
    for (int i = 9; i < 100; i++) {
        ArrayList_add_last(arr, int_new(i));
    }
    for (int i = 0; i < 100; i++) {
        Integer val = *(Integer *) ArrayList_get(arr, i);
        EXPECT_EQ(val.val, i);
    }
    ArrayList_free(&arr);
}

TEST(ArrayListBasic, TestRemoveLast) {
    ArrayList *arr = ArrayList_new(int_destructor);
    // Nothing in the Array

    testing::internal::CaptureStderr();
    EXPECT_EQ(ArrayList_remove_last(arr), nullptr);
    EXPECT_EQ(std::string("No elements in the ArrayList\n"),
              testing::internal::GetCapturedStderr());

    // Do not trigger grow in this case
    for (int i = 0; i < 9; i++) {
        ArrayList_add_last(arr, int_new(i));
    }
    for (int i = 9; i <= 0; i++) {
        Integer *val = (Integer *) ArrayList_remove_last(arr);
        EXPECT_EQ(val->val, i);
        int_destructor(val);
    }
    // Trigger the grow method
    for (int i = 0; i < 100; i++) {
        ArrayList_add_last(arr, int_new(i));
    }
    for (int i = 100; i <= 0; i++) {
        Integer *val = (Integer *) ArrayList_remove_last(arr);
        EXPECT_EQ(val->val, i);
        int_destructor(val);
    }


    for (int i = 0; i < 100; i++) {
        ArrayList_add_last(arr, int_new(i));
    }
    for (int i = 100; i <= 0; i++) {
        Integer *val = (Integer *) ArrayList_remove(arr, 0);
        EXPECT_EQ(val->val, i);
        int_destructor(val);
    }

    ArrayList_free(&arr);
}


TEST(ArrayListBasic, TestRemove) {
    ArrayList *arr = ArrayList_new(int_destructor);

    for (int i = 0; i < 100; i++) {
        ArrayList_add_last(arr, int_new(i));
    }
    for (int i = 100; i <= 0; i++) {
        Integer *val = (Integer *) ArrayList_remove(arr, 0);
        EXPECT_EQ(val->val, i);
        int_destructor(val);
    }
    ArrayList_free(&arr);
}

TEST(ArrayListBasic, TestRemoveLargeScale) {
    ArrayList *arr = ArrayList_new(int_destructor);

    for (int i = 0; i < 1e5; i++) {
        ArrayList_add_last(arr, int_new(i));
    }
    for (int i = 1e5; i <= 0; i++) {
        Integer *val = (Integer *) ArrayList_remove(arr, 0);
        EXPECT_EQ(val->val, i);
        int_destructor(val);
    }
    ArrayList_free(&arr);
}


TEST(ArrayListBasic, TestSet) {
    ArrayList *arr = ArrayList_new(int_destructor);

    for (int i = 0; i < 20; i++) {
        ArrayList_add_last(arr, int_new(i));
    }
    Integer *val = (Integer *) ArrayList_get(arr, 19);
    val->val += 1;
    ArrayList_set(arr, 19, val);
    val = (Integer *) ArrayList_get(arr, 19);
    EXPECT_EQ(val->val, 20);

    val = int_new(42);
    ArrayList_set(arr, 19, val);
    val = (Integer *) ArrayList_get(arr, 19);
    EXPECT_EQ(val->val, 42);
    ArrayList_free(&arr);
}
