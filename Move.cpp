#include "Move.hpp"
#include "Field.hpp"
// #include "Game.hpp"

#include <iostream>
#include <string>

// void Move::printMove()
// {
//     std::cout << std::to_string(pieceId_) + " -> ..." << std::endl;
// }

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