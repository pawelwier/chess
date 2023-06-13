#include "../Player.hpp"
#include "../Piece.hpp"
#include "../MoveOptions.hpp"
#include "../Field.hpp"
#include "../Move.hpp"

class Queen : public Piece
{
public:
    explicit Queen(unsigned int id, Player player, unsigned int fieldId);

    void getAvailableMoves(
        MoveOptions *options,
        unsigned int from,
        std::vector<Field *> board,
        std::vector<Piece *> pieces,
        std::vector<Move *> moves);
};
