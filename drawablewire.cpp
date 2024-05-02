#include "drawablewire.h"

DrawableWire::DrawableWire(Gate* startGate, Gate* endGate, int inputPort, QPoint start, QPoint end):
    line(QLineF(start, end)), startGate(startGate), endGate(endGate), inputPort(inputPort) { }

Gate* DrawableWire::getStartGate() {
    return startGate;
}

Gate* DrawableWire::getEndGate() {
    return endGate;
}

QLineF DrawableWire::getLine() {
    return line;
}

int DrawableWire::getInputPort() {
    return inputPort;
}

bool DrawableWire::collision(int x, int y)
{
    QPointF point(x, y);
    QLineF intersectionLine(QPointF(x - 5, y - 5), QPointF(x + 5, y + 5));
    return (line.intersects(intersectionLine) == QLineF::BoundedIntersection);
}
