#pragma once

#include "Piece.hpp"
#include "Field.hpp"
#include "Player.hpp"
#include "Move.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

class Game
{
private:
    std::string icon_;
    Player currentPlayer_;
    std::vector<Field> board_;
    std::vector<Piece *> pieces_;
    std::vector<Move *> moves_;

public:
    Game(std::vector<Piece *> pieces);

    std::vector<Field> getBoard();

    void addField(Field field);

    std::string getPieceInfo(unsigned int fieldId);

    wchar_t getPieceIcon(unsigned int fieldId);

    Player getCurrentPlayer();

    std::vector<Piece *> getPieces();

    void setPlayer(Player newPlayer);

    void nextPlayer();

    void addPiece(Piece *piece);

    void takePiece(unsigned int fieldId);

    void printBoard();

    unsigned int getMoveCount();

    void addMove(Move *move);

    std::vector<Move *> getMoves();

    Field getFieldById(unsigned int id);

    void printMove(unsigned int moveId);
};