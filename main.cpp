#include "Game.hpp"
#include "Utils.hpp"
#include "FieldUtils.hpp"
#include "PieceUtils.hpp"
#include "InitialConfig.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include "Player.hpp"
#include "Move.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <iostream>

#define LOG(x) std::cout << x

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 1200;
const int FPS = 20;
const float SQUARE_SIZE = 100.f;
const int COORD_SPACE = 65;
const int PIECE_SIZE = 90;
const int COORD_SIZE = 25;
const int PIECE_MARGIN = 15;
const int COORD_MARGIN = 10;

// TODO: move out of main, refactor main
sf::RectangleShape getSquare(Field *field)
{
    sf::RectangleShape square;
    InitialConfig config;

    sf::Vector2f size(SQUARE_SIZE, SQUARE_SIZE);
    square.setSize(size);
    sf::Color dark(71, 71, 71);
    sf::Color light(171, 171, 171);
    square.setFillColor(field->isBlack() ? dark : light);

    unsigned int x = field->getX() - config.startLetter();
    unsigned int y = field->getY();

    sf::Vector2f position((x * SQUARE_SIZE), (y - 1) * SQUARE_SIZE);
    square.setPosition(position);

    return square;
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

        std::cout << Utils::getFieldCoordinates(clickX, clickY) << std::endl;

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
            p->getAvailableFieldIds(options, fromIndex, fields, game->getPieces());

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

            std::cout << std::to_string(toIndex) << std::endl;

            bool takeOk = Utils::includes(game->getTakeOptions(), toIndex);
            bool moveOk = Utils::includes(game->getMoveOptions(), toIndex);

            Piece *piece = game->getSelectedPiece();

            if (takeOk || moveOk)
            {
                if (takeOk)
                {
                    game->takePiece(toIndex);
                }

                piece->move(toIndex);

                game->setSelectedPiece(nullptr);

                game->nextPlayer();

                Move *move = new Move(moveNum, piece->getId(), fromIndex, toIndex);
                game->addMove(move);

                delete options;
            }
            else
            {
                break;
            }
        }
        break;
        // case sf::Event::MouseButtonPressed:

        //     break;
        // case sf::Event::MouseButtonPressed:

        //     break;
        // case sf::Event::MouseButtonPressed:

        //     break;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chess game");

    window.setFramerateLimit(FPS);

    std::vector<Piece *> pieces;
    std::vector<sf::RectangleShape> squares;
    InitialConfig config;

    Game game = Game(pieces);

    std::vector<Field *> fields = game.getBoard();

    sf::Font font;
    font.loadFromFile("FreeSerif.ttf");

    unsigned int id{0};
    for (Field *field : fields)
    {
        unsigned int fieldId = field->getId();
        if (!game.fieldHasPiece(fieldId))
            continue;

        Player player = FieldUtils::initPiecePlayer(fieldId);

        // TODO: refactor
        if (Utils::includes(config.pawnIds(), fieldId))
        {
            game.addPiece(new Pawn(id, player, fieldId));
            id++;
        }

        if (Utils::includes(config.rookIds(), fieldId))
        {
            game.addPiece(new Rook(id, player, fieldId));
            id++;
        }

        if (Utils::includes(config.knightIds(), fieldId))
        {
            game.addPiece(new Knight(id, player, fieldId));
            id++;
        }

        if (Utils::includes(config.bishopIds(), fieldId))
        {
            game.addPiece(new Bishop(id, player, fieldId));
            id++;
        }

        if (Utils::includes(config.queenIds(), fieldId))
        {
            game.addPiece(new Queen(id, player, fieldId));
            id++;
        }

        if (Utils::includes(config.kingIds(), fieldId))
        {
            game.addPiece(new King(id, player, fieldId));
            id++;
        }
    }

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

        window.display();
    }

    return 0;
}