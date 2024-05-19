#include "drawablewire.h"
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsSceneHoverEvent>
#include <QKeyEvent>
#include <QCursor>

DrawableWire::DrawableWire(Wire* wire, DrawableGate* start, DrawableGate* end, QGraphicsItem* parent)
    : QObject(nullptr), QGraphicsItem(parent), wire(wire), startGate(start), endGate(end)
{
    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemIsSelectable);

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
    emit deleteRequested(wire->id);
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

    QPen pen;
    if (wire->getValue()) {
        pen = QPen(QColor(102, 204, 102), wireWidth);
    } else {
        pen = QPen(Qt::gray, wireWidth);
    }
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

QPainterPath DrawableWire::shape() const
{
    QPainterPath path;
    // Define a path that covers the area around the line with a width of 10 units
    QPainterPathStroker stroker;
    stroker.setWidth(25);
    path.moveTo(startPoint);
    path.lineTo(endPoint);
    return stroker.createStroke(path);
}

void DrawableWire::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete) {

    } else {
        QGraphicsItem::keyPressEvent(event);
    }
}

void DrawableWire::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mousePressEvent(event);
}

void DrawableWire::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    setCursor(QCursor(Qt::PointingHandCursor));
    QGraphicsItem::hoverEnterEvent(event);
}

void DrawableWire::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    setCursor(QCursor(Qt::ArrowCursor));
    QGraphicsItem::hoverLeaveEvent(event);
}

void DrawableWire::requestDeleteIfSelected()
{
    if (isSelected()) {
        emit deleteRequested(wire->id);
    }
}
