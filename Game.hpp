#pragma once

#include "Piece.hpp"
#include "Field.hpp"
#include "Player.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

class Game
{
private:
    Player currentPlayer_;
    std::vector<Field> board_;
    std::vector<Piece *> pieces_;
    unsigned int move_;

public:
    // Game(std::vector<Field> board, std::vector<Piece *> pieces);
    Game(std::vector<Piece *> pieces, unsigned int startNumber, unsigned int startLetter);
    std::vector<Field> getBoard();
    void addField(Field field);
    std::string getPieceInfo(unsigned int fieldId);
    Player getCurrentPlayer();
    std::vector<Piece *> getPieces();
    unsigned int getMove();

    void setPlayer(Player newPlayer);
    void nextPlayer();
    void nextMove();
    void addPiece(Piece *piece);
    void takePiece(unsigned int fieldId);
    void printPieces();
    void printBoard();
};