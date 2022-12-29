#include <string>
#include <iostream>
#include <iomanip>

#include "utils.hpp"
#include "boardData.hpp"
#include "initialConfig.hpp"

bool isInTypeArray(unsigned short int ids[], size_t s, unsigned short int id)
{
    unsigned short int *end = ids + s;
    return std::find(ids, end, id) != end;
}

Piece initPieceType(unsigned short int id) // refactor
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

Player initPiecePlayer(short unsigned id)
{
    return isWithinValues(id, whitePieces)
               ? white
           : isWithinValues(id, blackPieces)
               ? black
               : empty;
}

std::string getPieceName(Piece piece)
{
    return pieces[piece];
}

std::string getPiecePlayer(Player player)
{
    return players[player];
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

    std::string getField()
    {
        return getChar(x) + std::to_string(y);
    }

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
        piece = initPieceType(id);
        player = initPiecePlayer(idValue);
    }

    void printField()
    {
        std::cout << std::setw(2) << getField();
        std::cout << std::setw(16) << getPieceName(piece) + " " + getPiecePlayer(player) + " | ";
    }

    unsigned short int getId()
    {
        return id;
    }

    Piece getPiece()
    {
        return piece;
    }

    void setPiece(Piece newPiece)
    {
        piece = newPiece;
    }

    void setPlayer(Player currentPlayer)
    {
        player = currentPlayer;
    }
};