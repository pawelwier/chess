#pragma once

#include "MoveOptions.hpp"
#include "Field.hpp"
#include "PieceType.hpp"
#include "Player.hpp"

#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

class Piece
{
private:
    unsigned int id_;
    PieceType type_;
    Player player_;
    unsigned int fieldId_;
    unsigned int points_;
    bool isTaken_;

public:
    Piece(unsigned int id, Player player, PieceType type, unsigned int fieldId, unsigned int points);

    virtual void getAvailableMoves(
        MoveOptions *options,
        unsigned int from,
        std::vector<Field *> board,
        std::vector<Piece *> pieces) = 0;

    void move(unsigned int to);

    std::string getName();

    wchar_t getIcon();

    Player getPlayer();

    unsigned int getId();

    unsigned int getFieldId();

    void setFieldId(unsigned int fieldId);

    unsigned int findPieceIndex(std::vector<Piece *> v, unsigned int fieldId);

    bool getTaken();

    void setTaken(bool isTaken);

    unsigned int getPoints();

    Piece *findPieceByFieldId(std::vector<Piece *> v, unsigned int fieldId);

    bool isPlayersPieceOnField(Player player, std::vector<Piece *> v, unsigned int fieldId);

    std::string getPlayerColor(Player player);
};