#include "UIElements.hpp"
#include "InitialConfig.hpp"
#include "MoveOptions.hpp"
#include "Piece.hpp"
#include "Move.hpp"

const std::string UIElements::title()
{
    return TITLE_;
}

const int UIElements::width()
{
    return WINDOW_WIDTH_;
}

const int UIElements::height()
{
    return WINDOW_HEIGHT_;
}

const int UIElements::fps()
{
    return FPS_;
}

const float UIElements::squareSize()
{
    return SQUARE_SIZE_;
}

const int UIElements::coordSpace()
{
    return COORD_SPACE_;
}

const int UIElements::pieceSize()
{
    return PIECE_SIZE_;
}

const int UIElements::coordSize()
{
    return COORD_SIZE_;
}

const int UIElements::pieceMargin()
{
    return PIECE_MARGIN_;
}

const int UIElements::coordMargin()
{
    return COORD_MARGIN_;
}

const int UIElements::takesTop()
{
    return TAKES_TOP_;
}

const int UIElements::takesHeight()
{
    return TAKES_HEIGHT_;
}

const int UIElements::takesPieceSize()
{
    return TAKES_PIECE_SIZE_;
}

const int UIElements::takesNext()
{
    return TAKES_NEXT_;
}

const int UIElements::pointsDifferenceSize()
{
    return POINTS_DIFFERENCE_SIZE_;
}

const int UIElements::pointsDifferenceTop()
{
    return (TAKES_TOP_ + 2 * TAKES_PIECE_SIZE_);
}

sf::CircleShape UIElements::getMoveDot(Field *field, bool isTake, unsigned int squareSize)
{
    InitialConfig config;

    unsigned int x = field->getX() - config.startLetter();
    unsigned int y = config.size() - field->getY() + 1;

    unsigned int posX = x * squareSize + (squareSize / 3);
    unsigned int posY = (y - 1) * squareSize + (squareSize / 3);

    sf::CircleShape circle;
    sf::Color moveBg(74, 161, 109);
    sf::Color takeBg(168, 88, 92);
    circle.setRadius(squareSize / 6);
    circle.setFillColor(isTake ? takeBg : moveBg);
    circle.setPosition(float(posX), float(posY));

    return circle;
}

sf::RectangleShape UIElements::getSquare(Field *field)
{
    InitialConfig config;

    unsigned int x = field->getX() - config.startLetter();
    unsigned int y = field->getY();

    sf::RectangleShape square;
    sf::Vector2f size(SQUARE_SIZE_, SQUARE_SIZE_);
    sf::Color dark(71, 71, 71);
    sf::Color light(171, 171, 171);
    sf::Vector2f position((x * SQUARE_SIZE_), (y - 1) * SQUARE_SIZE_);

    square.setSize(size);
    square.setFillColor(field->isBlack() ? dark : light);
    square.setPosition(position);

    return square;
}

sf::RectangleShape UIElements::getTakesFrame()
{
    sf::RectangleShape takesFrame;
    sf::Vector2f size(WINDOW_WIDTH_, TAKES_HEIGHT_);
    sf::Color bg(171, 171, 171);
    sf::Vector2f position(0, TAKES_TOP_);

    takesFrame.setSize(size);
    takesFrame.setFillColor(bg);
    takesFrame.setPosition(position);

    return takesFrame;
}

void UIElements::handleEvents(Game *game, sf::RenderWindow *window, sf::Event event)
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
        if (mouseY > SQUARE_SIZE_ * config.size())
            break;

        int clickX = mouseX / SQUARE_SIZE_ + config.startLetter();
        int clickY = config.size() - (mouseY / SQUARE_SIZE_) + config.startNumber();

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
            else
            {
                game->setSelectedPiece(nullptr);

                game->clearOptions();
            }

            bool isPlayerPiece = PieceUtils::isPlayerPiece(p, player);
            if (!isPlayerPiece)
                break;

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

                options = nullptr;
                move = nullptr;

                delete options;
                delete move;
            }
            else
            {
                break;
            }
        }
        break;
    }
}
