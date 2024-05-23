#ifndef DRAWABLESANDBOXOUTPUTGATE_H
#define DRAWABLESANDBOXOUTPUTGATE_H

#include "DrawableGates/drawablegate.h"

class DrawableSandboxOutputGate : public DrawableGate
{
protected:
protected:
    virtual QPointF getInputOffset(int input) override;
    virtual QPointF getOutputOffset() override;

public:
    DrawableSandboxOutputGate(int gateId, bool value);
    virtual QSize getBounds() const override;
    virtual QPixmap getImage() override;
    virtual int getNumInputs() override;
};

#endif // DRAWABLESANDBOXOUTPUTGATE_H
