#ifndef DRAWABLEGATE_H
#define DRAWABLEGATE_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QRect>
#include <QObject>
#include "Gates/gate.h"


class DrawableGate : public QObject, public QGraphicsItem
{
    Q_OBJECT
private:

    /// @brief gate a Gate pointer to this gate
    Gate* gate;

    /// @brief If user dragging
    bool dragging;

    /// @brief If user hovering near output pin
    bool nearOutputPin;

protected:
    /// @brief Gets the offset value for the position of the specified input port
    /// @param input an int for which port to get the offset for
    /// @return an point for the offset
    virtual QPointF getInputOffset(int input) = 0;

    /// @brief Gets the offset value for the position of the specified output port
    /// @return an point for the offset
    virtual QPointF getOutputOffset() = 0;
public:
    explicit DrawableGate(Gate* gate, QGraphicsItem* parent = nullptr);

    /// @brief Gets the bounding rect
    QRectF boundingRect() const override;

    /// @brief Paints the gate
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    /// @brief Signals to draw a placeholder wire if the press was close enough
    /// Also gives focus to this element
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    /// @brief Signals to update the position of the wire placeholder
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    /// @brief Signals to stop drawing the placehodler wire and possible connect
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    /// @brief Qt method to listen to item moves
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    /// \brief setPos Sets the cucrrent positions of this gate
    /// \param x an int for the x positions
    /// \param y an int for the y position
    void setPos(int x, int y);

    /// \brief getInputPos Gets the input position of the specified port
    /// \param input an int for the ID of the port
    /// \return a QPoint object of the X,Y position of the port
    QPointF getInputPos(int input);

    /// \brief getOutputPos Gets the output position of the port
    /// \return a QPoint object of the X,Y position of the port
    QPointF getOutputPos();

    /// \brief getBounds Gets the bounds of this gate
    /// \return a QSize object with the bounds
    virtual QSize getBounds() const = 0;

    /// \brief getImage Gets the image for this gate
    /// \return a QPixmap object with the image
    virtual QPixmap getImage() = 0;

    /// \brief getNumInputs Gets how many input ports this gate has
    /// \return and int with the number of ports
    virtual int getNumInputs() = 0;

    /// @brief Gets the gate
    Gate* getGate();

public slots:
    void requestDeleteIfSelected();

signals:
    /// @brief Emitted when the user is starting to draw a wire
    /// @param startGate - The starting gate
    /// @param point - The point drawing from
    void startDrawingWire(Gate* startGate, QPointF point);

    /// @brief Emitted when the user is dragging a wire
    /// @param point - The point
    void updateDrawingWire(QPointF point);

    /// @brief Emitted when the user is ending drawing a wire
    /// @param point - The point
    void endDrawingWire(QPointF point);

    /// @brief Emitted when the position changes
    void positionChanged();

    /// @brief Emitted when user wants to delete this gate
    /// @param gateId - The real gate's id
    void deleteRequested(int gateId);
};

#endif // DRAWABLEGATE_H
