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
#include "GateTypes.h"

class CircuitCanvas : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CircuitCanvas(QWidget *parent = nullptr);
    ~CircuitCanvas();

    /// @brief Methods to add/remove drawable gates and wires
    void addDrawableGate(int gateId, bool value, GateType type);
    void removeDrawableGate(int gateId);
    void updateDrawableGate(int gateId, bool value);
    void addDrawableWire(int wireId, bool value, int startGateId, int endGateId, int port);
    void removeDrawableWire(int wireId);
    void updateDrawableWire(int wireId, bool value);

private:
    /// @brief The scene where the elements will be drawn on
    QGraphicsScene* scene;

    /// @brief Map from real gate id to drawable gate
    std::map<int, std::unique_ptr<DrawableGate>> gateMap;

    /// @brief Map from real wire id to drawable wire
    std::map<int, std::unique_ptr<DrawableWire>> wireMap;

    /// @brief The current wire being drawn
    QGraphicsLineItem* currentWire;

    /// @brief The gate id that a wire is being drawn from
    int wireStartGateId;

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
    int getGateIdAtPosition(QPointF& scenePos);

    /// @brief Listens for backspace key press to send delete signal
    void keyPressEvent(QKeyEvent* event) override;

public slots:
    /// @brief Start drawing a wire at the point
    /// @param startGate - The id of the gate drawing from
    /// @param start - The point to start drawing at
    void startDrawingWire(int startGateId, QPointF start);

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
    /// @brief Signals for a new connection between the two gates to be created
    /// @param startGateId -  The origin of the connection
    /// @param endGateId -  The destination of the connection
    /// @param inputPort - Which port to connect
    void requestedConnection(int startGateId, int endGateId, int inputPort);

    /// @brief Signals for the a gate to be deleted
    /// @param gateId - The id of the gate to be removed
    void requestedDeleteGate(int gateId);

    /// @brief Signals for the wire connected to these 2 gates to be deleted
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
