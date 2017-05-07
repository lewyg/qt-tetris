#include "gameboard.h"


PieceShape GameBoard::getRandomShape()
{
    int rand = qrand() % 100;
    int sum = 0;
    for (int i = 0; i < 7; ++i)
    {
        sum += shapeProbabilities[i];
        if (rand < sum)
            return PieceShape(i);
    }

    return PieceShape::ZShape;
}

GameBoard::GameBoard(QObject * parent) : QGraphicsScene(parent)
{
    removedLines = 0;
    level = 1;

    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            boardCells[i][j].setPosition(i, j);
            boardCells[i][j].setVisible(false);
            this->addItem(&boardCells[i][j]);
        }
    }
    currentPiece = nullptr;
    timeLine = nullptr;
    gameOver = true;
    paused = false;

    shapeProbabilities = new int[7]{
        14, 14, 14, 14, 14, 15, 15
    };
}

void GameBoard::clearBoard()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_HEIGHT; j++)
            boardCells[i][j].setVisible(false);

    if (currentPiece)
    {
        for (int i = 0; i < 4; ++i)
                this->removeItem(&(currentPiece->cells[i]));

        delete(currentPiece);
    }
}

void GameBoard::restartGame()
{
    removedLines = 0;
    level = 1;

    clearBoard();

    startNextPiece();

    emit updateLines(removedLines);
    emit updateLevel(level);

    if(timeLine)
        stopAnimation();

    gameOver = false;
    runAnimation();
}

void GameBoard::startGame()
{
    nextShape = getRandomShape();

    restartGame();
}

void GameBoard::startNextPiece()
{
    currentPiece = new Piece(nextShape);

    for (int i = 0; i < 4; i++)
    {
        this->addItem(&(currentPiece->cells[i]));
    }

    nextShape = getRandomShape();
    emit updateNextPiece(nextShape);
}

void GameBoard::setShapeProbabilities(int *probabilities)
{
    delete(shapeProbabilities);

    shapeProbabilities = probabilities;
}

void GameBoard::keyPressed(int key) {
    switch (key) {
        case Qt::Key_Up:
            rotateLeft();
            break;
        case Qt::Key_Down:
            rotateRight();
            break;
        case Qt::Key_Left:
            moveLeft();
            break;
        case Qt::Key_Right:
            moveRight();
            break;
        case Qt::Key_Space:
            fallDown();
            break;
    }
}

void GameBoard::pauseGame()
{
    if (!timeLine || gameOver)
        return;

    paused = !paused;
    timeLine->setPaused(paused);


    emit updatePauseLabel();
}

void GameBoard::stopAnimation() {
    timeLine->stop();
}

void GameBoard::runAnimation() {
    timeLine = new QTimeLine(20 / level);
    connect(timeLine, SIGNAL(finished()), this, SLOT(updateAnimation()));

    timeLine->start();
}

void GameBoard::updateAnimation() {
    moveDown();

    if (!gameOver)
        runAnimation();
}

bool GameBoard::canMoveCell(int x, int y)
{
    if (x < 0 || x > (BOARD_WIDTH - 1) * BLOCK_SIZE)
        return false;

    if (y > (BOARD_HEIGHT - 1) * BLOCK_SIZE)
        return false;

    int lx = x / BLOCK_SIZE;
    int ly = y / BLOCK_SIZE;

    if (boardCells[lx][ly].isVisible())
        return false;

    if (y % BLOCK_SIZE > 0 && boardCells[lx][ly + 1].isVisible())
        return false;

    return true;
}

void GameBoard::moveLeft() {
    for (int i = 0; i < 4; ++i)
    {
        int xx = currentPiece->cells[i].x();
        int yy = currentPiece->cells[i].y();

        if (!canMoveCell(xx - BLOCK_SIZE, yy))
            return;
    }

    currentPiece->addX(-BLOCK_SIZE);
}

void GameBoard::fallDown()
{
    if(!gameOver)
        while (moveDown()) {}
}

bool GameBoard::moveDown()
{
    bool canMove = true;

    for (int i = 0; i < 4; ++i)
    {
        int xx = currentPiece->cells[i].x();
        int yy = currentPiece->cells[i].y();

        if (!canMoveCell(xx, yy + MOVE_DOWN_STEP))
        {
            canMove = false;
            break;
        }
    }

    if (!canMove)
    {
        for (int i = 0; i < 4; i++)
        {
            int lx = currentPiece->cells[i].x() / BLOCK_SIZE;
            int ly = currentPiece->cells[i].y() / BLOCK_SIZE;
            boardCells[lx][ly].setColor(currentPiece->cells[i].getColor());
            boardCells[lx][ly].setVisible(true);
            this->removeItem(&(currentPiece->cells[i]));
        }

        delete(currentPiece);

        checkLines();

        startNextPiece();

        checkGameOver();
    }

    currentPiece->addY(MOVE_DOWN_STEP);

    return canMove;
}

void GameBoard::checkGameOver()
{
    for (int i = 0; i < BOARD_WIDTH; ++i)
        if (boardCells[i][0].isVisible())
            gameOver = true;
}

void GameBoard::checkLevel()
{
    if (removedLines % LEVEL_LINES == 0)
    {
        level++;
        emit updateLevel(level);
    }
}

void GameBoard::checkLines()
{
    bool filledLine;
    for (int i = BOARD_HEIGHT - 1; i > 0; --i)
    {
        filledLine = true;
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            if (!boardCells[j][i].isVisible())
                filledLine = false;
        }
        if (filledLine)
        {
            removeLine(i++);
            checkLevel();
            removedLines++;
            emit updateLines(removedLines);
        }
    }
}

void GameBoard::removeLine(int line)
{
    for (int i = 0; i < BOARD_WIDTH; ++i)
        boardCells[i][line].setVisible(false);

    for (int i = line; i > 0; --i)
    {
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            boardCells[j][i].setVisible(boardCells[j][i - 1].isVisible());
        }
    }
}

void GameBoard::moveRight() {
    for (int i = 0; i < 4; ++i)
    {
        int xx = currentPiece->cells[i].x();
        int yy = currentPiece->cells[i].y();

        if (!canMoveCell(xx + BLOCK_SIZE, yy))
            return;
    }
    currentPiece->addX(BLOCK_SIZE);
}

void GameBoard::rotateLeft() {
    for (int i = 0; i < 4; ++i)
    {
        int xx = currentPiece->cells[i].x() - currentPiece->getX();
        int yy = currentPiece->cells[i].y() - currentPiece->getY();

        if (!canMoveCell(currentPiece->getX() - yy,currentPiece->getY() + xx))
            return;
    }

    currentPiece->rotateLeft();
}

void GameBoard::rotateRight() {
    for (int i = 0; i < 4; ++i)
    {
        int xx = currentPiece->cells[i].x() - currentPiece->getX();
        int yy = currentPiece->cells[i].y() - currentPiece->getY();

        if (!canMoveCell(currentPiece->getX() + yy,currentPiece->getY() - xx))
            return;
    }

    currentPiece->rotateRight();
}
