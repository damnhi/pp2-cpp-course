//
// Created by Damian Otto on 17/04/2023.
//
#include "shape.h"
#ifndef ZAD4SHAPEDRAWING_DLASTUDENTOW_CIRCLE_H
#define ZAD4SHAPEDRAWING_DLASTUDENTOW_CIRCLE_H

#endif //ZAD4SHAPEDRAWING_DLASTUDENTOW_CIRCLE_H

namespace Shapes {
    class Circle :public Shape{
    public:
        Circle(int xCenter, int yCenter, int radius): x_center(xCenter), y_center(yCenter), circle_radius(radius){};

        bool isIn(int x, int y) const override;
        int x() const{
            return x_center;
        }
        int y() const{
            return y_center;
        }
        int getRadius() const{
            return circle_radius;
        };
    private:
        int x_center;
        int y_center;
        int circle_radius;
    };
}