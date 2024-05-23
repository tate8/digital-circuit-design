#include "DrawableGates/drawablenotgate.h"
#include <QPixmap>
#include <QPointF>

constexpr int IMAGE_HEIGHT = 60;
constexpr int PADDING = 25;
constexpr int TOTAL_PADDING = PADDING * 2;
constexpr int TOTAL_HEIGHT = IMAGE_HEIGHT + TOTAL_PADDING;


DrawableNotGate::DrawableNotGate(int gateId, bool value) : DrawableGate(gateId, value) {}

QPointF DrawableNotGate::getInputOffset(int input) {
    Q_UNUSED(input);
    return QPoint(PADDING, (IMAGE_HEIGHT * 0.5) + PADDING);
}

QPointF DrawableNotGate::getOutputOffset() {
    QPixmap pixmap = QPixmap(":/gatePorts/notGatePorts.png");
    int width = pixmap.width() * IMAGE_HEIGHT / pixmap.height();

    return QPointF(width + PADDING, TOTAL_HEIGHT * 0.5);
}

QPixmap DrawableNotGate::getImage() {
    return QPixmap(":/gatePorts/notGatePorts.png").scaledToHeight(IMAGE_HEIGHT, Qt::SmoothTransformation);
}

QSize DrawableNotGate::getBounds() const {
    QPixmap pixmap = QPixmap(":/gatePorts/andGatePorts.png");
    int width = pixmap.width() * IMAGE_HEIGHT / pixmap.height();
    return QSize(width + TOTAL_PADDING, TOTAL_HEIGHT);
}

int DrawableNotGate::getNumInputs() {
    return 1;
}
