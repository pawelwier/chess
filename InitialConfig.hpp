#pragma once

#include <vector>

class InitialConfig
{
private:
    // board
    const unsigned short int SIZE = 8;
    const short int START_LETTER = 65; // A
    const short int START_NUMBER = 1;

    // initial indexes
    const std::vector<unsigned int> PAWN_IDS = {8, 9, 10, 11, 12, 13, 14, 15, 48, 49, 50, 51, 52, 53, 54, 55};
    const std::vector<unsigned int> ROOK_IDS = {0, 7, 56, 63};
    const std::vector<unsigned int> KNIGHT_IDS = {1, 6, 57, 62};
    const std::vector<unsigned int> BISHOP_IDS = {2, 5, 58, 61};
    const std::vector<unsigned int> QUEEN_IDS = {3, 59};
    const std::vector<unsigned int> KING_IDS = {4, 60};

public:
    unsigned short int size();

    unsigned short int fieldCount();

    unsigned short int startLetter();

    unsigned short int startNumber();

    std::vector<unsigned int> pawnIds();

    std::vector<unsigned int> rookIds();

    std::vector<unsigned int> knightIds();

    std::vector<unsigned int> bishopIds();

    std::vector<unsigned int> queenIds();

    std::vector<unsigned int> kingIds();
};