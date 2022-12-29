#include "Field.hpp"

class Game
{
private:
    Player currentPlayer;

public:
    Player getCurrentPlayer()
    {
        return currentPlayer;
    }

    Game()
    {
        currentPlayer = white;
    }
};