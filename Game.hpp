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
    std::vector<Field *> board_;
    std::vector<Piece *> pieces_;
    std::vector<Move *> moves_;
    Piece *selectedPiece_ = nullptr;
    std::vector<unsigned int> moveOptions_;
    std::vector<unsigned int> takeOptions_;

public:
    Game(std::vector<Piece *> pieces);

    std::vector<Field *> getBoard();

    void addField(Field *field);

    Player getCurrentPlayer();

    std::vector<Piece *> getPieces();

    void setPlayer(Player newPlayer);

    void setSelectedPiece(Piece *piece);

    void nextPlayer();

    void addPiece(Piece *piece);

    void takePiece(unsigned int fieldId);

    unsigned int getMoveCount();

    Piece *getSelectedPiece();

    void addMove(Move *move);

    std::vector<Move *> getMoves();

    bool fieldHasPiece(unsigned int fieldId);

    void printMove(unsigned int moveId);

    void addMoveOption(unsigned int moveOption);

    std::vector<unsigned int> getMoveOptions();

    void addTakeOption(unsigned int takeOption);

    std::vector<unsigned int> getTakeOptions();
};