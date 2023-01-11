#include "Game.hpp"
#include "Utils.hpp"
#include "FieldUtils.hpp"
#include "PieceUtils.hpp"
#include "InitialConfig.hpp"
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

int main()
{
    bool gameOn = true;

    std::vector<Piece *> pieces;
    Game game = Game(pieces);
    std::vector<Field> fields = game.getBoard();

    for (Field field : fields) // refactor!:)
    {
        unsigned int id = field.getId();
        Player player = FieldUtils::initPiecePlayer(id);

        InitialConfig config;

        if (Utils::includes(config.pawnIds(), id))
        {
            game.addPiece(new Pawn(player, id));
        }

        if (Utils::includes(config.rookIds(), id))
        {
            game.addPiece(new Rook(player, id));
        }

        if (Utils::includes(config.knightIds(), id))
        {
            game.addPiece(new Knight(player, id));
        }

        if (Utils::includes(config.bishopIds(), id))
        {
            game.addPiece(new Bishop(player, id));
        }

        if (Utils::includes(config.queenIds(), id))
        {
            game.addPiece(new Queen(player, id));
        }

        if (Utils::includes(config.kingIds(), id))
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

        bool isPlayerPiece = PieceUtils::isPlayerPiece(p, player);
        if (!isPlayerPiece)
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