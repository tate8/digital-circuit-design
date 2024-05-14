#include "DrawableGates/drawableandgate.h"
#include "Gates/andgate.h"
#include <QPixmap>

DrawableAndGate::DrawableAndGate(AndGate* gate) : DrawableGate(gate)
{
}

int DrawableAndGate::getInputOffsetX(int input)
{
    return 0;
}

int DrawableAndGate::getInputOffsetY(int input)
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

int DrawableAndGate::getOutputOffsetX()
{
    return 120;
}

int DrawableAndGate::getOutputOffsetY()
{
    return 33;
}

QPixmap DrawableAndGate::getImage()
{
    return QPixmap(":/gatePorts/andGatePorts.png").scaled(120, 120);
}

QSize DrawableAndGate::getBounds()
{
   return QSize(120, 65);
}

int DrawableAndGate::getNumInputs()
{
    return 2;
}
