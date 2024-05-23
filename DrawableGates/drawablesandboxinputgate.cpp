#include "DrawableGates/drawablesandboxinputgate.h"
#include <QPixmap>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>

constexpr int IMAGE_HEIGHT = 60;
constexpr int PADDING = 25;
constexpr int TOTAL_PADDING = PADDING * 2;
constexpr int TOTAL_HEIGHT = IMAGE_HEIGHT + TOTAL_PADDING;


DrawableSandboxInputGate::DrawableSandboxInputGate(int gateId, bool value) : DrawableGate(gateId, value) {}

QPointF DrawableSandboxInputGate::getInputOffset(int input) {
    Q_UNUSED(input);
    return QPointF(NAN, NAN);
}

QPointF DrawableSandboxInputGate::getOutputOffset() {
    QPixmap pixmap = QPixmap(":/gatePorts/inputOn.png");
    int width = pixmap.width() * IMAGE_HEIGHT / pixmap.height();

    return QPointF(width + PADDING, TOTAL_HEIGHT * 0.5);
}

QPixmap DrawableSandboxInputGate::getImage() {
    QPixmap map;
    if (value) {
        map = QPixmap(":/gatePorts/inputOn.png");
    } else {
        map = QPixmap(":/gatePorts/inputOff.png");
    }
    return map.scaledToHeight(IMAGE_HEIGHT, Qt::SmoothTransformation);
}

QSize DrawableSandboxInputGate::getBounds() const {
    QPixmap pixmap = QPixmap(":/gatePorts/inputOn.png");
    int width = pixmap.width() * IMAGE_HEIGHT / pixmap.height();
    return QSize(width + TOTAL_PADDING, TOTAL_HEIGHT);
}

int DrawableSandboxInputGate::getNumInputs() {
    return 0;
}


void DrawableSandboxInputGate::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    pressLocation = event->scenePos();
    DrawableGate::mousePressEvent(event);
}

void DrawableSandboxInputGate::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->scenePos() == pressLocation) {
        emit toggleInput(gateId);
    }
    DrawableGate::mouseReleaseEvent(event);
}
