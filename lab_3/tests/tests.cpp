#include "gtest/gtest.h"
#include "../src/Trapezoid.h"
#include "../src/Pentagon.h"
#include "../src/Rhombus.h"
#include "../src/FigureArray.h"

TEST(TrapezoidTest, CopyConstructor) {
    Point vertices[4] = { Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2) };
    Trapezoid trapezoid1(vertices);
    Trapezoid trapezoid2 = trapezoid1;
    EXPECT_EQ(trapezoid1, trapezoid2);
}

TEST(TrapezoidTest, MoveConstructor) {
    Point vertices[4] = { Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2) };
    Trapezoid trapezoid1(vertices);
    Trapezoid trapezoid2 = std::move(trapezoid1);
    EXPECT_EQ(static_cast<double>(trapezoid2), 6.0);
}

TEST(TrapezoidTest, AreaOperator) {
    Point vertices[4] = { Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2) };
    Trapezoid trapezoid(vertices);
    double calculatedArea = static_cast<double>(trapezoid);
    EXPECT_NEAR(calculatedArea, 6.0, 1e-6);
}

TEST(TrapezoidTest, CenterCalculation) {
    Point vertices[4] = { Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2) };
    Trapezoid trapezoid(vertices);
    Point center = trapezoid.geometricCenter();
    EXPECT_NEAR(center.x_, 2.0, 1e-6);
    EXPECT_NEAR(center.y_, 1.0, 1e-6);
}

TEST(TrapezoidTest, EqualityCheck) {
    Point vertices1[4] = { Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2) };
    Trapezoid trapezoid1(vertices1);
    Trapezoid trapezoid2(vertices1);
    EXPECT_TRUE(trapezoid1 == trapezoid2);
}

TEST(PentagonTest, CopyConstructor) {
    Point vertices[5] = { Point(0, 0), Point(2, 0), Point(3, 1), Point(1.5, 3), Point(0, 1) };
    Pentagon pentagon1(vertices);
    Pentagon pentagon2 = pentagon1;
    EXPECT_EQ(pentagon1, pentagon2);
}

TEST(PentagonTest, MoveConstructor) {
    Point vertices[5] = { Point(0, 0), Point(2, 0), Point(3, 1), Point(1.5, 3), Point(0, 1) };
    Pentagon pentagon1(vertices);
    Pentagon pentagon2 = std::move(pentagon1);
    EXPECT_NEAR(static_cast<double>(pentagon2), 5.5, 1e-6);
}

TEST(PentagonTest, AreaOperator) {
    Point vertices[5] = { Point(0, 0), Point(2, 0), Point(3, 1), Point(1.5, 3), Point(0, 1) };
    Pentagon pentagon(vertices);
    double calculatedArea = static_cast<double>(pentagon);
    EXPECT_NEAR(calculatedArea, 5.5, 1e-6);
}

TEST(PentagonTest, CenterCalculation) {
    Point vertices[5] = { Point(0, 0), Point(2, 0), Point(3, 1), Point(1.5, 3), Point(0, 1) };
    Pentagon pentagon(vertices);
    Point center = pentagon.geometricCenter();
    EXPECT_NEAR(center.x_, 1.3, 1e-6);
    EXPECT_NEAR(center.y_, 1.0, 1e-6);
}

TEST(PentagonTest, EqualityCheck) {
    Point vertices1[5] = { Point(0, 0), Point(2, 0), Point(3, 1), Point(1.5, 3), Point(0, 1) };
    Pentagon pentagon1(vertices1);
    Pentagon pentagon2(vertices1);
    EXPECT_TRUE(pentagon1 == pentagon2);
}

TEST(RhombusTest, CopyConstructor) {
    Point vertices[4] = { Point(0, 0), Point(2, 1), Point(0, 2), Point(-2, 1) };
    Rhombus rhombus1(vertices);
    Rhombus rhombus2 = rhombus1;
    EXPECT_EQ(rhombus1, rhombus2);
}

TEST(RhombusTest, MoveConstructor) {
    Point vertices[4] = { Point(0, 0), Point(2, 1), Point(0, 2), Point(-2, 1) };
    Rhombus rhombus1(vertices);
    Rhombus rhombus2 = std::move(rhombus1);
    EXPECT_NEAR(static_cast<double>(rhombus2), 4.0, 1e-6);
}

TEST(RhombusTest, AreaOperator) {
    Point vertices[4] = { Point(0, 0), Point(2, 1), Point(0, 2), Point(-2, 1) };
    Rhombus rhombus(vertices);
    double calculatedArea = static_cast<double>(rhombus);
    EXPECT_NEAR(calculatedArea, 4.0, 1e-6);
}

TEST(RhombusTest, CenterCalculation) {
    Point vertices[4] = { Point(0, 0), Point(2, 1), Point(0, 2), Point(-2, 1) };
    Rhombus rhombus(vertices);
    Point center = rhombus.geometricCenter();
    EXPECT_NEAR(center.x_, 0.0, 1e-6);
    EXPECT_NEAR(center.y_, 1.0, 1e-6);
}

TEST(RhombusTest, EqualityCheck) {
    Point vertices1[4] = { Point(0, 0), Point(2, 1), Point(0, 2), Point(-2, 1) };
    Rhombus rhombus1(vertices1);
    Rhombus rhombus2(vertices1);
    EXPECT_TRUE(rhombus1 == rhombus2);
}

TEST(FigureArrayTest, AddAndCalculateTotalArea) {
    FigureArray figureArray(10);
    Point vertices[5] = { Point(0, 0), Point(2, 0), Point(3, 1), Point(1.5, 3), Point(0, 1) };
    Pentagon* pentagon = new Pentagon(vertices);
    figureArray.add(pentagon);
    EXPECT_NEAR(figureArray.totalArea(), static_cast<double>(*pentagon), 1e-6);
    delete pentagon;
}

TEST(FigureArrayTest, RemoveElement) {
    FigureArray figureArray(10);
    Point vertices[5] = { Point(0, 0), Point(2, 0), Point(3, 1), Point(1.5, 3), Point(0, 1) };
    Pentagon pentagon(vertices);
    figureArray.add(&pentagon);
    figureArray.remove(0);
    EXPECT_EQ(figureArray.size(), 0);
}

TEST(FigureArrayTest, VerifySize) {
    FigureArray figureArray(10);
    EXPECT_EQ(figureArray.size(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
