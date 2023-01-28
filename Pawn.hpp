#include "Player.hpp"
#include "Piece.hpp"
#include "MoveOptions.hpp"
#include "Field.hpp"

class Pawn : public Piece
{
public:
    explicit Pawn(unsigned int id, Player player, unsigned int fieldId);

    void getAvailableMoves(
        MoveOptions *options,
        unsigned int from,
        std::vector<Field *> board,
        std::vector<Piece *> pieces);
};
