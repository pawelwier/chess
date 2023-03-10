
#pragma once

#include <vector>

class MoveOptions
{
private:
    std::vector<unsigned int> moves_;
    std::vector<unsigned int> takes_;

public:
    std::vector<unsigned int> getMoves();
    std::vector<unsigned int> getTakes();
    void addMove(unsigned int move);
    void addTake(unsigned int take);
};
