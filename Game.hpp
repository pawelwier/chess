#ifndef GAME_H
#define GAME_H

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
    InitialConfig* config_;
    std::string icon_;
    Player currentPlayer_;
    std::vector<Field *> board_;
    std::vector<Piece *> pieces_;
    std::vector<Move *> moves_;
    std::vector<Piece *> takes_;
    Piece *selectedPiece_ = nullptr;
    std::vector<unsigned int> moveOptions_;
    std::vector<unsigned int> takeOptions_;

public:
    Game(InitialConfig* config);

    InitialConfig* config();

    std::vector<Field *> getBoard();

    void addField(Field *field);

    Player getCurrentPlayer();

    std::vector<Piece *> getPieces();

    void setPlayer(Player newPlayer);

    void setSelectedPiece(Piece *piece);

    void nextPlayer();

    void addPiece(Piece *piece);

    void takePiece(Piece *piece);

    unsigned int getMoveCount();

    Piece *getSelectedPiece();

    void addMove(Move *move);

    std::vector<Move *> getMoves();

    std::vector<Piece *> getTakes();

    std::vector<Piece *> getPiecesByPlayer(Player player);

    bool fieldHasPiece(unsigned int fieldId);

    void assignInitialPieces(std::vector<Field *> fields);

    void printMove(unsigned int moveId);

    void addMoveOption(unsigned int moveOption);

    std::vector<unsigned int> getMoveOptions();

    void addTakeOption(unsigned int takeOption);

    unsigned int getPlayerPoints(Player player);

    void clearOptions();

    std::vector<unsigned int> getTakeOptions();

    unsigned int getKingFieldId(Player player);

    bool isCheck();
};

#endif