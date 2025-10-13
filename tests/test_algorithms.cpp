// Copyright 2024 Polina Pozdnova

#include <gtest/gtest.h>
#include "..\lib_algorithms\algorithms.h"

//#define TEST_ALGORITHMS
#ifdef TEST_ALGORITHMS

TEST(TestAlgorithms, throw_error_when_index_row_out_of_range) {
    // Arrange
    Matrix<int> mat1 = {
            {1, 2},
            {1, 2}
    };

    // Act & Assert
    ASSERT_ANY_THROW(find_local_minimum_of_the_matrix(mat1, -1, 0));
}

TEST(TestAlgorithms, throw_error_when_index_column_out_of_range) {
    // Arrange
    Matrix<int> mat1 = {
            {1, 2},
            {1, 2}
    };

    // Act & Assert
    ASSERT_ANY_THROW(find_local_minimum_of_the_matrix(mat1, 0, 5));
}

TEST(TestAlgorithms, first_local_minimum_matrix_3x3) {
    // Arrange
    Matrix<int> mat1 = {
        {3, 2, 1},
        {5, 8, 4},
        {7, 6, 9}
    };

    // Act & Assert
    EXPECT_EQ(find_local_minimum_of_the_matrix(mat1, 2, 0), find_local_minimum_of_the_matrix(mat1, 0, 0)); // = 1
}

TEST(TestAlgorithms, second_local_minimum_matrix_3x3) {
    // Arrange
    Matrix<int> mat1 = {
        {3, 2, 1},
        {5, 8, 4},
        {7, 6, 9}
    };

    // Act & Assert
    EXPECT_EQ(6, find_local_minimum_of_the_matrix(mat1, 2, 1));
}

TEST(TestAlgorithms, first_local_minimum_matrix_4x4) {
    // Arrange
    Matrix<int> mat1 = {
        { 11, 15, 10, 9 },
        { 6, 16, 3, 8 },
        { 7, 4, 2, 13 },
        { 14, 12, 1, 5 }
    };

    // Act & Assert
    EXPECT_EQ(6, find_local_minimum_of_the_matrix(mat1, 0, 0));
}

TEST(TestAlgorithms, second_local_minimum_matrix_4x4) {
    // Arrange
    Matrix<int> mat1 = {
        { 11, 15, 10, 9 },
        { 6, 16, 3, 8 },
        { 7, 4, 2, 13 },
        { 14, 12, 1, 5 }
    };

    // Act & Assert
    EXPECT_EQ(1, find_local_minimum_of_the_matrix(mat1, 2, 0));
}

TEST(TestAlgorithms, bad_variant_for_the_algorithm) {
    // Arrange
    Matrix<double> mat1 = {
        { 16.5, 15.5, 14.5 },
        { 20.5, 20.5, 13.5 },
        { 10.5, 11.5, 12.5 },
    };

    // Act & Assert
    EXPECT_EQ(10.5, find_local_minimum_of_the_matrix(mat1, 0, 0));
}

#endif // TEST_ALGORITHMS