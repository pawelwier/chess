#include <map>
#include <vector>
#include <algorithm>
#include <iterator>

#include "../MoveOptions.hpp"
#include "../Field.hpp"

enum PieceType
{
    none,
    pawn,
    rook,
    knight,
    bishop,
    queen,
    king
};

std::map<PieceType, std::string> pieces{
    {none, "-"},
    {pawn, "pawn"},
    {rook, "rook"},
    {knight, "knight"},
    {bishop, "bishop"},
    {queen, "queen"},
    {king, "king"}};

class Piece
{
private:
    PieceType type_;
    Player player_;
    unsigned int fieldId_;

public:
    Piece(Player player, PieceType type, unsigned int fieldId)
    {
        player_ = player;
        type_ = type;
        fieldId_ = fieldId;
    }

    virtual void getAvailableFieldIds(
        MoveOptions *options,
        unsigned int from,
        std::array<Field, FIELD_COUNT> board,
        std::vector<Piece *> pieces) = 0;

    void move(unsigned int to)
    {
        setFieldId(to);
    }

    void take(unsigned int to)
    {
        std::cout << "Bam!" << std::endl;
    }

    std::string getName()
    {
        return pieces[type_];
    }

    Player getPlayer()
    {
        return player_;
    }

    unsigned int getFieldId()
    {
        return fieldId_;
    }

    void setFieldId(unsigned int fieldId)
    {
        fieldId_ = fieldId;
    }
};

Piece *findPieceByFieldId(std::vector<Piece *> v, unsigned int fieldId)
{
    auto result = std::find_if(v.begin(), v.end(), [fieldId](Piece *piece)
                               { return piece->getFieldId() == fieldId; }); // TODO: read into
    ptrdiff_t index = std::distance(v.begin(), result);
    if (result == v.end())
    {
        return 0;
    } // ??
    return v[index];
}

bool isPlayersPieceOnField(Player player, std::vector<Piece *> v, unsigned int fieldId)
{
    Piece *piece = findPieceByFieldId(v, fieldId);
    return piece->getPlayer() == player;
}

std::string getPlayerColor(Player player)
{
    return !player ? "(W.)" : "(B.)";
}