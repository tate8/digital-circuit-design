#include "DrawableGates/drawableandgate.h"
#include "Gates/gate.h"
#include <QPixmap>
#include <QPointF>

constexpr int HEIGHT = 60;

DrawableAndGate::DrawableAndGate(Gate* gate) : DrawableGate(gate) {}

QPointF DrawableAndGate::getInputOffset(int input) {
    if (input == 0) {
        return QPoint(5, HEIGHT * 0.2);
    } else {
        return QPoint(5, HEIGHT * 0.8);
    }
}

QPointF DrawableAndGate::getOutputOffset() {
    QPixmap pixmap = QPixmap(":/gatePorts/andGatePorts.png");
    int width = pixmap.width() * HEIGHT / pixmap.height();
    return QPointF(width - 5, HEIGHT * 0.5);
}

QPixmap DrawableAndGate::getImage() {
    return QPixmap(":/gatePorts/andGatePorts.png").scaledToHeight(HEIGHT, Qt::SmoothTransformation);
}

QSize DrawableAndGate::getBounds() const {
    QPixmap pixmap = QPixmap(":/gatePorts/andGatePorts.png");
    int width = pixmap.width() * HEIGHT / pixmap.height();
    return QSize(width, HEIGHT);
}

int DrawableAndGate::getNumInputs() {
    return 2;
}
