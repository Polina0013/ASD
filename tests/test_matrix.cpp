// Copyright 2024 Polina Pozdnova

#include <gtest/gtest.h>
#include "../lib_matrix/matrix.h"

#define TEST_MATRIX
#ifdef TEST_MATRIX

// Constructors //

TEST(TestMatrix, empty_constructor) {
    // Arrange
    Matrix<int> empty1, fake_empty(0, 0);

    // Act & Assert
    EXPECT_EQ(true, (empty1 == fake_empty));
}

TEST(TestMatrix, size_constructor) {
    // Arrange
    Matrix<int> mat1(10, 10), mat2(10, 10);

    // Act & Assert
    EXPECT_EQ(true, (mat1 == mat2));
}

TEST(TestMatrix, init_from_mathvector_constructor_and_initializer_list) {
    // Arrange
    MathVector<int> row1({ 1, 2, 3, 4, 5 });
    MathVector<int> row2({ 6, 7, 8, 9, 10 });

    MathVector<MathVector<int>> matrix;
    matrix.push_back(row1);
    matrix.push_back(row2);

    Matrix<int> mat1(matrix);
    Matrix<int> mat2 = {
        { 1, 2, 3, 4, 5 },
        { 6, 7, 8, 9, 10 }
    };

    // Act & Assert
    EXPECT_EQ(true, (mat1 == mat2));
}

TEST(TestMatrix, copy_constructor) {
    // Arrange
    Matrix<int> mat1 = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8}
    };

    // Act
    Matrix<int> mat2(mat1);

    // Assert
    EXPECT_EQ(true, (mat1 == mat2));
}

// Functions //

TEST(TestMatrix, throw_error_when_adding_matrices_of_different_sizes) {
    // Arrange
    Matrix<int>
    mvec1 = { 
        {1, 2, 3, 4, 5 },
        {1, 2, 3, 4, 5 }
    },

    mvec2 = {
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    };

    // Act & Assert
    ASSERT_ANY_THROW(mvec1+=mvec2);
}

TEST(TestMatrix, add) {
    // Arrange
    Matrix<int> mat1 = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8}
    }, mat2 = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8}
    }, result = {
        {2, 4},
        {6, 8},
        {10, 12},
        {14, 16}
    };

    // Act & Assert
    EXPECT_EQ(true, ((mat1 += mat2) == result));
}

TEST(TestMatrix, throw_error_when_subtracting_vectors_of_different_lengths) {
    // Arrange
    Matrix<int>
        mvec1 = {
            {1, 2, 3, 4, 5 },
            {1, 2, 3, 4, 5 }
    },

        mvec2 = {
            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    };

    // Act & Assert
    ASSERT_ANY_THROW(mvec1 -= mvec2);
}

TEST(TestMatrix, sub) {
    // Arrange
    Matrix<float> mat1 = {
        {1.1f, 2.2f},
        {3.1f, 4.2f},
        {5.1f, 6.2f},
        {7.1f, 8.2f}
    }, mat2 = {
        {1.0f, 2.0f},
        {3.0f, 4.0f},
        {5.0f, 6.0f},
        {7.0f, 8.0f}
    }, result = {
        {0.1f, 0.2f},
        {0.1f, 0.2f},
        {0.1f, 0.2f},
        {0.1f, 0.2f}
    };

    // Act & Assert
    EXPECT_EQ(true, ((mat1 -= mat2) == result));
}

TEST(TestMatrix, throw_error_when_matrix_dimensions_do_not_match_for_mult) {
    // Arrange
    Matrix<int>
        mvec1 = {
            {1, 2, 3, 4, 5 },
            {1, 2, 3, 4, 5 }
    }, mvec2 = {
            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    };

    // Act & Assert
    ASSERT_ANY_THROW(mvec1 *= mvec2);
}

TEST(TestMatrix, mult_matrix_by_matrix) {
    // Arrange
    Matrix<int> mat1 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    }, mat2 = {
        {5, 10},
        {15, 20},
        {25, 30},
        {35, 40}
    }, result = {
        {250, 300},
        {570, 700},
        {890, 1100}
    };

    // Act & Assert
    EXPECT_EQ(true, ((mat1 *= mat2) == result));
}

TEST(TestMatrix, mult_matrix_by_number) {
    // Arrange
    Matrix<int> matrix = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8}
    }, result = {
        {5, 10},
        {15, 20},
        {25, 30},
        {35, 40}
    };

    // Act & Assert
    EXPECT_EQ(true, ((matrix *= 5) == result));
}

TEST(TestMatrix, mult_number_by_matrix) {
    // Arrange
    Matrix<int> matrix = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8}
    }, result = {
        {5, 10},
        {15, 20},
        {25, 30},
        {35, 40}
    };
    // Act & Assert
    EXPECT_EQ(true, (( 5 * matrix) == result));
}

TEST(TestMatrix, div_by_number) {
    // Arrange
    Matrix<int> matrix = {
        {5, 10},
        {15, 20},
        {25, 30},
        {35, 40}
    }, result = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8}
    };
    // Act & Assert
    EXPECT_EQ(true, ((matrix / 5) == result));
}

TEST(TestMatrix, transpose) {
    // Arrange
    Matrix<int> matrix = {
        {5, 10},
        {15, 20},
        {25, 30},
        {35, 40}
    }, result = {
        {5, 15, 25, 35},
        {10, 20, 30, 40}
    };
    // Act & Assert
    EXPECT_EQ(true, ((matrix.transpose()) == result));
}

#endif // TEST_MATRIX