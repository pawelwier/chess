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
#include "Move.hpp"

#include <cmath>
#include <iostream>

#define LOG(x) std::cout << x

int main()
{
    bool gameOn = true;

    std::vector<Piece *> pieces;
    Game game = Game(pieces);
    std::vector<Field> fields = game.getBoard();

    unsigned int id{0};
    for (Field field : fields) // refactor!:)
    {
        unsigned int fieldId = field.getId();
        Player player = FieldUtils::initPiecePlayer(fieldId);

        InitialConfig config;

        if (Utils::includes(config.pawnIds(), fieldId))
        {
            game.addPiece(new Pawn(id, player, fieldId));
            id++;
        }

        if (Utils::includes(config.rookIds(), fieldId))
        {
            game.addPiece(new Rook(id, player, fieldId));
            id++;
        }

        if (Utils::includes(config.knightIds(), fieldId))
        {
            game.addPiece(new Knight(id, player, fieldId));
            id++;
        }

        if (Utils::includes(config.bishopIds(), fieldId))
        {
            game.addPiece(new Bishop(id, player, fieldId));
            id++;
        }

        if (Utils::includes(config.queenIds(), fieldId))
        {
            game.addPiece(new Queen(id, player, fieldId));
            id++;
        }

        if (Utils::includes(config.kingIds(), fieldId))
        {
            game.addPiece(new King(id, player, fieldId));
            id++;
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

        unsigned int moveNum = game.getMoveCount() + 1;
        LOG(std::to_string(moveNum));

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

            Move *move = new Move(moveNum, p->getId(), fromIndex, toIndex);
            game.addMove(move);
        }
        else
        {
            // TODO: leave piece selected
            LOG("\nCan't move there\n\n");
            continue;
        }

        game.printBoard();

        std::vector<Move *> moveHistory = game.getMoves();

        for (Move *m : moveHistory)
        {
            unsigned int order = m->getOrder();

            game.printMove(order);
        }

        delete options;

        game.nextPlayer();
    }
}