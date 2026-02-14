// Copyright 2025 Polina Pozdnova

#include <gtest/gtest.h>
#include "..\lib_list\list.h"

//#define TEST_LIST
#ifdef TEST_LIST

TEST(TestList, default_constructor) {
    // Arrange
    List<int> l1, l2;

    // Act
    l1.push_back(2);
    l1.pop_front();

    // Assert
    EXPECT_EQ(l1, l2);
}

#endif // TEST_LIST