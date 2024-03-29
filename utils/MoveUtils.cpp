#include "MoveUtils.hpp"
#include "PieceUtils.hpp"
#include "../Player.hpp"
#include "../InitialConfig.hpp"

#include <vector>
#include <algorithm>

#define LOOP(x) for (int i = 0; i < x; i++)

bool MoveUtils::isFieldEmpty(unsigned int index, std::vector<Piece *> pieces)
{
    Piece *piece = PieceUtils::findPieceByFieldId(pieces, index);
    return !piece;
}

bool MoveUtils::isOpponentPieceOnField(unsigned int index, std::vector<Piece *> pieces, Player player)
{
    Piece *piece = PieceUtils::findPieceByFieldId(pieces, index);
    Player opponent = !player ? black : white;
    return !!piece && piece->getPlayer() == opponent;
}

bool MoveUtils::isOutsideBoard(InitialConfig* config, unsigned int x, unsigned int y)
{
    unsigned int size = config->size;
    unsigned int startNumber = config->startNumber;
    unsigned int startLetter = config->startLetter;

    return (x < startLetter) || (x > (startLetter + size - 1)) || (y < startNumber) || (y > startNumber + size - 1);
}

void MoveUtils::addMoveOptions(std::vector<unsigned int> ids, std::vector<Piece *> pieces, MoveOptions *options, Player player, bool stopOnPiece)
{
    LOOP(ids.size())
    {
        if (isFieldEmpty(ids[i], pieces))
            options->addMove(ids[i]);
        else
        {
            if (isOpponentPieceOnField(ids[i], pieces, player))
            {
                options->addTake(ids[i]);
            }
            if (stopOnPiece)
            {
                break;
            }
        }
    }
}

std::vector<unsigned int> MoveUtils::removeFromOptions(std::vector<unsigned int> options, unsigned int option)
{
    std::vector<unsigned int> filteredOptions;
    std::copy_if(options.begin(), options.end(), std::back_inserter(filteredOptions), [option](unsigned int i) {
        return i != option;
    });

    return filteredOptions;
}