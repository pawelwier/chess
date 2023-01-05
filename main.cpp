#include <cmath>
#include "Game.hpp"

bool isPlayerPiece(Piece *piece, Player player)
{
    return piece->getPlayer() == player;
}

int main()
{
    bool gameOn = true;

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
    LOG("\n");

    while (gameOn) // TODO: refactor
    {
        Player player = game.getCurrentPlayer();
        std::string playerColor = !player ? "White" : "Black";

        std::array<Field, FIELD_COUNT> board = game.getBoard();

        LOG("Move: ");
        LOG(game.getMove());

        LOG("\n");

        LOG(playerColor);
        LOG("\'s turn. ");

        std::string from, to;

        LOG("Select piece: ");
        std::cin >> from;
        unsigned short int fromIndex = getFieldIndexByPosition(fields, from);

        Piece *p = findPieceByFieldId(game.getPieces(), fromIndex);

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
        unsigned int toIndex = getFieldIndexByPosition(fields, to);

        bool takeOk = includes(takes, toIndex);
        bool moveOk = includes(moves, toIndex);

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