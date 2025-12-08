// Copyright 2024 Polina Pozdnova

#include <gtest/gtest.h>
#include "../lib_trianglematrix/trianglematrix.h"

//#define TEST_TRIANGLEMATRIX
#ifdef TEST_TRIANGLEMATRIX

// Constructors //

TEST(TestTriangleMatrix, true_when_empty_constructor_and_upper_triangle_matrix) {
    // Arrange
    TriangleMatrix<int> empty1, fake_empty_up(0, TriangleType::Upper);

    // Act & Assert
    EXPECT_EQ(empty1, fake_empty_up);
}

TEST(TestTriangleMatrix, false_when_empty_constructor_and_lower_triangle_matrix) {
    // Arrange
    TriangleMatrix<int> empty1, fake_empty_low(0, TriangleType::Lower);

    // Act & Assert
    EXPECT_NE(empty1, fake_empty_low);
}

TEST(TestTriangleMatrix, size_constructor) {
    // Arrange
    TriangleMatrix<int> mat1(10, TriangleType::Upper), mat2(10, TriangleType::Upper);

    // Act & Assert
    EXPECT_EQ(mat1, mat2);
}

TEST(TestTriangleMatrix, init_from_mathvector_constructor_and_initializer_list_for_upper_triangle_matrix) {
    // Arrange
    MathVector<int> row1({ 1, 2, 3, 4 });
    MathVector<int> row2({ 1, 2, 3 });
    MathVector<int> row3({ 1, 2 });
    MathVector<int> row4({ 1 });

    MathVector<MathVector<int>> matrix;
    matrix.push_back(row1);
    matrix.push_back(row2);
    matrix.push_back(row3);
    matrix.push_back(row4);

    TriangleMatrix<int> mat1(matrix, TriangleType::Upper);
    TriangleMatrix<int> mat2({
        {1, 2, 3, 4},
        {1, 2, 3},
        {1, 2},
        {1}
    }, TriangleType::Upper);

    // Act & Assert
    EXPECT_EQ(mat1, mat2);
}

TEST(TestTriangleMatrix, init_from_mathvector_constructor_and_initializer_list_for_lower_triangle_matrix) {
    // Arrange
    MathVector<int> row1({ 1 });
    MathVector<int> row2({ 1, 2 });
    MathVector<int> row3({ 1, 2, 3 });
    MathVector<int> row4({ 1, 2, 3, 4 });

    MathVector<MathVector<int>> matrix;
    matrix.push_back(row1);
    matrix.push_back(row2);
    matrix.push_back(row3);
    matrix.push_back(row4);

    TriangleMatrix<int> mat1(matrix, TriangleType::Lower);
    TriangleMatrix<int> mat2({
        {1},
        {1, 2},
        {1, 2, 3},
        {1, 2, 3, 4}
    }, TriangleType::Lower);

    // Act & Assert
    EXPECT_EQ(mat1, mat2);
}

TEST(TestTriangleMatrix, TriangleMatrix_to_Matrix) {
    // Arrange
    TriangleMatrix<int> triangle_matrix({
            {1},
            {1, 2},
            {1, 2, 3},
            {1, 2, 3, 4}
        }, TriangleType::Lower);

    Matrix<int> result({
           {1, 0, 0, 0},
           {1, 2, 0, 0},
           {1, 2, 3, 0},
           {1, 2, 3, 4}
        });

    Matrix<int> matrix(triangle_matrix);

    //std::cout << triangle_matrix << std::endl;
    //std::cout << result << std::endl;

   // Act & Assert
    EXPECT_EQ(matrix, result);
}

TEST(TestTriangleMatrix, Matrix_to_TriangleMatrix) {
    // Arrange
    Matrix<int> matrix({
        {1, 0, 0, 0},
        {1, 2, 0, 0},
        {1, 2, 3, 0},
        {1, 2, 3, 4}
    });
    
    TriangleMatrix<int> result({
            {1},
            {1, 2},
            {1, 2, 3},
            {1, 2, 3, 4}
        }, TriangleType::Lower);

    TriangleMatrix<int> triangle_matrix(matrix);

   // Act & Assert
    EXPECT_EQ(triangle_matrix, result);
}

TEST(TestTriangleMatrix, copy_constructor) {
    // Arrange
    TriangleMatrix<int> mat1({
        {1, 2, 3, 4},
        {1, 2, 3},
        {1, 2},
        {1}
        }, TriangleType::Upper);

    // Act
    TriangleMatrix<int> mat2(mat1);

    // Assert
    EXPECT_EQ(mat1, mat2);
}

// Functions //

TEST(TestTriangleMatrix, throw_error_when_adding_matrices_of_different_sizes) {
    // Arrange
    TriangleMatrix<int> mat1({
        {1, 2, 3, 4},
        {1, 2, 3},
        {1, 2},
        {1}
    }, TriangleType::Upper),
    mat2({
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4},
        {1, 2, 3},
        {1, 2},
        {1}
    }, TriangleType::Upper);

    // Act & Assert
    ASSERT_ANY_THROW(mat1 += mat2);
}

TEST(TestTriangleMatrix, add) {
    // Arrange
    TriangleMatrix<double> mat1({
        {1.0, 2.0, 3.0},
        {1.0, 2.0},
        {1.0}
    }, TriangleType::Upper),
    mat2({
        {1.0, 2.0, 3.0},
        {1.0, 2.0},
        {1.0}
    }, TriangleType::Upper),
    result({
        {2.0, 4.0, 6.0},
        {2.0, 4.0},
        {2.0}
    }, TriangleType::Upper);

    //std::cout << result;

    // Act & Assert
    EXPECT_EQ(mat1 += mat2, result);
}

TEST(TestTriangleMatrix, throw_error_when_subtracting_vectors_of_different_lengths) {
    // Arrange
    TriangleMatrix<int> mat1({
        {1},
        {1, 2},
        {1, 2, 3},
        {1, 2, 3, 4}
    }, TriangleType::Lower),
    mat2({
        {1},
        {1, 2},
        {1, 2, 3},
        {1, 2, 3, 4},
        {1, 2, 3, 4, 5}
    }, TriangleType::Lower);

    // Act & Assert
    ASSERT_ANY_THROW(mat1 -= mat2);
}

TEST(TestTriangleMatrix, sub) {
    // Arrange
    TriangleMatrix<float> mat1({
        {2.0f},
        {2.0f, 4.0f},
        {2.0f, 4.0f, 6.0f}
    }, TriangleType::Lower),
    mat2({
        {1.0f},
        {1.0f, 2.0f},
        {1.0f, 2.0f, 3.0f}
    }, TriangleType::Lower),
    result({
        {1.0f},
        {1.0f, 2.0f},
        {1.0f, 2.0f, 3.0f}
    }, TriangleType::Lower);

    // Act & Assert
    EXPECT_EQ(mat1 -= mat2, result);
}

TEST(TestTriangleMatrix, throw_error_when_matrix_dimensions_do_not_match_for_mult) {
    // Arrange
    TriangleMatrix<int> mat1({
            {1, 2, 3, 4},
            {1, 2, 3},
            {1, 2},
            {1}
            }, TriangleType::Upper),
        mat2({
            {1},
            {1, 2},
            {1, 2, 3},
            {1, 2, 3, 4}
            }, TriangleType::Lower);

    // Act & Assert
    ASSERT_ANY_THROW(mat1 *= mat2);
}

TEST(TestTriangleMatrix, mult_matrix_by_matrix) {
    // Arrange
    TriangleMatrix<int> mat1({
            {1, 2, 3},
            {1, 2},
            {1}
            }, TriangleType::Upper),
        mat2({
            {4, 5, 6},
            {4, 5},
            {4}
            }, TriangleType::Upper),
        result({
            {4, 13, 28},
            {4, 13},
            {4}
            }, TriangleType::Upper);

    // Act & Assert
    EXPECT_EQ(mat1 *= mat2, result);
}

TEST(TestTriangleMatrix, mult_matrix_by_number) {
    // Arrange
    TriangleMatrix<int> matrix({
            {1},
            {1, 2},
            {1, 2, 3}
            }, TriangleType::Lower),
        result({
            {5},
            {5, 10},
            {5, 10, 15}
            }, TriangleType::Lower);

    // Act & Assert
    EXPECT_EQ(matrix *= 5, result);
}

TEST(TestTriangleMatrix, mult_number_by_matrix) {
    // Arrange
    TriangleMatrix<int> matrix({
            {1},
            {1, 2},
            {1, 2, 3}
            }, TriangleType::Lower),
        result({
            {5},
            {5, 10},
            {5, 10, 15}
            }, TriangleType::Lower);

    // Act & Assert
    EXPECT_EQ(5 * matrix, result);
}

TEST(TestTriangleMatrix, div_by_number) {
    // Arrange
    TriangleMatrix<int> matrix({
            {5},
            {5, 10},
            {5, 10, 15}
            }, TriangleType::Lower),
        result({
            {1},
            {1, 2},
            {1, 2, 3}
            }, TriangleType::Lower);
    // Act & Assert
    EXPECT_EQ(matrix / 5, result);
}

TEST(TestTriangleMatrix, transpose) {
    // Arrange
    TriangleMatrix<int> matrix({
            {1},
            {1, 2},
            {1, 2, 3},
            {1, 2, 3, 4},
            {1, 2, 3, 4, 5}
        }, TriangleType::Lower),
        result({
            {1, 1, 1, 1, 1},
            {2, 2, 2, 2},
            {3, 3, 3},
            {4, 4},
            {5}
        }, TriangleType::Upper);
    // Act & Assert
    EXPECT_EQ(matrix.transpose(), result);
}

#endif // TEST_TRIANGLEMATRIX