#include <QRect>
#include <QPixmap>
#include "DrawableGates/drawablegate.h"
#include <QPainter>
#include <QSizeF>
#include <QRectF>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QObject>
#include <QKeyEvent>

DrawableGate::DrawableGate(int gateId, bool value, QGraphicsItem* parent)
    : QObject(nullptr), QGraphicsItem(parent), gateId(gateId), value(value)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
}

QRectF DrawableGate::boundingRect() const
{
    return QRectF(0, 0, getBounds().width(), getBounds().height());
}

void DrawableGate::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPixmap pixmap = getImage();
    QSize bounds = getBounds();

    // Calculate position to draw the pixmap in the center
    int x = (bounds.width() - pixmap.width()) / 2;
    int y = (bounds.height() - pixmap.height()) / 2;

    painter->drawPixmap(x, y, pixmap);

    // Draw a box around the item if it is selected
    if (isSelected()) {
        QPen pen(Qt::lightGray, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
        pen.setDashOffset(10);
        painter->setPen(pen);
        painter->drawRect(boundingRect());
    }
}

void DrawableGate::requestDeleteIfSelected()
{
    if (isSelected()) {
        emit deleteRequested(gateId);
    }
}

void DrawableGate::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF localPos = event->pos();
    QPointF outputPos = getOutputOffset();

    // Check if click is near the output pin
    if ((localPos - outputPos).manhattanLength() < 25)
    {
        dragging = true;
        QGraphicsItem::mousePressEvent(event);
        emit startDrawingWire(gateId, mapToScene(outputPos));
    } else
    {
        QGraphicsItem::mousePressEvent(event);
    }
}

void DrawableGate::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (dragging)
    {
        emit updateDrawingWire(mapToScene(event->pos()));
    }
    else
    {
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void DrawableGate::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (dragging)
    {
        emit endDrawingWire(mapToScene(event->pos()));
        dragging = false;
    }
    else
    {
        QGraphicsItem::mouseReleaseEvent(event);
    }
}

void DrawableGate::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    setCursor(Qt::PointingHandCursor);
    QGraphicsItem::hoverEnterEvent(event);
}

void DrawableGate::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::hoverLeaveEvent(event);
}

QVariant DrawableGate::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged)
    {
        emit positionChanged();
    }
    return QGraphicsItem::itemChange(change, value);
}

QPointF DrawableGate::getInputPos(int input)
{
    return mapToScene(getInputOffset(input));
}

QPointF DrawableGate::getOutputPos()
{
    return mapToScene(getOutputOffset());
}

void DrawableGate::setValue(bool value)
{
    this->value = value;
    update();
}

int DrawableGate::getId()
{
    return gateId;
}
