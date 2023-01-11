// #include "./pieces/PieceTypes.hpp"
#include "Game.hpp"
#include "PieceUtils.hpp"
#include "Player.hpp"
#include "InitialConfig.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>

#define LOOP(x) for (int i = 0; i < x; i++)
#define LOG(x) std::cout << x

// Game::Game(std::vector<Field> board, std::vector<Piece *> pieces)
// {
//     move_ = 1;
//     board_ = board;
//     currentPlayer_ = white;
//     pieces_ = pieces;
// }
Game::Game(std::vector<Piece *> pieces, unsigned int startNumber, unsigned int startLetter)
{
    unsigned int size = InitialConfig::getSize();
    int xIndex = startLetter;
    int yIndex = startNumber;
    int fieldIndex = 0;

    LOOP(size)
    {
        LOOP(size)
        {
            Field field = Field(xIndex, yIndex, fieldIndex);
            board_.push_back(field);

            xIndex++;
            fieldIndex++;
        }
        xIndex = startLetter;
        yIndex++;
    }

    move_ = 1;
    currentPlayer_ = white;
    pieces_ = pieces;
}

std::vector<Field> Game::getBoard()
{
    return board_;
}

void Game::addField(Field field)
{
    board_.push_back(field);
}

void Game::setPlayer(Player newPlayer)
{
    currentPlayer_ = newPlayer;
}

Player Game::getCurrentPlayer()
{
    return currentPlayer_;
}

std::vector<Piece *> Game::getPieces()
{
    return pieces_;
}

unsigned int Game::getMove()
{
    return move_;
}

void Game::nextPlayer()
{
    currentPlayer_ == white ? setPlayer(black) : setPlayer(white);
}

void Game::nextMove()
{
    move_++;
}

void Game::addPiece(Piece *piece)
{
    pieces_.push_back(piece);
}

void Game::takePiece(unsigned int fieldId)
{
    std::erase_if(pieces_, [fieldId](Piece *p)
                  { return p->getFieldId() == fieldId; });
    // TODO: add to taken pieces list in Game
}

void Game::printPieces()
{
    for (Piece *p : pieces_)
    {
        std::cout << p->getName() << std::endl; // TODO: read into
    }
}

std::string Game::getPieceInfo(unsigned int fieldId)
{
    Piece *piece = PieceUtils::findPieceByFieldId(pieces_, fieldId);
    if (piece)
        return piece->getName() + " " + PieceUtils::getPlayerColor(piece->getPlayer());
    return "";
}

void Game::printBoard()
{
    unsigned int fieldCount = InitialConfig::getFieldCount();

    for (size_t i = 0; i < fieldCount; i++)
    {

        std::cout << std::setw(6) << board_[i].getField() + board_[i].getFieldColor();
        std::cout << std::setw(14) << getPieceInfo(i) + " | ";
        if (!((i + 1) % (int)sqrt(fieldCount)))
        {
            std::cout << '\n';
        }
    }
};