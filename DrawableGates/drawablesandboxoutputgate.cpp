#include "DrawableGates/drawablesandboxoutputgate.h"
#include <QPixmap>
#include <QPointF>

constexpr int IMAGE_HEIGHT = 60;
constexpr int PADDING = 25;
constexpr int TOTAL_PADDING = PADDING * 2;
constexpr int TOTAL_HEIGHT = IMAGE_HEIGHT + TOTAL_PADDING;


DrawableSandboxOutputGate::DrawableSandboxOutputGate(int gateId, bool value) : DrawableGate(gateId, value) {}

QPointF DrawableSandboxOutputGate::getInputOffset(int input) {
    Q_UNUSED(input);
    return QPoint(PADDING + 15, (IMAGE_HEIGHT * 0.5) + PADDING);
}

QPointF DrawableSandboxOutputGate::getOutputOffset() {
    return QPointF(NAN, NAN);
}

QPixmap DrawableSandboxOutputGate::getImage() {
    QPixmap map;
    if (value) {
        map = QPixmap(":/gatePorts/lightOn.png");
    } else {
        map = QPixmap(":/gatePorts/lightOff.png");
    }
    return map.scaledToHeight(IMAGE_HEIGHT, Qt::SmoothTransformation);
}

QSize DrawableSandboxOutputGate::getBounds() const {
    QPixmap pixmap = QPixmap(":/gatePorts/lightOn.png");
    int width = pixmap.width() * IMAGE_HEIGHT / pixmap.height();
    return QSize(width + TOTAL_PADDING, TOTAL_HEIGHT);
}

int DrawableSandboxOutputGate::getNumInputs() {
    return 1;
}
