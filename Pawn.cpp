#include "Pawn.hpp"
#include "Player.hpp"
#include "PieceType.hpp"
#include "MoveOptions.hpp"
#include "MoveUtils.hpp"
#include "Piece.hpp"
#include "Field.hpp"

Pawn::Pawn(unsigned int id, Player player, unsigned int fieldId) : Piece(id, player, pawn, fieldId)
{
}

void Pawn::getAvailableFieldIds(
    MoveOptions *options,
    unsigned int from,
    std::vector<Field> board,
    std::vector<Piece *> pieces)
{
    Player player = this->getPlayer();
    InitialConfig config;

    unsigned int size = config.size();
    unsigned int startLetter = config.startLetter();

    // Move

    // Check if there is piece on field in front
    unsigned int firstIndex = player ? from - size : from + size;
    if (MoveUtils::isFieldEmpty(firstIndex, pieces))
        options->addMove(firstIndex);

    // Check if first move
    // TODO: add move history to Game, check if piece has been moved
    // delete this var
    unsigned short int pawnIds[16] = {8, 9, 10, 11, 12, 13, 14, 15, 48, 49, 50, 51, 52, 53, 54, 55};

    unsigned short int *isFirstMove = std::find(std::begin(pawnIds), std::end(pawnIds), from);
    if (isFirstMove != std::end(pawnIds))
    {
        unsigned int longMoveIndex = player ? firstIndex - size : firstIndex + size;
        if (MoveUtils::isFieldEmpty(longMoveIndex, pieces))
            options->addMove(longMoveIndex);
    }

    // Take

    // TODO: add en passant

    unsigned int x = board[from].getX();

    bool isBorderLeft = x == startLetter;
    bool isBorderRight = x == (startLetter + size - 1);

    unsigned int takeRight = player ? (from - size + 1) : (from + size + 1);
    unsigned int takeLeft = player ? (from - size - 1) : (from + size - 1);

    if (!isBorderLeft && MoveUtils::isOpponentPieceOnField(takeLeft, pieces, player))
        options->addTake(takeLeft);
    if (!isBorderRight && MoveUtils::isOpponentPieceOnField(takeRight, pieces, player))
        options->addTake(takeRight);
}