#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <iostream>

class Move
{
private:
    unsigned int order_;
    unsigned int pieceId_;
    unsigned int from_;
    unsigned int to_;
    bool isTake_;

public:
    Move(unsigned int order,
         unsigned int pieceId,
         unsigned int from,
         unsigned int to,
         bool isTake)
    {
        order_ = order;
        pieceId_ = pieceId;
        from_ = from;
        to_ = to;
        isTake_ = isTake;
    }

    unsigned int getFrom();

    unsigned int getTo();

    unsigned int getOrder();

    unsigned int getPieceId();
};

#endif