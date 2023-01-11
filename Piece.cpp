#include "Piece.hpp"
#include "MoveOptions.hpp"
#include "Field.hpp"
#include "PieceType.hpp"

#include <map>
#include <vector>
#include <algorithm>
#include <iterator>

Piece::Piece(Player player, PieceType type, unsigned int fieldId)
{
	player_ = player;
	type_ = type;
	fieldId_ = fieldId;
}

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

Player Piece::getPlayer()
{
	return player_;
}

unsigned int Piece::getFieldId()
{
	return fieldId_;
}

void Piece::setFieldId(unsigned int fieldId)
{
	fieldId_ = fieldId;
}

unsigned int findPieceIndex(std::vector<Piece *> v, unsigned int fieldId)
{
	std::vector<Piece *>::iterator result = std::find_if(v.begin(), v.end(), [fieldId](Piece *piece)
																											 { return piece->getFieldId() == fieldId; }); // TODO: read into
	ptrdiff_t index = std::distance(v.begin(), result);
	return index;
}

Piece *findPieceByFieldId(std::vector<Piece *> v, unsigned int fieldId)
{
	unsigned int index = findPieceIndex(v, fieldId);
	if (index == -1 || index == v.size()) // TODO: is that ok??
	{
		return 0;
	}
	return v[index];
}

bool isPlayersPieceOnField(Player player, std::vector<Piece *> v, unsigned int fieldId)
{
	Piece *piece = findPieceByFieldId(v, fieldId);
	return piece->getPlayer() == player;
}

std::string getPlayerColor(Player player)
{
	return !player ? "(W.)" : "(B.)";
}