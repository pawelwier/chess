#include "Knight.hpp"
#include "Player.hpp"
#include "PieceType.hpp"
#include "FieldUtils.hpp"
#include "MoveUtils.hpp"
#include "MoveOptions.hpp"
#include "Piece.hpp"
#include "Field.hpp"
#include "Move.hpp"

Knight::Knight(unsigned int id, Player player, unsigned int fieldId) : Piece(id, player, PieceType::knight, fieldId, 3)
{
}

void Knight::getAvailableMoves(
    MoveOptions *options,
    unsigned int from,
    std::vector<Field *> board,
    std::vector<Piece *> pieces,
    std::vector<Move *> moveHistory)
{
    Player player = this->getPlayer();

    unsigned int x = FieldUtils::findFieldByFieldId(board, from)->getX();
    unsigned int y = FieldUtils::findFieldByFieldId(board, from)->getY();

    signed int two = 2, one = 1;

    std::array<std::array<unsigned int, 2>, 8>
        moves = {{{x + two, y + one},
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
