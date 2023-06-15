#include "../Field.hpp"
#include "../Player.hpp"
#include "../Game.hpp"
#include "../InitialConfig.hpp"

class FieldUtils
{
public:
    static unsigned short int getFieldIndexByPosition(InitialConfig* config, std::vector<Field *> fields, std::string position);

    static Player initPiecePlayer(short unsigned id);

    static void addField();

    static Field *findFieldByFieldId(std::vector<Field *> v, unsigned int fieldId);
};