// Copyright 2024 Polina Pozdnova

#include <gtest/gtest.h>
#include "..\algorithms\algorithms.h"

#define TEST_ALGORITHMS
#ifdef TEST_ALGORITHMS

TEST(TestCheckBreckets, simple_true_string) {
    // Arrange
    std::string str = "()()";

    // Act & Assert
    EXPECT_EQ(true, check_breckets(str));
}

TEST(TestCheckBreckets, complex_true_string) {
    // Arrange
    std::string str = "[(()())(())]";

    // Act & Assert
    EXPECT_EQ(true, check_breckets(str));
}

TEST(TestCheckBreckets, false_when_one_parenthesis_without_closing_pair) {
    // Arrange
    std::string str = "(()()";

    // Act & Assert
    EXPECT_EQ(false, check_breckets(str));
}

TEST(TestCheckBreckets, false_when_one_parenthesis_without_opening_pair) {
    // Arrange
    std::string str = "())(())";

    // Act & Assert
    EXPECT_EQ(false, check_breckets(str));
}

TEST(TestCheckBreckets, false_when_types_of_brackets_do_not_match) {
    // Arrange
    std::string str = "({)}";

    // Act & Assert
    EXPECT_EQ(false, check_breckets(str));
}


#endif //TEST_ALGORITHMS