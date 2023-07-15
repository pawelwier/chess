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

        ui.drawCoords(&window, config, &squares, fields);

        ui.drawPieces(&window, config, game->getBoard(), game->getPieces());

        ui.drawDots(&window, config, game->getMoveOptions(), game->getBoard());
        ui.drawDots(&window, config, game->getTakeOptions(), game->getBoard(), true);

        if (game->isCheck())
        {
            unsigned int kingFieldId = game->getKingFieldId(game->getCurrentPlayer());
            Field *kingField = FieldUtils::findFieldByFieldId(game->getBoard(), kingFieldId);

            ui.drawCheckMark(&window, config, kingField);
        }

        ui.drawTakesFrame(&window, game->getTakes());
        ui.drawTakesDetails(&window, game->getPlayerPoints(Player::white), game->getPlayerPoints(Player::black));

        window.display();
    }

    return 0;
}