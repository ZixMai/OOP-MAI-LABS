#include "gtest/gtest.h"
#include "../src/Trapezoid.h"
#include "../src/Pentagon.h"
#include "../src/Rhombus.h"
#include "../src/FigureArray.h"

TEST(TrapezoidTest, ConstructorCopy) {
    Point<double> points[4] = { Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2) };
    Trapezoid<double> t1(points);
    Trapezoid<double> t2 = t1;
    EXPECT_EQ(t1, t2);
}

TEST(TrapezoidTest, ConstructorMove) {
    Point<double> points[4] = { Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2) };
    Trapezoid<double> t1(points);
    Trapezoid<double> t2 = std::move(t1);
    EXPECT_NEAR(static_cast<double>(t2), 6.0, 1e-6);
}

TEST(TrapezoidTest, OperatorDouble) {
    Point<double> points[4] = { Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2) };
    Trapezoid<double> t(points);
    double area = static_cast<double>(t);
    EXPECT_NEAR(area, 6.0, 1e-6);
}

TEST(TrapezoidTest, GeometricCenter) {
    Point<double> points[4] = { Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2) };
    Trapezoid<double> t(points);
    Point<double> center = t.geometricCenter();
    EXPECT_NEAR(center.x_, 2.0, 1e-6);
    EXPECT_NEAR(center.y_, 1.0, 1e-6);
}

TEST(TrapezoidTest, EqualityOperator) {
    Point<double> points1[4] = { Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2) };
    Trapezoid<double> t1(points1);
    Trapezoid<double> t2(points1);
    EXPECT_TRUE(t1 == t2);
}

TEST(PentagonTest, ConstructorCopy) {
    Point<double> points[5] = { Point<double>(0, 0), Point<double>(2, 0), Point<double>(2.618, 1.902), Point<double>(1, 3.077), Point<double>(-0.618, 1.902) };
    Pentagon<double> p1(points);
    Pentagon<double> p2 = p1;
    EXPECT_EQ(p1, p2);
}

TEST(PentagonTest, ConstructorMove) {
    Point<double> points[5] = { Point<double>(0, 0), Point<double>(2, 0), Point<double>(2.618, 1.902), Point<double>(1, 3.077), Point<double>(-0.618, 1.902) };
    Pentagon<double> p1(points);
    Pentagon<double> p2 = std::move(p1);
    EXPECT_NEAR(static_cast<double>(p2), 6.88, 1e-3);
}

TEST(PentagonTest, OperatorDouble) {
    Point<double> points[5] = { Point<double>(0, 0), Point<double>(2, 0), Point<double>(2.618, 1.902), Point<double>(1, 3.077), Point<double>(-0.618, 1.902) };
    Pentagon<double> p(points);
    double area = static_cast<double>(p);
    EXPECT_NEAR(area, 6.88, 1e-3);
}

TEST(PentagonTest, GeometricCenter) {
    Point<double> points[5] = { Point<double>(0, 0), Point<double>(2, 0), Point<double>(2.618, 1.902), Point<double>(1, 3.077), Point<double>(-0.618, 1.902) };
    Pentagon<double> p(points);
    Point<double> center = p.geometricCenter();
    EXPECT_NEAR(center.x_, 1.0, 1e-3);
    EXPECT_NEAR(center.y_, 1.376, 1e-3);
}

TEST(PentagonTest, EqualityOperator) {
    Point<double> points1[5] = { Point<double>(0, 0), Point<double>(2, 0), Point<double>(2.618, 1.902), Point<double>(1, 3.077), Point<double>(-0.618, 1.902) };
    Pentagon<double> p1(points1);
    Pentagon<double> p2(points1);
    EXPECT_TRUE(p1 == p2);
}

TEST(RhombusTest, ConstructorCopy) {
    Point<double> points[4] = { Point<double>(0, 0), Point<double>(2, 1), Point<double>(0, 2), Point<double>(-2, 1) };
    Rhombus<double> r1(points);
    Rhombus<double> r2 = r1;
    EXPECT_EQ(r1, r2);
}

TEST(RhombusTest, ConstructorMove) {
    Point<double> points[4] = { Point<double>(0, 0), Point<double>(2, 1), Point<double>(0, 2), Point<double>(-2, 1) };
    Rhombus<double> r1(points);
    Rhombus<double> r2 = std::move(r1);
    EXPECT_NEAR(static_cast<double>(r2), 4.0, 1e-6);
}

TEST(RhombusTest, OperatorDouble) {
    Point<double> points[4] = { Point<double>(0, 0), Point<double>(2, 1), Point<double>(0, 2), Point<double>(-2, 1) };
    Rhombus<double> r(points);
    double area = static_cast<double>(r);
    EXPECT_NEAR(area, 4.0, 1e-6);
}

TEST(RhombusTest, GeometricCenter) {
    Point<double> points[4] = { Point<double>(0, 0), Point<double>(2, 1), Point<double>(0, 2), Point<double>(-2, 1) };
    Rhombus<double> r(points);
    Point<double> center = r.geometricCenter();
    EXPECT_NEAR(center.x_, 0.0, 1e-6);
    EXPECT_NEAR(center.y_, 1.0, 1e-6);
}

TEST(RhombusTest, EqualityOperator) {
    Point<double> points1[4] = { Point<double>(0, 0), Point<double>(2, 1), Point<double>(0, 2), Point<double>(-2, 1) };
    Rhombus<double> r1(points1);
    Rhombus<double> r2(points1);
    EXPECT_TRUE(r1 == r2);
}

TEST(FigureArrayTest, AddAndTotalArea) {
    FigureArray<Figure<double>> array;
    Point<double> points[5] { Point<double>(0, 0), Point<double>(2, 0), Point<double>(2.618, 1.902), Point<double>(1, 3.077), Point<double>(-0.618, 1.902) };
    auto p = std::make_shared<Pentagon<double>>(points);
    array.add(p);
    EXPECT_NEAR(array.totalArea(), static_cast<double>(*p), 1e-6);
}

TEST(FigureArrayTest, Remove) {
    FigureArray<Figure<double>> array;
    Point<double> points[5] { Point<double>(0, 0), Point<double>(2, 0), Point<double>(2.618, 1.902), Point<double>(1, 3.077), Point<double>(-0.618, 1.902) };
    auto p = std::make_shared<Pentagon<double>>(points);
    array.add(p);
    array.remove(0);
    EXPECT_EQ(array.size(), 0);
}

TEST(FigureArrayTest, Size) {
    FigureArray<Figure<double>> array;
    EXPECT_EQ(array.size(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}