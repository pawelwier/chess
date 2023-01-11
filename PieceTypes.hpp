// #pragma once

// #include "Piece.hpp"
// #include "../Utils.hpp"
// #include "../MoveUtils.hpp"
// #include "../FieldUtils.hpp"

// #include <array>
// #include <iostream>

// #define LOG(x) std::cout << x

// class Pawn : public Piece
// {
// public:
//     explicit Pawn(Player player, unsigned int fieldId) : Piece(player, pawn, fieldId)
//     {
//     }

//     void getAvailableFieldIds(
//         MoveOptions *options,
//         unsigned int from,
//         std::vector<Field> board,
//         std::vector<Piece *> pieces)
//     {
//         Player player = this->getPlayer();

//         unsigned int size = InitialConfig::getSize();
//         unsigned int startLetter = InitialConfig::getStartLetter();

//         // Move

//         // Check if there is piece on field in front
//         unsigned int firstIndex = player ? from - size : from + size;
//         if (MoveUtils::isFieldEmpty(firstIndex, pieces))
//             options->addMove(firstIndex);

//         // Check if first move
//         // TODO: add move history to Game, check if piece has been moved
//         // delete this var
//         unsigned short int pawnIds[16] = {8, 9, 10, 11, 12, 13, 14, 15, 48, 49, 50, 51, 52, 53, 54, 55};

//         unsigned short int *isFirstMove = std::find(std::begin(pawnIds), std::end(pawnIds), from);
//         if (isFirstMove != std::end(pawnIds))
//         {
//             unsigned int longMoveIndex = player ? firstIndex - size : firstIndex + size;
//             if (MoveUtils::isFieldEmpty(longMoveIndex, pieces))
//                 options->addMove(longMoveIndex);
//         }

//         // Take

//         // TODO: add en passant

//         unsigned int x = board[from].getX();

//         bool isBorderLeft = x == startLetter;
//         bool isBorderRight = x == (startLetter + size - 1);

//         unsigned int takeRight = player ? (from - size + 1) : (from + size + 1);
//         unsigned int takeLeft = player ? (from - size - 1) : (from + size - 1);

//         if (!isBorderLeft && MoveUtils::isOpponentPieceOnField(takeLeft, pieces, player))
//             options->addTake(takeLeft);
//         if (!isBorderRight && MoveUtils::isOpponentPieceOnField(takeRight, pieces, player))
//             options->addTake(takeRight);
//     }
// };

// class Rook : public Piece::Piece
// {
// public:
//     explicit Rook(Player player, unsigned int fieldId) : Piece(player, rook, fieldId)
//     {
//     }

//     void getAvailableFieldIds(
//         MoveOptions *options,
//         unsigned int from,
//         std::vector<Field> board,
//         std::vector<Piece *> pieces)
//     {
//         Player player = this->getPlayer();

//         unsigned int x = board[from].getX();
//         unsigned int y = board[from].getY();

//         std::vector<unsigned int> horizontalLeft, horizontalRight, verticalUp, verticalDown;

//         for (Field f : board)
//         {
//             if (f.getX() == x && f.getY() != y)
//                 if (f.getId() > from)
//                 {
//                     verticalUp.push_back(f.getId());
//                 }
//                 else
//                 {
//                     verticalDown.push_back(f.getId());
//                 }
//             if (f.getY() == y && f.getX() != x)
//                 if (f.getId() > from)
//                 {
//                     horizontalRight.push_back(f.getId());
//                 }
//                 else
//                 {
//                     horizontalLeft.push_back(f.getId());
//                 }
//         }

//         Utils::reverseVector(verticalDown);
//         Utils::reverseVector(horizontalLeft);

//         std::array<std::vector<unsigned int>, 4> moveOptions{
//             horizontalLeft,
//             horizontalRight,
//             verticalUp,
//             verticalDown};

//         for (std::vector<unsigned int> moveSet : moveOptions)
//         {
//             MoveUtils::addMoveOptions(moveSet, pieces, options, player);
//         }
//     }
// };

// class Knight : public Piece
// {
// public:
//     explicit Knight(Player player, unsigned int fieldId) : Piece(player, knight, fieldId)
//     {
//     }

//     void getAvailableFieldIds(
//         MoveOptions *options,
//         unsigned int from,
//         std::vector<Field> board,
//         std::vector<Piece *> pieces)
//     {
//         Player player = this->getPlayer();

//         unsigned int x = board[from].getX();
//         unsigned int y = board[from].getY();

//         signed int two = 2, one = 1;

//         std::array<std::array<unsigned int, 2>, 8>
//             // TODO: make a fn
//             moves = {
//                 {{x + two, y + one},
//                  {x + two, y - one},
//                  {x - two, y + one},
//                  {x - two, y - one},
//                  {x + one, y + two},
//                  {x + one, y - two},
//                  {x - one, y + two},
//                  {x - one, y - two}}};

//         std::vector<unsigned int> ids;

//         for (std::array<unsigned int, 2> move : moves)
//         {

//             if (MoveUtils::isOutsideBoard(move[0], move[1]))
//                 continue;
//             unsigned int index = FieldUtils::getFieldIndexByPosition(board, Utils::getFieldCoordinates(move[0], move[1]));
//             ids.push_back(index);
//         }
//         MoveUtils::addMoveOptions(ids, pieces, options, player, false);
//     }
// };

// class Bishop : public Piece
// {
// public:
//     explicit Bishop(Player player, unsigned int fieldId) : Piece(player, bishop, fieldId)
//     {
//     }

//     void getAvailableFieldIds(
//         MoveOptions *options,
//         unsigned int from,
//         std::vector<Field> board,
//         std::vector<Piece *> pieces)
//     {
//         LOG("looking for bishop fields ...");
//     }
// };

// class Queen : public Piece
// {
// public:
//     explicit Queen(Player player, unsigned int fieldId) : Piece(player, queen, fieldId)
//     {
//     }

//     void getAvailableFieldIds(
//         MoveOptions *options,
//         unsigned int from,
//         std::vector<Field> board,
//         std::vector<Piece *> pieces)
//     {
//         LOG("looking for queen fields ...");
//     }
// };

// class King : public Piece
// {
// public:
//     explicit King(Player player, unsigned int fieldId) : Piece(player, king, fieldId)
//     {
//     }

//     void getAvailableFieldIds(
//         MoveOptions *options,
//         unsigned int from,
//         std::vector<Field> board,
//         std::vector<Piece *> pieces)
//     {
//         LOG("looking for king fields ...");
//     }
// };