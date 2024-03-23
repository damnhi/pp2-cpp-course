//
// Created by Damian Otto on 17/04/2023.
//
#include <utility>

#include "shape.h"
#ifndef ZAD4SHAPEDRAWING_DLASTUDENTOW_SHAPECOMPOSITE_H
#define ZAD4SHAPEDRAWING_DLASTUDENTOW_SHAPECOMPOSITE_H

#endif //ZAD4SHAPEDRAWING_DLASTUDENTOW_SHAPECOMPOSITE_H
namespace Shapes {
    class ShapeComposite : public Shape {
    public:
        ShapeComposite(std::shared_ptr<Shape> shape1, std::shared_ptr<Shape> shape2, ShapeOperation operation)
                : shape1(std::move(shape1)), shape2(std::move(shape2)), operation(operation) {}
        bool isIn(int x, int y) const override;

    private:
        std::shared_ptr<Shape> shape1;
        std::shared_ptr<Shape> shape2;
        ShapeOperation operation;
    };
}