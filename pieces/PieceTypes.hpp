#include "Piece.hpp"

#define log(x) std::cout << x

bool isFieldEmpty(unsigned int index, std::vector<Piece *> pieces)
{
    Piece *piece = findPieceByFieldId(pieces, index);
    return !piece;
}

bool isOpponentPieceOnField(unsigned int index, std::vector<Piece *> pieces, Player player)
{
    Piece *piece = findPieceByFieldId(pieces, index);
    Player opponent = !player ? black : white;
    return !!piece && piece->getPlayer() == opponent;
}

class Pawn : public Piece
{
public:
    explicit Pawn(Player player, unsigned int fieldId) : Piece(player, pawn, fieldId)
    {
    }

    void getAvailableFieldIds(
        MoveOptions *options,
        unsigned int from,
        std::array<Field, FIELD_COUNT> board,
        std::vector<Piece *> pieces)
    {
        Player player = this->getPlayer();

        // Move
        // Check if there is piece on field in front
        unsigned int firstIndex = player ? from - SIZE : from + SIZE;
        if (isFieldEmpty(firstIndex, pieces))
            options->addMove(firstIndex);

        // Check if first move
        // TODO: add move history to Game, check if piece has been moved
        unsigned short int *isFirstMove = std::find(std::begin(pawnIds), std::end(pawnIds), from);
        if (isFirstMove != std::end(pawnIds))
        {
            unsigned int longMoveIndex = player ? firstIndex - SIZE : firstIndex + SIZE;
            if (isFieldEmpty(longMoveIndex, pieces))
                options->addMove(longMoveIndex);
        }

        // Take
        unsigned int x = board[from].getX();

        bool isBorderLeft = x == START_LETTER;
        bool isBorderRight = x == (START_LETTER + SIZE - 1);

        unsigned int takeRight = player ? (from - SIZE + 1) : (from + SIZE + 1);
        unsigned int takeLeft = player ? (from - SIZE - 1) : (from + SIZE - 1);

        if (!isBorderLeft && isOpponentPieceOnField(takeLeft, pieces, player))
            options->addTake(takeLeft);
        if (!isBorderRight && isOpponentPieceOnField(takeRight, pieces, player))
            options->addTake(takeRight);

        // log("attacker fields: ");
        // for (unsigned int take : options->getTakes())
        // {
        //     log("\n");
        //     log(board[take].getField());
        //     log("\n");
        // }
    }
};

class Rook : public Piece
{
public:
    explicit Rook(Player player, unsigned int fieldId) : Piece(player, rook, fieldId)
    {
    }

    void getAvailableFieldIds(
        MoveOptions *options,
        unsigned int from,
        std::array<Field, FIELD_COUNT> board,
        std::vector<Piece *> pieces)
    {
        std::cout << "looking for rook fields ..." << std::endl;
    }
};

class Knight : public Piece
{
public:
    explicit Knight(Player player, unsigned int fieldId) : Piece(player, knight, fieldId)
    {
    }

    void getAvailableFieldIds(
        MoveOptions *options,
        unsigned int from,
        std::array<Field, FIELD_COUNT> board,
        std::vector<Piece *> pieces)
    {
        std::cout << "looking for knight fields ..." << std::endl;
    }
};

class Bishop : public Piece
{
public:
    explicit Bishop(Player player, unsigned int fieldId) : Piece(player, bishop, fieldId)
    {
    }

    void getAvailableFieldIds(
        MoveOptions *options,
        unsigned int from,
        std::array<Field, FIELD_COUNT> board,
        std::vector<Piece *> pieces)
    {
        std::cout << "looking for bishop fields ..." << std::endl;
    }
};

class Queen : public Piece
{
public:
    explicit Queen(Player player, unsigned int fieldId) : Piece(player, queen, fieldId)
    {
    }

    void getAvailableFieldIds(
        MoveOptions *options,
        unsigned int from,
        std::array<Field, FIELD_COUNT> board,
        std::vector<Piece *> pieces)
    {
        std::cout << "looking for queen fields ..." << std::endl;
    }
};

class King : public Piece
{
public:
    explicit King(Player player, unsigned int fieldId) : Piece(player, king, fieldId)
    {
    }

    void getAvailableFieldIds(
        MoveOptions *options,
        unsigned int from,
        std::array<Field, FIELD_COUNT> board,
        std::vector<Piece *> pieces)
    {
        std::cout << "looking for king fields ..." << std::endl;
    }
};