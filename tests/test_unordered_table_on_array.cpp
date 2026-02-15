// Copyright 2026 Polina Pozdnova

#include <gtest/gtest.h>
#include "..\lib_unordered_table_on_array\unordered_table_on_array.h"

//#define TEST_UNORDERED_TABLE_ON_ARRAY
#ifdef TEST_UNORDERED_TABLE_ON_ARRAY

TEST(TestUnorderedTableOnArray, check_the_insert_after_erase) {
    UnsortedTableOnArr<int, std::string> t1, t2;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");
    t1.erase(2);
    t1.insert(4, "Fourth");

    t2.insert(1, "First");
    t2.insert(3, "Third");
    t2.insert(4, "Fourth");

    //std::cout << t1 << t2;

    EXPECT_EQ(t1, t2);
}

TEST(TestUnorderedTableOnArray, check_the_unsorted) {
    UnsortedTableOnArr<int, std::string> t1, t2;

    t1.insert(1, "First");
    t1.insert(2, "Second");

    t2.insert(2, "Second");
    t2.insert(1, "First");

    //std::cout << t1 << t2;

    EXPECT_EQ(t1, t2);
}

TEST(TestUnorderedTableOnArray, check_the_erase) {
    UnsortedTableOnArr<int, std::string> t1, t2;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");
    t1.erase(1);
    t1.erase(2);
    t1.erase(3);

    //std::cout << t1 << t2;

    EXPECT_EQ(t1, t2);
}

TEST(TestUnorderedTableOnArray, the_exception_is_when_deleting_by_a_key_that_does_not_exist) {
    UnsortedTableOnArr<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.erase(5));
}

TEST(TestUnorderedTableOnArray, check_the_key_find) {
    UnsortedTableOnArr<std::string, std::string> t1;

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    //std::cout << t1;

    EXPECT_EQ(t1.find("r974"), "when");
}

TEST(TestUnorderedTableOnArray, the_exception_is_when_the_key_is_not_found) {
    UnsortedTableOnArr<std::string, std::string> t1;

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.find("r1024"));
}

TEST(TestUnorderedTableOnArray, check_an_empty_table) {
    UnsortedTableOnArr<double, std::string> t1;

    t1.insert(1.5, "it is double");
    t1.erase(1.5);

    //std::cout << t1;

    EXPECT_TRUE(t1.is_empty());
}

TEST(TestUnorderedTableOnArray, check_a_non_empty_table) {
    UnsortedTableOnArr<double, std::string> t1;

    t1.insert(1.5, "it is double");

    //std::cout << t1;

    EXPECT_FALSE(t1.is_empty());
}

#endif //TEST_UNORDERED_TABLE_ON_ARRAY