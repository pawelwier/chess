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
    moveOptions_ = new MoveOptions();
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
    std::vector<std::vector<unsigned int>> pieceIds{
        {config_->pawnIds, config_->rookIds, config_->knightIds, config_->bishopIds, config_->queenIds, config_->kingIds}};
    bool hasPiece{};

    for (std::vector<unsigned int> idSet : pieceIds)
    {
        if (Utils::includes(idSet, fieldId))
        {
            hasPiece = true;
        }
    }
    return hasPiece;
}

MoveOptions *Game::getMoveOptions()
{
    return moveOptions_;
}

bool Game::hasMoveOptions()
{
    return moveOptions_->getMoves().size() || moveOptions_->getTakes().size();
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
        Piece *piece;

        if (Utils::includes(config_->pawnIds, fieldId)) piece = new Pawn(id, player, fieldId);
        if (Utils::includes(config_->rookIds, fieldId)) piece = new Rook(id, player, fieldId);
        if (Utils::includes(config_->knightIds, fieldId)) piece = new Knight(id, player, fieldId);
        if (Utils::includes(config_->bishopIds, fieldId)) piece = new Bishop(id, player, fieldId);
        if (Utils::includes(config_->queenIds, fieldId)) piece = new Queen(id, player, fieldId);
        if (Utils::includes(config_->kingIds, fieldId)) piece = new King(id, player, fieldId);
        
        this->addPiece(piece);
        id++;
    }
}

void Game::printMove(unsigned int order)
{
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

unsigned int Game::getKingFieldId(Player player)
{
    std::vector<Piece *> pieces = this->getPiecesByPlayer(player);
    std::vector<Piece *>::iterator result = std::find_if(pieces.begin(), pieces.end(), [](Piece *piece) 
        {return piece->getType() == PieceType::king;});

    ptrdiff_t index = std::distance(pieces.begin(), result);

    return pieces[index]->getFieldId();
}

Player Game::getOpponent()
{
    Player current = this->getCurrentPlayer();
    return current == Player::black ? Player::white : Player::black;
}

bool Game::isFieldInThreat(int fieldIndex, std::vector<Piece *> pieces)
{
    bool isInThreat = false;
    Player current = this->getCurrentPlayer();
    Player opponent = this->getOpponent();

    MoveOptions *options = new MoveOptions;

    std::vector<Piece *> opponentPieces = getPiecesByPlayer(opponent);

    for (Piece* piece : opponentPieces)
    {
        piece->getAvailableMoves(
            this->config(), 
            options,
            this->getBoard(),
            pieces,
            this->getMoves(),
            opponent);

        // TODO: a bit ugly
        if ((piece->getType() != PieceType::pawn 
            && Utils::includes(options->getMoves(), fieldIndex))
                || Utils::includes(options->getTakes(), fieldIndex)
            )
        {
            isInThreat = true;
            break;
        }
    }

    options = nullptr;
    delete options;
    
    return isInThreat;
}

bool Game::isCheck(std::vector<Piece *> pieces)
{
    Player current = this->getCurrentPlayer();

    unsigned int kingIndex = this->getKingFieldId(current);

    return this->isFieldInThreat(kingIndex, pieces);
}