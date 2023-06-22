#include "Field.hpp"
#include "Game.hpp"
#include "InitialConfig.hpp"
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
    float pieceMargin;
    float coordMargin;

    // takes
    int takesTop;
    int takesHeight;
    int takesPieceSize;
    int takesNext;
    int pointsDifferenceSize;
    int pointsDifferenceTop;
    int checkMarkingSize;

    UIElements();

    std::array<float, 2> getSymbolPos(Field *field, InitialConfig *config, unsigned int size, std::array<float, 2> shift);

    sf::CircleShape getMoveDot(InitialConfig* config, Field *field, bool isTake);

    sf::Text getCheckMarking(InitialConfig* config, Field *field, sf::Font font);

    sf::RectangleShape getSquare(InitialConfig* config, Field *field);

    sf::RectangleShape getTakesFrame();

    void handleEvents(Game *game, sf::RenderWindow *window, sf::Event event);
};