#pragma once

#include "MoveOptions.hpp"
#include "Field.hpp"
#include "PieceType.hpp"
#include "Player.hpp"

#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

class Piece
{
private:
    PieceType type_;
    Player player_;
    unsigned int fieldId_;

public:
    Piece(Player player, PieceType type, unsigned int fieldId);

    virtual void getAvailableFieldIds(
        MoveOptions *options,
        unsigned int from,
        std::vector<Field> board,
        std::vector<Piece *> pieces) = 0;

    void move(unsigned int to);

    std::string getName();

    Player getPlayer();

    unsigned int getFieldId();

    void setFieldId(unsigned int fieldId);
};