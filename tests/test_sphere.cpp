// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_point3D/point3D.h"
#include "../lib_sphere/sphere.h"

#define EPSILON 0.000001

TEST(TestSphere, throw_when_try_create_with_cast_constructor_by_not_positive_radius) {
    // Arrange

    // Act & Assert
    ASSERT_ANY_THROW(Sphere<int> z1(3, 2, 4, 0));
}

TEST(TestSphere, throw_when_try_create_with_init_constructor_by_not_positive_radius) {
    // Arrange
    Point3D<int> p1(0, 0, 0);

    // Act & Assert
    ASSERT_ANY_THROW(Sphere<int> z1(p1, -1));
}

TEST(TestSphere, test_1_the_spheres_match) {
    // Arrange
    Sphere<float> z1(10, -10, -10, 5), z2(10, -10, -10, 5);

    // Act & Assert
    EXPECT_EQ("The spheres match", z1.check_relative_location(z2));
}

TEST(TestSphere, test_2_do_not_intersect_or_touch) {
    // Arrange
    Sphere<int> z1(Point3D<int>(0, 0, 0), 1), z2(Point3D<int>(10, -10, -10), 2);

    // Act
    std::string actual_result = z1.check_relative_location(z2);

    // Assert
    std::string expected_result = "The spheres do not intersect or touch";
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphere, test_3_touch_at_one_point_externally) {
    // Arrange
    Sphere<int> z1(5, 5, 5, 5), z2(-5, 5, 5, 5);

    // Act
    std::string actual_result = z1.check_relative_location(z2);

    // Assert
    std::string expected_result = "The spheres touch at one point (externally)";
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphere, test_4_1_intersect_in_a_circle) {
    // Arrange
    Sphere<float> z1(-2.3f, -3.4f, 3.0f, 15.7f), z2(-1.2f, 1.0f, -2.2f, 12.7f);

    // Act
    std::string actual_result = z1.check_relative_location(z2);

    // Assert
    std::string expected_result = "The spheres intersect in a circle";
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphere, test_4_2_intersect_in_a_circle) {
    // Arrange
    Sphere<int> z1(5, 5, 5, 5), z2(6, 6, 6, 5);

    // Act
    std::string actual_result = z1.check_relative_location(z2);

    // Assert
    std::string expected_result = "The spheres intersect in a circle";
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphere, test_5_1_smaller_inside_larger) {
    // Arrange
    Sphere<int> z1(5, 5, 5, 5), z2(5, 5, 5, 2);

    // Act
    std::string actual_result = z1.check_relative_location(z2);

    // Assert
    std::string expected_result = "One sphere is completely inside the other (smaller inside larger)";
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphere, test_5_2_larger_contains_smaller) {
    // Arrange
    Sphere<int> z1(5, 5, 5, 2), z2(5, 5, 5, 5);

    // Act
    std::string actual_result = z1.check_relative_location(z2);

    // Assert
    std::string expected_result = "One sphere is completely inside the other (larger contains smaller)";
    EXPECT_EQ(expected_result, actual_result);
}
