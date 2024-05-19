#include "circuitcanvas.h"
#include "DrawableGates/drawableandgate.h"
#include <QMouseEvent>
#include <QPainter>
#include "wire.h"

CircuitCanvas::CircuitCanvas(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);

    setScene(scene);

    setSceneRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX);

    QRectF size = QRectF(0, 0, width(), height());
    scene->setSceneRect(size);

    // setBackgroundBrush(Qt::white);
    setMouseTracking(true);
    setRenderHint(QPainter::Antialiasing, true);
    setDragMode(QGraphicsView::ScrollHandDrag);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

CircuitCanvas::~CircuitCanvas()
{
    for (auto it = wireMap.begin(); it != wireMap.end(); ++it)
    {
        delete it.value();
    }

    wireMap.clear();

    for (auto it = gateMap.begin(); it != gateMap.end(); ++it)
    {
        delete it.value();
    }

    gateMap.clear();
}

void CircuitCanvas::addDrawableGate(Gate* gate)
{
    DrawableGate* drawableGate = new DrawableAndGate(gate);
    addGateInteractionConnections(drawableGate);
    addWireDrawingConnections(drawableGate);
    scene->addItem(drawableGate);
    gateMap.insert(gate, drawableGate);
}

void CircuitCanvas::removeDrawableGate(Gate* gate)
{
    DrawableGate* drawableGate = gateMap.value(gate);
    if (drawableGate)
    {
        removeGateInteractionConnections(drawableGate);
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
    DrawableWire* drawableWire = new DrawableWire(wire->inputPort, wire->getValue(), wire->id, gateMap.value(wire->startGate), gateMap.value(wire->endGate));
    addWireInteractionConnections(drawableWire);
    scene->addItem(drawableWire);
    wireMap.insert(wire, drawableWire);
}

void CircuitCanvas::removeDrawableWire(Wire* wire)
{
    DrawableWire* drawableWire = wireMap.value(wire);
    if (drawableWire)
    {
        removeWireInteractionConnections(drawableWire);
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

void CircuitCanvas::addWireInteractionConnections(DrawableWire* wire)
{
    connect(this, &CircuitCanvas::deleteIfSelected, wire, &DrawableWire::requestDeleteIfSelected);
    connect(wire, &DrawableWire::deleteRequested, this, &CircuitCanvas::requestDeleteWire);
}

void CircuitCanvas::removeWireInteractionConnections(DrawableWire* wire)
{
    disconnect(this, &CircuitCanvas::deleteIfSelected, wire, &DrawableWire::requestDeleteIfSelected);
    disconnect(wire, &DrawableWire::deleteRequested, this, &CircuitCanvas::requestDeleteWire);
}

void CircuitCanvas::addGateInteractionConnections(DrawableGate* gate)
{
    connect(this, &CircuitCanvas::deleteIfSelected, gate, &DrawableGate::requestDeleteIfSelected);
    connect(gate, &DrawableGate::deleteRequested, this, &CircuitCanvas::requestDeleteGate);
}


void CircuitCanvas::removeGateInteractionConnections(DrawableGate* gate)
{
    disconnect(this, &CircuitCanvas::deleteIfSelected, gate, &DrawableGate::requestDeleteIfSelected);
    disconnect(gate, &DrawableGate::deleteRequested, this, &CircuitCanvas::requestDeleteGate);
}

void CircuitCanvas::startDrawingWire(Gate* startGate, QPointF startPos)
{
    // Customize pen color
    QPen pen(QColor(77, 166, 255));
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
        int snappingDistance = 50;
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

void CircuitCanvas::requestDeleteWire(int wireId)
{
    emit requestedDeleteWire(wireId);
}

void CircuitCanvas::requestDeleteGate(int gateId)
{
    emit requestedDeleteGate(gateId);
}

void CircuitCanvas::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete) {
        emit deleteIfSelected();
    } else {
        QGraphicsView::keyPressEvent(event);
    }
}

void CircuitCanvas::zoomToValue(double zoomValue)
{
    resetTransform();
    scale(zoomValue, zoomValue);
}
