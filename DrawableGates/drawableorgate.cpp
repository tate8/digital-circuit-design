#include "DrawableGates/drawableorgate.h"
#include "Gates/orgate.h"
#include <QPixmap>

DrawableOrGate::DrawableOrGate(OrGate* gate) : DrawableGate(gate)
{
}

int DrawableOrGate::getInputOffsetX(int input)
{
    return 0;
}

int DrawableOrGate::getInputOffsetY(int input)
{
    if (input == 0)
    {
        return 13;
    } else if (input == 1)
    {
        return 52;
    }
    return 0;
}

int DrawableOrGate::getOutputOffsetX()
{
    return 120;
}

int DrawableOrGate::getOutputOffsetY()
{
    return 32;
}

QPixmap DrawableOrGate::getImage()
{
    return QPixmap(":/gatePorts/orGatePorts.png").scaled(120, 120, Qt::KeepAspectRatio);
}

QSize DrawableOrGate::getBounds()
{
    return QSize(120, 65);
}

int DrawableOrGate::getNumInputs()
{
    return 2;
}
