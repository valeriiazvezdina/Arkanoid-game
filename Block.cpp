#include "Block.h"
#include <QBrush>

Block::Block(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    // drawing rectengular block
    setRect(0,0,50,35);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
    setBrush(brush);
}
