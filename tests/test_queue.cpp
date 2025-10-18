// Copyright 2024 Polina Pozdnova

#include <gtest/gtest.h>
#include "..\lib_queue\queue.h"

#define TEST_QUEUE
#ifdef TEST_QUEUE

// Constructors //

TEST(TestQueue, comparing_default_constructor_and_fake_default_constructor) {
    // Arrange
    Queue<int> default_queue, fake_default_queue(CAPACITY);

    // Act & Assert
    EXPECT_EQ(true, (default_queue == fake_default_queue));
}

TEST(TestQueue, throw_error_when_max_size_is_zero) {
    // Arrange & Act & Assert
    ASSERT_ANY_THROW(Queue<int> (0));
}

TEST(TestQueue, initialization_constructor_params) {
    // Arrange
    Queue<int> q1 = { 1, 2, 3, 4, 5 };

    // Act
    q1.pop();
    q1.push(6);

    // Assert
    EXPECT_EQ(true, (q1.head() == 2 &&
                     q1.tail() == 6 &&
                     q1.get_head() == 1 &&
                     q1.get_tail() == 1 &&
                     q1.get_count() == 5 &&
                     q1.get_max_size() == 5 &&
                     q1.is_full()));
}

TEST(TestQueue, initialization_constructor) {
    // Arrange
    Queue<int> q1 = { 1, 2, 3, 4, 5 };

    // Act
    q1.pop();
    q1.push(6);

    //& Assert
    EXPECT_EQ(true, (q1 == Queue<int> { 2, 3, 4, 5, 6 }));
}

TEST(TestQueue, is_empty) {
    // Arrange
    Queue<int> q1 = { 1, 2, 3, 4, 5 };

    // Act
    q1.pop();
    q1.pop();
    q1.pop();
    q1.pop();
    q1.pop();

    //& Assert
    EXPECT_EQ(true, q1.is_empty());
}

TEST(TestQueue, throw_error_push_when_queue_is_full) {
    // Arrange 
    Queue<int> q1 = { 1, 2, 3, 4, 5 };

    // Act & Assert
    ASSERT_ANY_THROW(q1.push(6));
}

TEST(TestQueue, throw_error_pop_when_queue_is_empty) {
    // Arrange 
    Queue<int> q1 = { 1, 2, 3, 4, 5 };

    // Act & Assert
    ASSERT_ANY_THROW(q1.push(6));
}

//TEST(TestMatrix, init_from_mathvector_constructor_and_initializer_list) {
//    // Arrange
//    MathVector<int> row1({ 1, 2, 3, 4, 5 });
//    MathVector<int> row2({ 6, 7, 8, 9, 10 });
//
//    MathVector<MathVector<int>> matrix;
//    matrix.push_back(row1);
//    matrix.push_back(row2);
//
//    Matrix<int> mat1(matrix);
//    Matrix<int> mat2 = {
//        { 1, 2, 3, 4, 5 },
//        { 6, 7, 8, 9, 10 }
//    };
//
//    // Act & Assert
//    EXPECT_EQ(true, (mat1 == mat2));
//}
//
//TEST(TestMatrix, copy_constructor) {
//    // Arrange
//    Matrix<int> mat1 = {
//        {1, 2},
//        {3, 4},
//        {5, 6},
//        {7, 8}
//    };
//
//    // Act
//    Matrix<int> mat2(mat1);
//
//    // Assert
//    EXPECT_EQ(true, (mat1 == mat2));
//}
//
//// Functions //
//
//TEST(TestMatrix, throw_error_when_adding_matrices_of_different_sizes) {
//    // Arrange
//    Matrix<int>
//    mat1 = { 
//        {1, 2, 3, 4, 5 },
//        {1, 2, 3, 4, 5 }
//    },
//
//    mat2 = {
//        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
//        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
//        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
//    };
//
//    // Act & Assert
//    ASSERT_ANY_THROW(mat1+=mat2);
//}
//
//TEST(TestMatrix, add) {
//    // Arrange
//    Matrix<int> mat1 = {
//        {1, 2},
//        {3, 4},
//        {5, 6},
//        {7, 8}
//    }, mat2 = {
//        {1, 2},
//        {3, 4},
//        {5, 6},
//        {7, 8}
//    }, result = {
//        {2, 4},
//        {6, 8},
//        {10, 12},
//        {14, 16}
//    };
//
//    // Act & Assert
//    EXPECT_EQ(true, ((mat1 += mat2) == result));
//}
//
//TEST(TestMatrix, throw_error_when_subtracting_vectors_of_different_lengths) {
//    // Arrange
//    Matrix<int>
//        mvec1 = {
//            {1, 2, 3, 4, 5 },
//            {1, 2, 3, 4, 5 }
//    },
//
//        mvec2 = {
//            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
//            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
//            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
//    };
//
//    // Act & Assert
//    ASSERT_ANY_THROW(mvec1 -= mvec2);
//}
//
//TEST(TestMatrix, sub) {
//    // Arrange
//    Matrix<float> mat1 = {
//        {1.1f, 2.2f},
//        {3.1f, 4.2f},
//        {5.1f, 6.2f},
//        {7.1f, 8.2f}
//    }, mat2 = {
//        {1.0f, 2.0f},
//        {3.0f, 4.0f},
//        {5.0f, 6.0f},
//        {7.0f, 8.0f}
//    }, result = {
//        {0.1f, 0.2f},
//        {0.1f, 0.2f},
//        {0.1f, 0.2f},
//        {0.1f, 0.2f}
//    };
//
//    // Act & Assert
//    EXPECT_EQ(true, ((mat1 -= mat2) == result));
//}
//
//TEST(TestMatrix, throw_error_when_matrix_dimensions_do_not_match_for_mult) {
//    // Arrange
//    Matrix<int>
//        mvec1 = {
//            {1, 2, 3, 4, 5 },
//            {1, 2, 3, 4, 5 }
//    }, mvec2 = {
//            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
//            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
//            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
//    };
//
//    // Act & Assert
//    ASSERT_ANY_THROW(mvec1 *= mvec2);
//}
//
//TEST(TestMatrix, mult_matrix_by_matrix) {
//    // Arrange
//    Matrix<int> mat1 = {
//        {1, 2, 3, 4},
//        {5, 6, 7, 8},
//        {9, 10, 11, 12}
//    }, mat2 = {
//        {5, 10},
//        {15, 20},
//        {25, 30},
//        {35, 40}
//    }, result = {
//        {250, 300},
//        {570, 700},
//        {890, 1100}
//    };
//
//    // Act & Assert
//    EXPECT_EQ(true, ((mat1 *= mat2) == result));
//}
//
//TEST(TestMatrix, mult_matrix_by_number) {
//    // Arrange
//    Matrix<int> matrix = {
//        {1, 2},
//        {3, 4},
//        {5, 6},
//        {7, 8}
//    }, result = {
//        {5, 10},
//        {15, 20},
//        {25, 30},
//        {35, 40}
//    };
//
//    // Act & Assert
//    EXPECT_EQ(true, ((matrix *= 5) == result));
//}
//
//TEST(TestMatrix, mult_number_by_matrix) {
//    // Arrange
//    Matrix<int> matrix = {
//        {1, 2},
//        {3, 4},
//        {5, 6},
//        {7, 8}
//    }, result = {
//        {5, 10},
//        {15, 20},
//        {25, 30},
//        {35, 40}
//    };
//    // Act & Assert
//    EXPECT_EQ(true, (( 5 * matrix) == result));
//}
//
//TEST(TestMatrix, div_by_number) {
//    // Arrange
//    Matrix<int> matrix = {
//        {5, 10},
//        {15, 20},
//        {25, 30},
//        {35, 40}
//    }, result = {
//        {1, 2},
//        {3, 4},
//        {5, 6},
//        {7, 8}
//    };
//    // Act & Assert
//    EXPECT_EQ(true, ((matrix / 5) == result));
//}
//
//TEST(TestMatrix, transpose) {
//    // Arrange
//    Matrix<double> matrix = {
//        {5.0, 10.0},
//        {15.0, 20.0},
//        {25.0, 30.0},
//        {35.0, 40.0}
//    }, result = {
//        {5.0, 15.0, 25.0, 35.0},
//        {10.0, 20.0, 30.0, 40.0}
//    };
//    // Act & Assert
//    EXPECT_EQ(true, ((matrix.transpose()) == result));
//}

#endif // TEST_QUEUE