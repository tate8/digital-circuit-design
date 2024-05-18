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

DrawableGate::DrawableGate(Gate* gate, QGraphicsItem* parent)
    : QObject(nullptr), QGraphicsItem(parent), gate(gate)
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
    painter->drawPixmap(0, 0, pixmap);

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
        emit deleteRequested(gate->id);
    }
}

void DrawableGate::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF localPos = event->pos();
    QPointF outputPos = getOutputOffset();

    // Check if click is near the output pin
    if ((localPos - outputPos).manhattanLength() < 10)
    {
        dragging = true;
        QGraphicsItem::mousePressEvent(event);
        emit startDrawingWire(getGate(), mapToScene(outputPos));
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

Gate* DrawableGate::getGate() {
    return gate;
}
