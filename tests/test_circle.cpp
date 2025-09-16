// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_point/point.h"
#include "../lib_circle/circle.h"

#define EPSILON 0.000001

TEST(TestCircle, test_0_1_the_radius_is_less_than_zero) {
    // Arrange

    // Act & Assert
    ASSERT_ANY_THROW(Circle<int> z1(3, 4, 0));
}

TEST(TestCircle, test_0_2_the_radius_is_less_than_zero) {
    // Arrange

    // Act & Assert
    ASSERT_ANY_THROW(Circle<int> z2(1, 3, -1));
}

TEST(TestCircle, test_0_3_the_radius_is_less_than_zero) {
    // Arrange
    Point<int> p1(0, 0), p2(10, -10);

    // Act & Assert
    ASSERT_ANY_THROW(Circle<int> z1(p1, 0));
}

TEST(TestCircle, test_0_4_the_radius_is_less_than_zero) {
    // Arrange
    Point<int> p1(0, 0), p2(10, -10);

    // Act & Assert
    ASSERT_ANY_THROW(Circle<int> z2(p2, -1));
}

TEST(TestCircle, test_1_the_circles_match) {
    // Arrange
    Circle<float> z1, z2;

    // Act
    std::string actual_result = z1.check_relative_location(z2);

    // Assert
    std::string expected_result = "The circles match";
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircle, test_2_do_not_intersect_or_touch) {
    // Arrange
    Point<int> p1(0, 0), p2(10, -10);
    Circle<int> z1(p1, 1), z2(p2, 2);

    // Act
    std::string actual_result = z1.check_relative_location(z2);

    // Assert
    std::string expected_result = "The circles do not intersect or touch";
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircle, test_3_touch_at_one_point_externally) {
    // Arrange
    Circle<int> z1(5, 5, 5), z2(-5, 5, 5);

    // Act
    std::string actual_result = z1.check_relative_location(z2);

    // Assert
    std::string expected_result = "The circles touch at one point (externally)";
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircle, test_4_1_intersect_at_two_points) {
    // Arrange
    Circle<float> z1(-2.3f, -3.4f, 5.7f), z2(-1.2f, 1.0f, 2.7f);

    // Act
    std::string actual_result = z1.check_relative_location(z2);

    // Assert
    std::string expected_result = "The circles intersect at two points";
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircle, test_4_2_intersect_at_two_points) {
    // Arrange
    Circle<int> z1(10, -2, 5), z2(6, -2, 2);

    // Act
    std::string actual_result = z1.check_relative_location(z2);

    // Assert
    std::string expected_result = "The circles intersect at two points";
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircle, test_5_1_one_circle_is_inside_the_other) {
    // Arrange
    Circle<double> z1(-2.3, -3.4, 5.7), z2(-2.2, -3.3, 2.5);

    // Act
    std::string actual_result = z1.check_relative_location(z2);

    // Assert
    std::string expected_result = "One circle is inside the other";
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircle, test_5_2_one_circle_is_inside_the_other) {
    // Arrange
    Circle<double> z1(-1.2, 3.4, 1.2), z2(-0.2, 3.4, 0.2);

    // Act
    std::string actual_result = z1.check_relative_location(z2);

    // Assert
    std::string expected_result = "One circle is inside the other";
    EXPECT_EQ(expected_result, actual_result);
}