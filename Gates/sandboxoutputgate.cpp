/// CS3505 - Digital Circuit Design Game
/// Reviewed by Philippe Gonzalez

#include "Gates/sandboxoutputgate.h"

SandboxOutputGate::SandboxOutputGate(QObject* parent, GateType type) : Gate(parent, type)
{
    inputStates[0] = false;
}

void SandboxOutputGate::calculateOutput()
{
    setOutputState(inputStates[0]);
}

void SandboxOutputGate::setInputPortState(int port, bool state)
{
    if(port == 0)
    {
        inputStates[0] = state;
        inputChanged();
    }
}
