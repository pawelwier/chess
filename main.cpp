#include "Game.hpp"
#include "./utils/Utils.hpp"
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
    UIElements ui;
    auto [
        title,
        width,
        height,
        fps,
        squareSize,
        coordSpace,
        pieceSize,
        coordSize,
        pieceMargin,
        coordMargin,
        takesTop,
        takesHeight,
        takesPieceSize,
        takesNext,
        pointsDifferenceSize,
        pointsDifferenceTop
    ] = ui;

    sf::RenderWindow window(sf::VideoMode(width, height), title);

    std::vector<sf::RectangleShape> squares;

    InitialConfig *config = new InitialConfig();

    Game *game = new Game(config);

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

            sf::Text pieceSymbol(icon, font, takesPieceSize);
            float takeX = float(player ? indexBlack : indexWhite);
            float takeY = float(player ? takesTop : takesTop + takesPieceSize);
            pieceSymbol.setPosition(takeX, takeY);
            player ? indexBlack += takesNext : indexWhite += takesNext;

            window.draw(pieceSymbol);
        }

        for (Field *field : fields)
        {
            squares.push_back(ui.getSquare(config, field));

            unsigned int x = field->getX() - config->startLetter;
            unsigned int y = config->size - field->getY() + 1;

            char letter = Utils::getChar(field->getX());
            sf::Text coordX(letter, font, coordSize);
            sf::Text coordY(std::to_string(field->getY()), font, coordSize);

            coordX.setPosition(float(x * squareSize + coordMargin), float((y - 1) * squareSize + coordSpace));
            coordY.setPosition(float(x * squareSize + coordMargin), float((y - 1) * squareSize + coordMargin));

            if (field->getY() == config->startNumber)
                window.draw(coordX);
            if (field->getX() == config->startLetter)
                window.draw(coordY);
        }

        for (Piece *piece : game->getPieces())
        {

            Field *field = FieldUtils::findFieldByFieldId(game->getBoard(), piece->getFieldId());
            const wchar_t icon = piece->getIcon();
            sf::Text pieceSymbol(icon, font, pieceSize);

            unsigned int x = field->getX() - config->startLetter;
            unsigned int y = config->size - field->getY() + 1;

            unsigned int posX = x * squareSize + pieceMargin;
            signed int posY = (y - 1) * squareSize - pieceMargin;

            pieceSymbol.setPosition(float(posX), float(posY));


            window.draw(pieceSymbol);
        }

        for (unsigned int fieldId : game->getMoveOptions())
        {
            Field *field = FieldUtils::findFieldByFieldId(game->getBoard(), fieldId);
            sf::CircleShape c = ui.getMoveDot(config, field, false, squareSize);

            window.draw(c);
        }

        for (unsigned int fieldId : game->getTakeOptions())
        {
            Field *field = FieldUtils::findFieldByFieldId(game->getBoard(), fieldId);
            sf::CircleShape c = ui.getMoveDot(config, field, true, squareSize);

            window.draw(c);
        }

        unsigned int whitePoints = game->getPlayerPoints(Player::white);
        unsigned int blackPoints = game->getPlayerPoints(Player::black);

        int difference = whitePoints - blackPoints;

        sf::Color color = difference > 0 ? sf::Color::White : sf::Color::Black;

        std::string differenceText = difference ? "+" + std::to_string(abs(difference)) : "";

        sf::Text text(differenceText, font, pointsDifferenceSize);
        text.setFillColor(color);
        text.setPosition(float(pieceMargin), float(pointsDifferenceTop));

        window.draw(text);

        window.display();
    }

    return 0;
}