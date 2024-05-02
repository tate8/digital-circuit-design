/// CS3505 - Digital Circuit Design Game
/// Reviewed by Philippe Gonzalez

#include "norgate.h"

NorGate::NorGate(QObject* parent, GateType type) : Gate(parent, type)
{
    inputStates[0] = false;
    inputStates[1] = false;
}

void NorGate::calculateOutput()
{
    setOutputState(!(inputStates[0] || inputStates[1]));
}

void NorGate::setInputPortState(int port, bool state)
{
    if (port >= 0 && port < 2)
    {
        inputStates[port] = state;
        inputChanged();
    }
}
