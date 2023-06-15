#include "Game.hpp"
#include "./pieces/Pawn.hpp"
#include "./pieces/Rook.hpp"
#include "./pieces/Knight.hpp"
#include "./pieces/Bishop.hpp"
#include "./pieces/Queen.hpp"
#include "./pieces/King.hpp"
#include "./utils/PieceUtils.hpp"
#include "./utils/FieldUtils.hpp"
#include "Player.hpp"
#include "InitialConfig.hpp"
#include "Move.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <iterator>

#define LOOP(x) for (int i = 0; i < x; i++)

Game::Game(InitialConfig* config) :
    currentPlayer_(white),
    config_(config)
{   
    pieces_ = {};
    unsigned int startLetter = config->startLetter;
    unsigned int size = config->size;

    int xIndex = startLetter;
    int yIndex = size;
    int fieldIndex = config->fieldCount;

    int iter = config->size;

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
        iter = config->size;
        xIndex = startLetter;
        yIndex--;
    }
}

InitialConfig* Game::config()
{
    return config_;
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

void Game::takePiece(Piece *piece)
{
    unsigned int id = piece->getId();

    std::erase_if(pieces_, [id](Piece *p)
                  { return p->getId() == id; });

    takes_.push_back(piece);
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

std::vector<Piece *> Game::getTakes()
{
    return takes_;
}

std::vector<Piece *> Game::getPiecesByPlayer(Player player)
{
    std::vector<Piece *> to;
    std::copy_if(pieces_.begin(),
                 pieces_.end(),
                 std::back_inserter(to),
                 [player](Piece *piece)
                 { return piece->getPlayer() == player && !piece->getTaken(); });
    return to;
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
    return Utils::includes(config_->pawnIds, fieldId) ||
           Utils::includes(config_->rookIds, fieldId) ||
           Utils::includes(config_->knightIds, fieldId) ||
           Utils::includes(config_->bishopIds, fieldId) ||
           Utils::includes(config_->kingIds, fieldId) ||
           Utils::includes(config_->queenIds, fieldId);
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

void Game::clearOptions()
{
    moveOptions_.clear();
    takeOptions_.clear();
}

std::vector<unsigned int> Game::getTakeOptions()
{
    return takeOptions_;
}

unsigned int Game::getPlayerPoints(Player player)
{
    return PieceUtils::getPiecePoints(this->getPiecesByPlayer(player));
}

void Game::assignInitialPieces(std::vector<Field *> fields)
{
    unsigned int id{0};

    for (Field *field : fields)
    {
        unsigned int fieldId = field->getId();
        if (!this->fieldHasPiece(fieldId))
            continue;

        Player player = FieldUtils::initPiecePlayer(fieldId);

        // TODO: refactor
        if (Utils::includes(config_->pawnIds, fieldId))
        {
            this->addPiece(new Pawn(id, player, fieldId));
            id++;
        }

        if (Utils::includes(config_->rookIds, fieldId))
        {
            this->addPiece(new Rook(id, player, fieldId));
            id++;
        }

        if (Utils::includes(config_->knightIds, fieldId))
        {
            this->addPiece(new Knight(id, player, fieldId));
            id++;
        }

        if (Utils::includes(config_->bishopIds, fieldId))
        {
            this->addPiece(new Bishop(id, player, fieldId));
            id++;
        }

        if (Utils::includes(config_->queenIds, fieldId))
        {
            this->addPiece(new Queen(id, player, fieldId));
            id++;
        }

        if (Utils::includes(config_->kingIds, fieldId))
        {
            this->addPiece(new King(id, player, fieldId));
            id++;
        }
    }
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