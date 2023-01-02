#include <iostream>
#include "Piece.hpp"

class Pawn : public Piece
{
public:
    explicit Pawn(Player player, unsigned int fieldId) : Piece(player, pawn, fieldId)
    {
    }

    void move()
    {
        std::cout << "moving pawn" << std::endl;
    }
};

class Rook : public Piece
{
public:
    explicit Rook(Player player, unsigned int fieldId) : Piece(player, rook, fieldId)
    {
    }

    void move()
    {
        std::cout << "moving rook" << std::endl;
    }
};

class Knight : public Piece
{
public:
    explicit Knight(Player player, unsigned int fieldId) : Piece(player, knight, fieldId)
    {
    }

    void move()
    {
        std::cout << "moving knight" << std::endl;
    }
};

class Bishop : public Piece
{
public:
    explicit Bishop(Player player, unsigned int fieldId) : Piece(player, bishop, fieldId)
    {
    }

    void move()
    {
        std::cout << "moving bishop" << std::endl;
    }
};

class Queen : public Piece
{
public:
    explicit Queen(Player player, unsigned int fieldId) : Piece(player, queen, fieldId)
    {
    }

    void move()
    {
        std::cout << "moving queen" << std::endl;
    }
};

class King : public Piece
{
public:
    explicit King(Player player, unsigned int fieldId) : Piece(player, king, fieldId)
    {
    }

    void move()
    {
        std::cout << "moving king" << std::endl;
    }
};