#ifndef DRAWABLEWIRE_H
#define DRAWABLEWIRE_H

#include <QGraphicsItem>
#include "DrawableGates/drawablegate.h"

class DrawableWire : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit DrawableWire(int inputPort, int value, int id, DrawableGate* start, DrawableGate* end, QGraphicsItem* parent = nullptr);
    ~DrawableWire();

    /// @brief Gets the bounding rect
    QRectF boundingRect() const override;

    /// @brief Updates the start and end positions based on the wire's gates
    void updatePositions();

private:
    /// @brief Paints the wire
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    /// @brief Listens for backspace key press to send delete signal
    void keyPressEvent(QKeyEvent* event) override;

    /// @brief Focuses wire on press
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    /// @brief Change the cursor on hover
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;

    /// @brief Change the cursor on hover
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    /// @brief Updates the shape to just be a line
    QPainterPath shape() const override;

    /// @brief The input port that the real wire connects to
    int wireInputPort;

    /// @brief The value of the real wire
    int wireValue;

    /// @brief The id of the real wire
    int wireId;

    /// @brief The start gate
    DrawableGate* startGate;

    /// @brief The end gate
    DrawableGate* endGate;

    /// @brief The start point
    QPointF startPoint;

    /// @brief The end point
    QPointF endPoint;

    /// @brief If the user is hovering over the wire
    bool isHovering;

public slots:
    /// @brief Emits the deleteRequested signal
    /// Used when an action needs to delete this wire if it is selected
    void requestDeleteIfSelected();

signals:
    /// @brief Emitted when user wants to delete this wire
    /// @param wireId - The real wire's id
    void deleteRequested(int wireId);
};

#endif // DRAWABLEWIRE_H
