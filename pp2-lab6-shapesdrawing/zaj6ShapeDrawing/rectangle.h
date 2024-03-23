//
// Created by Damian Otto on 17/04/2023.
//
#include "shape.h"
#ifndef ZAD4SHAPEDRAWING_DLASTUDENTOW_RECTANGLE_H
#define ZAD4SHAPEDRAWING_DLASTUDENTOW_RECTANGLE_H

#endif //ZAD4SHAPEDRAWING_DLASTUDENTOW_RECTANGLE_H
namespace Shapes {
    class Rectangle : public Shape {
    public:
        Rectangle(int xFrom, int yFrom, int xTo, int yTo) : first_x(xFrom), first_y(yFrom), second_x(xTo), second_y(yTo) {};

        bool isIn(int x, int y) const override;
        int x() const{
            return first_x;
        }
        int xTo() const{
            return second_x;
        }
        int y() const{
            return first_y;
        }
        int yTo() const{
            return second_y;
        };
    private:
        int first_x;
        int first_y;
        int second_x;
        int second_y;
    };
};