#include "Game.hpp"
#include "Utils.hpp"
#include "FieldUtils.hpp"
#include "PieceUtils.hpp"
#include "InitialConfig.hpp"
#include "Player.hpp"
#include "Move.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <iostream>

// general
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 1200;
const int FPS = 20;

// board
const float SQUARE_SIZE = 100.f;
const int COORD_SPACE = 65;
const int PIECE_SIZE = 90;
const int COORD_SIZE = 25;
const int PIECE_MARGIN = 15;
const int COORD_MARGIN = 10;

// takes
const int TAKES_TOP = 900;
const int TAKES_HEIGHT = 200;
const int TAKES_PIECE_SIZE = 70;
const int TAKES_NEXT = 40;
const int POINTS_DIFFERENCE_SIZE = 40;
const int POINTS_DIFFERENCE_TOP = (TAKES_TOP + 2 * TAKES_PIECE_SIZE);

// TODO: move out of main, refactor main
sf::RectangleShape getSquare(Field *field)
{
    InitialConfig config;

    unsigned int x = field->getX() - config.startLetter();
    unsigned int y = field->getY();

    sf::RectangleShape square;
    sf::Vector2f size(SQUARE_SIZE, SQUARE_SIZE);
    sf::Color dark(71, 71, 71);
    sf::Color light(171, 171, 171);
    sf::Vector2f position((x * SQUARE_SIZE), (y - 1) * SQUARE_SIZE);

    square.setSize(size);
    square.setFillColor(field->isBlack() ? dark : light);
    square.setPosition(position);

    return square;
}

sf::RectangleShape getTakesFrame()
{
    sf::RectangleShape takesFrame;
    sf::Vector2f size(WINDOW_WIDTH, TAKES_HEIGHT);
    sf::Color bg(171, 171, 171);
    sf::Vector2f position(0, TAKES_TOP);

    takesFrame.setSize(size);
    takesFrame.setFillColor(bg);
    takesFrame.setPosition(position);

    return takesFrame;
}

void handleEvents(Game *game, sf::RenderWindow *window, sf::Event event)
{
    InitialConfig config;
    Player player = game->getCurrentPlayer();

    unsigned int moveNum = game->getMoveCount() + 1;

    switch (event.type)
    {
    case sf::Event::Closed:
        window->close();

        break;
    case sf::Event::MouseButtonPressed:
        unsigned int mouseX = event.mouseButton.x;
        unsigned int mouseY = event.mouseButton.y;
        if (mouseY > SQUARE_SIZE * config.size())
            break;

        int clickX = mouseX / SQUARE_SIZE + config.startLetter();
        int clickY = config.size() - (mouseY / SQUARE_SIZE) + config.startNumber();

        std::vector<Field *> fields = game->getBoard();

        unsigned int fromIndex;
        unsigned int toIndex;

        MoveOptions *options = new MoveOptions;

        std::vector<unsigned int> moves;
        std::vector<unsigned int> takes;

        if (!game->getSelectedPiece())
        {
            fromIndex = FieldUtils::getFieldIndexByPosition(fields, Utils::getFieldCoordinates(clickX, clickY));

            Piece *p = PieceUtils::findPieceByFieldId(game->getPieces(), fromIndex);
            if (!p)
                break;

            bool isPlayerPiece = PieceUtils::isPlayerPiece(p, player);
            if (!isPlayerPiece)
                break;

            MoveOptions *options = new MoveOptions;
            p->getAvailableMoves(options, fromIndex, fields, game->getPieces());

            moves = options->getMoves();
            takes = options->getTakes();

            if (moves.size())
            {
                for (unsigned int move : moves)
                {
                    game->addMoveOption(move);
                }
            }

            if (takes.size())
            {
                for (unsigned int take : takes)
                {
                    game->addTakeOption(take);
                }
            }
            game->setSelectedPiece(p);
        }
        else
        {
            toIndex = FieldUtils::getFieldIndexByPosition(fields, Utils::getFieldCoordinates(clickX, clickY));

            bool takeOk = Utils::includes(game->getTakeOptions(), toIndex);
            bool moveOk = Utils::includes(game->getMoveOptions(), toIndex);

            Piece *piece = game->getSelectedPiece();

            if (takeOk || moveOk)
            {
                if (takeOk)
                {
                    Piece *piece = PieceUtils::findPieceByFieldId(game->getPieces(), toIndex);

                    game->takePiece(piece);

                    piece->setTaken(true);

                    // delete piece; // ?? gets moved to takes frame
                }

                piece->move(toIndex);

                game->setSelectedPiece(nullptr);

                game->clearOptions();

                game->nextPlayer();

                Move *move = new Move(moveNum, piece->getId(), fromIndex, toIndex, takeOk);
                game->addMove(move);

                delete options;
            }
            else
            {
                break;
            }
        }
        break;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chess game");

    std::vector<Piece *> pieces;
    std::vector<sf::RectangleShape> squares;
    InitialConfig config;

    Game game = Game(pieces);

    std::vector<Field *> fields = game.getBoard();

    sf::Font font;
    font.loadFromFile("FreeSerif.ttf");

    game.assignInitialPieces(fields);

    while (window.isOpen())
    {
        sf::Event event;

        window.clear();

        while (window.pollEvent(event))
        {
            handleEvents(&game, &window, event);
        }

        for (sf::RectangleShape square : squares)
        {
            window.draw(square);
        }

        sf::RectangleShape takesFrame = getTakesFrame();

        window.draw(takesFrame);

        std::vector<Piece *> takes = game.getTakes();
        unsigned int indexWhite{0};
        unsigned int indexBlack{0};
        for (Piece *piece : takes)
        {
            wchar_t icon = piece->getIcon();
            Player player = piece->getPlayer();

            sf::Text pieceSymbol(icon, font, TAKES_PIECE_SIZE);
            float takeX = float(player ? indexBlack : indexWhite);
            float takeY = float(player ? TAKES_TOP : TAKES_TOP + TAKES_PIECE_SIZE);
            pieceSymbol.setPosition(takeX, takeY);
            player ? indexBlack += TAKES_NEXT : indexWhite += TAKES_NEXT;

            window.draw(pieceSymbol);
        }

        for (Field *field : fields)
        {
            squares.push_back(getSquare(field));

            unsigned int fieldId = field->getId();

            unsigned int x = field->getX() - config.startLetter();
            unsigned int y = config.size() - field->getY() + 1;

            char letter = Utils::getChar(field->getX());
            sf::Text coordX(letter, font, COORD_SIZE);
            sf::Text coordY(std::to_string(field->getY()), font, COORD_SIZE);

            coordX.setPosition(float(x * SQUARE_SIZE + COORD_MARGIN), float((y - 1) * SQUARE_SIZE + COORD_SPACE));
            coordY.setPosition(float(x * SQUARE_SIZE + COORD_MARGIN), float((y - 1) * SQUARE_SIZE + COORD_MARGIN));

            if (field->getY() == config.startNumber())
                window.draw(coordX);
            if (field->getX() == config.startLetter())
                window.draw(coordY);
        }
        for (Piece *piece : game.getPieces())
        {
            Field *field = FieldUtils::findFieldByFieldId(game.getBoard(), piece->getFieldId());
            const wchar_t icon = piece->getIcon();
            sf::Text pieceSymbol(icon, font, PIECE_SIZE);

            unsigned int x = field->getX() - config.startLetter();
            unsigned int y = config.size() - field->getY() + 1;

            pieceSymbol.setPosition(float(x * SQUARE_SIZE + PIECE_MARGIN), float((y - 1) * SQUARE_SIZE - PIECE_MARGIN));
            window.draw(pieceSymbol);
        }

        // move to function
        unsigned int whitePoints = game.getPlayerPoints(Player::white);
        unsigned int blackPoints = game.getPlayerPoints(Player::black);

        int difference = whitePoints - blackPoints;

        sf::Color color = difference > 0 ? sf::Color::White : sf::Color::Black;

        if (difference)
        {
            std::string differenceText = "+" + std::to_string(abs(difference));
            sf::Text text(differenceText, font, POINTS_DIFFERENCE_SIZE);

            text.setFillColor(color);
            text.setPosition(float(10), float(POINTS_DIFFERENCE_TOP));

            window.draw(text);
        }

        window.display();
    }

    return 0;
}