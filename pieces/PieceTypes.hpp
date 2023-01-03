#include <array>
#include "Piece.hpp"

#define log(x) std::cout << x

class Pawn : public Piece
{
public:
    explicit Pawn(Player player, unsigned int fieldId) : Piece(player, pawn, fieldId)
    {
    }

    void getAvailableFields(unsigned int from, std::array<Field, FIELD_COUNT> board, std::vector<Piece *> pieces)
    {
        Player player = this->getPlayer();

        unsigned int firstIndex = player ? from - SIZE : from + SIZE;

        std::vector<unsigned int> available{firstIndex};

        unsigned short int *isFirstMove = std::find(std::begin(pawnIds), std::end(pawnIds), from);

        if (isFirstMove != std::end(pawnIds))
        {
            available.push_back(player ? firstIndex - SIZE : firstIndex + SIZE);
        }

        for (int i : available)
        {
            Piece *p = findPieceByFieldId(pieces, i);
            if (p)
            {
                log("can't move to");
                log(board[i].getField()); // TODO: finish
            }
        }
    }
};

class Rook : public Piece
{
public:
    explicit Rook(Player player, unsigned int fieldId) : Piece(player, rook, fieldId)
    {
    }

    void getAvailableFields(unsigned int from, std::array<Field, FIELD_COUNT> board, std::vector<Piece *> pieces)
    {
        std::cout << "looking for rook fields ..." << std::endl;
    }
};

class Knight : public Piece
{
public:
    explicit Knight(Player player, unsigned int fieldId) : Piece(player, knight, fieldId)
    {
    }

    void getAvailableFields(unsigned int from, std::array<Field, FIELD_COUNT> board, std::vector<Piece *> pieces)

    {
        std::cout << "looking for knight fields ..." << std::endl;
    }
};

class Bishop : public Piece
{
public:
    explicit Bishop(Player player, unsigned int fieldId) : Piece(player, bishop, fieldId)
    {
    }

    void getAvailableFields(unsigned int from, std::array<Field, FIELD_COUNT> board, std::vector<Piece *> pieces)
    {
        std::cout << "looking for bishop fields ..." << std::endl;
    }
};

class Queen : public Piece
{
public:
    explicit Queen(Player player, unsigned int fieldId) : Piece(player, queen, fieldId)
    {
    }

    void getAvailableFields(unsigned int from, std::array<Field, FIELD_COUNT> board, std::vector<Piece *> pieces)
    {
        std::cout << "looking for queen fields ..." << std::endl;
    }
};

class King : public Piece
{
public:
    explicit King(Player player, unsigned int fieldId) : Piece(player, king, fieldId)
    {
    }

    void getAvailableFields(unsigned int from, std::array<Field, FIELD_COUNT> board, std::vector<Piece *> pieces)
    {
        std::cout << "looking for king fields ..." << std::endl;
    }
};