#include <array>
#include "Piece.hpp"

#define log(x) std::cout << x

bool isFieldEmpty(unsigned int index, std::vector<Piece *> pieces)
{
    Piece *piece = findPieceByFieldId(pieces, index);
    return !piece;
}

class Pawn : public Piece
{
public:
    explicit Pawn(Player player, unsigned int fieldId) : Piece(player, pawn, fieldId)
    {
    }

    std::vector<unsigned int> getAvailableFieldIds(unsigned int from, std::array<Field, FIELD_COUNT> board, std::vector<Piece *> pieces)
    {
        std::vector<unsigned int> available{};

        Player player = this->getPlayer();

        // Check if there is piece on field in front
        unsigned int firstIndex = player ? from - SIZE : from + SIZE;
        if (isFieldEmpty(firstIndex, pieces))
            available.push_back(firstIndex);

        // Check if first move
        // TODO: add move history to Game, check if piece has been moved
        unsigned short int *isFirstMove = std::find(std::begin(pawnIds), std::end(pawnIds), from);
        if (isFirstMove != std::end(pawnIds))
        {
            unsigned int longMoveIndex = player ? firstIndex - SIZE : firstIndex + SIZE;
            if (isFieldEmpty(longMoveIndex, pieces))
                available.push_back(longMoveIndex);
        }

        return available;
    }
};

class Rook : public Piece
{
public:
    explicit Rook(Player player, unsigned int fieldId) : Piece(player, rook, fieldId)
    {
    }

    std::vector<unsigned int> getAvailableFieldIds(unsigned int from, std::array<Field, FIELD_COUNT> board, std::vector<Piece *> pieces)
    {
        std::cout << "looking for rook fields ..." << std::endl;
        return {};
    }
};

class Knight : public Piece
{
public:
    explicit Knight(Player player, unsigned int fieldId) : Piece(player, knight, fieldId)
    {
    }

    std::vector<unsigned int> getAvailableFieldIds(unsigned int from, std::array<Field, FIELD_COUNT> board, std::vector<Piece *> pieces)

    {
        std::cout << "looking for knight fields ..." << std::endl;
        return {};
    }
};

class Bishop : public Piece
{
public:
    explicit Bishop(Player player, unsigned int fieldId) : Piece(player, bishop, fieldId)
    {
    }

    std::vector<unsigned int> getAvailableFieldIds(unsigned int from, std::array<Field, FIELD_COUNT> board, std::vector<Piece *> pieces)
    {
        std::cout << "looking for bishop fields ..." << std::endl;
        return {};
    }
};

class Queen : public Piece
{
public:
    explicit Queen(Player player, unsigned int fieldId) : Piece(player, queen, fieldId)
    {
    }

    std::vector<unsigned int> getAvailableFieldIds(unsigned int from, std::array<Field, FIELD_COUNT> board, std::vector<Piece *> pieces)
    {
        std::cout << "looking for queen fields ..." << std::endl;
        return {};
    }
};

class King : public Piece
{
public:
    explicit King(Player player, unsigned int fieldId) : Piece(player, king, fieldId)
    {
    }

    std::vector<unsigned int> getAvailableFieldIds(unsigned int from, std::array<Field, FIELD_COUNT> board, std::vector<Piece *> pieces)
    {
        std::cout << "looking for king fields ..." << std::endl;
        return {};
    }
};