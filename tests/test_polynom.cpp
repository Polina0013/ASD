// Copyright 2026 Polina Pozdnova

#include <gtest/gtest.h>
#include "..\lib_polynom\polynom.h"

//#define TEST_POLYNOM
#ifdef TEST_POLYNOM

TEST(TestPolynom, check_empty_constructor) {
    Polynom poly;
    EXPECT_TRUE(poly.is_zero());
}

TEST(TestPolynom, check_monom_constructor_and_set_name) {
    Monom mon(3.14, {1, 2, 3});
    Polynom poly(mon);
    poly.set_name("polynom");
    //std::cout << poly << " " << poly.to_string();

    EXPECT_EQ(poly.to_string(), "3.14xy^2z^3");
    EXPECT_EQ(poly.get_name(), "polynom");
}

TEST(TestPolynom, check_monom_and_name_constructor) {
    Monom mon(3.1456, { 1, 2, 0 });
    Polynom poly(mon, "pol345");
    //std::cout << poly << " " << poly.to_string();

    EXPECT_EQ(poly.to_string(), "3.1456xy^2");
    EXPECT_EQ(poly.get_name(), "pol345");
}

TEST(TestPolynom, check_copy_constructor) {
    Monom mon1(3.14, { 45, 98, 23 });
    Monom mon2(6.3, { 12, 8, 0 });

    Polynom poly1 = Polynom(mon1) + mon2;
    Polynom poly2(poly1);

    EXPECT_EQ(poly1, poly2);
}

TEST(TestPolynom, check_add) {
    Monom mon1(6.34, { 0, 0, 0 });
    Monom mon2(8.6, { 0, 8, 1 });
    Monom mon3(3.14, { 45, 98, 23 });

    Polynom poly = Polynom(mon1) + mon2*2 + mon3;

    //std::cout << poly << " " << poly.to_string();
    EXPECT_EQ(poly.to_string(), "3.14x^45y^98z^23 + 17.2y^8z + 6.34");
}

TEST(TestPolynom, check_sub) {
    Monom mon2(8.6, { 0, 8, 1 });
    Monom mon3(3.14, { 45, 98, 23 });

    Polynom poly = Polynom(mon3) - mon3;
    //std::cout << poly << " " << poly.to_string() << " ";

    EXPECT_TRUE(poly.is_zero());

    poly -= mon2;

    //std::cout << poly << " " << poly.to_string() << " ";
    EXPECT_EQ(poly.to_string(), "-8.6y^8z");
}

TEST(TestPolynom, check_mult) {
    Monom mon1(6.34, { 0, 0, 0 });
    Monom mon2(8.6, { 0, 8, 1 });
    Monom mon3(-3.14, { 45, 98, 23 });

    Polynom poly = Polynom(mon1) * mon2;
    poly *= mon3;

    EXPECT_EQ(poly.to_string(), "-171.20536x^45y^106z^24");
}

TEST(TestPolynom, the_exception_is_when_div_by_zero) {
    Polynom poly(Monom(3.14, { 45, 98, 23 }));
    Polynom zero_poly;

    ASSERT_ANY_THROW(poly / zero_poly);
}

TEST(TestPolynom, division_when_the_power_is_negative) {
    Polynom dividend;
    dividend += Monom(6.0, { 2, 0, 0 });

    Polynom divisor;
    divisor += Monom(2.0, { 3, 0, 0 });

    std::pair<Polynom, Polynom> pair = dividend.divmod(divisor);

    //std::cout << "Dividend:  " << dividend << std::endl;
    //std::cout << "Divisor:   " << divisor << std::endl;
    //std::cout << "Quotient:  " << pair.first << std::endl;
    //std::cout << "Remainder: " << pair.second << std::endl;

    ASSERT_EQ(pair.first.to_string(), "0");
    ASSERT_EQ(pair.second.to_string(), "6x^2");
}

TEST(TestPolynom, check_divmod) {
    Polynom dividend;
    dividend += Monom(6.0, { 5, 8, 1 });
    dividend += Monom(4.0, { 3, 0, 2 });
    dividend += Monom(2.0, { 1, 0, 1 });
    dividend += Monom(5.0, { 0, 0, 1 });

    Polynom divisor;
    divisor += Monom(2.0, { 2, 0, 1 });
    divisor += Monom(1.0, { 0, 0, 0 });

    std::pair<Polynom, Polynom> pair = dividend.divmod(divisor);

    //std::cout << "Dividend:  " << dividend << std::endl;
    //std::cout << "Divisor:   " << divisor << std::endl;
    //std::cout << "Quotient:  " << pair.first << std::endl;
    //std::cout << "Remainder: " << pair.second << std::endl;

    ASSERT_EQ(pair.first.to_string(), "3x^3y^8");
    ASSERT_EQ(pair.second.to_string(), "-3x^3y^8 + 4x^3z^2 + 2xz + 5z");
}

TEST(TestPolynom, check_value_at_the_point) {
    Polynom poly;
    poly += Monom(6.0, { 5, 8, 1 });
    poly += Monom(-4.2, { 3, 0, 2 });

    double x = 3.7;
    double y = -1.1;
    double z = -2.0;

    double expected = 6.0 * pow(x, 5) * pow(y, 8) * pow(z, 1) - 4.2 * pow(x, 3) * pow(y, 0) * pow(z, 2);

    EXPECT_DOUBLE_EQ(poly.value_at_the_point(x, y, z), expected);
}

TEST(TestPolynom, check_parser) {
    EXPECT_EQ(Polynom("-3.14x^5y^56z^0 -  2.6x  ^1z^9").to_string(), "-3.14x^5y^56 -2.6xz^9");
    EXPECT_EQ(Polynom("POLY = -3.14x^5y^56z^0 -  2.6x  ^1z^9").get_name(), "POLY");
    EXPECT_ANY_THROW(Polynom("-3.14x^1y^-56z^0 + 6.89"));
    EXPECT_ANY_THROW(Polynom("-3.14x^1y^5z^ - 4.564x^7"));
    EXPECT_ANY_THROW(Polynom("-3.14x^1y^5z^ +"));
}

#endif // TEST_POLYNOM