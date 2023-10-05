#ifndef MOVE_UTILS_H
#define MOVE_UTILS_H

#include "../MoveOptions.hpp"
#include "../InitialConfig.hpp"
#include "../Player.hpp"
#include "../Piece.hpp"

#include <vector>

class MoveUtils
{
public:
    static bool isFieldEmpty(unsigned int index, std::vector<Piece *> pieces);

    static bool isOpponentPieceOnField(unsigned int index, std::vector<Piece *> pieces, Player player);

    static bool isOutsideBoard(InitialConfig* config, unsigned int x, unsigned int y);

    static void addMoveOptions(std::vector<unsigned int> ids, std::vector<Piece *> pieces, MoveOptions *options, Player player, bool stopOnPiece = true);

    static std::vector<unsigned int> removeFromOptions(std::vector<unsigned int> options, unsigned int option);
};

#endif