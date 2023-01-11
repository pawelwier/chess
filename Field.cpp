#include "Field.hpp"
#include "Utils.hpp"

#define LOOP(x) for (int i = 0; i < x; i++)

Field::Field(unsigned short int x, unsigned short int y, unsigned short int id)
{
    x_ = x;
    y_ = y;
    id_ = id;
    isBlack_ = Utils::isOdd(x) == Utils::isOdd(y);
}

std::string Field::getField()
{
    return Utils::getFieldCoordinates(x_, y_);
}

// void Field::setField(
//     unsigned short int x,
//     unsigned short int y,
//     unsigned short int id)
// {
//     x_ = x;
//     y_ = y;
//     id_ = id;
//     isBlack_ = Utils::isOdd(x) == Utils::isOdd(y);
// }

unsigned short int Field::getId()
{
    return id_;
}

unsigned short int Field::getX()
{
    return x_;
}

unsigned short int Field::getY()
{
    return y_;
}

std::string Field::getFieldColor()
{
    return isBlack_ ? "(b)" : "(w)";
}