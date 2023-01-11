#include "Utils.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

bool Utils::isOdd(short unsigned int number)
{
    return number % 2;
}

char Utils::getChar(short unsigned int asciiNum)
{
    return char(asciiNum);
}

std::string Utils::getFieldCoordinates(unsigned int x, unsigned int y)
{
    return getChar(x) + std::to_string(y);
}

bool Utils::isWithinValues(short unsigned int value, short unsigned int values[2])
{
    return value >= values[0] && value <= values[1];
}

// template <typename T>
// bool Utils::includes(std::vector<T> vector, T value)
// {
//   return std::find(vector.begin(), vector.end(), value) != vector.end();
// }

// template <typename T>
// std::vector<T> Utils::reverseVector(std::vector<T> vector)
// {
//   std::reverse(vector.begin(), vector.end());
//   return vector;
// }

bool Utils::includes(std::vector<unsigned int> vector, unsigned int value)
{
    return std::find(vector.begin(), vector.end(), value) != vector.end();
}

std::vector<unsigned int> Utils::reverseVector(std::vector<unsigned int> vector)
{
    std::reverse(vector.begin(), vector.end());
    return vector;
}

bool Utils::isInTypeArray(unsigned short int ids[], size_t s, unsigned short int id)
{
    unsigned short int *end = ids + s;
    return std::find(ids, end, id) != end;
}