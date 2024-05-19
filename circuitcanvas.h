#ifndef CIRCUITCANVAS_H
#define CIRCUITCANVAS_H

#include <QWidget>
#include <QVector>
#include <QPen>
#include "DrawableGates/drawablegate.h"
#include "drawablewire.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRubberBand>
#include "wire.h"

class CircuitCanvas : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CircuitCanvas(QWidget *parent = nullptr);
    ~CircuitCanvas();

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

    /// @brief The rectangular selection area
    QRubberBand* rubberBand;

    /// @brief The start of the rectangular selection area
    QPoint origin;

    /// @brief Flag that is set if the user is dragging an item around the scene
    bool draggingItem;

    /// @brief Connects for drawing wires
    /// @param gate - The gate to connect
    void addWireDrawingConnections(DrawableGate* gate);

    /// @brief Disconnects for drawing wires
    /// @param gate - The gate to disconnect
    void removeWireDrawingConnections(DrawableGate* gate);

    /// @brief Connects for interacting with wires
    /// @param wire - The wire to connect
    void addWireInteractionConnections(DrawableWire* wire);

    /// @brief Disconnects for interacting with wires
    /// @param wire - The wire to disconnect
    void removeWireInteractionConnections(DrawableWire* wire);

    /// @brief Connects for interacting with gates
    /// @param gate - The gate to connect
    void addGateInteractionConnections(DrawableGate* gate);

    /// @brief Disconnects for interacting with gates
    /// @param gate - The gate to disconnect
    void removeGateInteractionConnections(DrawableGate* gate);

    /// @brief Gets which gate, if any is at the specified scene position
    /// @param scenePos - The position to check for gates
    DrawableGate* getGateAtPosition(QPointF& scenePos);

    /// @brief Listens for backspace key press to send delete signal
    void keyPressEvent(QKeyEvent* event) override;

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

    /// @brief Emits a request to delete the wire
    /// @param wireId - The id of the wire to delete
    void requestDeleteWire(int wireId);

    /// @brief Emits a request to delete the gate
    /// @param gateId - The id of the gate to delete
    void requestDeleteGate(int gateId);

    /// @brief Zooms the scene
    /// @param zoomValue - What the zoom value should be
    void zoomToValue(double zoomValue);

signals:
    /// @brief requestedConnection Signals for a new connection between the two gates to be created
    /// @param startGate a Gate where the connection originates
    /// @param endGate a Gate with the destination of the connection
    /// @param inputPort and int for which port to connect
    void requestedConnection(Gate* startGate, Gate* endGate, int inputPort);

    /// @brief requestedDeleteGate Signals for the a gate to be deleted
    /// @param gateId - The id of the gate to be removed
    void requestedDeleteGate(int gateId);

    /// @brief requestedDeleteWire Signals for the wire connected to these 2 gates to be deleted
    /// @param wireId - The id of the wire to delete
    void requestedDeleteWire(int wireId);

    /// @brief Emitted when a input is changed
    /// @param gateId - The id of the input gate to toggle
    void requestedToggleInput(int gateId);

    /// @brief Emitted to delete any selected items
    /// All drawable items should be listening for this
    void deleteIfSelected();

};

#endif // CIRCUITCANVAS_H
