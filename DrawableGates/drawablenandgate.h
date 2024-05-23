#ifndef DRAWABLENANDGATE_H
#define DRAWABLENANDGATE_H

#include "drawablegate.h"


class DrawableNandGate : public DrawableGate
{
protected:
    virtual QPointF getInputOffset(int input) override;
    virtual QPointF getOutputOffset() override;

public:
    DrawableNandGate(int gateId, bool value);
    virtual QSize getBounds() const override;
    virtual QPixmap getImage() override;
    virtual int getNumInputs() override;
};

#endif // DRAWABLENANDGATE_H
