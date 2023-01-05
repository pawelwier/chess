#include <algorithm>

bool isOdd(short unsigned int number)
{
    return number % 2;
}

char getChar(short unsigned int asciiNum)
{
    return char(asciiNum);
}

bool isWithinValues(short unsigned int value, short unsigned int values[2])
{
    return value >= values[0] && value <= values[1];
}

template <typename T>
bool includes(std::vector<T> vector, T value)
{
    return std::find(vector.begin(), vector.end(), value) != vector.end();
}

template <typename T>
std::vector<T> reverseVector(std::vector<T> vector)
{
    std::reverse(vector.begin(), vector.end());
    return vector;
}