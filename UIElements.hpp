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
    sf::Font font;

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

    sf::Text getPieceSymbol(Piece *piece, std::array<float, 2> pos, unsigned int size);

    void drawCoords(sf::RenderWindow* window, InitialConfig* config, std::vector<sf::RectangleShape>* squares, std::vector<Field *> fields);

    void drawPieces(sf::RenderWindow *window, InitialConfig* config, std::vector<Field *> board, std::vector<Piece *> pieces);

    sf::Text getCheckMarking(InitialConfig* config, Field *field);

    sf::RectangleShape getSquare(InitialConfig* config, Field *field);

    sf::RectangleShape getTakesFrame();

    void drawTakesFrame(sf::RenderWindow* window, std::vector<Piece *> takes);

    void drawTakesDetails(sf::RenderWindow* window, unsigned int whitePoints, unsigned int blackPoints);

    void drawCheckMark(sf::RenderWindow* window, InitialConfig* config, Field *kingField);

    void drawDots(sf::RenderWindow *window, InitialConfig* config, std::vector<unsigned int> fieldIds, std::vector<Field *> board, bool isTake = false);

    void handleEvents(Game *game, sf::RenderWindow *window, sf::Event event);
};