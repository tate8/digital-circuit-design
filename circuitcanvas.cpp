#include "circuitcanvas.h"
#include "DrawableGates/drawableandgate.h"
#include "DrawableGates/drawableinputgate.h"
#include "DrawableGates/drawableoutputgate.h"
#include <QMouseEvent>
#include <QPainter>
#include "GateTypes.h"

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
    wireMap.clear();
    gateMap.clear();
}

void CircuitCanvas::addDrawableGate(int gateId, bool value, GateType type)
{
    std::unique_ptr<DrawableGate> drawableGate;

    if (type == GateType::AndGateType)
    {
        drawableGate = std::make_unique<DrawableAndGate>(gateId, value);
    }
    else if (type == GateType::InputGateType)
    {
        // Additional logic for toggling the inputs
        drawableGate = std::make_unique<DrawableInputGate>(gateId, value);
        connect(dynamic_cast<DrawableInputGate*>(drawableGate.get()), &DrawableInputGate::toggleInput, this, [this](int gateId){
            emit requestedToggleInput(gateId);
        });
    }
    else if (type == GateType::OutputGateType)
    {
        drawableGate = std::make_unique<DrawableOutputGate>(gateId, value);
    }
    else
    {
        qDebug() << "Unhandled gate type";
        return;
    }

    drawableGate.get()->setData(0, gateId);
    addGateInteractionConnections(drawableGate.get());
    addWireDrawingConnections(drawableGate.get());
    scene->addItem(drawableGate.get());
    gateMap.emplace(gateId, std::move(drawableGate));
}

void CircuitCanvas::removeDrawableGate(int gateId)
{
    assert(gateMap.find(gateId) != gateMap.end());

    std::unique_ptr<DrawableGate>& drawableGate = gateMap[gateId];

    if (drawableGate)
    {
        removeGateInteractionConnections(drawableGate.get());
        removeWireDrawingConnections(drawableGate.get());
        scene->removeItem(drawableGate.get());
        gateMap.erase(gateId);
    }
}

void CircuitCanvas::updateDrawableGate(int gateId, bool value)
{
    assert(gateMap.find(gateId) != gateMap.end());

    std::unique_ptr<DrawableGate>& drawableGate = gateMap[gateId];
    drawableGate->setValue(value);
}

void CircuitCanvas::addDrawableWire(int wireId, bool value, int startGateId, int endGateId, int port)
{
    auto drawableWire = std::make_unique<DrawableWire>(wireId, value, gateMap.at(startGateId).get(), gateMap.at(endGateId).get(), port);
    addWireInteractionConnections(drawableWire.get());
    scene->addItem(drawableWire.get());
    wireMap.emplace(wireId, std::move(drawableWire));
}

void CircuitCanvas::removeDrawableWire(int wireId)
{
     assert(wireMap.find(wireId) != wireMap.end());

    std::unique_ptr<DrawableWire>& drawableWire = wireMap[wireId];

    if (drawableWire)
    {
        removeWireInteractionConnections(drawableWire.get());
        scene->removeItem(drawableWire.get());
        wireMap.erase(wireId);
    }
}

void CircuitCanvas::updateDrawableWire(int wireId, bool value)
{
    assert(wireMap.find(wireId) != wireMap.end());

    std::unique_ptr<DrawableWire>& drawableWire = wireMap[wireId];
    drawableWire->setValue(value);
}

int CircuitCanvas::getGateIdAtPosition(QPointF& scenePos)
{
    for (QGraphicsItem* item : scene->items(scenePos))
    {
        if (!item)
            continue;  // Skip if the item is a nullptr

        QVariant data = item->data(0); // Retrieve the data stored with key 0
        if (data.isValid())
        {
            return data.toInt(); // Convert QVariant to int and return
        }
    }
    return -1;
}

void CircuitCanvas::addWireDrawingConnections(DrawableGate* gate)
{
    assert(gate);

    connect(gate, &DrawableGate::startDrawingWire, this, &CircuitCanvas::startDrawingWire);
    connect(gate, &DrawableGate::updateDrawingWire, this, &CircuitCanvas::updateDrawingWire);
    connect(gate, &DrawableGate::endDrawingWire, this, &CircuitCanvas::endDrawingWire);
}

void CircuitCanvas::removeWireDrawingConnections(DrawableGate* gate)
{
    assert(gate);

    disconnect(gate, &DrawableGate::startDrawingWire, this, &CircuitCanvas::startDrawingWire);
    disconnect(gate, &DrawableGate::updateDrawingWire, this, &CircuitCanvas::updateDrawingWire);
    disconnect(gate, &DrawableGate::endDrawingWire, this, &CircuitCanvas::endDrawingWire);
}

void CircuitCanvas::addWireInteractionConnections(DrawableWire* wire)
{
    assert(wire);

    connect(this, &CircuitCanvas::deleteIfSelected, wire, &DrawableWire::requestDeleteIfSelected);
    connect(wire, &DrawableWire::deleteRequested, this, &CircuitCanvas::requestDeleteWire);
}

void CircuitCanvas::removeWireInteractionConnections(DrawableWire* wire)
{
    assert(wire);

    disconnect(this, &CircuitCanvas::deleteIfSelected, wire, &DrawableWire::requestDeleteIfSelected);
    disconnect(wire, &DrawableWire::deleteRequested, this, &CircuitCanvas::requestDeleteWire);
}

void CircuitCanvas::addGateInteractionConnections(DrawableGate* gate)
{
    assert(gate);

    connect(this, &CircuitCanvas::deleteIfSelected, gate, &DrawableGate::requestDeleteIfSelected);
    connect(gate, &DrawableGate::deleteRequested, this, &CircuitCanvas::requestDeleteGate);
}


void CircuitCanvas::removeGateInteractionConnections(DrawableGate* gate)
{
    assert(gate);

    disconnect(this, &CircuitCanvas::deleteIfSelected, gate, &DrawableGate::requestDeleteIfSelected);
    disconnect(gate, &DrawableGate::deleteRequested, this, &CircuitCanvas::requestDeleteGate);
}

void CircuitCanvas::startDrawingWire(int startGateId, QPointF startPos)
{
    // Customize pen color
    QPen pen(Qt::gray);
    pen.setWidth(2);

    currentWire = new QGraphicsLineItem(QLineF(startPos, startPos));
    currentWire->setPen(pen);

    wireStartGateId = startGateId;

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
    int endGateId = getGateIdAtPosition(endPos);
    if (endGateId != -1)
    {
        // Determine which input pin the wire is closest to on the end gate
        int closestPin = -1;
        // The maximum distance from the pin required to make a connection
        int snappingDistance = 50;
        double minDistance = std::numeric_limits<double>::max();
        int numInputs = gateMap.at(endGateId)->getNumInputs();
        // Loop through all inputs and determine which one is closest
        for (int i = 0; i < numInputs; i++)
        {
            QPointF pinPos = gateMap.at(endGateId)->getInputPos(i);
            double distance = QLineF(endPos, pinPos).length();
            if (distance < minDistance) {
                closestPin = i;
                minDistance = distance;
            }
        }

        if (closestPin != -1 && minDistance <= snappingDistance)
        {
            emit requestedConnection(wireStartGateId, endGateId, closestPin);
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
