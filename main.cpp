#include <iostream>
#include "Field.hpp"

#define log(x) std::cout << x
#define loop(x) for (int i = 0; i < x; i++)

using std::string;

int main()
{
    const int SIZE_X = 8;
    const int SIZE_Y = 8;
    const int SIZE = SIZE_X * SIZE_Y;
    const int START_LETTER = 65; // A
    const int START_NUMBER = 1;

    int xIndex = START_LETTER;
    int yIndex = START_NUMBER;
    int fieldIndex = 0;

    Field fields[SIZE];

    loop(SIZE_Y)
    {
        loop(SIZE_X)
        {
            fields[fieldIndex].setField(xIndex, yIndex, fieldIndex);

            xIndex++;
            fieldIndex++;
        }
        xIndex = START_LETTER;
        yIndex++;
    }

    for (Field field : fields)
    {
        std::string data = field.getField();
        log(data);
        if ((int)data[0] == START_LETTER + SIZE_X - 1)
        {
            log('\n');
        }
    };
}