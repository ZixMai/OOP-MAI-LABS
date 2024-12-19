#include <iostream>
#include "src/Point.h"
#include "src/Trapezoid.h"
#include "src/Pentagon.h"
#include "src/Rhombus.h"
#include "src/FigureArray.h"

int main()
{
    Point points_trapezoid[4] = { Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2) };
    Point points_pentagon[5] = { Point(0, 0), Point(2, 0), Point(3, 1), Point(1.5, 3), Point(0, 1) };
    Point points_rhombus[4] = { Point(0, 0), Point(2, 1), Point(0, 2), Point(-2, 1) };

    Trapezoid trapezoid(points_trapezoid);
    Pentagon pentagon(points_pentagon);
    Rhombus rhombus(points_rhombus);

    std::cout << "Trapezoid Information: " << std::endl;
    std::cout << trapezoid << std::endl;
    std::cout << "Area: " << static_cast<double>(trapezoid) << std::endl;
    std::cout << "Geometric Center: " << trapezoid.geometricCenter() << std::endl;
    
    std::cout << "\nPentagon Information: " << std::endl;
    std::cout << pentagon << std::endl;
    std::cout << "Area: " << static_cast<double>(pentagon) << std::endl;
    std::cout << "Geometric Center: " << pentagon.geometricCenter() << std::endl;
    
    std::cout << "\nRhombus Information: " << std::endl;
    std::cout << rhombus << std::endl;
    std::cout << "Area: " << static_cast<double>(rhombus) << std::endl;
    std::cout << "Geometric Center: " << rhombus.geometricCenter() << std::endl;

    return 0;
}
