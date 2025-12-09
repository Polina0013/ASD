// Copyright 2025 Polina Pozdnova

#include <gtest/gtest.h>
#include "..\lib_queue\queue.h"

//#define TEST_QUEUE
#ifdef TEST_QUEUE

TEST(TestQueue, comparing_default_constructor_and_fake_default_constructor) {
    // Arrange
    Queue<int> default_queue, fake_default_queue(STANDARD_SIZE);

    // Act & Assert
    EXPECT_EQ(default_queue, fake_default_queue);
}

TEST(TestQueue, throw_error_when_max_size_is_zero) {
    // Arrange & Act & Assert
    ASSERT_ANY_THROW(Queue<int> (0));
}

TEST(TestQueue, initialization_constructor) {
    // Arrange
    Queue<int> q1 = { 1, 2, 3, 4, 5 };

    // Act
    q1.pop();
    q1.push(6);

    //& Assert
    EXPECT_EQ(q1, (Queue<int> { 2, 3, 4, 5, 6 }));
}

TEST(TestQueue, copy_constructor) {
    // Arrange
    Queue<int> q1 = { 1, 2, 3, 4, 5 };
    
    // Act
    Queue<int> q2(q1);
    
    // Assert
    EXPECT_EQ(q1, q2);
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
    EXPECT_TRUE(q1.is_empty());
}

TEST(TestQueue, is_full) {
    // Arrange
    Queue<int> q1(5);

    // Act
    q1.push(1);
    q1.push(2);
    q1.push(3);
    q1.push(4);
    q1.push(5);

    //& Assert
    EXPECT_TRUE(q1.is_full());
}

TEST(TestQueue, throw_error_push_when_queue_is_full) {
    // Arrange 
    Queue<int> q1 = { 1, 2, 3, 4, 5 };

    // Act & Assert
    ASSERT_ANY_THROW(q1.push(6));
}

TEST(TestQueue, throw_error_pop_when_queue_is_empty) {
    // Arrange 
    Queue<int> q1 = { };

    // Act & Assert
    ASSERT_ANY_THROW(q1.pop());
}

TEST(TestQueue, clear) {
    // Arrange
    Queue<int> q1 = { 1, 2, 3, 4, 5 };

    // Act
    q1.clear();

    //& Assert
    EXPECT_TRUE(q1.is_empty());
}

TEST(TestQueue, head) {
    // Arrange
    Queue<int> q1(4);

    // Act
    q1.push(1);
    q1.push(2);
    q1.push(3);
    q1.pop();

    //& Assert
    EXPECT_EQ(q1.get_head(), 1);
}

TEST(TestQueue, tail) {
    // Arrange
    Queue<int> q1(4);

    // Act
    q1.push(1);
    q1.push(2);
    q1.push(3);
    q1.pop();

    //& Assert
    EXPECT_EQ(q1.get_tail(), 3);
}

#endif // TEST_QUEUE