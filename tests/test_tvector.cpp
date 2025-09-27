// Copyright 2024 Polina Pozdnova

#include <gtest/gtest.h>
#include "../lib_tvector/tvector.h"

#define EPSILON 0.000001

// Constructors //

TEST(TestTVector, empty_constructor) {
    // Arrange
    TVector<int> empty1, fake_empty(0);

    // Act & Assert
    EXPECT_EQ(true, (empty1 == fake_empty));
}

TEST(TestTVector, empty_constructor_params) {
    // Arrange
    TVector<int> empty1;

    // Act & Assert
    EXPECT_EQ(true, (empty1.size() == 0 && 
                     empty1.capacity() == CAPACITY &&
                     empty1.get_deleted() == 0 &&
                     empty1.data() != nullptr));
}

TEST(TestTVector, size_constructor) {
    // Arrange
    TVector<int> vec1(10), vec2(10);

    // Act & Assert
    EXPECT_EQ(true, (vec1 == vec2));
}

TEST(TestTVector, size_constructor_params) {
    // Arrange
    TVector<int> vec1(10);

    // Act
    vec1.push_front(11);

    // Assert
    EXPECT_EQ(true, (vec1.size() == 11 && 
                     vec1.capacity() == 25 && 
                     vec1.get_deleted() == 0 &&
                     vec1.data() != nullptr && vec1[0] == 11));
}

TEST(TestTVector, sizedata_constructor) {
    // Arrange
    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    TVector<int> vec1(10, arr), vec2(10, arr);

    // Act & Assert
    EXPECT_EQ(true, (vec1 == vec2));
}

TEST(TestTVector, sizedata_constructor_params) {
    // Arrange
    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    TVector<int> vec1(10, arr);

    // Act
    bool actual_result;
    if (vec1.size() == 10 && 
        vec1.capacity() == 25 && 
        vec1.get_deleted() == 0) {
        actual_result = true;
        for (int i = 0; i < vec1.size(); i++) {
            if (vec1[i] != i + 1) actual_result = false;
        }
    }
    else {
        actual_result = false;
    }

    // Assert
    EXPECT_EQ(true, actual_result);
}

TEST(TestTVector, init_constructor) {
    // Arrange
    int arr[5] = { 1, 2, 3, 4, 5 };
    TVector<int> vec1({ 1, 2, 3, 4, 5 }), vec2(5, arr);

    // Act & Assert
    EXPECT_EQ(true, (vec1 == vec2));
}

TEST(TestTVector, copy_constructor) {
    // Arrange
    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    TVector<int> vec1(10, arr);

    // Act
    vec1.pop_back();
    vec1.pop_front();
    TVector<int> vec2(vec1);

    // Assert
    EXPECT_EQ(true, (vec1 == vec2));
}

TEST(TestTVector, copy_constructor_params) {
    // Arrange
    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    TVector<int> vec1(10, arr);

    // Act
    vec1.pop_back();
    vec1.pop_front();
    TVector<int> vec2(vec1);

    // Assert
    EXPECT_EQ(true, (vec2.size() == 8 && 
                     vec2.capacity() == 25 && 
                     vec2[1] == 3));
}


// Functions //

TEST(TestTVector, is_empty) {
    // Arrange
    TVector<int> empty1, fake_empty(2);

    // Act
    fake_empty.pop_front();
    fake_empty.pop_front();

    // Assert
    EXPECT_EQ(true, (empty1.is_empty() && 
                     fake_empty.is_empty()));
}

TEST(TestTVector, at) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    TVector<int> vec2({ 3, 4, 6, 7, 8 });

    // Act
    vec1.pop_front();
    vec1.pop_front();
    vec1.pop_back();
    vec1.pop_back();
    vec1.erase(2);

    // Assert
    EXPECT_EQ(true, (vec1 == vec2));
}

TEST(TestTVector, at_empty) {
    // Arrange
    TVector<double> empty1;

    // Act & Assert
    ASSERT_ANY_THROW(empty1.at(0));
}

TEST(TestTVector, at_assign) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3 });

    // Act
    vec1[1] = -4;

    // Assert
    EXPECT_EQ(true, (vec1[1] == -4));
}

TEST(TestTVector, push_front) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4, 5 });
    TVector<int> vec2({ -5, -4, -3, -2, -1, 1, 2, 3, 4, 5 });

    // Act
    vec1.push_front(-1);
    vec1.push_front(-2);
    vec1.push_front(-3);
    vec1.push_front(-4);
    vec1.push_front(-5);

    // Assert
    EXPECT_EQ(true, (vec1 == vec2));
}

TEST(TestTVector, push_front_empty) {
    // Arrange
    TVector<int> empty1;

    // Act
    empty1.push_front(5);
    empty1.push_front(5);

    // Assert
    EXPECT_EQ(true, (empty1[0] == 5 && 
                     empty1[1] == 5));
}

TEST(TestTVector, push_front_capacity_overflow) {
    // Arrange
    TVector<int> empty1;

    // Act
    for (int i = 0; i < 16; i++) {
        empty1.push_front(5);
    }

    // Assert
    EXPECT_EQ(true, (empty1.capacity() == 30));
}

TEST(TestTVector, push_front_to_deleted) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4 }), vec2({ 5, 5, 3, 4 });

    // Act
    vec1.pop_front();
    vec1.pop_front();
    vec1.push_front(5);
    vec1.push_front(5);

    // Assert
    EXPECT_EQ(true, (vec1 == vec2));
}

TEST(TestTVector, push_back) {
    // Arrange
    TVector<int> vec1({ -5, -4, -3, -2, -1 });
    TVector<int> vec2({ -5, -4, -3, -2, -1, 1, 2, 3, 4, 5 });

    // Act
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);
    vec1.push_back(4);
    vec1.push_back(5);

    // Assert
    EXPECT_EQ(true, (vec1 == vec2));
}

TEST(TestTVector, push_back_empty) {
    // Arrange
    TVector<int> empty1;

    // Act
    empty1.push_back(5);
    empty1.push_back(5);

    // Assert
    EXPECT_EQ(true, (empty1[0] == 5 && 
                     empty1[1] == 5));
}

TEST(TestTVector, push_back_capacity_overflow) {
    // Arrange
    TVector<int> empty1;

    // Act
    for (int i = 0; i < 15; i++) {
        empty1.push_back(5);
    }

    // Assert
    EXPECT_EQ(true, (empty1.capacity() == 15));
}

TEST(TestTVector, insert_to_invalid_index) {
    // Arrange
    TVector<double> empty1;

    // Act & Assert
    ASSERT_ANY_THROW(empty1.insert(2, 3));
}

TEST(TestTVector, insert) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4 }), vec2({ 1, 5, 2, 3, 5, 4 });

    // Act
    vec1.insert(1, 5);
    vec1.insert(4, 5);

    // Assert
    EXPECT_EQ(true, (vec1 == vec2));
}

TEST(TestTVector, insert_to_empty) {
    // Arrange
    TVector<int> empty1;

    // Act
    empty1.insert(0, 5);
    empty1.insert(0, -1);

    // Assert
    EXPECT_EQ(true, (empty1[0] == -1 && empty1[1] == 5));
}

TEST(TestTVector, insert_capacity_overflow) {
    // Arrange
    TVector<int> vec1({ 1, 0 });

    // Act
    for (int i = 0; i < 16; i++) {
        vec1.insert(1, 5);
    }

    // Assert
    EXPECT_EQ(true, (vec1.capacity() == 32));
}

TEST(TestTVector, pop_front) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4, 5 }), vec2({ 3, 4, 5 });

    // Act
    vec1.pop_front();
    vec1.pop_front();

    // Assert
    EXPECT_EQ(true, (vec1 == vec2));
}

TEST(TestTVector, pop_front_to_empty) {
    // Arrange
    TVector<int> empty1;

    // Act & Assert
    ASSERT_ANY_THROW(empty1.pop_front());
}

TEST(TestTVector, pop_back) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4, 5 }), vec2({ 1, 2, 3 });

    // Act
    vec1.pop_back();
    vec1.pop_back();

    // Assert
    EXPECT_EQ(true, (vec1 == vec2));
}

TEST(TestTVector, pop_back_to_empty) {
    // Arrange
    TVector<int> empty1;

    // Act & Assert
    ASSERT_ANY_THROW(empty1.pop_back());
}

TEST(TestTVector, erase_to_invalid_index) {
    // Arrange
    TVector<double> vec1({ 1, 2 });

    // Act & Assert
    ASSERT_ANY_THROW(vec1.erase(3));
}

TEST(TestTVector, erase) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4, 5 }), vec2({ 1, 4, 5 });

    // Act
    vec1.erase(1);
    vec1.erase(1);

    // Assert
    EXPECT_EQ(true, (vec1 == vec2));
}

TEST(TestTVector, erase_to_empty) {
    // Arrange
    TVector<int> empty1;

    // Act & Assert
    ASSERT_ANY_THROW(empty1.erase(3));
}

TEST(TestTVector, clear) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4, 5 }), empty1;

    // Act
    vec1.clear();

    // Assert
    EXPECT_EQ(true, (vec1 == empty1));
}

TEST(TestTVector, shrink_to_fit_ln) {
    // Arrange
    TVector<int> vec1(34);

    // Act
    for (int i = 0; i < 3; i++) {
        vec1.erase(1);
    }
    vec1.erase(vec1.size() - 2);
    vec1.shrink_to_fit();

    // Assert
    EXPECT_EQ(true, (vec1.size() == 30 && 
                     vec1.capacity() == 0));
}

TEST(TestTVector, reserve) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4, 5 });

    // Act
    vec1.reserve(30);

    // Assert
    EXPECT_EQ(true, (vec1.size() == 5 && 
                     vec1.capacity() == 30));
}

TEST(TestTVector, reserve_lts) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4, 5 });

    // Act
    vec1.reserve(4);

    // Assert
    EXPECT_EQ(true, (vec1.size() == 5 && 
                     vec1.capacity() == 20));
}

TEST(TestTVector, resize_shrink) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4, 5 });

    // Act
    vec1.resize(2, 0);

    // Assert
    EXPECT_EQ(true, (vec1.size() == 2));
}

TEST(TestTVector, resize_enlarge_no_filler) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4, 5 });

    // Act
    vec1.resize(8, 0);

    // Assert
    EXPECT_EQ(true, (vec1.size() == 8));
}

TEST(TestTVector, resize_enlarge_with_filler) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4, -11 });

    // Act
    vec1.resize(8, 1);

    // Assert
    EXPECT_EQ(true, (vec1.size() == 8 && 
                     vec1[4] == -11 && 
                     vec1[5] == 1));
}

TEST(TestTVector, emplace) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4, 5 }), vec2({ 2, 2, 2, 2, 2 });

    // Act
    for (int i = 0; i < vec1.size(); i++) vec1.emplace(i, 2);

    // Assert
    EXPECT_EQ(true, (vec1 == vec2));
}

TEST(TestTVector, assign_empty) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4 }), empty1;

    // Act & Assert
    EXPECT_EQ(true, ((vec1 = empty1) == empty1));
}

TEST(TestTVector, assign) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4 }), vec2({ 37, 55, -19, 0, 0, 12 });

    // Act & Assert
    EXPECT_EQ(true, ((vec1 = vec2) == vec2));
}

// Sorting and Shuffle //

TEST(TestTVector, shuffle_and_sorting) {
    // Arrange
    TVector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    TVector<int> vec2({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });

    // Act
    knuth_shuffle(vec1);
    hoara_sort(vec1, 0, vec1.size() - 1);

    // Assert
    EXPECT_EQ(true, (vec1 == vec2));
}

// Searches //

TEST(TestTVector, searches) {
    // Arrange
    TVector<int> vec1({ -11, 2, 7, 2, 5, 2, 7, 2, 5, 110 });

    // Act & Assert
    EXPECT_EQ(true, (find_first(vec1, 5) == 4 && 
                     find_last(vec1, 7) == 6 && 
                     find_first(vec1, -1) == -1));
}
