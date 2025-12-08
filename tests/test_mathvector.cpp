// Copyright 2024 Polina Pozdnova

#include <gtest/gtest.h>
#include "../lib_mathvector/mathvector.h"

//#define TEST_MATHVECTOR
#ifdef TEST_MATHVECTOR

// Constructors //

TEST(TestMathVector, empty_constructor) {
    // Arrange
    MathVector<int> empty1, fake_empty(0);

    // Act & Assert
    EXPECT_EQ(true, (empty1.is_empty() == fake_empty.is_empty()));
}

TEST(TestMathVector, empty_constructor_params) {
    // Arrange
    MathVector<int> empty1;

    // Act & Assert
    EXPECT_EQ(empty1.size(), 0);
    EXPECT_EQ(empty1.capacity(), CAPACITY);
    EXPECT_EQ(empty1.get_deleted(), 0);
    EXPECT_NE(empty1.data(), nullptr);
}

TEST(TestMathVector, sizedata_constructor) {
    // Arrange
    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Act
    MathVector<int> vec1(10, arr); 

    // Assert
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(vec1[i], i+1);
    }
    EXPECT_EQ(vec1.size(), 10);
}

TEST(TestMathVector, init_constructor) {
    // Arrange
    int arr[5] = { 1, 2, 3, 4, 5 };
    MathVector<int> vec1({ 1, 2, 3, 4, 5 }), vec2(5, arr);

    // Act & Assert
    EXPECT_EQ(vec1, vec2);
}

TEST(TestMathVector, copy_constructor) {
    // Arrange
    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    MathVector<int> vec1(10, arr);

    // Act
    MathVector<int> vec2(vec1);

    // Assert
    EXPECT_EQ(vec1, vec2);
}

// Functions //

TEST(TestMathVector, throw_error_when_adding_vectors_of_different_lengths) {
    // Arrange
    MathVector<int> mvec1({ 1, 2, 3, 4, 5 }), mvec2({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });

    // Act & Assert
    ASSERT_ANY_THROW(mvec1+=mvec2);
}

TEST(TestMathVector, add) {
    // Arrange
    int arr1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int arr2[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    MathVector<int> mvec1(10, arr1), mvec2(10, arr2), result({ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 });

    // Act
    mvec1 += mvec2;

    // Assert
    EXPECT_EQ(mvec1, result);
}

TEST(TestMathVector, throw_error_when_subtracting_vectors_of_different_lengths) {
    // Arrange
    MathVector<int> mvec1({ 1, 2, 3, 4, 5 }), mvec2({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });

    // Act & Assert
    ASSERT_ANY_THROW(mvec1-=mvec2);
}

TEST(TestMathVector, sub) {
    // Arrange
    int arr1[5] = { 6, 7, 8, 9, 10 };
    int arr2[5] = { 1, 2, 3, 4, 5 };
    MathVector<int> mvec1(5, arr1), mvec2(5, arr2), result({ 5, 5, 5, 5, 5 });

    // Act
    mvec1 -= mvec2;

    // Assert
    EXPECT_EQ(mvec1, result);
}

TEST(TestMathVector, checking_for_float_match) {
    // Arrange
    float arr1[5] = { 6.0f, 7.0f, 8.0f, 9.0f, 10.0f };
    float arr2[5] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
    MathVector<float> mvec1(5, arr1), mvec2(5, arr2), result({ 5.0f, 5.0f, 5.0f, 5.0f, 5.0f });

    // Act
    mvec1 -= mvec2;

    // Assert
    EXPECT_EQ(mvec1, result);
}

TEST(TestMathVector, mult_by_number) {
    // Arrange
    MathVector<float> mvec1({ 1.1f, 2.2f, 3.3f, 4.4f, 5.5f }), result({ 2.42f, 4.84f, 7.26f, 9.68f, 12.1f });

    // Act & Assert
    EXPECT_EQ(mvec1 *= 2.2f, result);
}

TEST(TestMathVector, div_by_number) {
    // Arrange
    MathVector<float> mvec1({ 2.42f, 4.84f, 7.26f, 9.68f, 12.1f }), result({ 1.1f, 2.2f, 3.3f, 4.4f, 5.5f });

    // Act & Assert
    EXPECT_EQ(mvec1 /= 2.2f, result);
}

TEST(TestMathVector, scalar_mult) {
    // Arrange
    int arr1[5] = { 6, 7, 8, 9, 10 };
    int arr2[5] = { 1, 2, 3, 4, 5 };
    MathVector<int> mvec1(5, arr1), mvec2(5, arr2);

    // Act & Assert
    EXPECT_EQ(mvec1 * mvec2, 130);
}

#endif // TEST_MATHVECTOR