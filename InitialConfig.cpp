#include "InitialConfig.hpp"

#include <cmath>

constexpr unsigned short int SIZE = 8;
// const unsigned short int fieldCount_ = pow(SIZE, 2);
const unsigned short int START_LETTER = 65; // A
const unsigned short int START_NUMBER = 1;

unsigned short int InitialConfig::getSize()
{
    return SIZE;
}

unsigned short int InitialConfig::getFieldCount()
{
    return pow(SIZE, 2);
}

unsigned short int InitialConfig::getStartLetter()
{
    return START_LETTER;
}

unsigned short int InitialConfig::getStartNumber()
{
    return START_NUMBER;
}
