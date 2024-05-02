#include <QRect>
#include <QPixmap>
#include "drawablegate.h"

DrawableGate::DrawableGate(Gate* gate)
{
    this->gate = gate;
}

QPoint DrawableGate::getPos()
{
    return pos;
}

void DrawableGate::setPos(int x, int y)
{
    pos = QPoint(x, y);
}

QPoint DrawableGate::getInputPos(int input)
{
    return QPoint(pos.x() + this->getInputOffsetX(input), pos.y() + this->getInputOffsetY(input));
}

QPoint DrawableGate::getOutputPos()
{
    return QPoint(pos.x() + this->getOutputOffsetX(), pos.y() + this->getOutputOffsetY());
}

Gate* DrawableGate::getGate()
{
    return gate;
}
