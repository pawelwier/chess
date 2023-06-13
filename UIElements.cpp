#include "UIElements.hpp"
#include "InitialConfig.hpp"
#include "MoveOptions.hpp"
#include "Piece.hpp"
#include "Move.hpp"

UIElements::UIElements()
{
    title = "Chess game";
    width = 800;
    height = 1200;
    fps = 20;
    squareSize = 100.f;
    coordSpace = 65;
    pieceSize = 90;
    coordSize = 25;
    pieceMargin = 15;
    coordMargin = 10;
    takesTop = 900;
    takesHeight = 200;
    takesPieceSize = 70;
    takesNext = 40;
    pointsDifferenceSize = 40;
    pointsDifferenceTop = this->takesTop + 2 * this->takesPieceSize;
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
    sf::Vector2f size(squareSize, squareSize);
    sf::Color dark(71, 71, 71);
    sf::Color light(171, 171, 171);
    sf::Vector2f position((x * squareSize), (y - 1) * squareSize);

    square.setSize(size);
    square.setFillColor(field->isBlack() ? dark : light);
    square.setPosition(position);

    return square;
}

sf::RectangleShape UIElements::getTakesFrame()
{
    sf::RectangleShape takesFrame;
    sf::Vector2f size(width, takesHeight);
    sf::Color bg(171, 171, 171);
    sf::Vector2f position(0, takesTop);

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
    unsigned short int size = config.size();

    switch (event.type)
    {
    case sf::Event::Closed:
        window->close();
        break;

    case sf::Event::MouseButtonPressed:
        unsigned int mouseX = event.mouseButton.x;
        unsigned int mouseY = event.mouseButton.y;
        if (mouseY > squareSize * size)
            break;

        int clickX = mouseX / squareSize + config.startLetter();
        int clickY = config.size() - (mouseY / squareSize) + config.startNumber();

        std::vector<Field *> fields = game->getBoard();

        MoveOptions *options = new MoveOptions;

        std::vector<unsigned int> moves;
        std::vector<unsigned int> takes;

        unsigned int clickIndex = FieldUtils::getFieldIndexByPosition(fields, Utils::getFieldCoordinates(clickX, clickY));

        Piece *p = PieceUtils::findPieceByFieldId(game->getPieces(), clickIndex);

        if (!p && !game->getSelectedPiece())
            break;

        bool isPlayerPiece = p && (p->getPlayer() == game->getCurrentPlayer());

        if (game->getSelectedPiece() && (!p || !isPlayerPiece))
        {
            bool takeOk = Utils::includes(game->getTakeOptions(), clickIndex);
            bool moveOk = Utils::includes(game->getMoveOptions(), clickIndex);

            Piece *piece = game->getSelectedPiece();

            if (takeOk || moveOk)
            {
                if (takeOk)
                {
                    Piece *piece = PieceUtils::findPieceByFieldId(game->getPieces(), clickIndex);

                    // en passant (some better way?)
                    if (!piece)
                    {
                        int indexPassed = player ? clickIndex + size : clickIndex - size;
                        Piece *piecePassed = PieceUtils::findPieceByFieldId(game->getPieces(), indexPassed);

                        game->takePiece(piecePassed);
                        piecePassed->setTaken(true);
                    }
                    else
                    {
                        game->takePiece(piece);
                        piece->setTaken(true);
                    }

                    // delete piece; // ?? gets moved to takes frame
                }

                int from = piece->getFieldId();
                int indexDiff = from - clickIndex;

                // castle king/queen side
                if (piece->getType() == PieceType::king && std::abs(indexDiff) == 2)
                {
                    int rookIndex, rookDestination;
                    if (from < clickIndex)
                    {
                        rookIndex = 3;
                        rookDestination = 1;
                    }
                    else
                    {
                        rookIndex = -4;
                        rookDestination = -1;
                    }
                    Piece *rook = PieceUtils::findPieceByFieldId(game->getPieces(), from + rookIndex);
                    rook->move(from + rookDestination);
                }

                Move *move = new Move(moveNum, piece->getId(), from, clickIndex, takeOk);
                game->addMove(move);

                game->printMove(game->getMoves().size());

                piece->move(clickIndex);

                game->setSelectedPiece(nullptr);

                game->clearOptions();

                game->nextPlayer();

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
        else if (isPlayerPiece)
        {
            game->clearOptions();

            p->getAvailableMoves(options, clickIndex, fields, game->getPieces(), game->getMoves());

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
            break;
        }
    }
}
