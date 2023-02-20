#include "Pawn.hpp"
#include "Player.hpp"
#include "PieceType.hpp"
#include "FieldUtils.hpp"
#include "PieceUtils.hpp"
#include "MoveUtils.hpp"
#include "MoveOptions.hpp"
#include "Piece.hpp"
#include "Field.hpp"
#include "Move.hpp"

Pawn::Pawn(unsigned int id, Player player, unsigned int fieldId) : Piece(id, player, PieceType::pawn, fieldId, 1)
{
}

void Pawn::getAvailableMoves(
    MoveOptions *options,
    unsigned int from,
    std::vector<Field *> board,
    std::vector<Piece *> pieces,
    std::vector<Move *> moves)
{
    Player player = this->getPlayer();
    InitialConfig config;

    unsigned int size = config.size();
    unsigned int startLetter = config.startLetter();

    unsigned int firstIndex = player ? from - size : from + size;
    if (MoveUtils::isFieldEmpty(firstIndex, pieces))
        options->addMove(firstIndex);

    bool isFirstMove = !PieceUtils::pieceHasMoved(this, moves);

    if (isFirstMove)
    {
        unsigned int longMoveIndex = player ? firstIndex - size : firstIndex + size;
        if (MoveUtils::isFieldEmpty(firstIndex, pieces) && MoveUtils::isFieldEmpty(longMoveIndex, pieces))
            options->addMove(longMoveIndex);
    }

    unsigned int x = board[from]->getX();

    bool isBorderLeft = x == startLetter;
    bool isBorderRight = x == (startLetter + size - 1);

    // en passant
    if (moves.size())
    {
        Move *lastMove = moves[moves.size() - 1];

        Piece *piece = PieceUtils::findPieceByPieceId(pieces, lastMove->getPieceId());
        bool isPawn = piece->getType() == PieceType::pawn;

        Field *toField = FieldUtils::findFieldByFieldId(board, lastMove->getTo());
        bool toAdjacentRight = isBorderRight ? false : toField->getId() == from + 1;
        bool toAdjacentLeft = isBorderLeft ? false : toField->getId() == from - 1;

        bool addEnPassant = isPawn && (toAdjacentRight || toAdjacentLeft);

        if (addEnPassant)
        {
            std::cout << "asd" << std::endl;
        }
    }

    unsigned int takeRight = player ? (from - size + 1) : (from + size + 1);
    unsigned int takeLeft = player ? (from - size - 1) : (from + size - 1);

    if (!isBorderLeft && MoveUtils::isOpponentPieceOnField(takeLeft, pieces, player))
        options->addTake(takeLeft);
    if (!isBorderRight && MoveUtils::isOpponentPieceOnField(takeRight, pieces, player))
        options->addTake(takeRight);
}