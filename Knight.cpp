#include "Knight.hpp"
#include "Player.hpp"
#include "PieceType.hpp"
#include "MoveUtils.hpp"
#include "FieldUtils.hpp"
#include "MoveOptions.hpp"
#include "Piece.hpp"
#include "Field.hpp"

Knight::Knight(Player player, unsigned int fieldId) : Piece(player, PieceType::knight, fieldId)
{
}

void Knight::getAvailableFieldIds(
    MoveOptions *options,
    unsigned int from,
    std::vector<Field> board,
    std::vector<Piece *> pieces)
{
    Player player = this->getPlayer();

    unsigned int x = board[from].getX();
    unsigned int y = board[from].getY();

    signed int two = 2, one = 1;

    std::array<std::array<unsigned int, 2>, 8>
        // TODO: make a fn
        moves = {
            {{x + two, y + one},
             {x + two, y - one},
             {x - two, y + one},
             {x - two, y - one},
             {x + one, y + two},
             {x + one, y - two},
             {x - one, y + two},
             {x - one, y - two}}};

    std::vector<unsigned int> ids;

    for (std::array<unsigned int, 2> move : moves)
    {

        if (MoveUtils::isOutsideBoard(move[0], move[1]))
            continue;
        unsigned int index = FieldUtils::getFieldIndexByPosition(board, Utils::getFieldCoordinates(move[0], move[1]));
        ids.push_back(index);
    }
    MoveUtils::addMoveOptions(ids, pieces, options, player, false);
}
