#include "DrawableGates/drawableandgate.h"
#include "Gates/gate.h"
#include <QPixmap>
#include <QPointF>

constexpr int IMAGE_HEIGHT = 60;
constexpr int PADDING = 25;
constexpr int TOTAL_PADDING = PADDING * 2;
constexpr int TOTAL_HEIGHT = IMAGE_HEIGHT + TOTAL_PADDING;


DrawableAndGate::DrawableAndGate(Gate* gate) : DrawableGate(gate) {}

QPointF DrawableAndGate::getInputOffset(int input) {
    if (input == 0) {
        return QPoint(PADDING, (IMAGE_HEIGHT * 0.2) + PADDING);
    } else {
        return QPoint(PADDING, (IMAGE_HEIGHT * 0.8) + PADDING);
    }
}

QPointF DrawableAndGate::getOutputOffset() {
    QPixmap pixmap = QPixmap(":/gatePorts/andGatePorts.png");
    int width = pixmap.width() * IMAGE_HEIGHT / pixmap.height();

    return QPointF(width + PADDING, TOTAL_HEIGHT * 0.5);
}

QPixmap DrawableAndGate::getImage() {
    return QPixmap(":/gatePorts/andGatePorts.png").scaledToHeight(IMAGE_HEIGHT, Qt::SmoothTransformation);
}

QSize DrawableAndGate::getBounds() const {
    QPixmap pixmap = QPixmap(":/gatePorts/andGatePorts.png");
    int width = pixmap.width() * IMAGE_HEIGHT / pixmap.height();
    return QSize(width + TOTAL_PADDING, TOTAL_HEIGHT);
}

int DrawableAndGate::getNumInputs() {
    return 2;
}
