#ifndef CIRCUITCANVAS_H
#define CIRCUITCANVAS_H

#include <QWidget>
#include <QVector>
#include <QPen>
#include "DrawableGates/drawablegate.h"
#include "drawablewire.h"
#include <QGraphicsView>
#include <QGraphicsScene>

class CircuitCanvas : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CircuitCanvas(QWidget *parent = nullptr);

    /// @brief Methods to add/remove drawable gates and wires
    void addDrawableGate(Gate* gate);
    void removeDrawableGate(Gate* gate);
    void updateDrawableGate(Gate* gate);
    void addDrawableWire(Wire* wire);
    void removeDrawableWire(Wire* wire);
    void updateDrawableWire(Wire* wire);

private:
    /// @brief The scene where the elements will be drawn on
    QGraphicsScene* scene;

    /// @brief Map from real gate to drawable gate
    QMap<Gate*, DrawableGate*> gateMap;

    /// @brief Map from real wire to drawable wire
    QMap<Wire*, DrawableWire*> wireMap;

    /// @brief The current wire being drawn
    QGraphicsLineItem* currentWire;

    /// @brief The gate that a wire is being drawn from
    Gate* wireStartGate;

    /// @brief Connects for drawing wires
    /// @param gate - The gate to connect
    void addWireDrawingConnections(DrawableGate* gate);

    /// @brief Disconnects for drawing wires
    /// @param gate - The gate to disconnect
    void removeWireDrawingConnections(DrawableGate* gate);

    /// @brief Gets which gate, if any is at the specified scene position
    /// @param scenePos - The position to check for gates
    DrawableGate* getGateAtPosition(QPointF& scenePos);

public slots:
    /// @brief Start drawing a wire at the point
    /// @param startGate - The gate drawing from
    /// @param start - The point to start drawing at
    void startDrawingWire(Gate* startGate, QPointF start);

    /// @brief Update drawing a wire at the point
    /// @param update - The point to update drawing at
    void updateDrawingWire(QPointF update);

    /// @brief End drawing a wire at the point
    /// @param end - The point to end drawing at
    void endDrawingWire(QPointF end);

signals:
    /// @brief requestedConnection Signals for a new connection between the two gates to be created
    /// @param startGate a Gate where the connection originates
    /// @param endGate a Gate with the destination of the connection
    /// @param inputPort and int for which port to connect
    void requestedConnection(Gate* startGate, Gate* endGate, int inputPort);

    /// @brief requestedDeleteGate Signals for the a gate to be deleted
    /// @param gate the gate to be removed
    void requestedDeleteGate(Gate* gate);

    /// @brief requestedDeleteWire Signals for the wire connected to these 2 gates to be deleted
    /// @param startGate a Gate from which the wire is coming
    /// @param endGate a Gate in which the wire ends
    /// @param inputPort int the port from which the wire is originating
    void requestedDeleteWire(Gate* startGate, Gate* endGate, int inputPort);

    /// @brief Emitted when a input is changed
    /// @param changeFirstGate - If the first gate should be changed, otherwise the second
    /// @param newValue - The new value
    void requestedChangeInput(bool changeFirstGate, bool newValue);

};

#endif // CIRCUITCANVAS_H
