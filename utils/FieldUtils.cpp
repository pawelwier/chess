#include "FieldUtils.hpp"
#include "../InitialConfig.hpp"
#include "../Player.hpp"
#include "../Field.hpp"

#include <iostream>
#include <vector>

unsigned short int FieldUtils::getFieldIndexByPosition(InitialConfig* config, std::vector<Field *> fields, std::string position)
{
    int index;

    for (size_t i = 0; i < config->fieldCount; i++)
    {
        if (fields[i]->getField() == position)
        {
            index = fields[i]->getId();
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

Field *FieldUtils::findFieldByFieldId(std::vector<Field *> v, unsigned int fieldId)
{
    std::vector<Field *>::iterator result = std::find_if(v.begin(), v.end(), [fieldId](Field *field)
                                                         { return field->getId() == fieldId; });
    ptrdiff_t index = std::distance(v.begin(), result);
    return v[index];
}