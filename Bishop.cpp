#include "Bishop.hpp"
#include "Player.hpp"
#include "PieceType.hpp"
#include "MoveOptions.hpp"
#include "Piece.hpp"
#include "Field.hpp"

#include <iostream>

Bishop::Bishop(unsigned int id, Player player, unsigned int fieldId) : Piece(id, player, bishop, fieldId)
{
}

void Bishop::getAvailableFieldIds(
    MoveOptions *options,
    unsigned int from,
    std::vector<Field> board,
    std::vector<Piece *> pieces)
{
    std::cout << "looking for bishop fields ..." << std::endl;
}