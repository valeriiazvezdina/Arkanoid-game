#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Paddle: public QGraphicsRectItem{
public:
    Paddle(QGraphicsItem* parent = NULL);

    // public methods
    double getCenterX();

    // events
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
private:
    int widthPaddle = 100;
    int heightPaddle = 20;
};

#endif // PADDLE_H
