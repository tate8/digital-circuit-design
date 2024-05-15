#include "circuitcanvas.h"
#include "DrawableGates/drawableandgate.h"
#include <QMouseEvent>
#include <QPainter>

CircuitCanvas::CircuitCanvas(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    QRectF size = QRectF(0, 0, width(), height());
    scene->setSceneRect(size);
    setBackgroundBrush(Qt::white);
}

void CircuitCanvas::addDrawableGate(Gate* gate)
{
    DrawableGate* drawableGate = new DrawableAndGate(dynamic_cast<AndGate*>(gate));
    addWireDrawingConnections(drawableGate);
    scene->addItem(drawableGate);
    gateMap.insert(gate, drawableGate);
}

void CircuitCanvas::removeDrawableGate(Gate* gate)
{
    DrawableGate* drawableGate = gateMap.value(gate);
    if (drawableGate)
    {
        removeWireDrawingConnections(drawableGate);
        scene->removeItem(drawableGate);
        delete drawableGate;
        gateMap.remove(gate);
    }
}

void CircuitCanvas::updateDrawableGate(Gate* gate)
{
    DrawableGate* drawableGate = gateMap.value(gate);
    if (drawableGate)
    {
        /// TODO
    }
}

void CircuitCanvas::addDrawableWire(Wire* wire)
{
    DrawableWire* drawableWire = new DrawableWire(wire, gateMap.value(wire->startGate), gateMap.value(wire->endGate));
    scene->addItem(drawableWire);
    wireMap.insert(wire, drawableWire);
}

void CircuitCanvas::removeDrawableWire(Wire* wire)
{
    DrawableWire* drawableWire = wireMap.value(wire);
    if (drawableWire)
    {
        scene->removeItem(drawableWire);
        delete drawableWire;
        wireMap.remove(wire);
    }
}

void CircuitCanvas::updateDrawableWire(Wire* wire)
{
    DrawableWire* drawableWire = wireMap.value(wire);
    if (drawableWire)
    {
        // TODO
    }
}

DrawableGate* CircuitCanvas::getGateAtPosition(QPointF& scenePos)
{
    foreach (QGraphicsItem* item, scene->items(scenePos))
    {
        DrawableGate* gate = dynamic_cast<DrawableGate*>(item);
        if (gate)
        {
            return gate;
        }
    }
    return nullptr;
}

void CircuitCanvas::addWireDrawingConnections(DrawableGate* gate)
{
    connect(gate, &DrawableGate::startDrawingWire, this, &CircuitCanvas::startDrawingWire);
    connect(gate, &DrawableGate::updateDrawingWire, this, &CircuitCanvas::updateDrawingWire);
    connect(gate, &DrawableGate::endDrawingWire, this, &CircuitCanvas::endDrawingWire);
}

void CircuitCanvas::removeWireDrawingConnections(DrawableGate* gate)
{
    disconnect(gate, &DrawableGate::startDrawingWire, this, &CircuitCanvas::startDrawingWire);
    disconnect(gate, &DrawableGate::updateDrawingWire, this, &CircuitCanvas::updateDrawingWire);
    disconnect(gate, &DrawableGate::endDrawingWire, this, &CircuitCanvas::endDrawingWire);
}

void CircuitCanvas::startDrawingWire(Gate* startGate, QPointF startPos)
{
    // Customize pen color
    QPen pen(Qt::black);
    pen.setWidth(2);

    currentWire = new QGraphicsLineItem(QLineF(startPos, startPos));
    currentWire->setPen(pen);

    wireStartGate = startGate;

    scene->addItem(currentWire);
}

void CircuitCanvas::updateDrawingWire(QPointF newPos)
{
    if (currentWire)
    {
        currentWire->setLine(QLineF(currentWire->line().p1(), newPos));
    }
}

void CircuitCanvas::endDrawingWire(QPointF endPos)
{
    DrawableGate* endGate = getGateAtPosition(endPos);
    if (wireStartGate && endGate)
    {
        // Determine which input pin the wire is closest to on the end gate
        int closestPin = -1;
        // The maximum distance from the pin required to make a connection
        int snappingDistance = 10;
        double minDistance = std::numeric_limits<double>::max();
        int numInputs = endGate->getNumInputs();
        // Loop through all inputs and determine which one is closest
        for (int i = 0; i < numInputs; i++)
        {
            QPointF pinPos = endGate->getInputPos(i);
            double distance = QLineF(endPos, pinPos).length();
            if (distance < minDistance) {
                closestPin = i;
                minDistance = distance;
            }
        }

        if (closestPin != -1 && minDistance <= snappingDistance)
        {
            emit requestedConnection(wireStartGate, endGate->getGate(), closestPin);
        }
    }

    scene->removeItem(currentWire);
    delete currentWire;
    currentWire = nullptr;
}
