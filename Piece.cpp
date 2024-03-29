#include "Piece.hpp"
#include "Field.hpp"
#include "PieceType.hpp"
#include "./utils/PieceUtils.hpp"

#include <map>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>

Piece::Piece(unsigned int id, Player player, PieceType type, unsigned int fieldId, unsigned int points) : 
    id_(id),
    player_(player),
    type_(type),
    fieldId_(fieldId),
    points_(points),
    isTaken_(false) {}

void Piece::move(unsigned int to)
{
    setFieldId(to);
}

std::string Piece::getName()
{
    std::map<PieceType, std::string> pieces{
        {PieceType::none, "-"},
        {PieceType::pawn, "pawn"},
        {PieceType::rook, "rook"},
        {PieceType::knight, "knight"},
        {PieceType::bishop, "bishop"},
        {PieceType::queen, "queen"},
        {PieceType::king, "king"}};

    return pieces[type_];
}

wchar_t Piece::getIcon()
{
    std::map<PieceType, std::array<wchar_t, 2>> pieces{
        {PieceType::pawn, {0x2659, 0x265F}},
        {PieceType::rook, {0x2656, 0x265C}},
        {PieceType::knight, {0x2658, 0x265E}},
        {PieceType::bishop, {0x2657, 0x265D}},
        {PieceType::queen, {0x2655, 0x265B}},
        {PieceType::king, {0x2654, 0x265A}}};

    std::array<wchar_t, 2> pieceVariants = pieces[type_];
    return this->getPlayer() ? pieceVariants[0] : pieceVariants[1];
}

Player Piece::getPlayer()
{
    return player_;
}

unsigned int Piece::getFieldId()
{
    return fieldId_;
}

PieceType Piece::getType()
{
    return type_;
}

unsigned int Piece::getId()
{
    return id_;
}

void Piece::setFieldId(unsigned int fieldId)
{
    fieldId_ = fieldId;
}

bool Piece::getTaken()
{
    return isTaken_;
}

void Piece::setTaken(bool isTaken)
{
    isTaken_ = isTaken;
}

unsigned int Piece::getPoints()
{
    return points_;
}

bool Piece::isPlayersPieceOnField(Player player, std::vector<Piece *> pieces, unsigned int fieldId)
{
    Piece *piece = PieceUtils::findPieceByFieldId(pieces, fieldId);
    return piece->getPlayer() == player;
}

std::string Piece::getPlayerColor(Player player)
{
    return !player ? "(W.)" : "(B.)";
}