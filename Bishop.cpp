#include "Bishop.hpp"
#include "Player.hpp"
#include "PieceType.hpp"
#include "FieldUtils.hpp"
#include "MoveUtils.hpp"
#include "MoveOptions.hpp"
#include "Piece.hpp"
#include "Field.hpp"
#include "Move.hpp"

#include <iostream>

Bishop::Bishop(unsigned int id, Player player, unsigned int fieldId) : Piece(id, player, PieceType::bishop, fieldId, 3)
{
}

void Bishop::getAvailableMoves(
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

    std::vector<unsigned int> upLeft, upRight, downLeft, downRight;

    for (Field *f : board)
    {
        int id = f->getId();
        unsigned int fieldX = f->getX();
        unsigned int fieldY = f->getY();

        // TODO: find a simple way?
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

    std::array<std::vector<unsigned int>, 4> moveOptions{
        upLeft,
        upRight,
        downLeft,
        downRight};

    for (std::vector<unsigned int> moveSet : moveOptions)
    {
        MoveUtils::addMoveOptions(moveSet, pieces, options, player);
    }
}