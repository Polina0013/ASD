// Copyright 2026 Polina Pozdnova

#include <gtest/gtest.h>
#include "..\lib_unsorted_table_on_list\unsorted_table_on_list.h"

//#define TEST_UNSORTED_TABLE_ON_LIST
#ifdef TEST_UNSORTED_TABLE_ON_LIST

TEST(TestUnsortedTableOnList, the_exception_is_when_insert_not_a_unique_key) {
    UnsortedTableOnList<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.insert(3, "Third"));
}

TEST(TestUnsortedTableOnList, check_the_insert_after_erase) {
    UnsortedTableOnList<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");
    t1.erase(2);
    t1.insert(4, "Fourth");

    //std::cout << t1;

    EXPECT_EQ(t1.find(4), "Fourth");
}

TEST(TestUnsortedTableOnList, check_the_erase) {
    UnsortedTableOnList<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");
    t1.erase(1);

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.find(1));
}

TEST(TestUnsortedTableOnList, the_exception_is_when_deleting_by_a_key_that_does_not_exist) {
    UnsortedTableOnList<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.erase(5));
}

TEST(TestUnsortedTableOnList, check_the_key_find) {
    UnsortedTableOnList<std::string, std::string> t1;

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    //std::cout << t1;

    EXPECT_EQ(t1.find("r974"), "when");
}

TEST(TestUnsortedTableOnList, the_exception_is_when_the_key_is_not_found) {
    UnsortedTableOnList<std::string, std::string> t1;

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    std::cout << t1;

    ASSERT_ANY_THROW(t1.find("r1024"));
}

TEST(TestUnsortedTableOnList, check_an_empty_table) {
    UnsortedTableOnList<double, std::string> t1;

    t1.insert(1.5, "it is double");
    t1.erase(1.5);

    //std::cout << t1;

    EXPECT_TRUE(t1.is_empty());
}

TEST(TestUnsortedTableOnList, check_a_non_empty_table) {
    UnsortedTableOnList<double, std::string> t1;

    t1.insert(1.5, "it is double");

    //std::cout << t1;

    EXPECT_FALSE(t1.is_empty());
}

#endif //TEST_UNSORTED_TABLE_ON_LIST