
#ifndef MOVE_OPTIONS_H
#define MOVE_OPTIONS_H

#include <vector>

class MoveOptions
{
private:
    std::vector<unsigned int> moves_;
    std::vector<unsigned int> takes_;

public:
    MoveOptions();
    
    std::vector<unsigned int> getMoves();
    std::vector<unsigned int> getTakes();

    void addMove(unsigned int move);
    void addTake(unsigned int take);

    void removeMove(unsigned int move);
    void removeTake(unsigned int take);

    void clear();
};

#endif