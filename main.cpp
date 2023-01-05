#include <cmath>
#include "Game.hpp"

#define log(x) std::cout << x

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
    log("\n");

    while (gameOn) // TODO: refactor
    {
        Player player = game.getCurrentPlayer();
        std::string playerColor = !player ? "White" : "Black";

        std::array<Field, FIELD_COUNT> board = game.getBoard();

        log("Move: ");
        log(game.getMove());

        log("\n");

        log(playerColor);
        log("\'s turn. ");

        std::string from, to;

        log("Select piece: ");
        std::cin >> from;
        unsigned short int fromIndex = getFieldIndexByPosition(fields, from);

        Piece *p = findPieceByFieldId(game.getPieces(), fromIndex);

        if (!p)
        {
            log("\nNo piece there. Try again.\n\n");
            continue;
        }

        if (!isPlayerPiece(p, player))
        {
            log("\nNot your piece! Try again.\n\n");
            continue;
        }

        MoveOptions *options = new MoveOptions;
        p->getAvailableFieldIds(options, fromIndex, board, game.getPieces());

        std::vector<unsigned int> moves = options->getMoves();
        std::vector<unsigned int> takes = options->getTakes();

        if (moves.size())
        {
            log("Possible moves: ");
            for (unsigned int move : moves)
            {
                log(board[move].getField() + " ");
            }
            log("\n");
        }

        if (takes.size())
        {
            log("Possible takes: ");
            for (unsigned int take : takes)
            {
                log(board[take].getField() + " ");
            }
            log("\n");
        }

        if (!moves.size() && !takes.size())
        {
            log("No moves possible\n\n");
            continue;
        }

        log("Move to: ");
        std::cin >> to;
        unsigned int toIndex = getFieldIndexByPosition(fields, to);

        if (includes(takes, toIndex))
        {
            p->take(toIndex);
        }
        else if (includes(moves, toIndex))
        {
            p->move(toIndex);
        }
        else
        {
            // TODO: leave piece selected
            log("\nCan't move there\n\n");
            continue;
        }

        game.printBoard();

        log("\n");

        delete options;

        game.nextPlayer();
        game.nextMove();
    }
}