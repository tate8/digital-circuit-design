#include "drawablesandboxoutputgate.h"
#include "sandboxoutputgate.h"

DrawableSandboxOutputGate::DrawableSandboxOutputGate(SandboxOutputGate* gate) : DrawableGate(gate)
{
}

int DrawableSandboxOutputGate::getInputOffsetX(int input)
{
    return 23;
}

int DrawableSandboxOutputGate::getInputOffsetY(int input)
{
    return 40;
}

int DrawableSandboxOutputGate::getOutputOffsetX()
{
    return 5000;
}

int DrawableSandboxOutputGate::getOutputOffsetY()
{
    return 5000;
}

QPixmap DrawableSandboxOutputGate::getImage()
{
    QMap<int,Gate*> inputs = this->getGate()->inputs;

    if(inputs.empty())
    {
        return QPixmap(":/gatePorts/lightOff.png").scaled(170,80);
    }else
    {
        int state = this->getGate()->getOutputState();
        if(state == 1)
        {
            return QPixmap(":/gatePorts/lightOn.png").scaled(170,80);

        }else
        {
            return QPixmap(":/gatePorts/lightOff.png").scaled(170,80);
        }
    }
}

QSize DrawableSandboxOutputGate::getBounds()
{
    return QSize(170,80);
}

int DrawableSandboxOutputGate::getNumInputs()
{
    return 1;
}
