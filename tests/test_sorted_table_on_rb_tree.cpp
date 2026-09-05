// Copyright 2026 Polina Pozdnova

#include "..\lib_sorted_table_on_rb_tree\sorted_table_on_rb_tree.h"
#include <gtest/gtest.h>

//#define TEST_SORTED_TABLE_ON_RB_TREE
#ifdef TEST_SORTED_TABLE_ON_RB_TREE

TEST(TestSortedTableOnRBTree, the_exception_is_when_insert_not_a_unique_key) {
    SortedTableOnRBTree<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.insert(3, "Third"));
}

TEST(TestSortedTableOnRBTree, check_the_insert_after_erase) {
    SortedTableOnRBTree<int, std::string> t1;

    t1.insert(3, "Third");
    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.erase(2);
    t1.insert(4, "Fourth");

    //std::cout << t1;

    EXPECT_EQ(t1.find(4), "Fourth");
}

TEST(TestSortedTableOnRBTree, check_the_erase) {
    SortedTableOnRBTree<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");
    t1.erase(1);

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.find(1));
}

TEST(TestSortedTableOnRBTree, the_exception_is_when_deleting_by_a_key_that_does_not_exist) {
    SortedTableOnRBTree<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.erase(5));
}

TEST(TestSortedTableOnRBTree, check_the_table_for_sorting) {
    SortedTableOnRBTree<std::string, std::string> t1;

    t1.insert("pos3", "Third");
    t1.insert("pos2", "Second");
    t1.insert("pos1", "First");

    std::cout << t1;

    EXPECT_EQ(t1.find("pos3"), "Third");
}

TEST(TestSortedTableOnRBTree, check_the_key_find) {
    SortedTableOnRBTree<std::string, std::string> t1;

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    //std::cout << t1;

    EXPECT_EQ(t1.find("r974"), "when");
}

TEST(TestSortedTableOnRBTree, the_exception_is_when_the_key_is_not_found) {
    SortedTableOnRBTree<std::string, std::string> t1;

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.find("r1024"));
}

TEST(TestSortedTableOnRBTree, check_an_empty_table) {
    SortedTableOnRBTree<double, std::string> t1;

    t1.insert(1.5, "it is double");
    t1.insert(3.7, "it is double too");

    EXPECT_FALSE(t1.is_empty());

    t1.erase(1.5);
    t1.erase(3.7);

    //std::cout << t1;

    EXPECT_TRUE(t1.is_empty());
}

#endif //TEST_SORTED_TABLE_ON_RB_TREE