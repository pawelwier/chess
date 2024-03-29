#include "Rook.hpp"
#include "../Player.hpp"
#include "../PieceType.hpp"
#include "../utils/FieldUtils.hpp"
#include "../utils/MoveUtils.hpp"
#include "../utils/Utils.hpp"
#include "../MoveOptions.hpp"
#include "../Piece.hpp"
#include "../Field.hpp"
#include "../Move.hpp"

#include <vector>
#include <array>

Rook::Rook(unsigned int id, Player player, unsigned int fieldId) : Piece(id, player, PieceType::rook, fieldId, 5)
{
}

void Rook::getAvailableMoves(
    InitialConfig *config,
    MoveOptions *options,
    std::vector<Field *> board,
    std::vector<Piece *> pieces,
    std::vector<Move *> moves,
    Player player)
{
    unsigned int from = this->getFieldId();
    Field *fromField = FieldUtils::findFieldByFieldId(board, from);
    unsigned int x = fromField->getX();
    unsigned int y = fromField->getY();

    std::vector<unsigned int> horizontalLeft, horizontalRight, verticalUp, verticalDown;

    for (Field *f : board)
    {
        unsigned int id = f->getId();
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
    }

    std::array<std::vector<unsigned int>, 4> moveOptions{
        Utils::reverseVector(horizontalLeft),
        horizontalRight,
        Utils::reverseVector(verticalUp),
        verticalDown};

    for (std::vector<unsigned int> moveSet : moveOptions)
    {
        MoveUtils::addMoveOptions(moveSet, pieces, options, player);
    }
}