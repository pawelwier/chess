#include <string>
#include <iostream>
#include <iomanip>

#include "utils.hpp"
#include "initialConfig.hpp"

#define LOOP(x) for (int i = 0; i < x; i++)

enum Player
{
    white,
    black
};

bool isInTypeArray(unsigned short int ids[], size_t s, unsigned short int id)
{
    unsigned short int *end = ids + s;
    return std::find(ids, end, id) != end;
}

Player initPiecePlayer(short unsigned id)
{
    return isWithinValues(id, whitePieces) ? white : black;
}

class Field
{
private:
    unsigned short int x_;
    unsigned short int y_;
    unsigned short int id_; // delete, use x & y only?
    bool isBlack_;
    unsigned int pieceId;

public:
    std::string getField()
    {
        return getChar(x_) + std::to_string(y_);
    }

    void setField(
        unsigned short int x,
        unsigned short int y,
        unsigned short int id)
    {
        x_ = x;
        y_ = y;
        id_ = id;
        isBlack_ = isOdd(x) == isOdd(y);
    }

    unsigned short int getId()
    {
        return id_;
    }

    unsigned short int getX()
    {
        return x_;
    }

    unsigned short int getY()
    {
        return y_;
    }

    std::string getFieldColor()
    {
        return isBlack_ ? "(b)" : "(w)";
    }
};

unsigned short int getFieldIndexByPosition(std::array<Field, FIELD_COUNT> &fields, std::string position)
{
    int index;

    for (size_t i = 0; i < FIELD_COUNT; i++)
    {
        if (fields[i].getField() == position)
        {
            index = i;
        }
    }

    return index;
}

void getInitialSetup(std::array<Field, FIELD_COUNT> &fields, int startNum, int startLetter)
{
    int xIndex = startLetter;
    int yIndex = startNum;
    int fieldIndex = 0;

    LOOP(SIZE)
    {
        LOOP(SIZE)
        {
            fields[fieldIndex].setField(xIndex, yIndex, fieldIndex);

            xIndex++;
            fieldIndex++;
        }
        xIndex = startLetter;
        yIndex++;
    }
}