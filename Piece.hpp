#ifndef PIECE_H
#define PIECE_H

#include "MoveOptions.hpp"
#include "InitialConfig.hpp"
#include "Field.hpp"
#include "Move.hpp"
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
        InitialConfig* config,
        MoveOptions *options,
        std::vector<Field *> board,
        std::vector<Piece *> pieces,
        std::vector<Move *> moves,
        Player player) = 0;

    void move(unsigned int to);

    std::string getName();

    wchar_t getIcon();

    Player getPlayer();

    unsigned int getId();

    unsigned int getFieldId();

    PieceType getType();

    void setFieldId(unsigned int fieldId);

    bool getTaken();

    void setTaken(bool isTaken);

    unsigned int getPoints();

    bool isPlayersPieceOnField(Player player, std::vector<Piece *> pieces, unsigned int fieldId);

    std::string getPlayerColor(Player player);
};

#endif