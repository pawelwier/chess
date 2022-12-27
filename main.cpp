#include <iostream>
#include <cmath>
#include "Field.hpp"

#define log(x) std::cout << x
#define loop(x) for (int i = 0; i < x; i++)

using std::string;

void getInitialSetup(Field fields[], int size, int startNum, int startLetter)
{
    int xIndex = startLetter;
    int yIndex = startNum;
    int fieldIndex = 0;

    loop(size)
    {
        loop(size)
        {
            fields[fieldIndex].setField(xIndex, yIndex, fieldIndex);

            xIndex++;
            fieldIndex++;
        }
        xIndex = startLetter;
        yIndex++;
    }
}

void printBoard(Field board[], unsigned short int boardSize)
{
    for (size_t i = 0; i < boardSize; i++)
    {
        std::string data = board[i].getField();
        log(data);
        if (!((i + 1) % (int)sqrt(boardSize)))
        {
            log('\n');
        }
    }
}

int main()
{
    const unsigned short int SIZE = 8;
    const unsigned short int FIELD_COUNT = pow(8, 2);
    const unsigned short int START_LETTER = 65; // A
    const unsigned short int START_NUMBER = 1;

    Field fields[FIELD_COUNT];

    getInitialSetup(fields, SIZE, START_NUMBER, START_LETTER);

    printBoard(fields, FIELD_COUNT);
}