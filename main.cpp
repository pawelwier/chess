#include <iostream>
#include <cmath>
#include "Game.hpp"

#define log(x) std::cout << x
#define loop(x) for (int i = 0; i < x; i++)

using std::string;

void getInitialSetup(Field fields[], int size, int startNum, int startLetter)
{
    int xIndex = startLetter;
    int yIndex = startNum;
    int fieldIndex = 0;

    loop(size)
    {
        loop(size)
        {
            fields[fieldIndex].setField(xIndex, yIndex, fieldIndex);

            xIndex++;
            fieldIndex++;
        }
        xIndex = startLetter;
        yIndex++;
    }
}

void printBoard(Field board[], unsigned short int boardSize)
{
    for (size_t i = 0; i < boardSize; i++)
    {
        board[i].printField();
        if (!((i + 1) % (int)sqrt(boardSize)))
        {
            log('\n');
        }
    }
}

void move(Game game, Field fields[], Field start, Field destination)
{
    Piece startPiece = start.getPiece();
    Player player = game.getCurrentPlayer();

    unsigned short int startId = start.getId();
    unsigned short int destinationId = destination.getId();

    fields[startId].setPiece(none);
    fields[startId].setPlayer(empty);

    fields[destinationId].setPiece(startPiece);
    fields[destinationId].setPlayer(player);
};

int main()
{
    const unsigned short int SIZE = 8;
    const unsigned short int FIELD_COUNT = pow(8, 2);
    const unsigned short int START_LETTER = 65; // A
    const unsigned short int START_NUMBER = 1;

    Game game;
    Field fields[FIELD_COUNT];

    getInitialSetup(fields, SIZE, START_NUMBER, START_LETTER);

    printBoard(fields, FIELD_COUNT);

    log(" \n");

    move(game, fields, fields[12], fields[28]); // move pawn E2 -> E4

    printBoard(fields, FIELD_COUNT);
}