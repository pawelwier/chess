#include "Field.hpp"
#include "GameUtils.hpp"

#define LOOP(x) for (int i = 0; i < x; i++)
#define LOG(x) std::cout << x

void GameUtils::getInitialSetup(Game game, int startNum, int startLetter)
{
    unsigned int size = InitialConfig::getSize();
    int xIndex = startLetter;
    int yIndex = startNum;
    int fieldIndex = 0;

    LOOP(size)
    {
        LOOP(size)
        {
            Field field = Field(xIndex, yIndex, fieldIndex);

            game.addField(field);
            // fields[fieldIndex].setField(xIndex, yIndex, fieldIndex);

            xIndex++;
            fieldIndex++;
        }
        xIndex = startLetter;
        yIndex++;
    }
}