#include "Player.hpp"
#include "Piece.hpp"
#include "MoveOptions.hpp"
#include "Field.hpp"

class Queen : public Piece
{
public:
    explicit Queen(unsigned int id, Player player, unsigned int fieldId);

    void getAvailableFieldIds(
        MoveOptions *options,
        unsigned int from,
        std::vector<Field *> board,
        std::vector<Piece *> pieces);
};
