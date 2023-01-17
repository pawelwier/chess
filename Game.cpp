#include "Game.hpp"
#include "PieceUtils.hpp"
#include "Player.hpp"
#include "InitialConfig.hpp"
#include "Move.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <iterator>

#define LOOP(x) for (int i = 0; i < x; i++)

Game::Game(std::vector<Piece *> pieces)
{
    InitialConfig config;

    unsigned int startNumber = config.startNumber();
    unsigned int startLetter = config.startLetter();
    unsigned int size = config.size();

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

void Game::nextPlayer()
{
    currentPlayer_ == white ? setPlayer(black) : setPlayer(white);
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

std::string Game::getPieceInfo(unsigned int fieldId)
{
    Piece *piece = PieceUtils::findPieceByFieldId(pieces_, fieldId);
    if (piece)
        return piece->getName() + " " + PieceUtils::getPlayerColor(piece->getPlayer());
    return "";
}

void Game::printBoard()
{
    InitialConfig config;

    unsigned int fieldCount = config.fieldCount();

    for (size_t i = 0; i < fieldCount; i++)
    {

        std::cout << std::setw(6) << board_[i].getField() + board_[i].getFieldColor();
        std::cout << std::setw(14) << getPieceInfo(i) + " | ";
        if (!((i + 1) % (int)sqrt(fieldCount)))
        {
            std::cout << '\n';
        }
    }
}

unsigned int Game::getMoveCount()
{
    return moves_.size();
}

void Game::addMove(Move *move)
{
    moves_.push_back(move);
}

std::vector<Move *> Game::getMoves()
{
    return moves_;
}

Field Game::getFieldById(unsigned int id)
{
    return board_[id];
}

void Game::printMove(unsigned int order)
{
    // TODO: edit
    std::vector<Move *> moves = this->getMoves();
    std::vector<Move *>::iterator result = std::find_if(std::begin(moves), std::end(moves), [order](Move *move)
                                                        { return move->getOrder() == order; });
    ptrdiff_t index = std::distance(moves.begin(), result);

    Move *move = moves_[index];
    Field from = this->getFieldById(move->getFrom());
    Field to = this->getFieldById(move->getTo());

    unsigned int pieceId = move->getPieceId();
    std::vector<Piece *> pieces = this->getPieces();
    std::vector<Piece *>::iterator found = std::find_if(std::begin(pieces), std::end(pieces), [pieceId](Piece *piece)
                                                        { return piece->getId() == pieceId; });
    ptrdiff_t i = std::distance(pieces.begin(), found);

    Piece *piece = pieces[i];

    Player player = piece->getPlayer();

    std::cout
        << "Move "
        << order
        << ": "
        << piece->getName()
        << " "
        << piece->getPlayerColor(player)
        << " "
        << from.getField()
        << " -> "
        << to.getField() << std::endl;
}