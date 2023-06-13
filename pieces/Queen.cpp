#include "Queen.hpp"
#include "../Player.hpp"
#include "../PieceType.hpp"
#include "../utils/FieldUtils.hpp"
#include "../utils/MoveUtils.hpp"
#include "../MoveOptions.hpp"
#include "../Piece.hpp"
#include "../Field.hpp"
#include "../Move.hpp"

#include <iostream>

Queen::Queen(unsigned int id, Player player, unsigned int fieldId) : Piece(id, player, PieceType::queen, fieldId, 9)
{
}

void Queen::getAvailableMoves(
    MoveOptions *options,
    unsigned int from,
    std::vector<Field *> board,
    std::vector<Piece *> pieces,
    std::vector<Move *> moves)
{
    Player player = this->getPlayer();

    InitialConfig config;
    unsigned int number = config.startNumber();
    unsigned int letter = config.startLetter();
    unsigned int count = config.fieldCount();
    unsigned int size = config.size();

    Field *fromField = FieldUtils::findFieldByFieldId(board, from);
    unsigned int x = fromField->getX();
    unsigned int y = fromField->getY();

    std::vector<unsigned int> upLeft, upRight, downLeft, downRight, horizontalLeft, horizontalRight, verticalUp, verticalDown;

    for (Field *f : board)
    {
        int id = f->getId();
        unsigned int fieldX = f->getX();
        unsigned int fieldY = f->getY();

        // TODO: take out logic, use in rook, bishop, queen
        if (f->getX() == x && f->getY() != y)
            if (id > from)
            {
                verticalUp.push_back(id);
            }
            else
            {
                verticalDown.push_back(id);
            }
        if (f->getY() == y && f->getX() != x)
            if (id > from)
            {
                horizontalRight.push_back(id);
            }
            else
            {
                horizontalLeft.push_back(id);
            }
        if (fieldY == y + 1)
            if (x > letter && fieldX == x - 1)
            {
                while (id <= count && id % size != (size - 1))
                {
                    upLeft.push_back(id);
                    id += (size - 1);
                }
            }
            else if (x < (letter + size) && fieldX == x + 1)
            {
                while (id <= count && id % size)
                {
                    upRight.push_back(id);
                    id += (size + 1);
                }
            }
        if (fieldY == y - 1)
            if (x > letter && fieldX == x - 1)
            {
                while (id >= 0 && id % size != (size - 1))
                {
                    downLeft.push_back(id);
                    id -= (size + 1);
                }
            }
            else if (x < (letter + size) && fieldX == x + 1)
            {
                while (id >= 0 && id % size)
                {
                    downRight.push_back(id);
                    id -= (size - 1);
                }
            }
    }

    std::array<std::vector<unsigned int>, 8> moveOptions{
        upLeft, upRight, downLeft, downRight,
        Utils::reverseVector(horizontalLeft), horizontalRight, Utils::reverseVector(verticalUp), verticalDown};

    for (std::vector<unsigned int> moveSet : moveOptions)
    {
        MoveUtils::addMoveOptions(moveSet, pieces, options, player);
    }
}