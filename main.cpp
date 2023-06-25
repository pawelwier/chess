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
        font,
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
        pointsDifferenceTop,
        checkMarkingSize
    ] = ui;

    sf::RenderWindow window(sf::VideoMode(width, height), title);

    std::vector<sf::RectangleShape> squares;

    InitialConfig *config = new InitialConfig();

    Game *game = new Game(config);

    std::vector<Field *> fields = game->getBoard();

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

        ui.drawTakesFrame(&window, game->getTakes());

        ui.drawCoords(&window, config, &squares, fields);

        ui.drawPieces(&window, config, game->getBoard(), game->getPieces());

        if (game->isCheck())
        {
            unsigned int kingFieldId = game->getKingFieldId(game->getCurrentPlayer());
            Field *kingField = FieldUtils::findFieldByFieldId(game->getBoard(), kingFieldId);

            ui.drawCheckMark();
        }

        for (unsigned int fieldId : game->getMoveOptions())
        {
            Field *field = FieldUtils::findFieldByFieldId(game->getBoard(), fieldId);
            sf::CircleShape c = ui.getMoveDot(config, field, false);

            window.draw(c);
        }

        for (unsigned int fieldId : game->getTakeOptions())
        {
            Field *field = FieldUtils::findFieldByFieldId(game->getBoard(), fieldId);
            sf::CircleShape c = ui.getMoveDot(config, field, true);

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