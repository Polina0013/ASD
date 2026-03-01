// Copyright 2026 Polina Pozdnova

#include <gtest/gtest.h>
#include "..\lib_sorted_table_on_vector\sorted_table_on_vector.h"

//#define TEST_SORTED_TABLE_ON_VECTOR
#ifdef TEST_SORTED_TABLE_ON_VECTOR

TEST(TestSortedTableOnVector, the_exception_is_when_insert_not_a_unique_key) {
    SortedTableOnVector<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.insert(3, "Third"));
}

TEST(TestSortedTableOnVector, check_the_insert_after_erase) {
    SortedTableOnVector<int, std::string> t1;

    t1.insert(3, "Third");
    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.erase(2);
    t1.insert(4, "Fourth");

    //std::cout << t1;

    EXPECT_EQ(t1.find(4), "Fourth");
}

TEST(TestSortedTableOnVector, check_the_erase) {
    SortedTableOnVector<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");
    t1.erase(1);

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.find(1));
}

TEST(TestSortedTableOnVector, the_exception_is_when_deleting_by_a_key_that_does_not_exist) {
    SortedTableOnVector<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.erase(5));
}

TEST(TestSortedTableOnVector, check_the_table_for_sorting) {
    SortedTableOnVector<std::string, std::string> t1;

    t1.insert("pos3", "Third");
    t1.insert("pos2", "Second");
    t1.insert("pos1", "First");

    //std::cout << t1;

    EXPECT_EQ(t1.find("pos3"), "Third");
}

TEST(TestSortedTableOnVector, check_the_key_find) {
    SortedTableOnVector<std::string, std::string> t1;

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    //std::cout << t1;

    EXPECT_EQ(t1.find("r974"), "when");
}

TEST(TestSortedTableOnVector, the_exception_is_when_the_key_is_not_found) {
    SortedTableOnVector<std::string, std::string> t1;

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.find("r1024"));
}

TEST(TestSortedTableOnVector, check_an_empty_table) {
    SortedTableOnVector<double, std::string> t1;

    t1.insert(1.5, "it is double");
    t1.erase(1.5);

    //std::cout << t1;

    EXPECT_TRUE(t1.is_empty());
}

TEST(TestSortedTableOnVector, check_a_non_empty_table) {
    SortedTableOnVector<double, std::string> t1;

    t1.insert(1.5, "it is double");

    //std::cout << t1;

    EXPECT_FALSE(t1.is_empty());
}

#endif //TEST_SORTED_TABLE_ON_VECTOR