// #include "./pieces/PieceTypes.hpp"
#include "Game.hpp"
#include "Utils.hpp"
#include "FieldUtils.hpp"
#include "GameUtils.hpp"
#include "PieceUtils.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include "Player.hpp"

#include <cmath>
#include <iostream>

#define LOG(x) std::cout << x

bool isPlayerPiece(Piece *piece, Player player)
{
    return piece->getPlayer() == player;
}

int main()
{
    bool gameOn = true;

    unsigned int startNumber = InitialConfig::getStartNumber();
    unsigned int startLetter = InitialConfig::getStartLetter();

    std::vector<Piece *> pieces;
    Game game = Game(pieces, startNumber, startLetter);

    GameUtils::getInitialSetup(game, startNumber, startLetter);

    std::vector<Field> fields = game.getBoard();

    // move to config class
    const size_t pawnCount{16};
    const size_t rookCount{4};
    const size_t knightCount{4};
    const size_t bishopCount{4};
    const size_t queenCount{2};
    const size_t kingCount{2};
    unsigned short int pawnIds[pawnCount] = {8, 9, 10, 11, 12, 13, 14, 15, 48, 49, 50, 51, 52, 53, 54, 55};
    unsigned short int rookIds[rookCount] = {0, 7, 56, 63};
    unsigned short int knightIds[knightCount] = {1, 6, 57, 62};
    unsigned short int bishopIds[bishopCount] = {2, 5, 58, 61};
    unsigned short int queenIds[2] = {3, 59};
    unsigned short int kingIds[2] = {4, 60};

    for (Field field : fields) // refactor!:)
    {
        unsigned int id = field.getId();
        Player player = FieldUtils::initPiecePlayer(id);

        if (Utils::isInTypeArray(pawnIds, pawnCount, id))
        {
            game.addPiece(new Pawn(player, id));
        }

        if (Utils::isInTypeArray(rookIds, rookCount, id))
        {
            game.addPiece(new Rook(player, id));
        }

        if (Utils::isInTypeArray(knightIds, knightCount, id))
        {
            game.addPiece(new Knight(player, id));
        }

        if (Utils::isInTypeArray(bishopIds, bishopCount, id))
        {
            game.addPiece(new Bishop(player, id));
        }

        if (Utils::isInTypeArray(queenIds, queenCount, id))
        {
            game.addPiece(new Queen(player, id));
        }

        if (Utils::isInTypeArray(kingIds, kingCount, id))
        {
            game.addPiece(new King(player, id));
        }
    }

    game.printBoard();
    LOG("\n");

    while (gameOn) // TODO: refactor
    {
        Player player = game.getCurrentPlayer();
        std::string playerColor = !player ? "White" : "Black";

        std::vector<Field> board = game.getBoard();

        LOG("Move: ");
        LOG(game.getMove());

        LOG("\n");

        LOG(playerColor);
        LOG("\'s turn. ");

        std::string from, to;

        LOG("Select piece: ");
        std::cin >> from;
        unsigned short int fromIndex = FieldUtils::getFieldIndexByPosition(fields, from);

        Piece *p = PieceUtils::findPieceByFieldId(game.getPieces(), fromIndex);

        if (!p)
        {
            LOG("\nNo piece there. Try again.\n\n");
            continue;
        }

        if (!isPlayerPiece(p, player))
        {
            LOG("\nNot your piece! Try again.\n\n");
            continue;
        }

        MoveOptions *options = new MoveOptions;
        p->getAvailableFieldIds(options, fromIndex, board, game.getPieces());

        std::vector<unsigned int> moves = options->getMoves();
        std::vector<unsigned int> takes = options->getTakes();

        if (moves.size())
        {
            LOG("Possible moves: ");
            for (unsigned int move : moves)
            {
                LOG(board[move].getField() + " ");
            }
            LOG("\n");
        }

        if (takes.size())
        {
            LOG("Possible takes: ");
            for (unsigned int take : takes)
            {
                LOG(board[take].getField() + " ");
            }
            LOG("\n");
        }

        if (!moves.size() && !takes.size())
        {
            LOG("No moves possible\n\n");
            continue;
        }

        LOG("Move to: ");
        std::cin >> to;
        unsigned int toIndex = FieldUtils::getFieldIndexByPosition(fields, to);

        bool takeOk = Utils::includes(takes, toIndex);
        bool moveOk = Utils::includes(moves, toIndex);

        if (takeOk || moveOk)
        {
            if (takeOk)
            {
                game.takePiece(toIndex);
            }
            p->move(toIndex);
        }
        else
        {
            // TODO: leave piece selected
            LOG("\nCan't move there\n\n");
            continue;
        }

        game.printBoard();

        delete options;

        game.nextPlayer();
        game.nextMove();
    }
}