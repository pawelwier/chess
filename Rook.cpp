#include "Rook.hpp"
#include "Player.hpp"
#include "PieceType.hpp"
#include "MoveOptions.hpp"
#include "MoveUtils.hpp"
#include "Piece.hpp"
#include "Field.hpp"
#include "Utils.hpp"

#include <vector>
#include <array>

Rook::Rook(Player player, unsigned int fieldId) : Piece(player, rook, fieldId)
{
}

void Rook::getAvailableFieldIds(
    MoveOptions *options,
    unsigned int from,
    std::vector<Field> board,
    std::vector<Piece *> pieces)
{
    Player player = this->getPlayer();

    unsigned int x = board[from].getX();
    unsigned int y = board[from].getY();

    std::vector<unsigned int> horizontalLeft, horizontalRight, verticalUp, verticalDown;

    for (Field f : board)
    {
        if (f.getX() == x && f.getY() != y)
            if (f.getId() > from)
            {
                verticalUp.push_back(f.getId());
            }
            else
            {
                verticalDown.push_back(f.getId());
            }
        if (f.getY() == y && f.getX() != x)
            if (f.getId() > from)
            {
                horizontalRight.push_back(f.getId());
            }
            else
            {
                horizontalLeft.push_back(f.getId());
            }
    }

    // Utils::reverseVector(verticalDown);
    // Utils::reverseVector(horizontalLeft);

    std::array<std::vector<unsigned int>, 4> moveOptions{
        horizontalLeft,
        horizontalRight,
        verticalUp,
        verticalDown};

    for (std::vector<unsigned int> moveSet : moveOptions)
    {
        MoveUtils::addMoveOptions(moveSet, pieces, options, player);
    }
}