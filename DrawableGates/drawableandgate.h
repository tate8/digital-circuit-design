#ifndef DRAWABLEANDGATE_H
#define DRAWABLEANDGATE_H

#include "DrawableGates/drawablegate.h"
#include "Gates/andgate.h"

class DrawableAndGate : public DrawableGate
{
protected:
    QPointF getInputOffset(int input) override;
    QPointF getOutputOffset() override;

public:
    DrawableAndGate(AndGate* gate);
    virtual QSize getBounds() const override;
    virtual QPixmap getImage() override;
    virtual int getNumInputs() override;
};

#endif // DRAWABLEANDGATE_H
