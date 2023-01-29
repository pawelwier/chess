#include "King.hpp"
#include "Player.hpp"
#include "PieceType.hpp"
#include "FieldUtils.hpp"
#include "MoveUtils.hpp"
#include "MoveOptions.hpp"
#include "Piece.hpp"
#include "Field.hpp"

#include <iostream>

King::King(unsigned int id, Player player, unsigned int fieldId) : Piece(id, player, PieceType::king, fieldId, 0)
{
}

void King::getAvailableMoves(
    MoveOptions *options,
    unsigned int from,
    std::vector<Field *> board,
    std::vector<Piece *> pieces)
{
    Player player = this->getPlayer();
    std::vector<unsigned int> moves;

    InitialConfig config;
    unsigned int number = config.startNumber();
    unsigned int letter = config.startLetter();
    unsigned int count = config.fieldCount();
    unsigned int size = config.size();

    Field *fromField = FieldUtils::findFieldByFieldId(board, from);
    unsigned int id = fromField->getId();
    unsigned int x = fromField->getX();
    unsigned int y = fromField->getY();

    bool isTop = y == size;
    bool isBottom = y == number;
    bool isLeft = x == letter;
    bool isRight = y == letter + size - 1;

    if (!isTop)
    {
        moves.push_back(id + size);
        if (!isRight)
            moves.push_back(id + size - 1);
        if (!isLeft)
            moves.push_back(id + size + 1);
    }
    if (!isBottom)
    {
        moves.push_back(id - size);
        if (!isRight)
            moves.push_back(id - size - 1);
        if (!isLeft)
            moves.push_back(id - size + 1);
    }
    if (!isRight)
        moves.push_back(id - 1);
    if (!isLeft)
        moves.push_back(id + 1);

    MoveUtils::addMoveOptions(moves, pieces, options, player, false);
}