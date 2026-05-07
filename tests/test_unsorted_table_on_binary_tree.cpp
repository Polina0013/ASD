// Copyright 2026 Polina Pozdnova

#include <gtest/gtest.h>
#include "..\lib_unsorted_table_on_binary_tree\unsorted_table_on_binary_tree.h"

//#define TEST_UNSORTED_TABLE_ON_BINARY_TREE
#ifdef TEST_UNSORTED_TABLE_ON_BINARY_TREE

TEST(TestUnsortedTableOnBinaryTree, the_exception_is_when_insert_not_a_unique_key) {
    UnsortedTableOnBinaryTree<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.insert(3, "Third"));
}

TEST(TestUnsortedTableOnBinaryTree, check_the_insert_after_erase) {
    UnsortedTableOnBinaryTree<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");
    t1.erase(2);
    t1.insert(4, "Fourth");

    //std::cout << t1;

    EXPECT_EQ(t1.find(4), "Fourth");
}

TEST(TestUnsortedTableOnBinaryTree, check_the_erase) {
    UnsortedTableOnBinaryTree<int, std::string> t1;

    t1.insert(5, "Five");
    t1.insert(1, "First");
    t1.insert(3, "Third");
    t1.insert(7, "Seven");
    t1.insert(2, "Second");
    t1.insert(4, "Four");

    t1.erase(7);
    EXPECT_ANY_THROW(t1.find(7));

    t1.erase(5);
    EXPECT_ANY_THROW(t1.find(5));

    std::string s = t1.find(2) + t1.find(1) + t1.find(3) + t1.find(4);
    EXPECT_EQ(s, "SecondFirstThirdFour");
}

TEST(TestUnsortedTableOnBinaryTree, the_exception_is_when_deleting_by_a_key_that_does_not_exist) {
    UnsortedTableOnBinaryTree<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.erase(5));
}

TEST(TestUnsortedTableOnBinaryTree, check_the_key_find) {
    UnsortedTableOnBinaryTree<std::string, std::string> t1;

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    //std::cout << t1;

    EXPECT_EQ(t1.find("r974"), "when");
}

TEST(TestUnsortedTableOnBinaryTree, the_exception_is_when_the_key_is_not_found) {
    UnsortedTableOnBinaryTree<std::string, std::string> t1;

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.find("r1024"));
}

TEST(TestUnsortedTableOnBinaryTree, check_an_empty_table) {
    UnsortedTableOnBinaryTree<double, std::string> t1;

    t1.insert(1.5, "it is double");
    t1.erase(1.5);

    //std::cout << t1;

    EXPECT_TRUE(t1.is_empty());
}

TEST(TestUnsortedTableOnBinaryTree, check_a_non_empty_table) {
    UnsortedTableOnBinaryTree<double, std::string> t1;

    t1.insert(1.5, "it is double");

    //std::cout << t1;

    EXPECT_FALSE(t1.is_empty());
}

#endif //TEST_UNSORTED_TABLE_ON_BINARY_TREE