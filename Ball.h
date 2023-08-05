#ifndef BALL_H
#define BALL_H

#include <QGraphicsRectItem>

class Ball: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    // constructors
    Ball(QGraphicsItem* parent=NULL);

    int score;

    // public methods
    double getCenterX();

public slots:
    // public slots
    void move();

private:
    // private attributes
    double xVelocity;
    double yVelocity;

    // private methods
    void reverseVelocity();
    void handlePaddleCollision();
    void handleBlockCollision();
    void handleBottomSceneCollision();
};

#endif // BALL_H
