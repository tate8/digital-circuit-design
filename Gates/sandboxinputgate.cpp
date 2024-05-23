#include "Gates/sandboxinputgate.h"

SandboxInputGate::SandboxInputGate(QObject* parent, GateType type) : Gate(parent, type)
{
    inputStates[0] = false;
}

void SandboxInputGate::calculateOutput()
{
    setOutputState(inputStates[0]);
}

void SandboxInputGate::setInputPortState(int port, bool state)
{
    if(port == 0)
    {
        inputStates[0] = state;
        inputChanged();
    }
}
