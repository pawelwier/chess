#include "Field.hpp"
#include "Game.hpp"
#include "FieldUtils.hpp"
#include "PieceUtils.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>

class UIElements
{
private:
    // general
    const std::string TITLE_ = "Chess game";
    const int WINDOW_WIDTH_ = 800;
    const int WINDOW_HEIGHT_ = 1200;
    const int FPS_ = 20;

    // board
    const float SQUARE_SIZE_ = 100.f;
    const int COORD_SPACE_ = 65;
    const int PIECE_SIZE_ = 90;
    const int COORD_SIZE_ = 25;
    const int PIECE_MARGIN_ = 15;
    const int COORD_MARGIN_ = 10;

    // takes
    const int TAKES_TOP_ = 900;
    const int TAKES_HEIGHT_ = 200;
    const int TAKES_PIECE_SIZE_ = 70;
    const int TAKES_NEXT_ = 40;
    const int POINTS_DIFFERENCE_SIZE_ = 40;
    const int POINTS_DIFFERENCE_TOP_ = (TAKES_TOP_ + 2 * TAKES_PIECE_SIZE_);

public:
    const std::string title();
    const int width();
    const int height();
    const int fps();

    const float squareSize();
    const int coordSpace();
    const int pieceSize();
    const int coordSize();
    const int pieceMargin();
    const int coordMargin();

    const int takesTop();
    const int takesHeight();
    const int takesPieceSize();
    const int takesNext();
    const int pointsDifferenceSize();
    const int pointsDifferenceTop();

    sf::CircleShape getMoveDot(Field *field, bool isTake, unsigned int squareSize);

    sf::RectangleShape getSquare(Field *field);

    sf::RectangleShape getTakesFrame();

    void handleEvents(Game *game, sf::RenderWindow *window, sf::Event event);
};