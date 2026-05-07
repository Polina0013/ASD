// Copyright 2026 Polina Pozdnova

#include <gtest/gtest.h>
#include "..\lib_monom\monom.h"

#define EPSILON 1e-10

//#define TEST_MONOM
#ifdef TEST_MONOM

TEST(TestMonom, check_empty_constructor) {
    Monom mon;
    EXPECT_TRUE(mon.is_zero());
}

TEST(TestMonom, check_coeff_constructor) {
    Monom mon(3.14);
    EXPECT_NEAR(mon.get_coeff(), 3.14, EPSILON);
}

TEST(TestMonom, check_coeff_and_powers_constructor) {
    int pow[3] = { 1, 0, 3 };
    Monom mon1(3.14, pow);
    Monom mon2(3.14, {1, 0, 3});

    EXPECT_EQ(mon1, mon2);
    EXPECT_NEAR(mon1.get_coeff(), mon2.get_coeff(), EPSILON);
}

TEST(TestMonom, check_copy_constructor) {
    Monom mon1(3.14, { 45, 98, 23 });
    Monom mon2(mon1);

    EXPECT_EQ(mon1, mon2);
}

TEST(TestMonom, the_exception_is_when_add_monomials_with_different_powers) {
    Monom mon1(3.14, { 45, 98, 23 });
    Monom mon2(8.6, { 5, 8, 3 });

    ASSERT_ANY_THROW(mon1 + mon2);
}

TEST(TestMonom, check_add) {
    Monom mon1(3.14, { 45, 98, 23 });
    Monom mon2(8.6, { 45, 98, 23 });

    EXPECT_NEAR((mon1 + mon2).get_coeff(), 11.74, EPSILON);
    EXPECT_EQ(mon1 + mon2, Monom(11.74, { 45, 98, 23 }));
}

TEST(TestMonom, the_exception_is_when_sub_monomials_with_different_powers) {
    Monom mon1(3.14, { 45, 98, 23 });
    Monom mon2(8.6, { 5, 8, 3 });

    ASSERT_ANY_THROW(mon1 - mon2);
}

TEST(TestMonom, check_sub) {
    Monom mon1(3.14, { 45, 98, 23 });
    Monom mon2(8.6, { 45, 98, 23 });

    EXPECT_NEAR((mon1 - mon2).get_coeff(), -5.46, EPSILON);
    EXPECT_EQ(mon1 - mon2, Monom(-5.46, { 45, 98, 23 }));
}

TEST(TestMonom, check_mult) {
    Monom mon1(7.365, { 5, 8, 3 });
    Monom mon2(-61, { 4, 9, 2 });

    EXPECT_NEAR((mon1 * mon2).get_coeff(), -449.265, EPSILON);
    EXPECT_EQ(mon1 * mon2, Monom(-449.265, { 9, 17, 5 }));
}

TEST(TestMonom, the_exception_is_when_div_by_zero_monom) {
    Monom mon1(3.14, { 45, 98, 23 });
    Monom mon2;

    ASSERT_ANY_THROW(mon1 / mon2);
}

TEST(TestMonom, the_exception_is_when_div_of_monomials_gets_negative_powers) {
    Monom mon1(3.14, { 45, 98, 23 });
    Monom mon2(8, { 45, 98, 33 });

    ASSERT_ANY_THROW(mon1 / mon2);
}

TEST(TestMonom, check_div) {
    Monom mon1(4.5, { 15, 83, 3 });
    Monom mon2(-1.55, { 4, 9, 2 });

    EXPECT_NEAR((mon1 / mon2).get_coeff(), -2.90322580645, EPSILON);
    EXPECT_EQ(mon1 / mon2, Monom(-2.90322580645, { 11, 74, 1 }));
}

TEST(TestMonom, check_mult_by_number) {
    Monom mon1(4.5, { 15, 83, 3 });

    EXPECT_NEAR((mon1 * (-0.256)).get_coeff(), -1.152, EPSILON);
    EXPECT_EQ(mon1 * (-0.256), Monom(-1.152, { 15, 83, 3 }));
}

TEST(TestMonom, the_exception_is_when_div_by_zero) {
    Monom mon1(3.14, { 45, 98, 23 });

    ASSERT_ANY_THROW(mon1 / 0.0);
}

TEST(TestMonom, check_div_by_number) {
    Monom mon1(1.152, { 15, 83, 3 });

    EXPECT_NEAR((mon1 / (0.8956)).get_coeff(), 1.28628852166, EPSILON);
    EXPECT_EQ(mon1 / (0.8956), Monom(1.28628852166, { 15, 83, 3 }));
}

TEST(TestMonom, check_value_at_the_point) {
    Monom mon1(1.5, { 5, 8, 3 });

    double x = 3.7;
    double y = -1.1;
    double z = -21.0;

    double expected = 1.5 * pow(x, 5) * pow(y, 8) * pow(z, 3);

    EXPECT_DOUBLE_EQ(mon1.value_at_the_point(x, y, z), expected);
}

TEST(TestMonom, check_the_comparison) {
    EXPECT_TRUE(Monom("-3.14x^1y^5") > Monom("-3.14y^5z^5"));
    EXPECT_FALSE(Monom("-3.14x^1y^5") < Monom("-3.14y^5z^5"));
}

TEST(TestMonom, check_parser) {
    EXPECT_EQ(Monom("-3.14x^1y^56z^0").to_string(), "-3.14xy^56");
    EXPECT_EQ(Monom("-x^1y^56z^0").to_string(), "-xy^56");
    EXPECT_ANY_THROW(Monom("-3.14x^1y^-56z^0"));
    EXPECT_ANY_THROW(Monom("-3.14x^1y^5z^"));
}

#endif // TEST_MONOM