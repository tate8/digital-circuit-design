#ifndef DRAWABLEXORGATE_H
#define DRAWABLEXORGATE_H

#include "DrawableGates/drawablegate.h"

class DrawableXorGate : public DrawableGate
{
protected:
    virtual QPointF getInputOffset(int input) override;
    virtual QPointF getOutputOffset() override;

public:
    DrawableXorGate(int gateId, bool value);
    virtual QSize getBounds() const override;
    virtual QPixmap getImage() override;
    virtual int getNumInputs() override;
};

#endif // DRAWABLEXORGATE_H
