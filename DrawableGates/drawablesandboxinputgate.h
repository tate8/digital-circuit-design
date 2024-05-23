#ifndef DRAWABLESANDBOXINPUTGATE_H
#define DRAWABLESANDBOXINPUTGATE_H

#include "DrawableGates/drawablegate.h"
#include <QObject>

class DrawableSandboxInputGate : public DrawableGate
{
    Q_OBJECT
private:
    /// @brief The location of the previous press
    QPointF pressLocation;

    /// @brief Stores the press location
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    /// @brief Determines if the release should toggle the gate value
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

protected:
    virtual QPointF getInputOffset(int input) override;
    virtual QPointF getOutputOffset() override;

public:
    DrawableSandboxInputGate(int gateId, bool value);
    virtual QSize getBounds() const override;
    virtual QPixmap getImage() override;
    virtual int getNumInputs() override;

signals:
    /// @brief Emitted when the user wants to toggle this input
    /// @param gateId - The id of the input gate to toggle
    void toggleInput(int gateId);
};

#endif // DRAWABLESANDBOXINPUTGATE_H
