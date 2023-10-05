#include "MoveOptions.hpp"
#include "./utils/MoveUtils.hpp"

#include <vector>

MoveOptions::MoveOptions() : 
    moves_({}),
    takes_({})
    {}

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
    this->moves_.push_back(move);
}

void MoveOptions::addTake(unsigned int take)
{
    this->takes_.push_back(take);
}

void MoveOptions::removeMove(unsigned int move)
{
    this->moves_ = MoveUtils::removeFromOptions(this->moves_, move);
}

void MoveOptions::removeTake(unsigned int take)
{
    this->takes_ = MoveUtils::removeFromOptions(this->takes_, take);
}

void MoveOptions::clear()
{
    this->moves_ = {};
    this->takes_ = {};
}