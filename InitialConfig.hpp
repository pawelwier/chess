#ifndef INITIAL_CONFIG_H
#define INITIAL_CONFIG_H

#include <vector>

struct InitialConfig
{
    // board
    unsigned short int size;
    unsigned short int fieldCount;
    unsigned short int startLetter;
    unsigned short int startNumber;

    // initial indexes
    std::vector<unsigned int> pawnIds;
    std::vector<unsigned int> rookIds;
    std::vector<unsigned int> knightIds;
    std::vector<unsigned int> bishopIds;
    std::vector<unsigned int> queenIds;
    std::vector<unsigned int> kingIds;

    InitialConfig();
};

#endif