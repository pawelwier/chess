#include "Queen.hpp"
#include "Player.hpp"
#include "PieceType.hpp"
#include "MoveOptions.hpp"
#include "Piece.hpp"
#include "Field.hpp"

#include <iostream>

Queen::Queen(Player player, unsigned int fieldId) : Piece(player, queen, fieldId)
{
}

void Queen::getAvailableFieldIds(
    MoveOptions *options,
    unsigned int from,
    std::vector<Field> board,
    std::vector<Piece *> pieces)
{
    std::cout << "looking for queen fields ..." << std::endl;
}