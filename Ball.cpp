#include "Ball.h"
#include <QTimer>
#include <QBrush>
#include "Game.h"
#include "Paddle.h"
#include "Block.h"

extern Game* game;

Ball::Ball(QGraphicsItem *parent): QGraphicsRectItem(parent), QObject()
{
    // drawing reсtengular ball
    setRect(0,0,50,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);

    // automatical moving down of the ball
    xVelocity = 0;
    yVelocity = -5;

    // timer for repeating the actions
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(15);
}

double Ball::getCenterX()
{
    return x() + rect().width()/2;
}

// set up the moving of the ball
void Ball::move()
{
    // if the ball is out of bounds (top, left, right), reverse the velocity
    reverseVelocity();

    // if the ball touches the bottom, end the game
    handleBottomSceneCollision();

    // if collides with paddle, reverse velocity and a little bit directions
    handlePaddleCollision();

    // handle collisions with blocks (destroy blocks and reverse ball velocity)
    handleBlockCollision();

    // set up the velocity
    moveBy(xVelocity,yVelocity);
}

// reversing the velocity of ball after collides with scene bounds
void Ball::reverseVelocity()
{
    // check if out of bound, if so, reverse the proper velocity
    double screenW = game->width();

    // left edge
    double ballLeft = mapToScene(rect().topLeft()).x();

    if (ballLeft <= 0)
    {
        xVelocity = -1 * xVelocity;
    }

    // right edge
    double ballRight = mapToScene(rect().topRight()).x();

    if (ballRight >= screenW)
    {
        xVelocity = -1 * xVelocity;
    }

    // top edge
    double ballTop = mapToScene(rect().topLeft()).y();

    if (ballTop <= 0)
    {
        yVelocity = -1 * yVelocity;
    }
}

// checking if the ball collides with the paddle
void Ball::handlePaddleCollision()
{
    // function returns a QList<QGraphicsItem *> containing pointers to all of
    // the QGraphicsItem objects that are currently colliding with the item
    QList<QGraphicsItem*> cItems = collidingItems();

    for (size_t i = 0, n = cItems.size(); i < n; ++i)
    {
        // dynamic_cast because it is a runtime cast, which provides
        // a runtime check to ensure that the conversion is valid
        Paddle* paddle = dynamic_cast<Paddle*>(cItems[i]);

        if (paddle)
        {
            // reverse the velocity to other direction
            yVelocity = -1 * yVelocity;

            double ballX = getCenterX();
            double paddleX = paddle->getCenterX();

            // changing the angle of the ball's direction
            double dvx = ballX - paddleX;
            xVelocity = (xVelocity + dvx)/15;

            return;
        }
    }
}

void Ball::handleBlockCollision()
{
    // function returns a QList<QGraphicsItem *> containing pointers to all of
    // the QGraphicsItem objects that are currently colliding with the item
    QList<QGraphicsItem*> collItems = collidingItems();

    // dynamic_cast because it is a runtime cast, which provides
    // a runtime check to ensure that the conversion is valid
    for (size_t i = 0, n = collItems.size(); i < n; ++i)
    {
        Block* block = dynamic_cast<Block*>(collItems[i]);

        // collides with block
        if (block)
        {
            // increasing the score of the game
            game->score++;

            // an angle to change the direction
            double yPad = 20;
            double xPad = 20;

            // coordinates of the ball
            double ballx = pos().x();
            double bally = pos().y();

            // coordinates of the block
            double blockx = block->pos().x();
            double blocky = block->pos().y();

            // collides with bottom
            if (bally > blocky + yPad && yVelocity < 0)
            {
                yVelocity = -1 * yVelocity;
            }

            // collides with top
            if (blocky > bally + yPad && yVelocity > 0 )
            {
                yVelocity = -1 * yVelocity;
            }

            // collides with right
            if (ballx > blockx + xPad && xVelocity < 0)
            {
                xVelocity = -1 * xVelocity;
            }

            // collides with left
            if (blockx > ballx + xPad && xVelocity > 0)
            {
                xVelocity = -1 * xVelocity;
            }

            // delete blocks
            game->scene->removeItem(block);
            delete block;
        }
        game->isWon = true;
        game->checkWin();
    }

}

// checking if the ball is not at the bottom
void Ball::handleBottomSceneCollision()
{
    double screenHeight = game->height();
    double ballHieght = mapToScene(rect().bottomLeft()).y();
    // or mapToScene(rect().topLeft()).y()

    if (ballHieght >= screenHeight)
    {
        // end the game if the ball touch the bottom of the screen
        game->inGame = false;
        game->checkGameStatus();
    }
}
