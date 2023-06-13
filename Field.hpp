#ifndef FIELD_H
#define FIELD_H

#include "./utils/Utils.hpp"
#include "InitialConfig.hpp"

#include <string>

class Field
{
private:
    unsigned short int x_;
    unsigned short int y_;
    unsigned short int id_; // delete, use x & y only?
    bool isBlack_;
    unsigned int pieceId;

public:
    Field(unsigned short int x, unsigned short int y, unsigned short int id);

    std::string getField();

    unsigned short int getId();

    unsigned short int getX();

    unsigned short int getY();

    std::string getFieldColor();

    bool isBlack();
};

#endif