#include "Game.hpp"
#include "PieceUtils.hpp"
#include "FieldUtils.hpp"
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
    int yIndex = size;
    int fieldIndex = config.fieldCount();

    int iter = config.size();

    LOOP(size)
    {
        LOOP(size)
        {
            int in = fieldIndex - iter;
            this->addField(new Field(xIndex, yIndex, in));

            iter--;
            xIndex++;
        }
        fieldIndex = fieldIndex - size;
        iter = config.size();
        xIndex = startLetter;
        yIndex--;
    }

    currentPlayer_ = white;
    pieces_ = pieces;
}

std::vector<Field *> Game::getBoard()
{
    return board_;
}

void Game::addField(Field *field)
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
    // TODO: add to taken pieces list in Game, delete piece
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

void Game::setSelectedPiece(Piece *piece)
{
    selectedPiece_ = piece;
}

Piece *Game::getSelectedPiece()
{
    return selectedPiece_;
}

bool Game::fieldHasPiece(unsigned int fieldId)
{
    InitialConfig config;
    return Utils::includes(config.pawnIds(), fieldId) ||
           Utils::includes(config.rookIds(), fieldId) ||
           Utils::includes(config.knightIds(), fieldId) ||
           Utils::includes(config.bishopIds(), fieldId) ||
           Utils::includes(config.kingIds(), fieldId) ||
           Utils::includes(config.queenIds(), fieldId);
}

void Game::addMoveOption(unsigned int option)
{
    moveOptions_.push_back(option);
}

std::vector<unsigned int> Game::getMoveOptions()
{
    return moveOptions_;
}

void Game::addTakeOption(unsigned int option)
{
    takeOptions_.push_back(option);
}

std::vector<unsigned int> Game::getTakeOptions()
{
    return takeOptions_;
}

void Game::printMove(unsigned int order)
{
    // TODO: edit / delete?
    std::vector<Move *> moves = this->getMoves();
    std::vector<Move *>::iterator result = std::find_if(std::begin(moves), std::end(moves), [order](Move *move)
                                                        { return move->getOrder() == order; });
    ptrdiff_t index = std::distance(moves.begin(), result);

    Move *move = moves_[index];
    Field *from = FieldUtils::findFieldByFieldId(board_, move->getFrom());
    Field *to = FieldUtils::findFieldByFieldId(board_, move->getTo());

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
        << from->getField()
        << " -> "
        << to->getField() << std::endl;
}