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