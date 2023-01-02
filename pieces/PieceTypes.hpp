#include <iostream>
#include "Piece.hpp"

class Pawn : public Piece
{
public:
    explicit Pawn(Player player, unsigned int fieldId) : Piece(player, pawn, fieldId)
    {
    }

    void getAvailableFields()
    {
        std::cout << "looking for pawn fields ..." << std::endl;
    }
};

class Rook : public Piece
{
public:
    explicit Rook(Player player, unsigned int fieldId) : Piece(player, rook, fieldId)
    {
    }

    void getAvailableFields()
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

    void getAvailableFields()
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

    void getAvailableFields()
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

    void getAvailableFields()
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

    void getAvailableFields()
    {
        std::cout << "looking for king fields ..." << std::endl;
    }
};