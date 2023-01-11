#include "Piece.hpp"
#include "Player.hpp"

#include <string>
#include <vector>

class PieceUtils
{
public:
    static unsigned int findPieceIndex(std::vector<Piece *> v, unsigned int fieldId);

    static Piece *findPieceByFieldId(std::vector<Piece *> v, unsigned int fieldId);

    static bool isPlayersPieceOnField(Player player, std::vector<Piece *> v, unsigned int fieldId);

    static std::string getPlayerColor(Player player);
};