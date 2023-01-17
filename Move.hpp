#pragma once

#include <string>
#include <iostream>

class Move
{
private:
    unsigned int order_;
    unsigned int pieceId_;
    unsigned int from_;
    unsigned int to_;

public:
    Move(unsigned int order,
         unsigned int pieceId,
         unsigned int from,
         unsigned int to)
    {
        order_ = order;
        pieceId_ = pieceId;
        from_ = from;
        to_ = to;
    }

    // void printMove();

    unsigned int getFrom();

    unsigned int getTo();

    unsigned int getOrder();

    unsigned int getPieceId();
};