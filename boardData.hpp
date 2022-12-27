#include <map>
#include <string>

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

std::map<Piece, std::string> pieces{
    {none, "-"},
    {pawn, "pawn"},
    {rook, "rook"},
    {knight, "knight"},
    {bishop, "bishop"},
    {queen, "queen"},
    {king, "king"}};