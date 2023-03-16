#include "King.hpp"
#include "Player.hpp"
#include "PieceType.hpp"
#include "FieldUtils.hpp"
#include "MoveUtils.hpp"
#include "PieceUtils.hpp"
#include "MoveOptions.hpp"
#include "Piece.hpp"
#include "Field.hpp"
#include "Move.hpp"

#include <iostream>

King::King(unsigned int id, Player player, unsigned int fieldId) : Piece(id, player, PieceType::king, fieldId, 0)
{
}

void King::getAvailableMoves(
    MoveOptions *options,
    unsigned int from,
    std::vector<Field *> board,
    std::vector<Piece *> pieces,
    std::vector<Move *> moveHistory)
{
    Player player = this->getPlayer();
    std::vector<unsigned int> moves;

    InitialConfig config;
    unsigned int number = config.startNumber();
    unsigned int letter = config.startLetter();
    unsigned int count = config.fieldCount();
    unsigned int size = config.size();

    Field *fromField = FieldUtils::findFieldByFieldId(board, from);
    unsigned int x = fromField->getX();
    unsigned int y = fromField->getY();

    bool isTop = y == size;
    bool isBottom = y == number;
    bool isLeft = x == letter;
    bool isRight = y == letter + size - 1;

    if (!isTop)
    {
        moves.push_back(from + size);
        if (!isRight)
            moves.push_back(from + size - 1);
        if (!isLeft)
            moves.push_back(from + size + 1);
    }
    if (!isBottom)
    {
        moves.push_back(from - size);
        if (!isRight)
            moves.push_back(from - size - 1);
        if (!isLeft)
            moves.push_back(from - size + 1);
    }
    if (!isRight)
        moves.push_back(from - 1);
    if (!isLeft)
        moves.push_back(from + 1);

    // castle
    bool kingHasMoved = PieceUtils::pieceHasMoved(this, moveHistory);

    if (!kingHasMoved)
    {
        // castle king side
        Piece *kingAdjacentRightOne = PieceUtils::findPieceByFieldId(pieces, from + 1);
        Piece *kingAdjacentRightTwo = PieceUtils::findPieceByFieldId(pieces, from + 2);

        if (!kingAdjacentRightOne && !kingAdjacentRightTwo)
        {
            Piece *cornerRight = PieceUtils::findPieceByFieldId(pieces, from + 3);
            if (cornerRight && cornerRight->getType() == PieceType::rook && cornerRight->getPlayer() == player)
            {
                bool rookHasMoved = PieceUtils::pieceHasMoved(cornerRight, moveHistory);
                if (!rookHasMoved)
                {
                    moves.push_back(from + 2);
                }
            }
        }

        // castle queen side
        std::vector<int> leftIndexes = {1, 2, 3};
        if (std::all_of(leftIndexes.begin(), leftIndexes.end(), [pieces, from](int index)
                        { return !PieceUtils::findPieceByFieldId(pieces, from - index); }))
        {
            Piece *cornerLeft = PieceUtils::findPieceByFieldId(pieces, from - 4);
            if (cornerLeft && cornerLeft->getType() == PieceType::rook && cornerLeft->getPlayer() == player)
            {
                bool rookHasMoved = PieceUtils::pieceHasMoved(cornerLeft, moveHistory);
                if (!rookHasMoved)
                {
                    moves.push_back(from - 2);
                }
            }
        }
    }

    MoveUtils::addMoveOptions(moves, pieces, options, player, false);
}