#include "DrawableGates/drawableinputgate.h"
#include <QPixmap>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>

constexpr int IMAGE_HEIGHT = 60;
constexpr int PADDING = 25;
constexpr int TOTAL_PADDING = PADDING * 2;
constexpr int TOTAL_HEIGHT = IMAGE_HEIGHT + TOTAL_PADDING;


DrawableInputGate::DrawableInputGate(int gateId, bool value) : DrawableGate(gateId, value)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
}

QPointF DrawableInputGate::getInputOffset(int input) {
    Q_UNUSED(input);
    return QPointF();
}

QPointF DrawableInputGate::getOutputOffset() {
    QPixmap pixmap = QPixmap(":/gatePorts/inputOn.png");
    int width = pixmap.width() * IMAGE_HEIGHT / pixmap.height();

    return QPointF(width + PADDING, TOTAL_HEIGHT * 0.5);
}

QPixmap DrawableInputGate::getImage() {
    QPixmap map;
    if (value) {
        map = QPixmap(":/gatePorts/inputOn.png");
    } else {
         map = QPixmap(":/gatePorts/inputOff.png");
    }
    return map.scaledToHeight(IMAGE_HEIGHT, Qt::SmoothTransformation);
}

QSize DrawableInputGate::getBounds() const {
    QPixmap pixmap = QPixmap(":/gatePorts/inputOn.png");
    int width = pixmap.width() * IMAGE_HEIGHT / pixmap.height();
    return QSize(width + TOTAL_PADDING, TOTAL_HEIGHT);
}

int DrawableInputGate::getNumInputs() {
    return 0;
}


void DrawableInputGate::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    pressLocation = event->scenePos();
    DrawableGate::mousePressEvent(event);
}

void DrawableInputGate::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->scenePos() == pressLocation) {
        emit toggleInput(gateId);
    }
    DrawableGate::mouseReleaseEvent(event);
}
