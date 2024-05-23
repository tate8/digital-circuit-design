#ifndef DRAWABLENOTGATE_H
#define DRAWABLENOTGATE_H

#include "drawablegate.h"


class DrawableNotGate : public DrawableGate
{
protected:
    virtual QPointF getInputOffset(int input) override;
    virtual QPointF getOutputOffset() override;

public:
    DrawableNotGate(int gateId, bool value);
    virtual QSize getBounds() const override;
    virtual QPixmap getImage() override;
    virtual int getNumInputs() override;
};

#endif // DRAWABLEORGATE_H
