#include "DrawableGates/drawablenorgate.h"
#include <QPixmap>
#include <QPointF>

constexpr int IMAGE_HEIGHT = 60;
constexpr int PADDING = 25;
constexpr int TOTAL_PADDING = PADDING * 2;
constexpr int TOTAL_HEIGHT = IMAGE_HEIGHT + TOTAL_PADDING;


DrawableNorGate::DrawableNorGate(int gateId, bool value) : DrawableGate(gateId, value) {}

QPointF DrawableNorGate::getInputOffset(int input) {
    if (input == 0) {
        return QPoint(PADDING, (IMAGE_HEIGHT * 0.2) + PADDING);
    } else {
        return QPoint(PADDING, (IMAGE_HEIGHT * 0.8) + PADDING);
    }
}

QPointF DrawableNorGate::getOutputOffset() {
    QPixmap pixmap = QPixmap(":/gatePorts/norGatePorts.png");
    int width = pixmap.width() * IMAGE_HEIGHT / pixmap.height();

    return QPointF(width + PADDING, TOTAL_HEIGHT * 0.5);
}

QPixmap DrawableNorGate::getImage() {
    return QPixmap(":/gatePorts/norGatePorts.png").scaledToHeight(IMAGE_HEIGHT, Qt::SmoothTransformation);
}

QSize DrawableNorGate::getBounds() const {
    QPixmap pixmap = QPixmap(":/gatePorts/norGatePorts.png");
    int width = pixmap.width() * IMAGE_HEIGHT / pixmap.height();
    return QSize(width + TOTAL_PADDING, TOTAL_HEIGHT);
}

int DrawableNorGate::getNumInputs() {
    return 2;
}
