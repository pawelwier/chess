#include "Player.hpp"
#include "Piece.hpp"
#include "MoveOptions.hpp"
#include "Field.hpp"

class Bishop : public Piece
{
public:
    explicit Bishop(Player player, unsigned int fieldId);

    void getAvailableFieldIds(
        MoveOptions *options,
        unsigned int from,
        std::vector<Field> board,
        std::vector<Piece *> pieces);
};