#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"

#include <QGraphicsTextItem>

#include <QApplication>

// constructor
Game::Game(QWidget *parent): QGraphicsView(parent)
{
    // initialization of the scene
    scene = new QGraphicsScene(0, 0, widthScene, heightScene);
    scene->setBackgroundBrush(Qt::white);
    setScene(scene);

    // setting the mouse tracking
    setMouseTracking(true);
}

// setup the game
void Game::start()
{
//    score = 0;

    // creating a ball
    Ball* ball = new Ball();
    ball->setPos(widthScene / 2, heightScene - spaceBetweenBallAndScene);
    scene->addItem(ball);

    // creating a paddle
    Paddle* paddle = new Paddle();
    paddle->setPos(widthScene / 2, heightScene - spaceBetweenPaddleAndScene);
    scene->addItem(paddle);
    // grabMouse() for capturing the mouse input events
    paddle->grabMouse();

    // creating the blocks grid
    creatBlockGrid();
}

void Game::showScore()
{
    // showing the score
    QGraphicsTextItem* scoreText = new QGraphicsTextItem(QString("%1").arg(score));
    scoreText->setDefaultTextColor(Qt::red);
    scoreText->setPos(widthScene - 30, heightScene - 30);
    scoreText->setTextWidth(100);
    scene->addItem(scoreText);
}

// drawing a one column of blocks
void Game::createBlockCol(double x)
{
    for (int i = 0, n = numRows; i < n; ++i)
    {
        Block* block = new Block();
        block->setPos(x + spaceBetweenSceneAndBlock, i * spaceBetweenBlocks);
        scene->addItem(block);
    }
}

// drawing the grid of the block
void Game::creatBlockGrid()
{
    for (int i = 0, n = numColumns; i < n; ++i)
    {
        createBlockCol(i * spaceBetweenBlocks);
    }
}

// checking the game status and if false, then "game over"
void Game::checkGameStatus()
{
    if (!inGame)
    {
        gameOver();
    } 
}

void Game::checkWin()
{
    if (score == numBlocks)
    {
        showWin();
    }
}

void Game::gameOver()
{
//    // showing the "game over"
//    QMessageBox mbGameOver;


//    mbGameOver.setText("game over");
    QString scoreString = "your score is %1";
//    mbGameOver.setInformativeText(scoreString.arg(score));
//    mbGameOver.exec();

    QMessageBox::information(this, "game over", scoreString.arg(score));

    // quit the application
    QApplication::quit();


}

void Game::showWin()
{
    // showing the congrats
    QMessageBox mbWin;
    mbWin.setText("congratulations, you won!");
    mbWin.exec();

    // quit the application
    QApplication::quit();
}
