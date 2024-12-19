#include <iostream>
#include "src/Point.h"
#include "src/Trapezoid.h"
#include "src/Pentagon.h"
#include "src/Rhombus.h"
#include "src/FigureArray.h"

int main()
{
    Point<double> points_trapezoid[4] = {
        Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2) 
    };
    Point<double> points_pentagon[5] = {
        Point<double>(0, 0),
        Point<double>(2, 0),
        Point<double>(2.618, 1.902),
        Point<double>(1, 3.077),
        Point<double>(-0.618, 1.902)
    };
    Point<double> points_rhombus[4] = {
        Point<double>(0, 0), Point<double>(2, 1), Point<double>(0, 2), Point<double>(-2, 1) 
    };

    Trapezoid<double> trapezoid(points_trapezoid);
    Pentagon<double> pentagon(points_pentagon);
    Rhombus<double> rhombus(points_rhombus);

    auto trapezoid_ptr = std::make_shared<Trapezoid<double>>(points_trapezoid);
    auto pentagon_ptr = std::make_shared<Pentagon<double>>(points_pentagon);
    auto rhombus_ptr = std::make_shared<Rhombus<double>>(points_rhombus);

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

    FigureArray<Figure<double>> figureArray;
    figureArray.add(trapezoid_ptr);
    figureArray.add(pentagon_ptr);
    figureArray.add(rhombus_ptr);

    std::cout << "\nFigures in Array: " << std::endl;
    for (size_t i = 0; i < figureArray.size(); ++i) {
        std::cout << figureArray[i] << std::endl;
    }

    return 0;
}
