#include <iostream>
#include <cmath>
#include <array>
#include "Game.hpp"

#define log(x) std::cout << x

int main()
{
    bool gameOn = true;
    int moveCount = 1;

    std::array<Field, FIELD_COUNT> fields;
    std::vector<Piece *> pieces;

    getInitialSetup(fields, START_NUMBER, START_LETTER);

    Game game = Game(fields, pieces);

    for (Field field : fields) // refactor!:)
    {
        unsigned int id = field.getId();
        Player player = initPiecePlayer(id);

        if (isInTypeArray(pawnIds, pawnCount, id))
        {
            game.addPiece(new Pawn(player, id));
        }

        if (isInTypeArray(rookIds, rookCount, id))
        {
            game.addPiece(new Rook(player, id));
        }

        if (isInTypeArray(knightIds, knightCount, id))
        {
            game.addPiece(new Knight(player, id));
        }

        if (isInTypeArray(bishopIds, bishopCount, id))
        {
            game.addPiece(new Bishop(player, id));
        }

        if (isInTypeArray(queenIds, queenCount, id))
        {
            game.addPiece(new Queen(player, id));
        }

        if (isInTypeArray(kingIds, kingCount, id))
        {
            game.addPiece(new King(player, id));
        }
    }

    game.printBoard();
    // log("\n");

    /*
        while (gameOn) // TODO: refactor
        {
            std::string player = game.getCurrentPlayer() == 1 ? "White" : "Black";

            log("Move: ");
            log(moveCount);

            log("\n");

            log(player);
            log("\'s turn. ");

            std::string from, to;

            log("Select piece: ");
            std::cin >> from;
            unsigned short int fromIndex = getFieldIndexByPosition(fields, from);

            log("Move to: ");
            std::cin >> to;
            unsigned short int toIndex = getFieldIndexByPosition(fields, to);

            log("\n");

            // move(game, fields, fromIndex, toIndex);

            printBoard(fields);

            log("\n\n");

            game.nextPlayer();
            moveCount++;
        }
    */
}