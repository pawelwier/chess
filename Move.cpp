#include "Move.hpp"
#include "Field.hpp"

#include <iostream>
#include <string>

unsigned int Move::getFrom()
{
    return from_;
}

unsigned int Move::getTo()
{
    return to_;
}

unsigned int Move::getOrder()
{
    return order_;
}

unsigned int Move::getPieceId()
{
    return pieceId_;
}