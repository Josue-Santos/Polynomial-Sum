#include "../Project_4/polynomial.hpp"
#include <iostream>
#include<gtest/gtest.h>


struct TestPolynomial : testing::Test
{
	Polynomial p1;
	Polynomial p2;

	Term t1;
	Term t2;
	Term t3;
	Term t4;
	Term t5;
};


TEST_F(TestPolynomial, CopyConstructor)
{
	// -99x^99 - 1x^100
	t1.coefficient = -99; t1.exponent = 99;
	t2.coefficient = -1; t2.exponent = 100;

	p1.addTerm(t1);
	p1.addTerm(t2);

	Polynomial p(p1);

	EXPECT_EQ(p.degree(), p1.degree());
	EXPECT_EQ(p.coefficientFor(99), p1.coefficientFor(99));
	EXPECT_EQ(p.coefficientFor(100), p1.coefficientFor(100));
}

TEST_F(TestPolynomial, MoveConstructor)
{
	// 111x^1 + 0
	t1.coefficient = 111; t1.exponent = 1;
	t2.coefficient = 0; t2.exponent = 0;

	p1.addTerm(t1);
	p1.addTerm(t2);

	Polynomial p(std::move(p1));

	EXPECT_EQ(1, p.degree());
	EXPECT_EQ(111, p.coefficientFor(1));
	EXPECT_EQ(0, p.coefficientFor(0));

}

TEST_F(TestPolynomial, CopyAssignment)
{
	// 2x^4 // 4x^2
	t1.coefficient = 2; t1.exponent = 4;
	t2.coefficient = 4; t2.exponent = 2;

	p1.addTerm(t1);
	p2.addTerm(t2);

	p1 = p2;

	EXPECT_EQ(p2.degree(), p1.degree());
	EXPECT_EQ(p2.coefficientFor(4), p1.coefficientFor(4));
	EXPECT_EQ(0, p1.coefficientFor(4));
}

TEST_F(TestPolynomial, MoveAssignment)
{
	//123x^321 // 456x^654
	t1.coefficient = 123; t1.exponent = 321;
	t2.coefficient = 456; t2.exponent = 654;

	p1.addTerm(t1);
	p2.addTerm(t2);

	p2 = std::move(p1);

	EXPECT_EQ(321, p2.degree());
	EXPECT_EQ(123, p2.coefficientFor(321));
}

TEST_F(TestPolynomial, Equality)
{
	//1000x^10 // 1000x^10
	t1.coefficient = 1000; t1.exponent = 10;
	t2.coefficient = 1000; t2.exponent = 10;

	p1.addTerm(t1);
	p2.addTerm(t2);

	EXPECT_TRUE(p1 == p2);
	EXPECT_FALSE(p1 != p2);
	EXPECT_TRUE(p1 >= p2);
	EXPECT_FALSE(p1 > p2);
	EXPECT_TRUE(p1 <= p2);
	EXPECT_FALSE(p1 < p2);
}

TEST_F(TestPolynomial, Inequality)
{
	//1000x^10 // 10x^1000
	t1.coefficient = 1000; t1.exponent = 10;
	t2.coefficient = 10; t2.exponent = 1000;

	p1.addTerm(t1);
	p2.addTerm(t2);

	EXPECT_FALSE(p1 == p2);
	EXPECT_TRUE(p1 != p2);
	EXPECT_FALSE(p1 >= p2);
	EXPECT_FALSE(p1 > p2);
	EXPECT_TRUE(p1 <= p2);
	EXPECT_TRUE(p1 < p2);
}

TEST_F(TestPolynomial, InequalityTermPoly)
{
	//10x^1000 - 1000x^10
	t1.coefficient = -1000; t1.exponent = 10;
	t2.coefficient = 10; t2.exponent = 1000;

	p1.addTerm(t1);
	p1.addTerm(t2);

	EXPECT_FALSE(p1 == t2);
	EXPECT_TRUE(p1 != t2);

	EXPECT_FALSE(p1 >= t2);

}

TEST_F(TestPolynomial, Great)
{
	Term t; t.coefficient = 1; t.exponent = 1;

	// 1x^1 + 1x^99 // 1x^1 - 1x^99
	t1.coefficient = 1; t1.exponent = 99;
	t2.coefficient = -1; t2.exponent = 99;

	p1.addTerm(t);
	p1.addTerm(t);
	p2.addTerm(t);
	p2.addTerm(t2);

	EXPECT_FALSE(p1 == p2);
	EXPECT_TRUE(p1 != p2);
	EXPECT_TRUE(p1 >= p2);
	EXPECT_TRUE(p1 > p2);
	EXPECT_FALSE(p1 <= p2);
	EXPECT_FALSE(p1 < p2);
}

TEST_F(TestPolynomial, Less)
{
	// -37x^10 // 37x^9
	t1.coefficient = -37; t1.exponent = 10;
	t2.coefficient = 37; t2.exponent = 9;

	p1.addTerm(t1);
	p2.addTerm(t2);

	EXPECT_FALSE(p1 == p2);
	EXPECT_TRUE(p1 != p2);
	EXPECT_FALSE(p1 >= p2);
	EXPECT_FALSE(p1 > p2);
	EXPECT_TRUE(p1 <= p2);
	EXPECT_TRUE(p1 < p2);
}

TEST_F(TestPolynomial, Addition)
{
	// 10x^3 // 20x^3
	t1.coefficient = 10; t1.exponent = 3;
	t2.coefficient = 20; t2.exponent = 3;

	p1.addTerm(t1);
	p2.addTerm(t2);

	Polynomial add;
	add = p1 + p2;

	EXPECT_EQ(3, add.degree());
	EXPECT_EQ(30, add.coefficientFor(3));
}

TEST_F(TestPolynomial, Substraction)
{
	// 30x^1 // 20x^1
	t1.coefficient = 30; t1.exponent = 1;
	t2.coefficient = 20; t2.exponent = 1;

	p1.addTerm(t1);
	p2.addTerm(t2);

	Polynomial sub;
	sub = p1 - p2;

	EXPECT_EQ(1, sub.degree());
	EXPECT_EQ(10, sub.coefficientFor(1));
}

TEST_F(TestPolynomial, ArraySubscript)
{
	// 20x^88 - 20x^77
	t1.coefficient = 20; t1.exponent = 88;
	t2.coefficient = -20; t2.exponent = 77;

	p1.addTerm(t1);
	p1.addTerm(t2);

	EXPECT_EQ(20, p1[88]);
	EXPECT_EQ(-20, p1[77]);
	EXPECT_EQ(0, p1[66]);
}

TEST_F(TestPolynomial, MinusUnary)
{
	// -20x^2 + 10x^1
	t1.coefficient = -20; t1.exponent = 2;
	t2.coefficient = 10; t2.exponent = 1;

	p1.addTerm(t1);
	p1.addTerm(t2);

	Polynomial p2 = -p1;

	EXPECT_EQ(20, p2.coefficientFor(2));
	EXPECT_EQ(-10, p2.coefficientFor(1));
}

TEST_F(TestPolynomial, plusEqual)
{
	// -20x^2 + 10x^1
	t1.coefficient = -20; t1.exponent = 2;
	t2.coefficient = 10; t2.exponent = 1;
	p1.addTerm(t1);
	p1.addTerm(t2);

	// 10x^2 - 7x^1
	t1.coefficient = 10; t1.exponent = 2;
	t2.coefficient = -7; t2.exponent = 1;

	p2.addTerm(t1);
	p2.addTerm(t2);

	Polynomial p3;
	p3 = p1 + p2;

	p1 += p2;

	EXPECT_TRUE(p3 == p1);
}

TEST_F(TestPolynomial, lessEqual)
{
	// 20x^2 + 10x^1
	t1.coefficient = 20; t1.exponent = 2;
	t2.coefficient = 10; t2.exponent = 1;
	p1.addTerm(t1);
	p1.addTerm(t2);

	// 10x^2 + 7x^1
	t1.coefficient = 10; t1.exponent = 2;
	t2.coefficient = 7; t2.exponent = 1;

	p2.addTerm(t1);
	p2.addTerm(t2);

	Polynomial p3;
	p3 = p1 - p2;

	p1 -= p2;

	EXPECT_TRUE(p3 == p1);
}

TEST_F(TestPolynomial, functionP)
{
	// 20x^2 + 10x^1
	t1.coefficient = 2; t1.exponent = 3;
	t2.coefficient = 7; t2.exponent = 1;
	p1.addTerm(t1);
	p1.addTerm(t2);


	EXPECT_EQ(285, p1(5));
}

TEST_F(TestPolynomial, functionP2)
{
	Term t3;
	Term t4;
	Term t5;

	// 20x^2 + 10x^1
	t1.coefficient = -20; t1.exponent = 4;
	t2.coefficient = 5; t2.exponent = 3;
	t3.coefficient = -2; t3.exponent = 2;
	t4.coefficient = 1; t4.exponent = 1;
	t5.coefficient = -7; t5.exponent = 0;
	p1.addTerm(t1);
	p1.addTerm(t2);
	p1.addTerm(t3);
	p1.addTerm(t4);
	p1.addTerm(t5);

	EXPECT_EQ(-293, p1(2));
}

TEST_F(TestPolynomial, TermToPolynomial)
{
	// 2
	t1.coefficient = 2; t1.exponent = 0;
	p1.addTerm(t1);
	Polynomial pp = t1;

	EXPECT_TRUE(p1 == pp);
	EXPECT_TRUE(pp == p1);
}

TEST_F(TestPolynomial, DoubleToPolynomial)
{
	// 10
	t1.coefficient = 10; t1.exponent = 0;
	p1.addTerm(t1);
	Polynomial pp = 10;

	EXPECT_TRUE(p1 == pp);
	EXPECT_TRUE(pp == p1);
}

TEST_F(TestPolynomial, PolynomialToTerm)
{
	// -2^77
	t1.coefficient = -2; t1.exponent = 77;
	p1.addTerm(t1);

	Term t = Term(p1);

	EXPECT_EQ(t.coefficient, p1.coefficientFor(77));
	EXPECT_EQ(t.exponent, p1.degree());
}


TEST_F(TestPolynomial, PolynomialToDouble)
{
	// 10
	t1.coefficient = 10; t1.exponent = 0;
	p1.addTerm(t1);

	double d = double(p1);

	EXPECT_TRUE(d == 10);
}


TEST_F(TestPolynomial, Insertion)
{
	// 1x^3 + 2x + 18
	t1.coefficient = 1; t1.exponent = 3;
	p1.addTerm(t1);
	t1.coefficient = 2; t1.exponent = 1;
	p1.addTerm(t1);
	t1.coefficient = 18; t1.exponent = 0;
	p1.addTerm(t1);

	EXPECT_EQ(3, p1.degree());
}

TEST_F(TestPolynomial, Print)
{
	// 1x^3 + 2x + 18
	t1.coefficient = 1; t1.exponent = 3;
	p1.addTerm(t1);

	std::cout << p2 << std::endl;

	EXPECT_EQ(3, p1.degree());
}

TEST_F(TestPolynomial, compareDoubleWithPolynomial)
{
	t1.coefficient = 1; t1.exponent = 4;
	p1.addTerm(t1);

	double x = 1;

	EXPECT_TRUE(p1 >= x);
	std::cout << p1;
	EXPECT_TRUE(p1 != x);
	EXPECT_TRUE(p1 > x);
	EXPECT_FALSE(p1 < x);
	EXPECT_FALSE(p1 <= x);
	EXPECT_FALSE(p1 == x);

	EXPECT_TRUE(x <= p1);
	EXPECT_TRUE(x != p1);
	EXPECT_TRUE(x < p1);
	EXPECT_FALSE(x == p1);
	EXPECT_FALSE(x > p1);
	EXPECT_FALSE(x >= p1);

}

TEST_F(TestPolynomial, compareTermWithPolynomial)
{
	// 1x^4 + 2x^2
	t1.coefficient = 1; t1.exponent = 4;
	t2.coefficient = 2; t2.exponent = 2;
	p1.addTerm(t1);
	p1.addTerm(t2);


	EXPECT_TRUE(p1 >= t1);
	EXPECT_TRUE(p1 != t1);
	EXPECT_TRUE(p1 > t1);
	EXPECT_FALSE(p1 < t1);
	EXPECT_FALSE(p1 <= t1);
	EXPECT_FALSE(p1 == t1);

	EXPECT_TRUE(t1 <= p1);
	EXPECT_TRUE(t1 != p1);
	EXPECT_TRUE(t1 < p1);
	EXPECT_FALSE(t1 == p1);
	EXPECT_FALSE(t1 > p1);
	EXPECT_FALSE(t1 >= p1);

}

TEST_F(TestPolynomial, Print2)
{
	// 2x^2 + x + 1
	t1.coefficient = 2; t1.exponent = 1;
	t2.coefficient = 2; t2.exponent = 0;

	p1.addTerm(t1);
	p1.addTerm(t2);

	std::cout << p1 << std::endl;
	EXPECT_TRUE(true);

}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
												BELOW IS THE TEST CASES FOR THE PROJECT THREE
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

TEST(PolynomialTests, CheckingConstructor) {
	Polynomial a;
	Term x;
	x.coefficient = 2;
	x.exponent = 4;
	EXPECT_TRUE(a.addTerm(x));

	Polynomial b;
	ASSERT_EQ(0, b.degree());
}
TEST(PolynomialTests, CheckingCopyConstructorandEquality) {
	Polynomial a;
	Term x;
	x.coefficient = 2;
	x.exponent = 4;
	Term y;
	y.coefficient = 5;
	y.exponent = 7;

	a.addTerm(x);
	Polynomial b(a);
	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a != b);

	Polynomial c;
	c.addTerm(x);
	EXPECT_TRUE(c == b);
	EXPECT_FALSE(c != b);

	Polynomial d;
	d.addTerm(y);

	c = std::move(d);
	ASSERT_TRUE(a != c);

}
TEST(PolynomialTests, CheckingCopyConstructor2) {
	Polynomial p;
	Polynomial q(p);
	Term x = { 2,3 };
	q.addTerm(x);
	p.addTerm(x);

	ASSERT_TRUE(3, q.degree());
	ASSERT_TRUE(3, p.degree());


}
TEST(PolynomialTests, CheckingMoveConstructor) {
	Polynomial a;
	Term x;
	x.coefficient = 2;
	x.exponent = 4;

	a.addTerm(x);
	Polynomial b;
	b = std::move(a);

	Polynomial c;
	c.addTerm(x);

	EXPECT_TRUE(c == b);
	EXPECT_TRUE(a != b);
}

TEST(PolynomialTests, CheckingGreaterThan) {
	Polynomial a, b;
	Term x;
	x.coefficient = 2;
	x.exponent = 4;

	Term y;
	y.coefficient = 6;
	y.exponent = 8;

	Term z;
	z.coefficient = 8;
	z.exponent = 8;

	a.addTerm(x);
	a.addTerm(y);

	b.addTerm(x);
	b.addTerm(z);


	EXPECT_TRUE(b > a);
	EXPECT_TRUE(a < b);
	EXPECT_TRUE(b > a);
	EXPECT_TRUE(a < b);
	EXPECT_FALSE(a > b);
	EXPECT_FALSE(b < a);

}
TEST(PolynomialTests, CheckingLessThan) {
	Polynomial a, b;
	Term x;
	x.coefficient = 2;
	x.exponent = 4;

	Term y;
	y.coefficient = 6;
	y.exponent = 8;

	Term z;
	z.coefficient = 3;
	z.exponent = 2;

	a.addTerm(x);
	b.addTerm(y);


	EXPECT_TRUE(a <= b);
	EXPECT_TRUE(b >= a);
	EXPECT_FALSE(a >= b);
	EXPECT_FALSE(b <= a);

	a.addTerm(z);

}
TEST(PolynomialTests, CopyAssigmentTest1) {
	Term x = { 3,2 };

	Polynomial p;
	p.addTerm(x);

	Polynomial q = p;
	ASSERT_EQ(2, q.degree());
	ASSERT_EQ(2, p.degree());
}
TEST(PolynomialTests, CopyAssignmentTest2) {
	Term x = { 3,2 };
	Term y = { 4,123 };
	Term z = { 123,34 };


	Polynomial p;
	p.addTerm(x);
	p.addTerm(y);
	p.addTerm(z);


	Polynomial q = p;
	ASSERT_EQ(123, q.degree());
	ASSERT_EQ(123, p.degree());
}
TEST(PolynomialTests, MoveAssignment) {
	Term x = { 3,2 };
	Term y = { 4,123 };
	Term z = { 123,34 };

	Polynomial p;
	p.addTerm(x);
	p.addTerm(y);
	p.addTerm(z);

	Polynomial q;
	q = std::move(p);

	ASSERT_EQ(123, q.degree());

	p = q;

	ASSERT_EQ(123, q.degree());
	ASSERT_EQ(123, p.degree());

	Polynomial b;
	b = std::move(b);
	ASSERT_EQ(NULL, b.coefficientFor(b.degree()));
	b.addTerm(x);

	ASSERT_EQ(2, b.degree());
}
TEST(PolynomialTests, Comparison) {

	Polynomial p;
	//polynomial with one coeffient and no exponent
	Polynomial g;
	Term z{ 4,0 };
	g.addTerm(z);

	//null poly
	Polynomial h;
	//null double
	double v = 0;
	//to populate p
	Term x{ 3,4 };
	Term y{ 0,2 };

	Term t{ 5,6 };
	double d = 4;

	p.addTerm(x);
	p.addTerm(y);

	ASSERT_TRUE(p != t);
	ASSERT_TRUE(t != p);
	ASSERT_TRUE(p != d);
	ASSERT_TRUE(d != p);

	ASSERT_FALSE(p == t);
	ASSERT_FALSE(t == p);
	ASSERT_FALSE(p == d);
	ASSERT_FALSE(d == p);

	//poly to double & opposite is true = 4
	ASSERT_TRUE(g == d);
	ASSERT_TRUE(d == g);

	//poly to double & opposite is true = null 
	ASSERT_TRUE(v == h);
	ASSERT_TRUE(h == v);



}
//Project 3 TESTS 
TEST(PolynomialTests, CheckingConstructor3) {
	Polynomial a;
	Term x;
	x.coefficient = 2;
	x.exponent = 4;
	EXPECT_TRUE(a.addTerm(x));
}

TEST(PolynomialTests, CheckingCopyConstructorandEquality3) {
	Polynomial a;
	Term x;
	x.coefficient = 2;
	x.exponent = 4;
	Term y;
	y.coefficient = 5;
	y.exponent = 7;

	a.addTerm(x);
	Polynomial b(a);
	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a != b);

	Polynomial c;
	c.addTerm(x);
	EXPECT_TRUE(c == b);
	EXPECT_FALSE(c != b);

	Polynomial d;
	d.addTerm(y);

	c = std::move(d);
	ASSERT_TRUE(a != c);

}
TEST(PolynomialTests, CheckingCopyConstructor23) {
	Polynomial a;
	Term x;
	x.coefficient = 2;
	x.exponent = 4;

	a.addTerm(x);
	Polynomial b(a);
	EXPECT_TRUE(a == b);

	Polynomial d = b;

	EXPECT_TRUE(a == d);
}
TEST(PolynomialTests, CheckingMoveConstructor3) {
	Polynomial a;
	Term x;
	x.coefficient = 2;
	x.exponent = 4;

	a.addTerm(x);
	Polynomial b;
	b = std::move(a);

	Polynomial c;
	c.addTerm(x);

	EXPECT_TRUE(c == b);
	EXPECT_TRUE(a != b);
}

TEST(PolynomialTests, CheckingGreaterThan3) {
	Polynomial a, b;
	Term x;
	x.coefficient = 2;
	x.exponent = 4;

	Term y;
	y.coefficient = 6;
	y.exponent = 8;

	Term z;
	z.coefficient = 2;
	z.exponent = 2;

	a.addTerm(x);
	b.addTerm(y);

	EXPECT_TRUE(b > a);
	EXPECT_TRUE(a < b);
	EXPECT_FALSE(a > b);
	EXPECT_FALSE(b < a);

	a.addTerm(y);
	b.addTerm(x);

	EXPECT_FALSE(a > b);

	a.addTerm(z);

	EXPECT_TRUE(a > b);
	EXPECT_FALSE(b > a);

	Polynomial c, d;
	c.addTerm(x);
	c.addTerm(y);

	d.addTerm(x);
	d.addTerm(y);
	d.addTerm(z);

	EXPECT_TRUE(d > c);
}
TEST(PolynomialTests, CheckingLessThan3) {
	Polynomial a, b;
	Term x;
	x.coefficient = 2;
	x.exponent = 4;

	Term y;
	y.coefficient = 6;
	y.exponent = 8;

	Term z;
	z.coefficient = 3;
	z.exponent = 2;

	a.addTerm(x);
	b.addTerm(y);


	EXPECT_TRUE(a <= b);
	EXPECT_TRUE(b >= a);
	EXPECT_FALSE(a >= b);
	EXPECT_FALSE(b <= a);

	a.addTerm(z);

}
TEST(PolynomialTests, MoveConstructorTest3) {
	Term x = { 3,2 };
	Polynomial p;
	p.addTerm(x);
	Polynomial q = p;
	ASSERT_EQ(2, q.degree());
	ASSERT_EQ(2, p.degree());


}
