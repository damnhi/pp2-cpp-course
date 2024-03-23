#include "object.h"
ObjectType Object::type() const
{
    return type_;
}
Position Object::position() const
{
    return position_;
}
void Object::setPosition(Position newPosition_)
{
    position_ = newPosition_;
}
void Object::moveUp()
{
    position_.moveUp();
}
void Object::moveDown()
{
    position_.moveDown();
}
void Object::moveLeft()
{
    position_.moveLeft();
}
void Object::moveRight()
{
    position_.moveRight();
}