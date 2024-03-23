//
// Created by Damian Otto on 17/04/2023.
//
#include <cmath>
#include "circle.h"
bool Shapes::Circle::isIn(int x, int y) const {
    float distance_from_center = sqrt(pow(x_center-x,2) + pow(y_center-y,2));
    if(distance_from_center <= (float) circle_radius){
        return true;
    }
    else {
        return false;
    }
}