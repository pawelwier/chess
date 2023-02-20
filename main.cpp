#include "Game.hpp"
#include "Utils.hpp"
#include "InitialConfig.hpp"
#include "Player.hpp"
#include "Move.hpp"
#include "UIElements.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <iostream>

// TODO: refactor main
int main()
{
    InitialConfig config;
    UIElements ui;

    std::string uiTitle = ui.title();
    unsigned int uiWidth = ui.width();
    unsigned int uiHeight = ui.height();
    unsigned int uiTakesPieceSize = ui.takesPieceSize();
    unsigned int uiTakesTop = ui.takesTop();
    unsigned int uiTakesNext = ui.takesNext();
    unsigned int uiCoordMargin = ui.coordMargin();
    unsigned int uiCoordSize = ui.coordSize();
    unsigned int uiCoordSpace = ui.coordSpace();
    unsigned int uiPieceSize = ui.pieceSize();
    unsigned int uiPieceMargin = ui.pieceMargin();
    unsigned int uiSquareSize = ui.squareSize();
    unsigned int uiPointsDifferenceSize = ui.pointsDifferenceSize();
    unsigned int uiPointsDifferenceTop = ui.pointsDifferenceTop();

    sf::RenderWindow window(sf::VideoMode(uiWidth, uiHeight), uiTitle);

    std::vector<Piece *> pieces;
    std::vector<sf::RectangleShape> squares;

    Game *game = new Game(pieces);

    std::vector<Field *> fields = game->getBoard();

    sf::Font font;
    font.loadFromFile("FreeSerif.ttf");

    game->assignInitialPieces(fields);

    while (window.isOpen())
    {
        sf::Event event;

        window.clear();

        while (window.pollEvent(event))
        {
            ui.handleEvents(game, &window, event);
        }

        for (sf::RectangleShape square : squares)
        {
            window.draw(square);
        }

        sf::RectangleShape takesFrame = ui.getTakesFrame();

        window.draw(takesFrame);

        std::vector<Piece *> takes = game->getTakes();
        unsigned int indexWhite{};
        unsigned int indexBlack{};

        for (Piece *piece : takes)
        {
            wchar_t icon = piece->getIcon();
            Player player = piece->getPlayer();

            sf::Text pieceSymbol(icon, font, uiTakesPieceSize);
            float takeX = float(player ? indexBlack : indexWhite);
            float takeY = float(player ? uiTakesTop : uiTakesTop + uiTakesPieceSize);
            pieceSymbol.setPosition(takeX, takeY);
            player ? indexBlack += uiTakesNext : indexWhite += uiTakesNext;

            window.draw(pieceSymbol);
        }

        for (Field *field : fields)
        {
            squares.push_back(ui.getSquare(field));

            unsigned int x = field->getX() - config.startLetter();
            unsigned int y = config.size() - field->getY() + 1;

            char letter = Utils::getChar(field->getX());
            sf::Text coordX(letter, font, uiCoordSize);
            sf::Text coordY(std::to_string(field->getY()), font, uiCoordSize);

            coordX.setPosition(float(x * uiSquareSize + uiCoordMargin), float((y - 1) * uiSquareSize + uiCoordSpace));
            coordY.setPosition(float(x * uiSquareSize + uiCoordMargin), float((y - 1) * uiSquareSize + uiCoordMargin));

            if (field->getY() == config.startNumber())
                window.draw(coordX);
            if (field->getX() == config.startLetter())
                window.draw(coordY);
        }

        for (Piece *piece : game->getPieces())
        {
            Field *field = FieldUtils::findFieldByFieldId(game->getBoard(), piece->getFieldId());
            const wchar_t icon = piece->getIcon();
            sf::Text pieceSymbol(icon, font, uiPieceSize);

            unsigned int x = field->getX() - config.startLetter();
            unsigned int y = config.size() - field->getY() + 1;

            unsigned int posX = x * uiSquareSize + uiPieceMargin;
            signed int posY = (y - 1) * uiSquareSize - uiPieceMargin;

            pieceSymbol.setPosition(float(posX), float(posY));

            window.draw(pieceSymbol);
        }

        for (unsigned int fieldId : game->getMoveOptions())
        {
            Field *field = FieldUtils::findFieldByFieldId(game->getBoard(), fieldId);
            sf::CircleShape c = ui.getMoveDot(field, false, uiSquareSize);

            window.draw(c);
        }

        for (unsigned int fieldId : game->getTakeOptions())
        {
            Field *field = FieldUtils::findFieldByFieldId(game->getBoard(), fieldId);
            sf::CircleShape c = ui.getMoveDot(field, true, uiSquareSize);

            window.draw(c);
        }

        unsigned int whitePoints = game->getPlayerPoints(Player::white);
        unsigned int blackPoints = game->getPlayerPoints(Player::black);

        int difference = whitePoints - blackPoints;

        sf::Color color = difference > 0 ? sf::Color::White : sf::Color::Black;

        std::string differenceText = difference ? "+" + std::to_string(abs(difference)) : "";

        sf::Text text(differenceText, font, uiPointsDifferenceSize);
        text.setFillColor(color);
        text.setPosition(float(uiPieceMargin), float(uiPointsDifferenceTop));

        window.draw(text);

        window.display();
    }

    return 0;
}