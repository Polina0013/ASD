// Copyright 2025 Polina Pozdnova

#include <gtest/gtest.h>
#include "../lib_point/point.h"
#include "../lib_circle/circle.h"

#define EPSILON 0.000001

TEST(TestCircle, the_radius_is_zero) {
    // Arrange

    // Act & Assert
    ASSERT_ANY_THROW(Circle<int> z1(3, 4, 0));
}

TEST(TestCircle, the_radius_is_less_than_zero) {
    // Arrange

    // Act & Assert
    ASSERT_ANY_THROW(Circle<int> z2(1, 3, -1));
}

TEST(TestCircle, the_radius_is_zero_with_class_point) {
    // Arrange
    Point<int> p(0, 0);

    // Act & Assert
    ASSERT_ANY_THROW(Circle<int> z1(p, 0));
}

TEST(TestCircle, the_radius_is_less_than_zero_with_class_point) {
    // Arrange
    Point<int> p(10, -10);

    // Act & Assert
    ASSERT_ANY_THROW(Circle<int> z2(p, -1));
}

TEST(TestCircle, the_circles_match) {
    // Arrange
    Circle<float> z1, z2;

    // Act & Assert
    EXPECT_EQ("The circles match", z1.check_relative_location(z2));
}

TEST(TestCircle, do_not_intersect_or_touch) {
    // Arrange
    Circle<int> z1(Point<int>(0, 0), 1), z2(Point<int> (10, -10), 2);

    // Act & Assert
    EXPECT_EQ("The circles do not intersect or touch", z1.check_relative_location(z2));
}

TEST(TestCircle, touch_at_one_point_externally) {
    // Arrange
    Circle<int> z1(5, 5, 5), z2(-5, 5, 5);

    // Act & Assert
    EXPECT_EQ("The circles touch at one point (externally)", z1.check_relative_location(z2));
}

TEST(TestCircle, intersect_at_two_points_and_no_circle_is_inside_the_other) {
    // Arrange
    Circle<float> z1(-2.3f, -3.4f, 5.7f), z2(-1.2f, 1.0f, 2.7f);

    // Act & Assert
    EXPECT_EQ("The circles intersect at two points", z1.check_relative_location(z2));
}

TEST(TestCircle, intersect_at_two_points_and_one_inside_the_other) {
    // Arrange
    Circle<int> z1(10, -2, 5), z2(6, -2, 2);

    // Act & Assert
    EXPECT_EQ("The circles intersect at two points", z1.check_relative_location(z2));
}

TEST(TestCircle, one_circle_is_inside_the_other) {
    // Arrange
    Circle<double> z1(-2.3, -3.4, 5.7), z2(-2.2, -3.3, 2.5);

    // Act & Assert
    EXPECT_EQ("One circle is inside the other", z1.check_relative_location(z2));
}
