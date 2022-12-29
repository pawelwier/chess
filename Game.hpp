#include "Field.hpp"

class Game
{
private:
    Player currentPlayer;

public:
    Game()
    {
        currentPlayer = white;
    }

    void setPlayer(Player newPlayer)
    {
        currentPlayer = newPlayer;
    }

    Player getCurrentPlayer()
    {
        return currentPlayer;
    }

    void nextPlayer()
    {
        currentPlayer == white ? setPlayer(black) : setPlayer(white);
    }
};