#include "DrawableGates/drawableorgate.h"
#include <QPixmap>
#include <QPointF>

constexpr int IMAGE_HEIGHT = 60;
constexpr int PADDING = 25;
constexpr int TOTAL_PADDING = PADDING * 2;
constexpr int TOTAL_HEIGHT = IMAGE_HEIGHT + TOTAL_PADDING;


DrawableOrGate::DrawableOrGate(int gateId, bool value) : DrawableGate(gateId, value) {}

QPointF DrawableOrGate::getInputOffset(int input) {
    if (input == 0) {
        return QPoint(PADDING, (IMAGE_HEIGHT * 0.2) + PADDING);
    } else {
        return QPoint(PADDING, (IMAGE_HEIGHT * 0.8) + PADDING);
    }
}

QPointF DrawableOrGate::getOutputOffset() {
    QPixmap pixmap = QPixmap(":/gatePorts/orGatePorts.png");
    int width = pixmap.width() * IMAGE_HEIGHT / pixmap.height();

    return QPointF(width + PADDING, TOTAL_HEIGHT * 0.5);
}

QPixmap DrawableOrGate::getImage() {
    return QPixmap(":/gatePorts/orGatePorts.png").scaledToHeight(IMAGE_HEIGHT, Qt::SmoothTransformation);
}

QSize DrawableOrGate::getBounds() const {
    QPixmap pixmap = QPixmap(":/gatePorts/orGatePorts.png");
    int width = pixmap.width() * IMAGE_HEIGHT / pixmap.height();
    return QSize(width + TOTAL_PADDING, TOTAL_HEIGHT);
}

int DrawableOrGate::getNumInputs() {
    return 2;
}
