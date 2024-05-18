#ifndef DRAWABLEANDGATE_H
#define DRAWABLEANDGATE_H

#include "DrawableGates/drawablegate.h"
#include "Gates/gate.h"

class DrawableAndGate : public DrawableGate
{
protected:
    virtual QPointF getInputOffset(int input) override;
    virtual QPointF getOutputOffset() override;

public:
    DrawableAndGate(Gate* gate);
    virtual QSize getBounds() const override;
    virtual QPixmap getImage() override;
    virtual int getNumInputs() override;
};

#endif // DRAWABLEANDGATE_H
