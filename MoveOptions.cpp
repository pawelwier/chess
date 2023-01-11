#include "MoveOptions.hpp"

#include <vector>

std::vector<unsigned int> MoveOptions::getMoves()
{
    return moves_;
}

std::vector<unsigned int> MoveOptions::getTakes()
{
    return takes_;
}

void MoveOptions::addMove(unsigned int move)
{
    moves_.push_back(move);
}

void MoveOptions::addTake(unsigned int take)
{
    takes_.push_back(take);
}
