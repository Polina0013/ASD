// Copyright 2026 Polina Pozdnova

#include <gtest/gtest.h>
#include "..\lib_skip_list\skip_list.h"

//#define TEST_SKIP_LIST
#ifdef TEST_SKIP_LIST

TEST(TestSkipList, check_the_print) {
    SkipList<int, std::string> list;

    list.insert(3, "three");
    list.print();
    list.insert(5, "five");
    list.print();
    list.insert(1, "one");
    list.print();
    list.insert(7, "seven");
    list.print();
    list.insert(9, "nine");
    list.print();
    list.insert(0, "zero");
    list.print();
    list.insert(11, "eleven");
    list.print();
    list.insert(6, "six");
    list.print();
}

TEST(TestSkipList, the_exception_is_when_the_keys_match) {
    SkipList<int, std::string> list;

    list.insert(3, "three");
    list.insert(1, "one");

    list.print();

    ASSERT_ANY_THROW(list.insert(3, "2three"););
}

#endif //TEST_SKIP_LIST