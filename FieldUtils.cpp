#include "FieldUtils.hpp"
#include "Player.hpp"
#include "Field.hpp"

#include <iostream>
#include <vector>

unsigned short int FieldUtils::getFieldIndexByPosition(std::vector<Field> &fields, std::string position)
{
    int index;

    InitialConfig config;

    for (size_t i = 0; i < config.fieldCount(); i++)
    {
        if (fields[i].getField() == position)
        {
            index = i;
        }
    }

    return index;
}

Player FieldUtils::initPiecePlayer(short unsigned id)
{
    // move to config
    unsigned short int whitePieces[2]{0, 15};
    return Utils::isWithinValues(id, whitePieces) ? white : black;
}