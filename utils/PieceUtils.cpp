#include "PieceUtils.hpp"
#include "../Player.hpp"

#include <algorithm>
#include <numeric>

unsigned int PieceUtils::findPieceIndex(std::vector<Piece *> pieces, unsigned int fieldId)
{
    std::vector<Piece *>::iterator result = std::find_if(pieces.begin(), pieces.end(), [fieldId](Piece *piece)
                                                         { return piece->getFieldId() == fieldId; });
    ptrdiff_t index = std::distance(pieces.begin(), result);
    return index;
}

Piece *PieceUtils::findPieceByFieldId(std::vector<Piece *> pieces, unsigned int fieldId)
{
    unsigned int index = PieceUtils::findPieceIndex(pieces, fieldId);
    if (index == -1 || index == pieces.size())
    {
        return 0;
    }
    return pieces[index];
}

bool PieceUtils::isPlayersPieceOnField(Player player, std::vector<Piece *> pieces, unsigned int fieldId)
{
    Piece *piece = findPieceByFieldId(pieces, fieldId);
    return piece->getPlayer() == player;
}

bool PieceUtils::isPlayerPiece(Piece *piece, Player player)
{
    return piece->getPlayer() == player;
}

Piece *PieceUtils::findPieceByPieceId(std::vector<Piece *> pieces, unsigned int pieceId)
{
    std::vector<Piece *>::iterator result = std::find_if(pieces.begin(), pieces.end(), [pieceId](Piece *piece)
        { return piece->getId() == pieceId; });
    ptrdiff_t index = std::distance(pieces.begin(), result);
    return pieces[index];
}

unsigned int PieceUtils::getPiecePoints(std::vector<Piece *> pieces)
{
    std::vector<unsigned int> points;

    points.resize(pieces.size());

    std::transform(pieces.begin(), pieces.end(), points.begin(), [](Piece *piece)
        { return piece->getPoints(); });

    unsigned int sum = std::accumulate(points.begin(), points.end(), 0);

    return sum;
}

bool PieceUtils::pieceHasMoved(Piece *piece, std::vector<Move *> moves)
{
    unsigned int id = piece->getId();
    std::vector<Move *>::iterator it = std::find_if(moves.begin(), moves.end(), [id](Move *move)
                                                    { return (move->getPieceId() == id); });
    return it != moves.end();
}