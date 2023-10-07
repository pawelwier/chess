#ifndef PIECE_UTILS_H
#define PIECE_UTILS_H

#include "../Piece.hpp"
#include "../Player.hpp"

#include <string>
#include <vector>

class PieceUtils
{
public:
    static unsigned int findPieceIndex(std::vector<Piece *> pieces, unsigned int fieldId);

    static Piece *findPieceByFieldId(std::vector<Piece *> pieces, unsigned int fieldId);

    static bool isPlayersPieceOnField(Player player, std::vector<Piece *> pieces, unsigned int fieldId);

    static bool isPlayerPiece(Piece *piece, Player player);

    static Piece *findPieceByPieceId(std::vector<Piece *> pieces, unsigned int pieceId);

    static unsigned int getPiecePoints(std::vector<Piece *> pieces);

    static bool pieceHasMoved(Piece *piece, std::vector<Move *> moves);
};

#endif