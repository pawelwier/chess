#include <string>

bool isOdd(int number)
{
    return number % 2;
}

char getChar(int asciiNum)
{
    return char(asciiNum);
}

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

Piece getPieceType(int x, int y)
{
    if (y == 2 || y == 7)
    {
        return pawn;
    }
    if (y == 1 || y == 8)
    {
        if (x == 'A' || x == 'H')
        {
            return rook;
        }
        if (x == 'B' || x == 'G')
        {
            return knight;
        }
    }
    return none;
}

class Field
{
private:
    int x;
    int y;
    bool isBlack;
    Piece piece;
    Player player;

public:
    void setField(int xValue, int yValue)
    {
        x = xValue;
        y = yValue;
        isBlack = isOdd(x) == isOdd(y);
        piece = getPieceType(xValue, yValue);
    }

    std::string getField()
    {
        return getChar(x) + std::to_string(y) + " - " + std::to_string(isBlack) + " - " + std::to_string(piece);
    }
};