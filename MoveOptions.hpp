#include <vector>

class MoveOptions
{
private:
    std::vector<unsigned int> moves_;
    std::vector<unsigned int> takes_;

public:
    std::vector<unsigned int> getMoves()
    {
        return moves_;
    }

    std::vector<unsigned int> getTakes()
    {
        return takes_;
    }

    void addMove(unsigned int move)
    {
        moves_.push_back(move);
    }

    void addTake(unsigned int take)
    {
        takes_.push_back(take);
    }
};