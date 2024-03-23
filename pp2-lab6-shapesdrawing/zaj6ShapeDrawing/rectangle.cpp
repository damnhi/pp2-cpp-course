//
// Created by Damian Otto on 17/04/2023.
//
#include "rectangle.h"

bool Shapes::Rectangle::isIn(int x, int y) const {
    if(first_x <= x && x<= second_x && first_y <= y && y<= second_y){
        return true;
    }
    else {
        return false;
    }
}