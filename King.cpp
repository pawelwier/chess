#include "King.hpp"
#include "Player.hpp"
#include "PieceType.hpp"
#include "MoveOptions.hpp"
#include "Piece.hpp"
#include "Field.hpp"

#include <iostream>

King::King(unsigned int id, Player player, unsigned int fieldId) : Piece(id, player, PieceType::king, fieldId)
{
}

void King::getAvailableFieldIds(
    MoveOptions *options,
    unsigned int from,
    std::vector<Field *> board,
    std::vector<Piece *> pieces)
{
    std::cout << "looking for king fields ..." << std::endl;
}