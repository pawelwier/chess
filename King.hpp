
#include "Player.hpp"
#include "MoveOptions.hpp"
#include "Piece.hpp"
#include "Field.hpp"

class King : public Piece
{
public:
    explicit King(unsigned int id, Player player, unsigned int fieldId);

    void getAvailableFieldIds(
        MoveOptions *options,
        unsigned int from,
        std::vector<Field> board,
        std::vector<Piece *> pieces);
};
