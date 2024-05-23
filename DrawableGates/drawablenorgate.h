#ifndef DRAWABLENORGATE_H
#define DRAWABLENORGATE_H

#include "drawablegate.h"


class DrawableNorGate : public DrawableGate
{
protected:
    virtual QPointF getInputOffset(int input) override;
    virtual QPointF getOutputOffset() override;

public:
    DrawableNorGate(int gateId, bool value);
    virtual QSize getBounds() const override;
    virtual QPixmap getImage() override;
    virtual int getNumInputs() override;
};

#endif // DRAWABLENORGATE_H
