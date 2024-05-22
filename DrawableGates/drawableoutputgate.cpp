#include "DrawableGates/drawableoutputgate.h"
#include <QPixmap>
#include <QPointF>

constexpr int IMAGE_HEIGHT = 60;
constexpr int PADDING = 25;
constexpr int TOTAL_PADDING = PADDING * 2;
constexpr int TOTAL_HEIGHT = IMAGE_HEIGHT + TOTAL_PADDING;


DrawableOutputGate::DrawableOutputGate(int gateId, bool value) : DrawableGate(gateId, value) {}

QPointF DrawableOutputGate::getInputOffset(int input) {
    Q_UNUSED(input);
    return QPoint(PADDING + 15, (IMAGE_HEIGHT * 0.5) + PADDING);
}

QPointF DrawableOutputGate::getOutputOffset() {
    return QPointF();
}

QPixmap DrawableOutputGate::getImage() {
    QPixmap map;
    if (value) {
        map = QPixmap(":/gatePorts/lightOn.png");
    } else {
        map = QPixmap(":/gatePorts/lightOff.png");
    }
    return map.scaledToHeight(IMAGE_HEIGHT, Qt::SmoothTransformation);
}

QSize DrawableOutputGate::getBounds() const {
    QPixmap pixmap = QPixmap(":/gatePorts/lightOn.png");
    int width = pixmap.width() * IMAGE_HEIGHT / pixmap.height();
    return QSize(width + TOTAL_PADDING, TOTAL_HEIGHT);
}

int DrawableOutputGate::getNumInputs() {
    return 1;
}
