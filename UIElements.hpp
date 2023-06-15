#include "Field.hpp"
#include "Game.hpp"
#include "./utils/FieldUtils.hpp"
#include "./utils/PieceUtils.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>

struct UIElements
{
    // general
    std::string title;
    int width;
    int height;
    int fps;

    // board
    float squareSize;
    int coordSpace;
    int pieceSize;
    int coordSize;
    int pieceMargin;
    int coordMargin;

    // takes
    int takesTop;
    int takesHeight;
    int takesPieceSize;
    int takesNext;
    int pointsDifferenceSize;
    int pointsDifferenceTop;

    UIElements();

    sf::CircleShape getMoveDot(InitialConfig* config, Field *field, bool isTake, unsigned int squareSize);

    sf::RectangleShape getSquare(InitialConfig* config, Field *field);

    sf::RectangleShape getTakesFrame();

    void handleEvents(Game *game, sf::RenderWindow *window, sf::Event event);
};