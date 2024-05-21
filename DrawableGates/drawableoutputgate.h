#ifndef DRAWABLEOUTPUTGATE_H
#define DRAWABLEOUTPUTGATE_H

#include "DrawableGates/drawablegate.h"

class DrawableOutputGate : public DrawableGate
{
protected:
protected:
    virtual QPointF getInputOffset(int input) override;
    virtual QPointF getOutputOffset() override;

public:
    DrawableOutputGate(int gateId, bool value);
    virtual QSize getBounds() const override;
    virtual QPixmap getImage() override;
    virtual int getNumInputs() override;
};
#endif // DRAWABLEOUTPUTGATE_H
