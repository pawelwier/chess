#include <string>
#include "utils.hpp"

enum Player
{
    empty,
    white,
    black
};

enum Piece
{
    none,
    pawn,
    rook,
    knight,
    bishop,
    queen,
    king
};

bool isInTypeArray(unsigned short int ids[], size_t s, unsigned short int id)
{
    unsigned short int *end = ids + s;
    return std::find(ids, end, id) != end;
}

unsigned short int whitePieces[2]{0, 15};
unsigned short int blackPieces[2]{48, 63};

const size_t pawnCount{16};
const size_t rookCount{4};
const size_t knightCount{4};
const size_t bishopCount{4};
const size_t queenCount{2};
const size_t kingCount{2};

unsigned short int pawnIds[2][2] = {{8, 15}, {48, 55}};
unsigned short int rookIds[rookCount] = {0, 7, 56, 63};
unsigned short int knightIds[knightCount] = {1, 6, 57, 62};
unsigned short int bishopIds[bishopCount] = {2, 5, 58, 61};
unsigned short int queenIds[2] = {3, 60};
unsigned short int kingIds[2] = {4, 59};

Piece getPieceType(unsigned short int id) // refactor
{
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            if (isWithinValues(id, pawnIds[j]))
                return pawn;
        };
    }
    if (isInTypeArray(rookIds, rookCount, id))
        return rook;
    if (isInTypeArray(knightIds, knightCount, id))
        return knight;
    if (isInTypeArray(bishopIds, bishopCount, id))
        return bishop;
    if (isInTypeArray(queenIds, queenCount, id))
        return queen;
    if (isInTypeArray(kingIds, kingCount, id))
        return king;
    return none;
}

Player
getPiecePlayer(short unsigned id)
{
    return isWithinValues(id, whitePieces)
               ? white
           : isWithinValues(id, blackPieces)
               ? black
               : empty;
}

class Field
{
private:
    unsigned short int x;
    unsigned short int y;
    unsigned short int id; // delete, use x & y only?
    bool isBlack;
    Piece piece;
    Player player;

public:
    void setField(
        unsigned short int xValue,
        unsigned short int yValue,
        unsigned short int idValue)
    {
        x = xValue;
        y = yValue;
        id = idValue;
        isBlack = isOdd(x) == isOdd(y);
        piece = getPieceType(id);
        player = getPiecePlayer(idValue);
    }

    std::string getField()
    {
        return getChar(x) + std::to_string(y)
               //
               //    + " color: " + std::to_string(isBlack)
               //
               + " piece: " + std::to_string(piece)
               //
               //    + " player: " + std::to_string(player)
               //
               + " | ";
    }
};