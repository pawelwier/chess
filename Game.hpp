#include <iostream>
#include <iomanip>
#include <array>
#include <vector>
#include "Field.hpp"

class Game
{
private:
    Player currentPlayer_;
    std::array<Field, FIELD_COUNT> board_;
    std::vector<Piece *> pieces_;

public:
    Game(std::array<Field, FIELD_COUNT> board, std::vector<Piece *> pieces)
    {
        board_ = board;
        currentPlayer_ = white;
        pieces_ = pieces;
    }

    void setPlayer(Player newPlayer)
    {
        currentPlayer_ = newPlayer;
    }

    Player getCurrentPlayer()
    {
        return currentPlayer_;
    }

    std::vector<Piece *> getPieces()
    {
        return pieces_;
    }

    void nextPlayer()
    {
        currentPlayer_ == white ? setPlayer(black) : setPlayer(white);
    }

    void addPiece(Piece *piece)
    {
        pieces_.push_back(piece);
    }

    void printPieces()
    {
        for (Piece *p : pieces_)
        {
            std::cout << p->getName() << std::endl; // TODO: read into
        }
    }

    std::string getPieceInfo(unsigned int fieldId)
    {
        Piece *piece = findPieceByFieldId(pieces_, fieldId);
        if (piece)
            return piece->getName() + " " + getPlayerColor(piece->getPlayer());
        return "";
    }

    void printBoard()
    {
        for (size_t i = 0; i < FIELD_COUNT; i++)
        {
            std::cout << std::setw(6) << board_[i].getField() + board_[i].getFieldColor();
            std::cout << std::setw(14) << getPieceInfo(i) + " | ";
            if (!((i + 1) % (int)sqrt(FIELD_COUNT)))
            {
                std::cout << '\n';
            }
        }
    }
};