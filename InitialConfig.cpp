#include "InitialConfig.hpp"

#include <cmath>

unsigned short int InitialConfig::size()
{
    return SIZE;
}

unsigned short int InitialConfig::fieldCount()
{
    return pow(SIZE, 2);
}

unsigned short int InitialConfig::startLetter()
{
    return START_LETTER;
}

unsigned short int InitialConfig::startNumber()
{
    return START_NUMBER;
}

std::vector<unsigned int> InitialConfig::pawnIds()
{
    return PAWN_IDS;
}

std::vector<unsigned int> InitialConfig::rookIds()
{
    return ROOK_IDS;
}

std::vector<unsigned int> InitialConfig::knightIds()
{
    return KNIGHT_IDS;
}

std::vector<unsigned int> InitialConfig::bishopIds()
{
    return BISHOP_IDS;
}

std::vector<unsigned int> InitialConfig::queenIds()
{
    return QUEEN_IDS;
}

std::vector<unsigned int> InitialConfig::kingIds()
{
    return KING_IDS;
}