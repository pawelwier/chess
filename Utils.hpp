#pragma once

#include <algorithm>
#include <string>
#include <vector>

class Utils
{
public:
    static bool isOdd(short unsigned int number);

    static char getChar(short unsigned int asciiNum);

    static std::string getFieldCoordinates(unsigned int x, unsigned int y);

    static bool isWithinValues(short unsigned int value, short unsigned int values[2]);

    // template <typename T>
    // static bool includes(std::vector<T> vector, T value);

    // template <typename T>
    // static std::vector<T> reverseVector(std::vector<T> vector);

    static bool includes(std::vector<unsigned int> vector, unsigned int value);

    static std::vector<unsigned int> reverseVector(std::vector<unsigned int> vector);

    static bool isInTypeArray(unsigned short int ids[], size_t s, unsigned short int id);
};
