#ifndef DRAWABLEORGATE_H
#define DRAWABLEORGATE_H

#include "DrawableGates/drawablegate.h"

class DrawableOrGate : public DrawableGate
{
protected:
    virtual QPointF getInputOffset(int input) override;
    virtual QPointF getOutputOffset() override;

public:
    DrawableOrGate(int gateId, bool value);
    virtual QSize getBounds() const override;
    virtual QPixmap getImage() override;
    virtual int getNumInputs() override;
};


#endif // DRAWABLEORGATE_H
