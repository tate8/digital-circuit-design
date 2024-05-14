#include "DrawableGates/drawablenorgate.h"
#include "Gates/norgate.h"
#include <QPixmap>

DrawableNorGate::DrawableNorGate(NorGate* gate) : DrawableGate(gate)
{
}

int DrawableNorGate::getInputOffsetX(int input)
{
    return 0;
}

int DrawableNorGate::getInputOffsetY(int input)
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

int DrawableNorGate::getOutputOffsetX()
{
    return 120;
}

int DrawableNorGate::getOutputOffsetY()
{
    return 33;
}

QPixmap DrawableNorGate::getImage() {
    return QPixmap(":/gatePorts/norGatePorts.png").scaled(120, 120);
}

QSize DrawableNorGate::getBounds()
{
   return QSize(120, 65);
}

int DrawableNorGate::getNumInputs()
{
    return 2;
}
