#include "DrawableGates/drawableinputgate.h"

drawableInputGate::drawableInputGate(InputGate* gate) : DrawableGate(gate)
{
}

int drawableInputGate::getInputOffsetX(int input)
{
    return -1;
}

int drawableInputGate::getInputOffsetY(int input)
{
    // no inputs on input gate
    return -1;
}

int drawableInputGate::getOutputOffsetX()
{
    return 148;
}

int drawableInputGate::getOutputOffsetY()
{
    return 41;
}

QPixmap drawableInputGate::getImage()
{
    int state = this->getGate()->getOutputState();
    if(state == 1)
    {
        return QPixmap(":/gates/inputGateOn.png").scaled(170,80);

    }else
    {
        return QPixmap(":/gates/inputGateOff.png").scaled(170,80);
    }
}

QSize drawableInputGate::getBounds()
{
    return QSize(170,80);
}

int drawableInputGate::getNumInputs()
{
    return -1;
}
