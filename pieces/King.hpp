#include "../Player.hpp"
#include "../MoveOptions.hpp"
#include "../Piece.hpp"
#include "../Field.hpp"
#include "../Move.hpp"

class King : public Piece
{
public:
    explicit King(unsigned int id, Player player, unsigned int fieldId);

    void getAvailableMoves(
        InitialConfig *config, 
        MoveOptions *options,
        std::vector<Field *> board,
        std::vector<Piece *> pieces,
        std::vector<Move *> moves,
        Player player);
};
