// Copyright 2025 Polina Pozdnova

#include <gtest/gtest.h>
#include "..\lib_stack\stack.h"

//#define TEST_STACK
#ifdef TEST_STACK
//
//TEST(TestStack, default_constructor) {
//    // Arrange
//    Stack<int> s1, s2;
//
//    // Act
//    s1.push(6);
//    s1.pop();
//
//    // Assert
//    EXPECT_EQ(s1, s2);
//}
//
//TEST(TestStack, initialization_constructor) {
//    // Arrange
//    Stack<int> s1 = { 1, 2, 3, 4, 5 };
//
//    // Act
//    s1.pop();
//    s1.push(6);
//
//    //& Assert
//    EXPECT_EQ(s1, (Stack<int> { 1, 2, 3, 4, 6 }));
//}
//
//TEST(TestStack, copy_constructor) {
//    // Arrange
//    Stack<int> s1 = { 1, 2, 3, 4, 5 };
//
//    // Act
//    s1.pop();
//    s1.pop();
//    s1.push(10);
//    Stack<int> s2(s1);
//
//    // Assert
//    EXPECT_EQ(s1, s2);
//}
//
//TEST(TestStack, is_empty) {
//    // Arrange
//    Stack<int> s1 = { 1, 2, 3, 4, 5 };
//
//    // Act
//    s1.pop();
//    s1.pop();
//    s1.pop();
//    s1.pop();
//    s1.pop();
//
//    //& Assert
//    EXPECT_TRUE(s1.is_empty());
//}
//
//TEST(TestStack, throw_error_pop_when_stack_is_empty) {
//    // Arrange 
//    Stack<int> s1 = { };
//
//    // Act & Assert
//    ASSERT_ANY_THROW(s1.pop());
//}
//
//TEST(TestStack, clear) {
//    // Arrange
//    Stack<float> s1 = { 1.0f, 2.0f, 3.0f };
//
//    // Act
//    s1.clear();
//
//    //& Assert
//    EXPECT_TRUE(s1.is_empty());
//}
//
//TEST(TestStack, top) {
//    // Arrange
//    Stack<double> s1 = { 1.0, 2.0, 3.0 };
//
//    // Act
//    s1.push(1.0);
//    s1.push(2.0);
//    s1.push(3.0);
//    s1.pop();
//
//    //& Assert
//    EXPECT_EQ(s1.top(), 2.0);
//}

#endif // TEST_STACK