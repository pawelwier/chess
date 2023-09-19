#include "InitialConfig.hpp"

#include <cmath>

InitialConfig::InitialConfig() :
    size(8),
    startLetter(65), // A
    startNumber(1),
    pawnIds({8, 9, 10, 11, 12, 13, 14, 15, 48, 49, 50, 51, 52, 53, 54, 55}),
    rookIds({0, 7, 56, 63}),
    knightIds({1, 6, 57, 62}),
    bishopIds({2, 5, 58, 61}),
    queenIds({3, 59}),
    kingIds({4, 60})
    {
        fieldCount = pow(size, 2);

        std::vector<std::vector<unsigned int>> pieceIds = {pawnIds, rookIds, knightIds, bishopIds, queenIds, kingIds};
    }
