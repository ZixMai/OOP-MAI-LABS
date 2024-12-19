#include "gtest/gtest.h"
#include "../src/Trapezoid.h"
#include "../src/Pentagon.h"
#include "../src/Rhombus.h"
#include "../src/FigureArray.h"

TEST(TrapezoidTests, CopyConstructorTest) {
    Point<double> vertices[4] = { Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2) };
    Trapezoid<double> trapezoidA(vertices);
    Trapezoid<double> trapezoidB = trapezoidA;
    EXPECT_EQ(trapezoidA, trapezoidB);
}

TEST(TrapezoidTests, MoveConstructorTest) {
    Point<double> vertices[4] = { Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2) };
    Trapezoid<double> trapezoidA(vertices);
    Trapezoid<double> trapezoidB = std::move(trapezoidA);
    EXPECT_NEAR(static_cast<double>(trapezoidB), 6.0, 1e-6);
}

TEST(TrapezoidTests, AreaOperatorTest) {
    Point<double> vertices[4] = { Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2) };
    Trapezoid<double> trapezoid(vertices);
    double area = static_cast<double>(trapezoid);
    EXPECT_NEAR(area, 6.0, 1e-6);
}

TEST(TrapezoidTests, CenterCalculationTest) {
    Point<double> vertices[4] = { Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2) };
    Trapezoid<double> trapezoid(vertices);
    Point<double> center = trapezoid.geometricCenter();
    EXPECT_NEAR(center.x_, 2.0, 1e-6);
    EXPECT_NEAR(center.y_, 1.0, 1e-6);
}

TEST(TrapezoidTests, EqualityCheckTest) {
    Point<double> vertices[4] = { Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2) };
    Trapezoid<double> trapezoidA(vertices);
    Trapezoid<double> trapezoidB(vertices);
    EXPECT_TRUE(trapezoidA == trapezoidB);
}

TEST(PentagonTests, CopyConstructorTest) {
    Point<double> vertices[5] = { Point<double>(0, 0), Point<double>(2, 0), Point<double>(2.618, 1.902), Point<double>(1, 3.077), Point<double>(-0.618, 1.902) };
    Pentagon<double> pentagonA(vertices);
    Pentagon<double> pentagonB = pentagonA;
    EXPECT_EQ(pentagonA, pentagonB);
}

TEST(PentagonTests, MoveConstructorTest) {
    Point<double> vertices[5] = { Point<double>(0, 0), Point<double>(2, 0), Point<double>(2.618, 1.902), Point<double>(1, 3.077), Point<double>(-0.618, 1.902) };
    Pentagon<double> pentagonA(vertices);
    Pentagon<double> pentagonB = std::move(pentagonA);
    EXPECT_NEAR(static_cast<double>(pentagonB), 6.88, 1e-3);
}

TEST(PentagonTests, AreaOperatorTest) {
    Point<double> vertices[5] = { Point<double>(0, 0), Point<double>(2, 0), Point<double>(2.618, 1.902), Point<double>(1, 3.077), Point<double>(-0.618, 1.902) };
    Pentagon<double> pentagon(vertices);
    double area = static_cast<double>(pentagon);
    EXPECT_NEAR(area, 6.88, 1e-3);
}

TEST(PentagonTests, CenterCalculationTest) {
    Point<double> vertices[5] = { Point<double>(0, 0), Point<double>(2, 0), Point<double>(2.618, 1.902), Point<double>(1, 3.077), Point<double>(-0.618, 1.902) };
    Pentagon<double> pentagon(vertices);
    Point<double> center = pentagon.geometricCenter();
    EXPECT_NEAR(center.x_, 1.0, 1e-3);
    EXPECT_NEAR(center.y_, 1.376, 1e-3);
}

TEST(PentagonTests, EqualityCheckTest) {
    Point<double> vertices[5] = { Point<double>(0, 0), Point<double>(2, 0), Point<double>(2.618, 1.902), Point<double>(1, 3.077), Point<double>(-0.618, 1.902) };
    Pentagon<double> pentagonA(vertices);
    Pentagon<double> pentagonB(vertices);
    EXPECT_TRUE(pentagonA == pentagonB);
}

TEST(RhombusTests, CopyConstructorTest) {
    Point<double> vertices[4] = { Point<double>(0, 0), Point<double>(2, 1), Point<double>(0, 2), Point<double>(-2, 1) };
    Rhombus<double> rhombusA(vertices);
    Rhombus<double> rhombusB = rhombusA;
    EXPECT_EQ(rhombusA, rhombusB);
}

TEST(RhombusTests, MoveConstructorTest) {
    Point<double> vertices[4] = { Point<double>(0, 0), Point<double>(2, 1), Point<double>(0, 2), Point<double>(-2, 1) };
    Rhombus<double> rhombusA(vertices);
    Rhombus<double> rhombusB = std::move(rhombusA);
    EXPECT_NEAR(static_cast<double>(rhombusB), 4.0, 1e-6);
}

TEST(RhombusTests, AreaOperatorTest) {
    Point<double> vertices[4] = { Point<double>(0, 0), Point<double>(2, 1), Point<double>(0, 2), Point<double>(-2, 1) };
    Rhombus<double> rhombus(vertices);
    double area = static_cast<double>(rhombus);
    EXPECT_NEAR(area, 4.0, 1e-6);
}

TEST(RhombusTests, CenterCalculationTest) {
    Point<double> vertices[4] = { Point<double>(0, 0), Point<double>(2, 1), Point<double>(0, 2), Point<double>(-2, 1) };
    Rhombus<double> rhombus(vertices);
    Point<double> center = rhombus.geometricCenter();
    EXPECT_NEAR(center.x_, 0.0, 1e-6);
    EXPECT_NEAR(center.y_, 1.0, 1e-6);
}

TEST(RhombusTests, EqualityCheckTest) {
    Point<double> vertices[4] = { Point<double>(0, 0), Point<double>(2, 1), Point<double>(0, 2), Point<double>(-2, 1) };
    Rhombus<double> rhombusA(vertices);
    Rhombus<double> rhombusB(vertices);
    EXPECT_TRUE(rhombusA == rhombusB);
}

TEST(FigureArrayTests, AddAndCalculateTotalAreaTest) {
    FigureArray<Figure<double>> figureArray;
    Point<double> vertices[5] { Point<double>(0, 0), Point<double>(2, 0), Point<double>(2.618, 1.902), Point<double>(1, 3.077), Point<double>(-0.618, 1.902) };
    auto pentagon = std::make_shared<Pentagon<double>>(vertices);
    figureArray.add(pentagon);
    EXPECT_NEAR(figureArray.totalArea(), static_cast<double>(*pentagon), 1e-6);
}

TEST(FigureArrayTests, RemoveElementTest) {
    FigureArray<Figure<double>> figureArray;
    Point<double> vertices[5] { Point<double>(0, 0), Point<double>(2, 0), Point<double>(2.618, 1.902), Point<double>(1, 3.077), Point<double>(-0.618, 1.902) };
    auto pentagon = std::make_shared<Pentagon<double>>(vertices);
    figureArray.add(pentagon);
    figureArray.remove(0);
    EXPECT_EQ(figureArray.size(), 0);
}

TEST(FigureArrayTests, SizeCheckTest) {
    FigureArray<Figure<double>> figureArray;
    EXPECT_EQ(figureArray.size(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
