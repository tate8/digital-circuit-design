#include "drawablewire.h"
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsSceneHoverEvent>
#include <QKeyEvent>

DrawableWire::DrawableWire(Wire* wire, DrawableGate* start, DrawableGate* end, QGraphicsItem* parent)
    : QObject(nullptr), QGraphicsItem(parent), wire(wire), startGate(start), endGate(end)
{
    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);

    connect(startGate, &DrawableGate::positionChanged, this, [this](){
        updatePositions();
    });

    connect(endGate, &DrawableGate::positionChanged, this, [this](){
        updatePositions();
    });

    startPoint = startGate->getOutputPos();
    endPoint = endGate->getInputPos(wire->inputPort);

    updatePositions();
}

DrawableWire::~DrawableWire()
{
    disconnect(startGate, &DrawableGate::positionChanged, this, &DrawableWire::updatePositions);
    disconnect(endGate, &DrawableGate::positionChanged, this, &DrawableWire::updatePositions);
}

void DrawableWire::updatePositions()
{
    // Get the new start and end points, and then ask to redraw
    startPoint = startGate->getOutputPos();
    endPoint = endGate->getInputPos(wire->inputPort);
    prepareGeometryChange();
}

QRectF DrawableWire::boundingRect() const
{
    // Determing the left and right, in case line goes right to left
    double left = qMin(startPoint.x(), endPoint.x());
    double right = qMax(startPoint.x(), endPoint.x());
    double top = qMin(startPoint.y(), endPoint.y());
    double bottom = qMax(startPoint.y(), endPoint.y());

    return QRectF(left, top, right - left, bottom - top).normalized();
}

void DrawableWire::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    int wireWidth = 3;

    QPen pen (Qt::black, wireWidth);
    painter->setPen(pen);
    painter->setOpacity(1.0);

    painter->drawLine(mapFromScene(startPoint), mapFromScene(endPoint));

    if (isSelected()) {
        QPen pen(Qt::gray, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
        pen.setDashOffset(10);
        painter->setPen(pen);
        painter->drawRect(boundingRect());
    }
}

void DrawableWire::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete)
    {
        emit deleteRequested(wire->id);
    } else {
        QGraphicsItem::keyPressEvent(event);
    }
}

void DrawableWire::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    setFocus();
    QGraphicsItem::mousePressEvent(event);
}
