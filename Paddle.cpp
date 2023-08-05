#include "Paddle.h"
#include <QBrush>

// constructor
Paddle::Paddle(QGraphicsItem *parent)
{
    // drawing rectangular platrform
    setRect(0, 0, widthPaddle, heightPaddle);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBrush(brush);
}

double Paddle::getCenterX()
{
    return x()+rect().width()/2;
}

// following the mouse's x coordinate
void Paddle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    double mouseX = mapToScene(event->pos()).x();
    setPos(mouseX,y());
}
