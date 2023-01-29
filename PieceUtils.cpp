#include "PieceUtils.hpp"
#include "Player.hpp"

#include <algorithm>
#include <numeric>

unsigned int PieceUtils::findPieceIndex(std::vector<Piece *> v, unsigned int fieldId)
{
    std::vector<Piece *>::iterator result = std::find_if(v.begin(), v.end(), [fieldId](Piece *piece)
                                                         { return piece->getFieldId() == fieldId; }); // TODO: read into
    ptrdiff_t index = std::distance(v.begin(), result);
    return index;
}

Piece *PieceUtils::findPieceByFieldId(std::vector<Piece *> v, unsigned int fieldId)
{
    unsigned int index = PieceUtils::findPieceIndex(v, fieldId);
    if (index == -1 || index == v.size()) // TODO: is that ok??
    {
        return 0;
    }
    return v[index];
}

bool PieceUtils::isPlayersPieceOnField(Player player, std::vector<Piece *> v, unsigned int fieldId)
{
    Piece *piece = findPieceByFieldId(v, fieldId);
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